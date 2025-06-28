#include <napi.h>
#include <AudioUnit/AudioUnit.h>
#include <AudioToolbox/AudioToolbox.h>
#include <CoreAudio/CoreAudio.h>
#include <CoreFoundation/CFString.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include <cstring>
#include <sstream>
#include <map>

// Forward declarations
OSStatus AudioInputCallback(void *inRefCon,
                          AudioUnitRenderActionFlags *ioActionFlags,
                          const AudioTimeStamp *inTimeStamp,
                          UInt32 inBusNumber,
                          UInt32 inNumberFrames,
                          AudioBufferList *ioData);

// Forward declaration for the audio playback callback
static OSStatus AudioPlaybackCallback(void *inRefCon,
                                    AudioUnitRenderActionFlags *ioActionFlags,
                                    const AudioTimeStamp *inTimeStamp,
                                    UInt32 inBusNumber,
                                    UInt32 inNumberFrames,
                                    AudioBufferList *ioData);

// Device info structure
struct AudioDeviceInfo {
    std::string id;
    std::string name;
    bool isInput;
    bool isDefault;
};

// Forward declaration for device enumeration
std::vector<AudioDeviceInfo> EnumerateAudioDevices();

// Audio playback state structure
struct AudioPlaybackState {
    AudioComponentInstance audioUnit{nullptr};
    std::vector<int16_t> audioBuffer;
    size_t position{0};
    std::mutex bufferMutex;
    std::condition_variable bufferCV;
    bool isPlaying{false};
    
    ~AudioPlaybackState() {
        stop();
    }
    
    void stop() {
        std::unique_lock<std::mutex> lock(bufferMutex);
        if (!isPlaying) return;
        
        isPlaying = false;
        audioBuffer.clear();
        position = 0;
        bufferCV.notify_all();
        
        if (audioUnit) {
            AudioOutputUnitStop(audioUnit);
            AudioUnitUninitialize(audioUnit);
            AudioComponentInstanceDispose(audioUnit);
            audioUnit = nullptr;
        }
    }
    
    OSStatus render(AudioUnitRenderActionFlags *ioActionFlags,
                   const AudioTimeStamp *inTimeStamp,
                   UInt32 inBusNumber,
                   UInt32 inNumberFrames,
                   AudioBufferList *ioData) {
        std::unique_lock<std::mutex> lock(bufferMutex);
        
        if (!isPlaying || position >= audioBuffer.size()) {
            // Fill with silence if no more data
            for (UInt32 i = 0; i < ioData->mNumberBuffers; i++) {
                memset(ioData->mBuffers[i].mData, 0, ioData->mBuffers[i].mDataByteSize);
            }
            return noErr;
        }
        
        // Copy audio data to output buffer
        int16_t *outBuffer = static_cast<int16_t*>(ioData->mBuffers[0].mData);
        size_t framesToCopy = std::min(static_cast<size_t>(inNumberFrames), 
                                     (audioBuffer.size() - position) / ioData->mNumberBuffers);
        
        for (UInt32 i = 0; i < framesToCopy; i++) {
            for (UInt32 ch = 0; ch < ioData->mNumberBuffers; ch++) {
                outBuffer[i * ioData->mNumberBuffers + ch] = audioBuffer[position++];
            }
        }
        
        // Fill the rest with silence if needed
        for (UInt32 i = framesToCopy; i < inNumberFrames; i++) {
            for (UInt32 ch = 0; ch < ioData->mNumberBuffers; ch++) {
                outBuffer[i * ioData->mNumberBuffers + ch] = 0;
            }
        }
        
        return noErr;
    }
    
