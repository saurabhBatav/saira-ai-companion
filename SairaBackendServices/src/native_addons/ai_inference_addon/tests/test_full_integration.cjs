const assert = require('assert');
const path = require('path');

const addon = require(path.join(__dirname, '../native/build/Release/ai_inference_addon.node'));

// Mock node-llama-cpp getLlama function and Llama instance
const mockLlama = {
    loadModel: (modelPath) => {
        console.log(`Mock Llama: Loading model from ${modelPath}`);
        return Promise.resolve();
    },
    session: {
        prompt: (promptText, options) => {
            console.log(`Mock Llama: Generating for prompt: "${promptText}" with options:`, options);
            return Promise.resolve(`Mock generated text for: ${promptText}`);
        }
    },
    embed: (text) => {
        console.log(`Mock Llama: Embedding text: "${text}"`);
        return Promise.resolve(new Float32Array([0.1, 0.2, 0.3, 0.4]));
    }
};

function getMockLlama() {
    return mockLlama;
}

// Mock smart-whisper Whisper constructor and instance
class MockWhisper {
    constructor(modelPath) {
        console.log(`Mock Whisper: Initializing with model from ${modelPath}`);
        this.modelPath = modelPath;
    }

    transcribe(audioBuffer, options) {
        console.log(`Mock Whisper: Transcribing audio buffer of length ${audioBuffer.length} with options:`, options);
        return Promise.resolve(`Mock transcription for audio from ${this.modelPath}`);
    }

    free() {
        console.log(`Mock Whisper: Freeing resources for model ${this.modelPath}`);
        return Promise.resolve();
    }
}

function getMockWhisper() {
    return MockWhisper;
}

async function runTests() {
    console.log('Running full integration test...');

    // 1. Initialize the addon with mock functions
    console.log('Initializing addon with mock Llama and Whisper...');
    addon.initLlama(getMockLlama);
    addon.initWhisper(getMockWhisper);

    // 2. Load Llama and Whisper models
    console.log('Loading Llama model...');
    await addon.loadModel('llama', '/path/to/your/llama/model.bin');
    console.log('Loading Whisper model...');
    await addon.loadModel('whisper', '/path/to/your/whisper/model.bin');

    // 3. Transcribe sample audio
    console.log('Transcribing sample audio...');
    const audioBuffer = Buffer.from([1, 2, 3, 4, 5]);
    const transcription = await addon.asrTranscribe(audioBuffer, { language: 'en' });
    console.log('Transcription Result:', transcription);
    assert.ok(transcription.includes('Mock transcription'), 'Test failed: ASR transcription incorrect.');

    // 4. Generate text from prompt
    console.log('Generating text from prompt...');
    const generatedText = await addon.llmGenerate('Tell me a story about a cat.', { maxTokens: 50 });
    console.log('Generated Text Result:', generatedText);
    assert.ok(generatedText.includes('Mock generated text'), 'Test failed: LLM generation incorrect.');

    // 5. Embed a phrase
    console.log('Creating embedding for a phrase...');
    const embedding = await addon.createEmbedding('Hello, world!');
    console.log('Embedding Result:', embedding);
    assert.ok(embedding instanceof Float32Array, 'Test failed: Embedding is not Float32Array.');
    assert.strictEqual(embedding.length, 4, 'Test failed: Embedding length incorrect.');

    // 6. Unload both models
    console.log('Unloading Llama model...');
    await addon.unloadModel('llama');
    console.log('Unloading Whisper model...');
    await addon.unloadModel('whisper');

    console.log('\nFull integration test passed successfully!');
}

runTests().catch(err => {
    console.error('An unexpected error occurred during full integration test:', err);
    process.exit(1);
});
