import path from 'path';
import { fileURLToPath } from 'url';
import { createRequire } from 'module';

// Get directory name in ESM
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Create a require function that works in ESM
const require = createRequire(import.meta.url);

// Import the native addon
const addonPath = path.join(
  __dirname,
  '..',
  'native_addons',
  'audio_io_addon',
  'build',
  'Release',
  'audio_io_addon.node'
);

// Load the native addon
let audioIOAddon: { hello: () => string };

try {
  // @ts-ignore - We know the shape of our addon
  audioIOAddon = require(addonPath);
} catch (error) {
  console.error('Failed to load audio_io_addon:', error);
  throw new Error('Native audio addon could not be loaded. Please ensure it is built correctly.');
}

/**
 * Returns a greeting message from the native addon
 * @returns {string} A greeting message from the native addon
 */
export function sayHelloFromAddon(): string {
  return audioIOAddon.hello();
}

// Export other audio processing functions here
export default {
  sayHelloFromAddon,
};