    bool playAudio(const std::vector<int16_t>& buffer) {
        std::unique_lock<std::mutex> lock(bufferMutex);
        
        if (buffer.empty()) {
            return false;
        }
        
        // Copy the audio data
        audioBuffer = buffer;
        position = 0;
        
        // If not already playing, set up the audio unit
        if (!isPlaying) {
            // Configure audio format
            AudioComponentDescription desc;
            desc.componentType = kAudioUnitType_Output;
            desc.componentSubType = kAudioUnitSubType_DefaultOutput;
            desc.componentManufacturer = kAudioUnitManufacturer_Apple;
            desc.componentFlags = 0;
            desc.componentFlagsMask = 0;
            
            // Get default output component
            AudioComponent comp = AudioComponentFindNext(nullptr, &desc);
            if (!comp) {
                std::cerr << "Error finding audio component" << std::endl;
                return false;
            }
            
            // Create audio unit
            OSStatus err = AudioComponentInstanceNew(comp, &audioUnit);
            if (err != noErr) {
                std::cerr << "Error creating audio unit: " << err << std::endl;
                return false;
            }
            
            // Set up audio format (16-bit PCM)
            AudioStreamBasicDescription audioFormat;
            audioFormat.mSampleRate = 16000;  // 16kHz
            audioFormat.mFormatID = kAudioFormatLinearPCM;
            audioFormat.mFormatFlags = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
            audioFormat.mFramesPerPacket = 1;
            audioFormat.mChannelsPerFrame = 1;  // Mono
            audioFormat.mBitsPerChannel = 16;
            audioFormat.mBytesPerFrame = audioFormat.mChannelsPerFrame * (audioFormat.mBitsPerChannel / 8);
            audioFormat.mBytesPerPacket = audioFormat.mFramesPerPacket * audioFormat.mBytesPerFrame;
            audioFormat.mReserved = 0;
            
            // Apply format
            err = AudioUnitSetProperty(audioUnit,
                                     kAudioUnitProperty_StreamFormat,
                                     kAudioUnitScope_Input,
                                     0,
                                     &audioFormat,
                                     sizeof(audioFormat));
            if (err != noErr) {
                std::cerr << "Error setting audio format: " << err << std::endl;
                return false;
            }
            
            // Set up render callback
            AURenderCallbackStruct callbackInfo;
            callbackInfo.inputProc = &AudioPlaybackCallback;
            callbackInfo.inputProcRefCon = this;
            
            err = AudioUnitSetProperty(audioUnit,
                                     kAudioUnitProperty_SetRenderCallback,
                                     kAudioUnitScope_Input,
                                     0,
                                     &callbackInfo,
                                     sizeof(callbackInfo));
            if (err != noErr) {
                std::cerr << "Error setting render callback: " << err << std::endl;
                return false;
            }
            
            // Initialize audio unit
            err = AudioUnitInitialize(audioUnit);
            if (err != noErr) {
                std::cerr << "Error initializing audio unit: " << err << std::endl;
                return false;
            }
            
            isPlaying = true;
            
            // Start playback
            err = AudioOutputUnitStart(audioUnit);
            if (err != noErr) {
                std::cerr << "Error starting audio unit: " << err << std::endl;
                return false;
            }
        }
        
        return true;
    }
};

// Audio playback callback function
static OSStatus AudioPlaybackCallback(void *inRefCon,
                                    AudioUnitRenderActionFlags *ioActionFlags,
                                    const AudioTimeStamp *inTimeStamp,
                                    UInt32 inBusNumber,
                                    UInt32 inNumberFrames,
                                    AudioBufferList *ioData) {
    AudioPlaybackState* state = static_cast<AudioPlaybackState*>(inRefCon);
    if (state) {
        return state->render(ioActionFlags, inTimeStamp, inBusNumber, inNumberFrames, ioData);
    }
    return noErr;
}

// Audio capture state structure
struct AudioCaptureState {
    AudioComponentInstance audioUnit{nullptr};
    Napi::ThreadSafeFunction tsfn;
    std::atomic<bool> isRunning{false};
    std::mutex mutex;
    std::unique_ptr<AudioPlaybackState> playbackState;
    
    ~AudioCaptureState() {
        stop();
    }
    
