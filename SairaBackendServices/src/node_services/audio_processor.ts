import path from 'path';
import { fileURLToPath } from 'url';
import { createRequire } from 'module';

// Get the current module's directory
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

// Define the native addon interface
interface AudioIOAddon {
  startCapture(options: {
    deviceId?: string;
    sampleRate: number;
    channels: number;
  }, callback: (buffer: ArrayBuffer) => void): unknown;
  
  stopCapture(instance: unknown): boolean;
  
  // For testing
  sayHello(): string;
}

// Load the native addon
const audioAddon: AudioIOAddon = require(addonPath);

// Track active capture instances
const activeCaptures: Set<() => void> = new Set();

// Clean up all active captures on process exit
process.on('exit', () => {
  activeCaptures.forEach(stop => stop());
  activeCaptures.clear();
});

// Handle process termination signals
['SIGINT', 'SIGTERM'].forEach(signal => {
  process.on(signal, () => {
    activeCaptures.forEach(stop => stop());
    activeCaptures.clear();
    process.exit(0);
  });
});

/**
 * Audio capture options
 */
export interface AudioCaptureOptions {
  /** Device ID (optional, uses default if not specified) */
  deviceId?: string;
  /** Sample rate in Hz (e.g., 44100, 48000) */
  sampleRate: number;
  /** Number of audio channels (1 for mono, 2 for stereo) */
  channels: number;
}

/**
 * Start capturing audio from the default input device
 * @param options Audio capture options
 * @param callback Function to call with audio data
 * @returns A function to stop the capture
 */
export function startCapture(
  options: Partial<AudioCaptureOptions> = {},
  callback: (buffer: ArrayBuffer) => void
): () => void {
  // Set default values
  const captureOptions: AudioCaptureOptions = {
    sampleRate: 44100,
    channels: 1,
    ...options
  };

  try {
    // Start the capture and store the instance
    const instance = audioAddon.startCapture(captureOptions, callback);
    
    // Create a stop function that properly cleans up
    const stopCapture = () => {
      if (typeof instance === 'function') {
        instance();
      } else if (typeof instance === 'object' && instance !== null) {
        audioAddon.stopCapture(instance);
      }
      activeCaptures.delete(stopCapture);
    };
    
    // Store the stop function for cleanup
    activeCaptures.add(stopCapture);
    return stopCapture;
  } catch (error) {
    console.error('Failed to start audio capture:', error);
    throw new Error(`Audio capture failed to start: ${error instanceof Error ? error.message : String(error)}`);
  }
}

/**
 * Stop a specific audio capture instance
 * @param stopFunction The stop function returned by startCapture
 */
export function stopCapture(stopFunction: () => void): void {
  if (activeCaptures.has(stopFunction)) {
    stopFunction();
    activeCaptures.delete(stopFunction);
  } else {
    console.warn('Attempted to stop a capture that is not active');
  }
}

/**
 * Stop all active audio captures
 */
export function stopAllCaptures(): void {
  activeCaptures.forEach(stop => stop());
  activeCaptures.clear();
}

// For testing purposes
export function sayHelloFromAddon(): string {
  try {
    return audioAddon.sayHello();
  } catch (error) {
    console.error('Error calling native sayHello:', error);
    return 'Error calling native addon';
  }
}

// Export all functionality
export default {
  startCapture,
  stopCapture,
  stopAllCaptures,
  sayHelloFromAddon
};