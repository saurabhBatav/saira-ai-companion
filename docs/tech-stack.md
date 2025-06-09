# Tech Stack & Architecture Documentation  
**Project:** Saira – The Emotion-Aware Life Companion AI  
**Date:** 2025-06-09

---

## 1. Introduction

Saira is a privacy-focused, emotion-aware AI assistant designed to run fully offline on macOS initially, with future plans for iOS and a custom smart speaker integration. The goal is to deliver an intelligent, conversational experience that respects user privacy by performing all processing locally, without sending data to the cloud.

This document outlines the chosen technology stack, the reasons behind these choices, and how they fit together to form the foundation of Saira.

---

## 2. Project Goals & Constraints

- **Fully offline operation:** No reliance on cloud APIs or external servers. All AI models and data processing run locally.  
- **Cross-platform readiness:** Primary focus on macOS, with code reuse and architecture considerations for future iOS and custom hardware support.  
- **Privacy-first:** Sensitive user data never leaves the device; all storage and inference are local.  
- **Performance:** Efficient use of system resources, leveraging Apple Silicon optimizations where possible.  
- **Developer productivity:** Leverage existing expertise (React, Node.js) to accelerate development.  
- **Extensibility:** Modular design to allow future integration of new AI models and features.

---

## 3. Technology Stack Overview

| Component          | Chosen Technology                    | Justification / Benefits                               |
|--------------------|------------------------------------|-------------------------------------------------------|
| Frontend UI        | React Native + TypeScript           | Cross-platform, code reuse, developer familiarity     |
| Language Model     | Mistral 7B (Q4_0) via llama-node   | Local LLM, open-weight, efficient inference           |
| Speech-to-Text     | Whisper.cpp (base.en)               | Accurate, optimized for Apple Silicon, fully offline  |
| Text-to-Speech     | Piper (RHVoice model)               | Lightweight, real-time TTS, suitable for offline use  |
| Audio I/O          | node-portaudio + speaker            | Stable audio input/output, cross-platform support      |
| Local Storage      | SQLite                             | Lightweight, embedded DB, fully offline capable       |

---

## 4. Detailed Component Rationale

### 4.1 Frontend UI: React Native + TypeScript

- **Why React Native?**  
  React Native allows us to write one codebase that works across macOS and iOS, providing native UI performance and access to system APIs. It is mature enough for desktop support via community macOS extensions and aligns with our goal for multi-platform deployment.  

- **Why TypeScript?**  
  TypeScript enhances code quality through static typing, reduces runtime bugs, and improves developer experience, particularly on a complex app involving voice, AI, and local storage.

- **Developer Expertise:**  
  The team is already proficient in React and Node.js, making React Native a natural choice, reducing ramp-up time and facilitating rapid iteration.

---

### 4.2 Language Model: Mistral 7B (Q4_0) via llama-node

- **Why Mistral 7B?**  
  Mistral 7B is a compact, efficient large language model with excellent performance relative to its size. The Q4_0 quantization format further reduces memory footprint and inference latency.  

- **Why llama-node?**  
  This library enables local inference of LLaMA-based models using optimized runtimes. It supports Apple Silicon hardware acceleration and works entirely offline.

- **Privacy & Performance:**  
  Running locally ensures no data leakage, and the quantized model enables real-time interactions on consumer hardware.

---

### 4.3 Speech-to-Text: Whisper.cpp (base.en)

- **Why Whisper.cpp?**  
  Whisper.cpp is a C++ reimplementation of OpenAI’s Whisper model optimized for offline use on edge devices. The base English model provides good accuracy while maintaining real-time transcription speed.

- **Apple Silicon Optimization:**  
  The codebase includes optimizations specific to Apple’s hardware, ensuring smooth, low-latency transcription.

- **Offline Capability:**  
  Fully runs on-device with no internet connection required.

---

### 4.4 Text-to-Speech: Piper (RHVoice model)

- **Why Piper?**  
  Piper offers efficient, real-time text-to-speech synthesis suitable for embedded and offline applications.  

- **Model Choice:**  
  The RHVoice model is chosen for its naturalness and light resource consumption.

- **Real-Time Interaction:**  
  Enables quick, conversational voice responses without noticeable delay.

---

### 4.5 Audio Input/Output: node-portaudio + speaker

- **Why node-portaudio?**  
  A stable, well-maintained Node.js binding for PortAudio providing cross-platform access to audio I/O devices.  

- **Use Case:**  
  Essential for capturing microphone input and playing back synthesized speech reliably.

- **Cross-Platform Compatibility:**  
  Facilitates future extension to other platforms beyond macOS.

---

### 4.6 Local Data Storage: SQLite

- **Why SQLite?**  
  SQLite is an embedded, zero-configuration relational database ideal for local data persistence.  

- **Use Case:**  
  Storing user preferences, conversation logs, calendar events, and other data locally to maintain privacy and ensure offline availability.

- **Lightweight & Reliable:**  
  Requires minimal dependencies and is well-suited for desktop and mobile environments.

---

## 5. Architecture & Data Flow (Summary)

1. **User Interaction:** Voice or text input is received by the React Native UI.  
2. **Speech Recognition:** Audio is streamed to Whisper.cpp for transcription (if voice input).  
3. **Natural Language Processing:** The transcribed or typed input is sent to Mistral 7B running locally via llama-node.  
4. **Response Generation:** The LLM generates a reply based on context and memory.  
5. **Text-to-Speech:** Piper converts the reply text to audio output.  
6. **Audio Playback:** node-portaudio plays the synthesized voice.  
7. **Data Storage:** All interactions and relevant metadata are stored in SQLite for persistence and context retention.

---

## 6. Future Considerations

- **iOS Integration:** React Native codebase can be extended to iOS with platform-specific UI adjustments and API calls.  
- **Smart Speaker:** The modular AI and audio pipeline allow integration into custom hardware with similar system libraries.  
- **Syncing:** Secure cloud syncing of user data to enable multi-device experience, preserving privacy through end-to-end encryption (planned for later phases).  
- **Model Updates:** Support for dynamically updating AI models while keeping offline functionality intact.

---

## 7. Summary

This tech stack balances modern cross-platform development with privacy and offline-first principles. By leveraging open-source AI models optimized for local execution and a React Native frontend, we achieve both developer productivity and user-centric design goals. The architecture provides a strong foundation for future expansion while respecting user privacy and delivering a natural, responsive conversational AI experience.

---