    void stop() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!isRunning) return;
        
        // Stop the audio unit first
        if (audioUnit) {
            AudioOutputUnitStop(audioUnit);
            AudioUnitUninitialize(audioUnit);
            AudioComponentInstanceDispose(audioUnit);
            audioUnit = nullptr;
        }
        
        // Release the ThreadSafeFunction
        if (tsfn) {
            auto status = tsfn.Release();
            if (status != napi_ok) {
                std::cerr << "Error releasing ThreadSafeFunction" << std::endl;
            }
        }
        
        isRunning = false;
    }
    
    bool playAudio(const std::vector<int16_t>& buffer) {
        if (!playbackState) {
            playbackState = std::make_unique<AudioPlaybackState>();
            
            // Configure audio format
            AudioComponentDescription desc;
            desc.componentType = kAudioUnitType_Output;
            desc.componentSubType = kAudioUnitSubType_DefaultOutput;
            desc.componentManufacturer = kAudioUnitManufacturer_Apple;
            desc.componentFlags = 0;
            desc.componentFlagsMask = 0;
            
            // Get default output component
            AudioComponent comp = AudioComponentFindNext(nullptr, &desc);
            if (!comp) {
                std::cerr << "Error finding audio component" << std::endl;
                return false;
            }
            
            // Create audio unit
            OSStatus err = AudioComponentInstanceNew(comp, &playbackState->audioUnit);
            if (err != noErr) {
                std::cerr << "Error creating audio unit: " << err << std::endl;
                return false;
            }
            
            // Set up audio format (16-bit PCM)
            AudioStreamBasicDescription audioFormat;
            audioFormat.mSampleRate = 16000;  // 16kHz
            audioFormat.mFormatID = kAudioFormatLinearPCM;
            audioFormat.mFormatFlags = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
            audioFormat.mFramesPerPacket = 1;
            audioFormat.mChannelsPerFrame = 1;  // Mono
            audioFormat.mBitsPerChannel = 16;
            audioFormat.mBytesPerFrame = audioFormat.mChannelsPerFrame * (audioFormat.mBitsPerChannel / 8);
            audioFormat.mBytesPerPacket = audioFormat.mFramesPerPacket * audioFormat.mBytesPerFrame;
            audioFormat.mReserved = 0;
            
            // Apply format
            err = AudioUnitSetProperty(playbackState->audioUnit,
                                     kAudioUnitProperty_StreamFormat,
                                     kAudioUnitScope_Input,
                                     0,
                                     &audioFormat,
                                     sizeof(audioFormat));
            if (err != noErr) {
                std::cerr << "Error setting audio format: " << err << std::endl;
                return false;
            }
            
            // Set up render callback
            AURenderCallbackStruct callbackInfo;
            callbackInfo.inputProc = &AudioPlaybackCallback;
            callbackInfo.inputProcRefCon = this;
            
            err = AudioUnitSetProperty(playbackState->audioUnit,
                                     kAudioUnitProperty_SetRenderCallback,
                                     kAudioUnitScope_Input,
                                     0,
                                     &callbackInfo,
                                     sizeof(callbackInfo));
            if (err != noErr) {
                std::cerr << "Error setting render callback: " << err << std::endl;
                return false;
            }
            
            // Initialize audio unit
            err = AudioUnitInitialize(playbackState->audioUnit);
            if (err != noErr) {
                std::cerr << "Error initializing audio unit: " << err << std::endl;
                return false;
            }
            
            playbackState->isPlaying = true;
            
            // Start playback
            err = AudioOutputUnitStart(playbackState->audioUnit);
            if (err != noErr) {
                std::cerr << "Error starting audio unit: " << err << std::endl;
                return false;
            }
        }
        
        // Copy audio data
        {
            std::unique_lock<std::mutex> lock(playbackState->bufferMutex);
            playbackState->audioBuffer = buffer;
            playbackState->position = 0;
        }
        
        return true;
    }
    
    static OSStatus AudioPlaybackCallback(void *inRefCon,
                                        AudioUnitRenderActionFlags *ioActionFlags,
                                        const AudioTimeStamp *inTimeStamp,
                                        UInt32 inBusNumber,
                                        UInt32 inNumberFrames,
                                        AudioBufferList *ioData) {
        AudioCaptureState* state = static_cast<AudioCaptureState*>(inRefCon);
        if (state && state->playbackState) {
            return state->playbackState->render(ioActionFlags, inTimeStamp, inBusNumber, inNumberFrames, ioData);
        }
        return noErr;
    }
    
    int sampleRate{44100};
    int channels{1};
    std::string deviceId;
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
    
    if (!state) {
        return Napi::Boolean::New(env, false);
    }
    
    try {
        // Stop the capture and clean up resources
        state->stop();
        return Napi::Boolean::New(env, true);
    } catch (const std::exception& e) {
        Napi::Error::New(env, std::string("Error stopping audio capture: ") + e.what())
            .ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    } catch (...) {
        Napi::Error::New(env, "Unknown error stopping audio capture")
            .ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }
}
Napi::Value PlayAudio(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    try {
        // We expect the audio buffer as the first argument
        if (info.Length() < 2 || !info[1].IsTypedArray()) {
            Napi::TypeError::New(env, "Audio buffer (Int16Array) expected as second argument").ThrowAsJavaScriptException();
            return env.Null();
        }
        
        // Get the audio buffer (second argument)
        Napi::TypedArray buffer = info[1].As<Napi::TypedArray>();
        
        // Verify it's an Int16Array
        if (buffer.TypedArrayType() != napi_typedarray_type::napi_int16_array) {
            Napi::TypeError::New(env, "Expected Int16Array for audio data").ThrowAsJavaScriptException();
            return env.Null();
        }
        
        // Create a new playback state if needed
        static AudioPlaybackState* playbackState = new AudioPlaybackState();
        
        // Copy the audio data to a vector
        size_t sampleCount = buffer.ElementLength();
        std::vector<int16_t> audioData(sampleCount);
        
        // Get the raw data from the TypedArray
        void* data = buffer.ArrayBuffer().Data();
        if (!data) {
            Napi::Error::New(env, "Failed to get audio data from buffer").ThrowAsJavaScriptException();
            return env.Null();
        }
        
        // Copy the data
        memcpy(audioData.data(), data, sampleCount * sizeof(int16_t));
        
        // Play the audio
        bool success = playbackState->playAudio(audioData);
        
        return Napi::Boolean::New(env, success);
    } catch (const std::exception& e) {
        Napi::Error::New(env, std::string("Error playing audio: ") + e.what())
            .ThrowAsJavaScriptException();
        return env.Null();
    } catch (...) {
        Napi::Error::New(env, "Unknown error playing audio")
            .ThrowAsJavaScriptException();
        return env.Null();
    }
}

