const path = require('path');

// Load the native addon
const addon = require(path.join(__dirname, '../native/build/Release/ai_inference_addon.node'));

// --- Setup for node-llama-cpp ---
// This is a simplified setup. In a real application, you'd manage model paths and instances more robustly.
let llamaInstance;
function getLlama() {
    if (!llamaInstance) {
        // This is a placeholder. In a real scenario, you'd load your actual model.
        // For example: llamaInstance = new Llama(new LlamaModel({ modelPath: "/path/to/your/model.gguf" }));
        // For this example, we'll create a mock that behaves like a Llama instance.
        console.log("Creating mock Llama instance for example.");
        llamaInstance = {
            loadModel: (modelPath) => {
                console.log(`[Mock Llama] Loading model from: ${modelPath}`);
                return Promise.resolve();
            },
            session: {
                prompt: (promptText, options) => {
                    console.log(`[Mock Llama] Generating for: "${promptText}" with options:`, options);
                    return Promise.resolve(`Mock LLM response to: ${promptText}`);
                }
            },
            embed: (text) => {
                console.log(`[Mock Llama] Embedding text: "${text}"`);
                return Promise.resolve(new Float32Array([0.1, 0.2, 0.3, 0.4, 0.5]));
            }
        };
    }
    return llamaInstance;
}

// --- Setup for smart-whisper ---
let whisperInstance;
class MockWhisper {
    constructor(modelPath) {
        console.log(`[Mock Whisper] Initializing with model: ${modelPath}`);
        this.modelPath = modelPath;
    }

    transcribe(audioBuffer, options) {
        console.log(`[Mock Whisper] Transcribing audio (length: ${audioBuffer.length}) with options:`, options);
        return Promise.resolve(`Mock ASR transcription for audio from ${this.modelPath}`);
    }

    free() {
        console.log(`[Mock Whisper] Freeing resources for model: ${this.modelPath}`);
        return Promise.resolve();
    }
}

function getWhisperConstructor() {
    // In a real scenario, you would return the actual Whisper class:
    // return Whisper;
    console.log("Returning Mock Whisper constructor for example.");
    return MockWhisper;
}

(async function runExample() {
    console.log("\n--- Running AI Inference Addon Example ---");

    try {
        // 1. Initialize the addon with the actual (or mock) library functions
        console.log("Initializing addon...");
        addon.initLlama(getLlama);
        addon.initWhisper(getWhisperConstructor);

        // 2. Load models
        console.log("\nLoading Llama model...");
        await addon.loadModel('llama', '/path/to/your/llama-model.gguf');
        console.log("Llama model loaded.");

        console.log("\nLoading Whisper model...");
        await addon.loadModel('whisper', '/path/to/your/whisper-model.bin');
        console.log("Whisper model loaded.");

        // 3. Perform LLM Generation
        console.log("\nPerforming LLM generation...");
        const llmResponse = await addon.llmGenerate("What is the capital of France?", { maxTokens: 20 });
        console.log("LLM Response:", llmResponse);

        // 4. Create Embedding
        console.log("\nCreating embedding...");
        const embedding = await addon.createEmbedding("Hello, world!");
        console.log("Embedding:", embedding);

        // 5. Perform ASR Transcription
        console.log("\nPerforming ASR transcription...");
        // Create a dummy audio buffer (e.g., 16-bit mono PCM, 16kHz sample rate)
        const dummyAudioBuffer = Buffer.alloc(16000 * 2 * 5); // 5 seconds of 16kHz 16-bit mono audio
        const transcription = await addon.asrTranscribe(dummyAudioBuffer, { language: 'en' });
        console.log("ASR Transcription:", transcription);

        // 6. Unload models
        console.log("\nUnloading Llama model...");
        await addon.unloadModel('llama');
        console.log("Llama model unloaded.");

        console.log("\nUnloading Whisper model...");
        await addon.unloadModel('whisper');
        console.log("Whisper model unloaded.");

        console.log("\n--- AI Inference Addon Example Completed Successfully ---");

    } catch (error) {
        console.error("\n--- AI Inference Addon Example Failed ---");
        console.error("Error:", error);
    }
})();