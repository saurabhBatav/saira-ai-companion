#include <napi.h>
#include <AudioToolbox/AudioToolbox.h>
#include <CoreAudio/CoreAudio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Forward declarations
OSStatus AudioInputCallback(void *inRefCon,
                          AudioUnitRenderActionFlags *ioActionFlags,
                          const AudioTimeStamp *inTimeStamp,
                          UInt32 inBusNumber,
                          UInt32 inNumberFrames,
                          AudioBufferList *ioData);

// Audio capture state structure
struct AudioCaptureState {
    AudioComponentInstance audioUnit{nullptr};
    Napi::ThreadSafeFunction tsfn;
    bool isRunning{false};
    int sampleRate{44100};
    int channels{1};
    std::string deviceId;
    
    ~AudioCaptureState() {
        if (audioUnit) {
            AudioOutputUnitStop(audioUnit);
            AudioUnitUninitialize(audioUnit);
            AudioComponentInstanceDispose(audioUnit);
        }
    }
};

// Global state
struct AudioState {
    std::unique_ptr<AudioCaptureState> captureState;
};

// Create a new audio capture instance
Napi::Value StartCapture(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    // Create a new capture state
    auto state = std::make_unique<AudioCaptureState>();
    
    try {
        // Validate arguments
        if (info.Length() < 1 || !info[0].IsObject()) {
            throw std::runtime_error("Options object expected");
        }
        
        Napi::Object options = info[0].As<Napi::Object>();
        
        // Get sample rate (default to 44100)
        state->sampleRate = options.Has("sampleRate") ? options.Get("sampleRate").As<Napi::Number>().Int32Value() : 44100;
        
        // Get channel count (default to 1 for mono)
        state->channels = options.Has("channels") ? options.Get("channels").As<Napi::Number>().Uint32Value() : 1;
        
        // Get device ID if provided
        if (options.Has("deviceId") && options.Get("deviceId").IsString()) {
            state->deviceId = options.Get("deviceId").As<Napi::String>().Utf8Value();
        }
        
        // Get the callback function
        if (info.Length() < 2 || !info[1].IsFunction()) {
            throw std::runtime_error("Callback function expected");
        }
        
        // Create a ThreadSafeFunction
        state->tsfn = Napi::ThreadSafeFunction::New(
            env,
            info[1].As<Napi::Function>(),
            "Audio Capture Callback",
            0,  // Unlimited queue
            1,  // Initial thread count
            [](Napi::Env) {}  // Finalizer (no-op, cleanup is handled by the state destructor)
        );
        
        // Set up audio unit
        AudioComponentDescription desc;
        desc.componentType = kAudioUnitType_Output;
        desc.componentSubType = kAudioUnitSubType_HALOutput; // Use HAL for direct hardware access
        desc.componentManufacturer = kAudioUnitManufacturer_Apple;
        desc.componentFlags = 0;
        desc.componentFlagsMask = 0;
        
        // Find the audio component
        AudioComponent comp = AudioComponentFindNext(NULL, &desc);
        if (!comp) {
            throw std::runtime_error("Couldn't find audio component");
        }
        
        // Create the audio unit
        OSStatus status = AudioComponentInstanceNew(comp, &state->audioUnit);
        if (status != noErr) {
            throw std::runtime_error("Couldn't create audio unit");
        }
        
        // Enable input
        UInt32 flag = 1;
        status = AudioUnitSetProperty(state->audioUnit,
                                    kAudioOutputUnitProperty_EnableIO,
                                    kAudioUnitScope_Input,
                                    1, // Input bus
                                    &flag,
                                    sizeof(flag));
        if (status != noErr) {
            throw std::runtime_error("Couldn't enable input");
        }
        
        // Disable output
        flag = 0;
        status = AudioUnitSetProperty(state->audioUnit,
                                    kAudioOutputUnitProperty_EnableIO,
                                    kAudioUnitScope_Output,
                                    0, // Output bus
                                    &flag,
                                    sizeof(flag));
        if (status != noErr) {
            throw std::runtime_error("Couldn't disable output");
        }
        
        // Set format
        AudioStreamBasicDescription streamFormat;
        streamFormat.mSampleRate = state->sampleRate;
        streamFormat.mFormatID = kAudioFormatLinearPCM;
        streamFormat.mFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagIsPacked;
        streamFormat.mFramesPerPacket = 1;
        streamFormat.mChannelsPerFrame = state->channels;
        streamFormat.mBitsPerChannel = 32;
        streamFormat.mBytesPerPacket = state->channels * sizeof(Float32);
        streamFormat.mBytesPerFrame = state->channels * sizeof(Float32);
        
        status = AudioUnitSetProperty(state->audioUnit,
                                    kAudioUnitProperty_StreamFormat,
                                    kAudioUnitScope_Output,
                                    1, // Input bus
                                    &streamFormat,
                                    sizeof(streamFormat));
        if (status != noErr) {
            throw std::runtime_error("Couldn't set stream format");
        }
        
        // Set up the render callback
        AURenderCallbackStruct callback;
        callback.inputProc = AudioInputCallback;
        callback.inputProcRefCon = state.get();
        
        status = AudioUnitSetProperty(state->audioUnit,
                                    kAudioOutputUnitProperty_SetInputCallback,
                                    kAudioUnitScope_Global,
                                    1, // Input bus
                                    &callback,
                                    sizeof(callback));
        if (status != noErr) {
            throw std::runtime_error("Couldn't set input callback");
        }
        
        // Initialize the audio unit
        status = AudioUnitInitialize(state->audioUnit);
        if (status != noErr) {
            throw std::runtime_error("Couldn't initialize audio unit");
        }
        
        // Start the audio unit
        status = AudioOutputUnitStart(state->audioUnit);
        if (status != noErr) {
            throw std::runtime_error("Couldn't start audio unit");
        }
        
        state->isRunning = true;
        
        // Return the state as an external value
        return Napi::External<AudioCaptureState>::New(
            env,
            state.release(),
            [](Napi::Env env, AudioCaptureState* s) {
                delete s;
            }
        );
        
    } catch (const std::exception& e) {
        // Clean up on error
        if (state) {
            if (state->audioUnit) {
                AudioOutputUnitStop(state->audioUnit);
                AudioUnitUninitialize(state->audioUnit);
                AudioComponentInstanceDispose(state->audioUnit);
            }
        }
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
} // End of StartCapture function

// Audio input callback function
OSStatus AudioInputCallback(void *inRefCon,
                          AudioUnitRenderActionFlags *ioActionFlags,
                          const AudioTimeStamp *inTimeStamp,
                          UInt32 inBusNumber,
                          UInt32 inNumberFrames,
                          AudioBufferList *ioData) {
    AudioCaptureState *state = static_cast<AudioCaptureState*>(inRefCon);
    if (!state || !state->tsfn) {
        return noErr;
    }
    
    // Create a buffer to hold the audio data
    AudioBufferList bufferList;
    bufferList.mNumberBuffers = 1;
    bufferList.mBuffers[0].mDataByteSize = inNumberFrames * state->channels * sizeof(Float32);
    bufferList.mBuffers[0].mNumberChannels = state->channels;
    bufferList.mBuffers[0].mData = malloc(bufferList.mBuffers[0].mDataByteSize);
    
    // Render the audio
    OSStatus status = AudioUnitRender(state->audioUnit,
                                    ioActionFlags,
                                    inTimeStamp,
                                    inBusNumber,
                                    inNumberFrames,
                                    &bufferList);
    
    if (status == noErr) {
        // Create a copy of the audio data
        size_t dataSize = bufferList.mBuffers[0].mDataByteSize;
        auto *audioData = new std::vector<uint8_t>(dataSize);
        memcpy(audioData->data(), bufferList.mBuffers[0].mData, dataSize);
        
        // Send the audio data to Node.js
        state->tsfn.NonBlockingCall(
            audioData,
            [](Napi::Env env, Napi::Function jsCallback, std::vector<uint8_t>* data) {
                // Create an ArrayBuffer that owns the data
                Napi::ArrayBuffer buffer = Napi::ArrayBuffer::New(
                    env,
                    data->data(),
                    data->size(),
                    [](Napi::Env, void* /*data*/, std::vector<uint8_t>* vec) {
                        delete vec;
                    },
                    data
                );
                
                // Call the JavaScript callback with the buffer
                jsCallback.Call({ buffer });
            }
        );
    }
    
    // Clean up
    free(bufferList.mBuffers[0].mData);
    
    return noErr;
}

// Stop audio capture
Napi::Value StopCapture(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    if (info.Length() < 1 || !info[0].IsExternal()) {
        Napi::TypeError::New(env, "Audio capture instance expected").ThrowAsJavaScriptException();
        return env.Null();
    }
    
    Napi::External<AudioCaptureState> external = info[0].As<Napi::External<AudioCaptureState>>();
    AudioCaptureState* state = external.Data();
    
    if (state) {
        // The actual cleanup will happen when the external is garbage collected
        // or when the finalizer runs
        return Napi::Boolean::New(env, true);
    }
    
    return Napi::Boolean::New(env, false);
}

// Module initialization
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("startCapture", Napi::Function::New(env, StartCapture));
    exports.Set("stopCapture", Napi::Function::New(env, StopCapture));
    return exports;
}

NODE_API_MODULE(audio_io_addon, Init)