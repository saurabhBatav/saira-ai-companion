# Changelog

## [Unreleased]

### Added
- Initial N-API bindings for `loadModel` and `unloadModel`.
- Basic model registry for tracking loaded models.
- Placeholder C++ implementation for model loading/unloading.
- `binding.gyp` for native addon compilation.
- JavaScript test file (`test_load_unload.cjs`) for `loadModel` and `unloadModel`.
- N-API bindings for `llmGenerate` and `createEmbedding`.
- Integration with `node-llama-cpp`'s JavaScript API for LLM functions.
- JavaScript test file (`test_llm_functions.cjs`) for `llmGenerate` and `createEmbedding`.
- N-API binding for `asrTranscribe`.
- Integration with `smart-whisper`'s JavaScript API for ASR transcription.
- JavaScript test file (`test_asr_functions.cjs`) for `asrTranscribe`.
- JavaScript test file (`test_concurrency.cjs`) for stress and concurrency testing of LLM and ASR functions.
- JavaScript test file (`test_full_integration.cjs`) for comprehensive integration testing of all addon functionalities.
- Example usage file (`examples/example.cjs`) demonstrating the addon's API.
