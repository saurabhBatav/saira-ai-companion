import { startCapture, stopAllCaptures } from '../src/node_services/audio_processor.js';

/**
 * Test script to verify audio capture and stop functionality
 */
async function testAudioCapture() {
  console.log('🚀 Starting audio capture test...');
  
  try {
    let bufferCount = 0;
    let isStopped = false;
    
    // Start capturing audio
    const stopCapture = startCapture(
      {
        sampleRate: 44100,
        channels: 1
      },
      (buffer) => {
        if (isStopped) {
          console.error('❌ Error: Received buffer after stopping capture!');
          process.exit(1);
        }
        bufferCount++;
        console.log(`🔊 Received buffer #${bufferCount}, size: ${buffer.byteLength} bytes`);
      }
    );
    
    console.log('🎙️  Audio capture started. Will stop after 3 seconds...');
    
    // Stop capture after 3 seconds
    setTimeout(() => {
      console.log('⏹️  Stopping audio capture...');
      isStopped = true;
      
      // First stop
      console.log('🔄 First stop call...');
      stopCapture();
      
      // Second stop (should be idempotent)
      console.log('🔄 Second stop call (should be safe)...');
      stopCapture();
      
      console.log(`✅ Audio capture stopped. Received ${bufferCount} buffers.`);
      
      // Verify no more buffers are received
      console.log('⏳ Waiting 2 seconds to verify no more buffers are received...');
      setTimeout(() => {
        console.log('✅ Test completed successfully!');
        process.exit(0);
      }, 2000);
      
    }, 3000);
    
    // Handle process termination
    process.on('SIGINT', () => {
      console.log('\n🛑 Stopping capture due to interrupt...');
      stopAllCaptures();
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