// Module initialization
// Helper function to convert CFString to std::string
static std::string CFStringToStdString(CFStringRef cfStr) {
    if (!cfStr) return "";
    
    CFIndex length = CFStringGetLength(cfStr);
    CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8) + 1;
    std::string buffer(maxSize, 0);
    
    if (CFStringGetCString(cfStr, &buffer[0], maxSize, kCFStringEncodingUTF8)) {
        buffer.resize(strlen(buffer.c_str()));
        return buffer;
    }
    
    return "";
}

// Implementation of device enumeration
std::vector<AudioDeviceInfo> EnumerateAudioDevices() {
    std::vector<AudioDeviceInfo> devices;
    
    // Get default input and output device IDs
    AudioDeviceID defaultInputDeviceID = kAudioObjectUnknown;
    AudioDeviceID defaultOutputDeviceID = kAudioObjectUnknown;
    
    UInt32 defaultInputSize = sizeof(AudioDeviceID);
    AudioObjectPropertyAddress defaultInputAddress = {
        kAudioHardwarePropertyDefaultInputDevice,
        kAudioObjectPropertyScopeGlobal,
        kAudioObjectPropertyElementMain
    };
    
    UInt32 defaultOutputSize = sizeof(AudioDeviceID);
    AudioObjectPropertyAddress defaultOutputAddress = {
        kAudioHardwarePropertyDefaultOutputDevice,
        kAudioObjectPropertyScopeGlobal,
        kAudioObjectPropertyElementMain
    };
    
    AudioObjectGetPropertyData(kAudioObjectSystemObject, &defaultInputAddress, 0, NULL, &defaultInputSize, &defaultInputDeviceID);
    AudioObjectGetPropertyData(kAudioObjectSystemObject, &defaultOutputAddress, 0, NULL, &defaultOutputSize, &defaultOutputDeviceID);
    
    // Get all audio devices
    AudioObjectPropertyAddress propertyAddress = {
        kAudioHardwarePropertyDevices,
        kAudioObjectPropertyScopeGlobal,
        kAudioObjectPropertyElementMain
    };
    
    UInt32 dataSize = 0;
    OSStatus status = AudioObjectGetPropertyDataSize(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &dataSize);
    if (status != noErr || dataSize == 0) {
        return devices;
    }
    
    UInt32 deviceCount = dataSize / sizeof(AudioDeviceID);
    std::vector<AudioDeviceID> deviceIDs(deviceCount);
    
    status = AudioObjectGetPropertyData(kAudioObjectSystemObject, &propertyAddress, 0, NULL, &dataSize, deviceIDs.data());
    if (status != noErr) {
        return devices;
    }
    
    // Enumerate each device
    for (const auto& deviceID : deviceIDs) {
        // Skip invalid devices
        if (deviceID == kAudioObjectUnknown) continue;
        
        // Get device name
        CFStringRef deviceName = NULL;
        UInt32 nameSize = sizeof(CFStringRef);
        propertyAddress.mSelector = kAudioObjectPropertyName;
        propertyAddress.mScope = kAudioObjectPropertyScopeGlobal;
        
        status = AudioObjectGetPropertyData(deviceID, &propertyAddress, 0, NULL, &nameSize, &deviceName);
        if (status != noErr || !deviceName) continue;
        
        std::string name = CFStringToStdString(deviceName);
        CFRelease(deviceName);
        
        // Get device UID (used as a stable identifier)
        CFStringRef deviceUID = NULL;
        UInt32 uidSize = sizeof(CFStringRef);
        propertyAddress.mSelector = kAudioDevicePropertyDeviceUID;
        
        status = AudioObjectGetPropertyData(deviceID, &propertyAddress, 0, NULL, &uidSize, &deviceUID);
        if (status != noErr || !deviceUID) continue;
        
        std::string uid = CFStringToStdString(deviceUID);
        CFRelease(deviceUID);
        
        // Check input channels
        bool hasInput = false;
        propertyAddress.mSelector = kAudioDevicePropertyStreams;
        propertyAddress.mScope = kAudioObjectPropertyScopeInput;
        
        status = AudioObjectGetPropertyDataSize(deviceID, &propertyAddress, 0, NULL, &dataSize);
        if (status == noErr && dataSize > 0) {
            hasInput = true;
            
            // Add input device
            AudioDeviceInfo inputDevice;
            inputDevice.id = "input:" + uid;
            inputDevice.name = name + " (Input)";
            inputDevice.isInput = true;
            inputDevice.isDefault = (deviceID == defaultInputDeviceID);
            devices.push_back(inputDevice);
        }
        
        // Check output channels
        bool hasOutput = false;
        propertyAddress.mScope = kAudioObjectPropertyScopeOutput;
        
        status = AudioObjectGetPropertyDataSize(deviceID, &propertyAddress, 0, NULL, &dataSize);
        if (status == noErr && dataSize > 0) {
            hasOutput = true;
            
            // Add output device
            AudioDeviceInfo outputDevice;
            outputDevice.id = "output:" + uid;
            outputDevice.name = name + (hasInput ? " (Output)" : "");
            outputDevice.isInput = false;
            outputDevice.isDefault = (deviceID == defaultOutputDeviceID);
            devices.push_back(outputDevice);
        }
    }
    
    return devices;
}

