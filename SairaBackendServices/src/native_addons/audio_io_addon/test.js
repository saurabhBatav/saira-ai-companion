const addon = require('./build/Release/audio_io_addon.node');

// Test the hello function
const message = addon.hello();
console.log('Message from native addon:', message);

if (message === 'Hello from audio_io_addon!') {
  console.log('✅ Test passed!');
  process.exit(0);
} else {
  console.error('❌ Test failed!');
  process.exit(1);
}
