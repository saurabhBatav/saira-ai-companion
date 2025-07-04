const assert = require('assert');
const path = require('path');

// Adjust the path to load the native addon correctly
const addon = require(path.join(__dirname, '../native/build/Release/ai_inference_addon.node'));

async function runTests() {
    console.log('Running tests for loadModel and unloadModel...');

    // Test 1: Load a Llama model (placeholder)
    try {
        console.log('Attempting to load llama model...');
        addon.loadModel('llama', '/path/to/your/llama/model.bin');
        console.log('Llama model load initiated (placeholder).');
    } catch (error) {
        console.error('Error loading llama model:', error.message);
        assert.fail('Test 1 failed: Could not load llama model.');
    }

    // Test 2: Attempt to load an already loaded Llama model
    try {
        console.log('Attempting to load llama model again (should fail)...');
        addon.loadModel('llama', '/path/to/another/llama/model.bin');
        assert.fail('Test 2 failed: Loaded llama model again, but it should have thrown an error.');
    } catch (error) {
        console.log('Caught expected error:', error.message);
        assert.ok(error.message.includes('already loaded'), 'Test 2 failed: Error message did not indicate model already loaded.');
    }

    // Test 3: Load a Whisper model (placeholder)
    try {
        console.log('Attempting to load whisper model...');
        addon.loadModel('whisper', '/path/to/your/whisper/model.bin');
        console.log('Whisper model load initiated (placeholder).');
    } catch (error) {
        console.error('Error loading whisper model:', error.message);
        assert.fail('Test 3 failed: Could not load whisper model.');
    }

    // Test 4: Unload Llama model
    try {
        console.log('Attempting to unload llama model...');
        addon.unloadModel('llama');
        console.log('Llama model unloaded.');
    } catch (error) {
        console.error('Error unloading llama model:', error.message);
        assert.fail('Test 4 failed: Could not unload llama model.');
    }

    // Test 5: Attempt to unload an already unloaded Llama model
    try {
        console.log('Attempting to unload llama model again (should fail)...');
        addon.unloadModel('llama');
        assert.fail('Test 5 failed: Unloaded llama model again, but it should have thrown an error.');
    } catch (error) {
        console.log('Caught expected error:', error.message);
        assert.ok(error.message.includes('not loaded'), 'Test 5 failed: Error message did not indicate model not loaded.');
    }

    // Test 6: Unload Whisper model
    try {
        console.log('Attempting to unload whisper model...');
        addon.unloadModel('whisper');
        console.log('Whisper model unloaded.');
    } catch (error) {
        console.error('Error unloading whisper model:', error.message);
        assert.fail('Test 6 failed: Could not unload whisper model.');
    }

    console.log('\nAll tests passed!');
}

runTests().catch(err => {
    console.error('An unexpected error occurred during tests:', err);
    process.exit(1);
});
