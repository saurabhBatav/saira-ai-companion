import { startCapture, playAudio, stopAllCaptures, AudioCaptureOptions } from '../src/node_services/audio_processor.js';

/**
 * Generate a sine wave audio buffer
 * @param frequency Frequency in Hz
 * @param durationMs Duration in milliseconds
 * @param sampleRate Sample rate in Hz (default: 16000)
 * @param volume Volume level (0.0 to 1.0, default: 0.5)
 * @returns Int16Array containing the generated audio
 */
function generateSineWave(frequency: number, durationMs: number, sampleRate = 16000, volume = 0.5): Int16Array {
  const numSamples = Math.floor((durationMs / 1000) * sampleRate);
  const buffer = new Int16Array(numSamples);
  const amplitude = Math.min(Math.max(volume, 0), 1) * 32767; // Scale by volume (0.0 to 1.0)
  
  for (let i = 0; i < numSamples; i++) {
    const t = i / sampleRate;
    buffer[i] = Math.round(amplitude * Math.sin(2 * Math.PI * frequency * t));
  }
  
  return buffer;
}

/**
 * Test audio playback functionality
 */
async function testAudioPlayback() {
  console.log('🚀 Starting audio playback test...');
  
  try {
    // Test 1: Play a simple 440Hz sine wave (A4 note)
    console.log('\n🔊 Test 1: Playing 440Hz sine wave (A4 note) for 1 second...');
    const testTone1 = generateSineWave(440, 1000);
    if (!playAudio(testTone1)) {
      console.error('❌ Test 1 failed: Could not play 440Hz tone');
      return;
    }
    await new Promise(resolve => setTimeout(resolve, 1200));
    
    // Test 2: Play a sequence of different frequencies
    const frequencies = [261.63, 329.63, 392.00, 523.25]; // C4, E4, G4, C5
    for (let i = 0; i < frequencies.length; i++) {
      const freq = frequencies[i];
      console.log(`\n🔊 Test 2.${i + 1}: Playing ${freq.toFixed(2)}Hz tone for 0.5s...`);
      const tone = generateSineWave(freq, 500);
      if (!playAudio(tone)) {
        console.error(`❌ Test 2.${i + 1} failed: Could not play ${freq}Hz tone`);
        return;
      }
      await new Promise(resolve => setTimeout(resolve, 700));
    }
    
    // Test 3: Test with different volume levels
    console.log('\n🔊 Test 3: Testing different volume levels...');
    const volumes = [0.2, 0.5, 0.8];
    for (let i = 0; i < volumes.length; i++) {
      const volume = volumes[i];
      console.log(`\n🔊 Test 3.${i + 1}: Playing 440Hz at ${Math.round(volume * 100)}% volume...`);
      const tone = generateSineWave(440, 500, 16000, volume);
      if (!playAudio(tone)) {
        console.error(`❌ Test 3.${i + 1} failed: Could not play at ${volume} volume`);
        return;
      }
      await new Promise(resolve => setTimeout(resolve, 700));
    }
    
    // Test 4: Play a short melody (first few notes of "Twinkle Twinkle Little Star")
    console.log('\n🔊 Test 4: Playing a short melody (Twinkle Twinkle Little Star)...');
    const melody = [
      { freq: 261.63, duration: 400 }, // C4
      { freq: 261.63, duration: 400 }, // C4
      { freq: 392.00, duration: 400 }, // G4
      { freq: 392.00, duration: 400 }, // G4
      { freq: 440.00, duration: 400 }, // A4
      { freq: 440.00, duration: 400 }, // A4
      { freq: 392.00, duration: 800 }, // G4 (longer)
      
      { freq: 349.23, duration: 400 }, // F4
      { freq: 349.23, duration: 400 }, // F4
      { freq: 329.63, duration: 400 }, // E4
      { freq: 329.63, duration: 400 }, // E4
      { freq: 293.66, duration: 400 }, // D4
      { freq: 293.66, duration: 400 }, // D4
      { freq: 261.63, duration: 800 }  // C4 (longer)
    ];
    
    for (let i = 0; i < melody.length; i++) {
      const note = melody[i];
      const tone = generateSineWave(note.freq, note.duration);
      if (!playAudio(tone)) {
        console.error(`❌ Test 4 failed at note ${i + 1}`);
        return;
      }
      // Add a small gap between notes
      await new Promise(resolve => setTimeout(resolve, note.duration * 1.2));
    }
    
    console.log('\n✅ All audio playback tests completed successfully!');
    
  } catch (error) {
    console.error('❌ Audio playback test failed:', error);
  } finally {
    // Ensure all captures are stopped
    stopAllCaptures();
    process.exit(0);
  }
}

// Run the test
testAudioPlayback();
