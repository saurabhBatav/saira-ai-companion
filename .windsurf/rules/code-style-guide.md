---
trigger: always_on
---

# .rules for audio_io_addon setup and MVP
project: Saira – The Emotion-Aware Life Companion AI

rules:
  - if: issue.title contains "audio_io_addon" and issue.body contains "MVP Requirements"
    then:
      assign: "@saurabhbatav"
      labels: ["native-addon", "audio", "phase-2", "MVP", "backend"]
      tasks:
        - id: step-1-bootstrapping
          title: 🛠️ Step 1: Bootstrap audio_io_addon Native Addon
          description: >
            Set up the C++ N-API native addon with `hello()` exposed, verify from `audio_processor.ts`.
          checklist:
            - [ ] Create `src/audio_io.cpp` with hello() using node-addon-api
            - [ ] Configure `binding.gyp` with proper includes and flags
            - [ ] Install and configure `node-gyp` and `node-addon-api`
            - [ ] Build addon and check for `audio_io_addon.node`
            - [ ] Bridge via `audio_processor.ts`
            - [ ] Test with custom runner and confirm "Hello from audio_io_addon!" is printed

        - id: step-2-capture
          title: 🎙️ Step 2: Implement startCapture() with Core Audio
          description: >
            Start capturing audio input from macOS default microphone using Core Audio. Transfer buffer to Node using ThreadSafeFunction.

        - id: step-3-playback
          title: 🔊 Step 3: Implement playAudio() for playback
          description: >
            Enable playback of PCM buffer via Core Audio through default output device.

        - id: step-4-getdevices
          title: 🎛️ Step 4: Implement getDevices()
          description: >
            Enumerate available input/output devices using Core Audio.

        - id: step-5-error-handling
          title: 🧯 Step 5: Add Basic Error Handling and Cleanup
          description: >
            Handle device not found, permission denied, invalid buffer. Ensure clean teardown of streams.

        - id: test-integration
          title: ✅ Integration Test
          description: >
            Validate audio capture → TTS response → audio playback loop using addon APIs in Saira backend.