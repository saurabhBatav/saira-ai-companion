const assert = require('assert');
const path = require('path');

const addon = require(path.join(__dirname, '../native/build/Release/ai_inference_addon.node'));

// Mock node-llama-cpp getLlama function and Llama instance
const mockLlama = {
    loadModel: (modelPath) => {
        // console.log(`Mock Llama: Loading model from ${modelPath}`);
        return Promise.resolve();
    },
    session: {
        prompt: (promptText, options) => {
            // console.log(`Mock Llama: Generating for prompt: "${promptText}"`);
            return new Promise(resolve => {
                setTimeout(() => resolve(`Mock generated text for: ${promptText}`), 10);
            });
        }
    },
    embed: (text) => {
        // console.log(`Mock Llama: Embedding text: "${text}"`);
        return new Promise(resolve => {
            setTimeout(() => resolve(new Float32Array([0.1, 0.2, 0.3, 0.4])), 5);
        });
    }
};

function getMockLlama() {
    return mockLlama;
}

// Mock smart-whisper Whisper constructor and instance
class MockWhisper {
    constructor(modelPath) {
        // console.log(`Mock Whisper: Initializing with model from ${modelPath}`);
        this.modelPath = modelPath;
    }

    transcribe(audioBuffer, options) {
        // console.log(`Mock Whisper: Transcribing audio buffer of length ${audioBuffer.length}`);
        return new Promise(resolve => {
            setTimeout(() => resolve(`Mock transcription for audio from ${this.modelPath}`), 15);
        });
    }

    free() {
        // console.log(`Mock Whisper: Freeing resources for model ${this.modelPath}`);
        return Promise.resolve();
    }
}

function getMockWhisper() {
    return MockWhisper;
}

async function runTests() {
    console.log('Running stress and concurrency tests...');

    // Initialize the addon with mock functions
    addon.initLlama(getMockLlama);
    addon.initWhisper(getMockWhisper);

    // Load mock models
    await addon.loadModel('llama', '/path/to/mock/llama.gguf');
    await addon.loadModel('whisper', '/path/to/mock/whisper.bin');

    const numCalls = 100;
    const promises = [];

    console.log(`Initiating ${numCalls} concurrent LLM generation and ASR transcription calls...`);

    for (let i = 0; i < numCalls; i++) {
        promises.push(addon.llmGenerate(`Prompt ${i}`));
        promises.push(addon.createEmbedding(`Text ${i}`));
        promises.push(addon.asrTranscribe(Buffer.from([i, i + 1, i + 2])));
    }

    try {
        const results = await Promise.all(promises);
        console.log(`All ${results.length} concurrent calls completed.`);

        // Basic verification of results
        results.forEach(result => {
            assert.ok(result !== undefined && result !== null, 'Result should not be undefined or null.');
            if (typeof result === 'string') {
                assert.ok(result.includes('Mock generated text') || result.includes('Mock transcription'), 'String result is not as expected.');
            } else if (result instanceof Float32Array) {
                assert.strictEqual(result.length, 4, 'Embedding length is incorrect.');
            }
        });
        console.log('All results verified.');

    } catch (error) {
        console.error('Error during concurrent calls:', error.message);
        assert.fail('Stress and concurrency test failed unexpectedly.');
    }

    // Unload models
    await addon.unloadModel('llama');
    await addon.unloadModel('whisper');

    console.log('\nStress and concurrency tests passed!');
}

runTests().catch(err => {
    console.error('An unexpected error occurred during tests:', err);
    process.exit(1);
});