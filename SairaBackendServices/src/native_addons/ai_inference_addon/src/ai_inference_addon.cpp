#include <napi.h>
#include <map>
#include <string>
#include <iostream>
#include <vector>

// Global Napi::FunctionReference to node-llama-cpp's getLlama function
Napi::FunctionReference getLlamaRef;
// Global Napi::FunctionReference to smart-whisper's getWhisper function
Napi::FunctionReference getWhisperRef;

// Base class for models in the registry
class BaseModel {
public:
    virtual ~BaseModel() = default;
    Napi::ObjectReference jsObjectRef; // Reference to the JavaScript object (e.g., Llama, Whisper)
};

class LlamaModel : public BaseModel {
public:
    LlamaModel(Napi::Object jsLlamaObject) {
        jsObjectRef = Napi::Persistent(jsLlamaObject);
    }
    ~LlamaModel() {
        jsObjectRef.Reset(); // Release the reference
    }
};

class WhisperModel : public BaseModel {
public:
    WhisperModel(Napi::Object jsWhisperObject) {
        jsObjectRef = Napi::Persistent(jsWhisperObject);
    }
    ~WhisperModel() {
        jsObjectRef.Reset(); // Release the reference
    }
};

// Model registry
std::map<std::string, BaseModel*> modelRegistry;

