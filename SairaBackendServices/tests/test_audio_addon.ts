import { sayHelloFromAddon } from '../src/node_services/audio_processor.js';

/**
 * Test script to verify the native addon integration
 */
async function testAudioAddon() {
  try {
    const message = sayHelloFromAddon();
    console.log('Message from native addon:', message);
    
    if (message === 'Hello from audio_io_addon!') {
      console.log('✅ Test passed!');
      process.exit(0);
    } else {
      console.error('❌ Test failed: Unexpected message from addon');
      process.exit(1);
    }
  } catch (error) {
    console.error('❌ Test failed with error:', error);
    process.exit(1);
  }
}

// Run the test
testAudioAddon();