// N-API binding for getDevices
Napi::Value GetDevices(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    
    try {
        auto devices = EnumerateAudioDevices();
        Napi::Array result = Napi::Array::New(env, devices.size());
        
        for (size_t i = 0; i < devices.size(); i++) {
            const auto& device = devices[i];
            Napi::Object deviceObj = Napi::Object::New(env);
            
            deviceObj.Set("id", device.id);
            deviceObj.Set("name", device.name);
            deviceObj.Set("type", device.isInput ? "input" : "output");
            deviceObj.Set("isDefault", device.isDefault);
            
            result[i] = deviceObj;
        }
        
        return result;
    } catch (const std::exception& e) {
        Napi::Error::New(env, std::string("Error enumerating audio devices: ") + e.what())
            .ThrowAsJavaScriptException();
        return env.Null();
    } catch (...) {
        Napi::Error::New(env, "Unknown error enumerating audio devices")
            .ThrowAsJavaScriptException();
        return env.Null();
    }
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("startCapture", Napi::Function::New(env, StartCapture));
    exports.Set("stopCapture", Napi::Function::New(env, StopCapture));
    exports.Set("playAudio", Napi::Function::New(env, PlayAudio));
    exports.Set("getDevices", Napi::Function::New(env, GetDevices));
    return exports;
}

NODE_API_MODULE(audio_io_addon, Init)