Napi::Value LoadModel(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 2 || !info[0].IsString() || !info[1].IsString()) {
        Napi::TypeError::New(env, "Expected two string arguments: type and path").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    std::string type = info[0].As<Napi::String>().Utf8Value();
    std::string path = info[1].As<Napi::String>().Utf8Value();

    std::cout << "Attempting to load model: " << type << " from " << path << std::endl; // Basic logging

    if (modelRegistry.count(type)) {
        Napi::Error::New(env, "Model of type '" + type + "' is already loaded.").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    if (type == "llama") {
        if (getLlamaRef.IsEmpty()) {
            Napi::Error::New(env, "node-llama-cpp getLlama function not initialized. Pass it during addon initialization.").ThrowAsJavaScriptException();
            return env.Undefined();
        }
        // Call getLlama() from JS
        Napi::Object llamaInstance = getLlamaRef.Call({}).As<Napi::Object>();
        Napi::Function loadModelFn = llamaInstance.Get("loadModel").As<Napi::Function>();
        // Call loadModel on the Llama instance
        loadModelFn.Call(llamaInstance, {Napi::String::New(env, path)});
        modelRegistry[type] = new LlamaModel(llamaInstance);
        std::cout << "Llama model loaded successfully." << std::endl;
    } else if (type == "whisper") {
        if (getWhisperRef.IsEmpty()) {
            Napi::Error::New(env, "smart-whisper getWhisper function not initialized. Pass it during addon initialization.").ThrowAsJavaScriptException();
            return env.Undefined();
        }
        // Call getWhisper() from JS to get the Whisper constructor
        Napi::Function whisperConstructor = getWhisperRef.Call({}).As<Napi::Function>();
        // Instantiate Whisper model
        Napi::Object whisperInstance = whisperConstructor.New({Napi::String::New(env, path)});
        modelRegistry[type] = new WhisperModel(whisperInstance);
        std::cout << "Whisper model loaded successfully." << std::endl;
    } else {
        Napi::TypeError::New(env, "Unknown model type: " + type).ThrowAsJavaScriptException();
        return env.Undefined();
    }

    return env.Undefined();
}

Napi::Value UnloadModel(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "Expected one string argument: type").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    std::string type = info[0].As<Napi::String>().Utf8Value();

    std::cout << "Attempting to unload model: " << type << std::endl; // Basic logging

    if (!modelRegistry.count(type)) {
        Napi::Error::New(env, "Model of type '" + type + "' is not loaded.").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    BaseModel* model = modelRegistry[type];
    if (type == "llama") {
        // For node-llama-cpp, there isn't a direct 'unload' method on the Llama instance
        // The model is typically managed by the Llama instance itself. We just need to delete our C++ wrapper.
        std::cout << "Llama model unloaded (C++ wrapper removed)." << std::endl;
    } else if (type == "whisper") {
        // Call .free() on the JavaScript Whisper object
        Napi::Object whisperInstance = model->jsObjectRef.Value().As<Napi::Object>();
        Napi::Function freeFn = whisperInstance.Get("free").As<Napi::Function>();
        freeFn.Call(whisperInstance, {});
        std::cout << "Whisper model unloaded (JS .free() called)." << std::endl;
    }
    delete model;
    modelRegistry.erase(type);

    return env.Undefined();
}

Napi::Value LlmGenerate(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "Expected at least one string argument: prompt").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    std::string prompt = info[0].As<Napi::String>().Utf8Value();
    Napi::Object options = info.Length() > 1 && info[1].IsObject() ? info[1].As<Napi::Object>() : env.Undefined().As<Napi::Object>();

    if (!modelRegistry.count("llama")) {
        Napi::Error::New(env, "Llama model is not loaded. Call loadModel('llama', ...) first.").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    LlamaModel* llamaModel = static_cast<LlamaModel*>(modelRegistry["llama"]);
    Napi::Object llamaInstance = llamaModel->jsObjectRef.Value().As<Napi::Object>();

    Napi::Object session = llamaInstance.Get("session").As<Napi::Object>();
    Napi::Function promptFn = session.Get("prompt").As<Napi::Function>();

    Napi::Value jsPrompt = Napi::String::New(env, prompt);
    Napi::Value jsOptions = options.IsEmpty() ? env.Undefined() : options;

    // Call the JavaScript prompt function and return its result (which is a Promise)
    return promptFn.Call(session, {jsPrompt, jsOptions});
}

Napi::Value CreateEmbedding(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "Expected one string argument: text").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    std::string text = info[0].As<Napi::String>().Utf8Value();

    if (!modelRegistry.count("llama")) {
        Napi::Error::New(env, "Llama model is not loaded. Call loadModel('llama', ...) first.").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    LlamaModel* llamaModel = static_cast<LlamaModel*>(modelRegistry["llama"]);
    Napi::Object llamaInstance = llamaModel->jsObjectRef.Value().As<Napi::Object>();

    Napi::Function embedFn = llamaInstance.Get("embed").As<Napi::Function>();

    Napi::Value jsText = Napi::String::New(env, text);

    // Call the JavaScript embed function and return its result (which is a Promise)
    return embedFn.Call(llamaInstance, {jsText});
}

Napi::Value AsrTranscribe(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsBuffer()) {
        Napi::TypeError::New(env, "Expected at least one argument: audioBuffer (Buffer)").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    // Directly cast to Napi::Object, as Napi::Buffer is a type of Napi::Object
    Napi::Object audioBuffer = info[0].As<Napi::Object>();

    if (!modelRegistry.count("whisper")) {
        Napi::Error::New(env, "Whisper model is not loaded. Call loadModel('whisper', ...) first.").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    WhisperModel* whisperModel = static_cast<WhisperModel*>(modelRegistry["whisper"]);
    Napi::Object whisperInstance = whisperModel->jsObjectRef.Value().As<Napi::Object>();

    Napi::Function transcribeFn = whisperInstance.Get("transcribe").As<Napi::Function>();

    Napi::Value jsAudioBuffer = audioBuffer;
    Napi::Value jsOptions = info.Length() > 1 && info[1].IsObject() ? info[1].As<Napi::Object>() : env.Undefined();

    // Call the JavaScript transcribe function and return its result (which is a Promise)
    return transcribeFn.Call(whisperInstance, {jsAudioBuffer, jsOptions});
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // This is where the JavaScript side will pass the getLlama function
    exports.Set(Napi::String::New(env, "initLlama"), Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        Napi::Env env = info.Env();
        if (info.Length() < 1 || !info[0].IsFunction()) {
            Napi::TypeError::New(env, "Expected a function argument: getLlama function").ThrowAsJavaScriptException();
            return env.Undefined();
        }
        getLlamaRef = Napi::Persistent(info[0].As<Napi::Function>());
        return env.Undefined();
    }));

    // This is where the JavaScript side will pass the getWhisper function (constructor)
    exports.Set(Napi::String::New(env, "initWhisper"), Napi::Function::New(env, [](const Napi::CallbackInfo& info) {
        Napi::Env env = info.Env();
        if (info.Length() < 1 || !info[0].IsFunction()) {
            Napi::TypeError::New(env, "Expected a function argument: getWhisper function (constructor)").ThrowAsJavaScriptException();
            return env.Undefined();
        }
        getWhisperRef = Napi::Persistent(info[0].As<Napi::Function>());
        return env.Undefined();
    }));

    exports.Set(Napi::String::New(env, "loadModel"), Napi::Function::New(env, LoadModel));
    exports.Set(Napi::String::New(env, "unloadModel"), Napi::Function::New(env, UnloadModel));
    exports.Set(Napi::String::New(env, "llmGenerate"), Napi::Function::New(env, LlmGenerate));
    exports.Set(Napi::String::New(env, "createEmbedding"), Napi::Function::New(env, CreateEmbedding));
    exports.Set(Napi::String::New(env, "asrTranscribe"), Napi::Function::New(env, AsrTranscribe));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)