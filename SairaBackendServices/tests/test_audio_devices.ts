import { getDevices, DeviceInfo } from '../src/node_services/audio_processor.js';

/**
 * Test audio device enumeration
 */
async function testAudioDevices() {
  console.log('🔍 Testing audio device enumeration...');
  
  try {
    // Get all audio devices
    console.log('\n📋 Listing all audio devices:');
    const devices = await getDevices();
    
    if (devices.length === 0) {
      console.log('❌ No audio devices found');
      return;
    }
    
    // Group devices by type
    const inputDevices = devices.filter(d => d.type === 'input');
    const outputDevices = devices.filter(d => d.type === 'output');
    
    // Display input devices
    console.log('\n🎤 Input Devices:');
    inputDevices.forEach((device, index) => {
      console.log(`  ${index + 1}. ${device.name}${device.isDefault ? ' (Default)' : ''}`);
      console.log(`     ID: ${device.id}`);
    });
    
    // Display output devices
    console.log('\n🔈 Output Devices:');
    outputDevices.forEach((device, index) => {
      console.log(`  ${index + 1}. ${device.name}${device.isDefault ? ' (Default)' : ''}`);
      console.log(`     ID: ${device.id}`);
    });
    
    console.log('\n✅ Audio device test completed successfully!');
    
  } catch (error) {
    console.error('❌ Audio device test failed:', error);
  } finally {
    process.exit(0);
  }
}

// Run the test
testAudioDevices();
