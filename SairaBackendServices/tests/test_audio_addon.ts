import { startCapture, stopAllCaptures } from '../src/node_services/audio_processor.js';

/**
 * Test script to verify audio capture functionality
 */
async function testAudioCapture() {
  console.log('Starting audio capture test...');
  
  try {
    // Start capturing audio
    const stopCapture = startCapture(
      {
        sampleRate: 44100,
        channels: 1
      },
      (buffer) => {
        // This callback will be called with audio data
        console.log(`Received audio buffer of size: ${buffer.byteLength} bytes`);
      }
    );
    
    console.log('Audio capture started. Capturing for 5 seconds...');
    
    // Stop capture after 5 seconds
    setTimeout(() => {
      console.log('Stopping audio capture...');
      stopCapture();
      console.log('✅ Audio capture test completed successfully');
      process.exit(0);
    }, 5000);
    
    // Handle process termination
    process.on('SIGINT', () => {
      console.log('\nStopping capture due to interrupt...');
      stopCapture();
      process.exit(0);
    });
    
  } catch (error) {
    console.error('❌ Audio capture test failed with error:', error);
    stopAllCaptures();
    process.exit(1);
  }
}

// Run the test
testAudioCapture();
