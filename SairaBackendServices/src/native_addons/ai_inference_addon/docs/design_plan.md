# AI Inference Addon Design Plan

This document outlines the design for the `ai_inference_addon`, a C++ native Node.js addon that wraps `node-llama-cpp` for LLM generation and embeddings, and `smart-whisper` for ASR transcription.

## A. Model Registry

A central model registry manages the lifecycle of loaded LLM and ASR models.

- **Data Structure:** A `std::map<std::string, BaseModel*>` stores model instances, keyed by model type (e.g., "llama", "whisper"). `BaseModel` is a base class for `LlamaModel` and `WhisperModel`, each holding a `Napi::ObjectReference` to their respective JavaScript instances.
- **Purpose:**
    - Track currently loaded models to prevent duplicate loading.
    - Ensure proper cleanup (unloading) of models when no longer needed.
    - Provide a centralized access point for model instances.
- **Thread Safety:** Access to the model registry is protected by Node.js's single-threaded event loop for N-API calls. Direct access to the map is only within N-API callbacks, which are executed on the main thread.

## B. API Signatures via N-API

The addon exposes the following unified API to Node.js via N-API:

- `initLlama(getLlamaFn: Function): void`: Initializes the addon with `node-llama-cpp`'s `getLlama` function.
- `initWhisper(WhisperConstructor: Function): void`: Initializes the addon with `smart-whisper`'s `Whisper` constructor.
- `loadModel(type: string, path: string): void`: Loads a specified model (LLM or ASR) from the given path.
    - `type`: "llama" or "whisper".
    - `path`: Absolute path to the model file.
- `unloadModel(type: string): void`: Unloads the specified model.
    - `type`: "llama" or "whisper".
- `llmGenerate(prompt: string, options?: object): Promise<string>`: Generates text using the loaded LLM.
    - `prompt`: The input prompt for text generation.
    - `options`: Optional parameters for generation (e.g., `maxTokens`, `temperature`).
- `createEmbedding(text: string): Promise<Float32Array>`: Creates an embedding for the given text using the loaded LLM.
    - `text`: The input text for embedding.
- `asrTranscribe(audioBuffer: Buffer, options?: object): Promise<string>`: Transcribes audio using the loaded ASR model.
    - `audioBuffer`: Node.js `Buffer` containing audio data.
    - `options`: Optional parameters for transcription (e.g., `language`, `beamSize`).

All asynchronous operations return Node.js Promises, which are directly propagated from the underlying JavaScript libraries.

## C. Integration Strategy

- **`node-llama-cpp` Integration:**
    - The `initLlama` function receives `node-llama-cpp`'s `getLlama` function, which is stored as a `Napi::FunctionReference`.
    - `loadModel("llama", ...)` calls the stored `getLlama` function to obtain the `Llama` instance, then calls its `loadModel` method.
    - `llmGenerate` calls `llamaInstance.session.prompt()` and directly returns the resulting JavaScript Promise.
    - `createEmbedding` calls `llamaInstance.embed()` and directly returns the resulting JavaScript Promise.
- **`smart-whisper` Integration:**
    - The `initWhisper` function receives `smart-whisper`'s `Whisper` constructor, which is stored as a `Napi::FunctionReference`.
    - `loadModel("whisper", ...)` calls the stored `Whisper` constructor using `whisperConstructor.New()` to create a `Whisper` instance.
    - `unloadModel("whisper")` calls `whisperInstance.free()` to release resources.
    - `asrTranscribe` calls `whisperInstance.transcribe()` and directly returns the resulting JavaScript Promise.
- **N-API Bindings:** Each API function has a corresponding C++ N-API binding that handles argument parsing, calls the underlying JavaScript library functions, and returns their results (including Promises) directly to Node.js.

## D. Concurrency & Thread Safety

- The addon operates entirely on the Node.js main thread for N-API calls. All long-running operations (LLM generation, embedding, ASR transcription) are delegated to the underlying `node-llama-cpp` and `smart-whisper` JavaScript libraries, which handle their own asynchronous execution and threading (often offloading to native threads internally).
- The C++ addon does not introduce its own thread pools or asynchronous workers for these operations, simplifying the design and relying on the established concurrency models of the integrated libraries.
- Resource management (e.g., `Napi::Persistent` for `Napi::ObjectReference`) ensures that JavaScript objects are not garbage collected while still referenced by C++.

## E. Profiling & Logging

- **Structured Logging:** Basic `std::cout` statements are used for logging model loading/unloading. For more detailed profiling and structured logging, integration with a Node.js logging library (e.g., Winston) would be required on the JavaScript side, as the C++ addon primarily acts as a pass-through.
- **Key Metrics:** The addon itself does not directly capture performance metrics. These would be gathered by profiling the JavaScript calls to the addon and the underlying libraries.

## F. Error Handling

- **Robust Error Propagation:** Errors from underlying JavaScript libraries (`node-llama-cpp`, `smart-whisper`) are caught by the JavaScript engine and propagated as Promise rejections to the calling JavaScript code, as the C++ addon directly returns these Promises.
- **Input Validation:** Strict validation of input parameters (e.g., `type`, `path`, `prompt`, `audioBuffer`) is performed at the N-API boundary, throwing `Napi::TypeError` or `Napi::Error` exceptions for invalid arguments or when models are not loaded.

## G. Build System

- **Node-GYP:** `binding.gyp` is used as the primary build system for the C++ addon. This integrates with `node-gyp` for cross-platform compilation.
- **Dependency Management:** The addon relies on `node-llama-cpp` and `smart-whisper` being installed as npm dependencies in the parent project. The C++ code interacts with their JavaScript APIs, avoiding direct linking to their native components.

---
