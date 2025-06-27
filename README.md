# 🧠 Saira - The Emotion-Aware Life Companion AI

> An intelligent, empathetic AI companion that understands your emotions, remembers your conversations, and adapts to your needs across multiple devices.

## 🌟 Features

- **🎭 Emotion-Aware Conversations**: Detects and responds to your emotional state through voice analysis
- **🧠 Long-term Memory**: Remembers your preferences, goals, and past interactions using vector embeddings
- **📱 Multi-Platform**: Seamlessly works on Mac, iPhone, and Smart Speakers
- **🔒 Privacy-First**: All processing happens locally with encrypted sync
- **👥 Adaptive Personalities**: Switches between mom, girlfriend, best friend, or coach modes

## 🚀 Getting Started

### Prerequisites
- Node.js 18+
- Python 3.9+
- macOS 12+ (for Mac app)
- iOS 15+ (for iPhone app)

### Quick Installation

```bash
# Clone the repository
git clone https://github.com/saurabhBatav/saira-ai-companion.git
cd saira-ai-companion

# Install dependencies
npm install
pip install -r requirements.txt

# Setup development environment
npm run setup:dev

# Start development server
npm run dev
```

## 📋 Project Status

🚧 **Current Status**: Phase 1 - Planning & Setup

| Phase | Status | Timeline |
|-------|--------|----------|
| Phase 1: Planning & Setup | 🔄 In Progress | June 7-20, 2025 |
| Phase 2: Core Architecture | ⏳ Planned | June 21 - July 8, 2025 |
| Phase 3: Feature Integration | ⏳ Planned | July 9-24, 2025 |
| Phase 4: Multi-Modal Output | ⏳ Planned | July 25 - Aug 10, 2025 |
| Phase 5: UI/UX Polish | ⏳ Planned | Aug 11-25, 2025 |
| Phase 6: Cross-Platform | ⏳ Planned | Aug 26 - Sep 1, 2025 |
| Phase 7: Launch | ⏳ Planned | Sep 2-7, 2025 |

See our [Project Board](https://github.com/saurabhBatav/saira-ai-companion/projects) for detailed progress tracking.

## 🏗️ Architecture

```
saira-app/
├── .git/                                    # Git repository
├── .github/                                 # GitHub specific configurations
│   └── workflows/
│       └── ci.yml                           # GitHub Actions CI/CD pipeline for macOS and iOS builds [1, 2]
├── README.md                                # Project README
├── LICENSE                                  # Project license
├── docs/                                    # Project documentation
│   ├── architecture/
│   │   ├── system_diagram.md                # High-level system architecture diagrams
│   │   ├── api_spec.md                      # Comprehensive API specifications
│   │   ├── db_schema.md                     # Database schema definitions
│   │   └── security_model.md                # Detailed security considerations
│   └── features/
│       ├── onboarding.md
│       ├── voice_interaction.md
│       ├── long_term_memory.md
│       ├── data_sync.md
│       ├── personality_modes.md
│       ├── journaling.md
│       └── nudges.md
│
├── Saira/                     # Main macOS/iOS application (React Native + TypeScript)
│   ├── package.json                         # Node.js dependencies for React Native [3]
│   ├── tsconfig.json                        # TypeScript configuration [4, 5]
│   ├── index.js                             # Entry point for React Native app [6]
│   ├── App.tsx                              # Root React Native component
│   ├── src/
│   │   ├── components/                      # Reusable UI components (TypeScript/TSX)
│   │   │   ├── Button.tsx
│   │   │   ├── TextInput.tsx
│   │   │   └──...
│   │   ├── screens/                         # Main application screens (TypeScript/TSX)
│   │   │   ├── OnboardingScreen.tsx
│   │   │   ├── ConversationScreen.tsx
│   │   │   ├── JournalingScreen.tsx
│   │   │   ├── ProfileSettingsScreen.tsx
│   │   │   └── DeepTalkScreen.tsx
│   │   ├── navigation/                      # React Navigation setup [3]
│   │   │   └── AppNavigator.tsx
│   │   ├── services/                        # JavaScript/TypeScript services for app logic
│   │   │   ├── AppStateManager.ts           # Manages overall app state and lifecycle
│   │   │   ├── DataStoreService.ts          # High-level interface for SQLite operations
│   │   │   ├── IPCService.ts                # Manages communication with Node.js/Python backend processes
│   │   │   ├── NotificationService.ts       # Handles macOS notifications
│   │   │   ├── SyncService.ts               # Manages cloud synchronization logic
│   │   │   └── TaskManagerClient.ts         # NEW: Client for communicating with TaskManager
│   │   ├── models/                          # TypeScript data models (interfaces, types)
│   │   │   ├── AppModels.ts                 # User, Message, Memory, Goal, etc.
│   │   │   ├── DTOs.ts                      # Data Transfer Objects for IPC
│   │   │   └── TaskModels.ts                # NEW: Models for Task and TaskStatus
│   │   └── utils/                           # Utility functions and helpers
│   │       ├── Constants.ts
│   │       ├── Logger.ts                    # Structured logging utility
│   │       └── Permissions.ts               # Handles system permissions
│   ├── ios/                                 # iOS native project (Objective-C/Swift)
│   │   ├── Saira.xcodeproj/
│   │   ├── Saira/
│   │   │   ├── AppDelegate.mm               # Objective-C++ for native module bridging [7, 8, 9]
│   │   │   └── Info.plist
│   │   └── Podfile                          # CocoaPods for iOS dependencies [1]
│   ├── macos/                               # macOS native project (Objective-C/Swift)
│   │   ├── Saira.xcodeproj/
│   │   ├── Saira/
│   │   │   ├── AppDelegate.mm               # Objective-C++ for native module bridging [7, 8, 9]
│   │   │   └── Info.plist
│   │   └── Podfile                          # CocoaPods for macOS dependencies [1]
│   ├── __tests__/                           # Jest tests for React Native components [3]
│   └── e2e/                                 # End-to-end tests (e.g., Detox) [3]
│
├── SairaBackendServices/                    # Node.js and Python backend services
│   ├── package.json                         # Node.js dependencies for backend services
│   ├── tsconfig.json                        # TypeScript configuration for Node.js services
│   ├── node_modules/
│   ├── src/
│   │   ├── node_services/                   # Node.js services (TypeScript/JavaScript)
│   │   │   ├── main.ts                      # Entry point for Node.js backend process
│   │   │   ├── ai_inference_server.ts       # Local HTTP/WebSocket server for AI models
│   │   │   ├── audio_processor.ts           # Handles audio I/O via native addons
│   │   │   ├── data_manager.ts              # Handles SQLite operations
│   │   │   ├── model_manager.ts             # Manages AI model loading and updates
│   │   │   ├── ipc_handler.ts               # Handles IPC messages from frontend
│   │   │   └── task_manager.ts              # NEW: TaskManager service responsible for queuing and executing tasks
│   │   ├── python_services/                 # Python scripts
│   │   │   ├── rag_ingestion.py             # For RAG document processing (chunking, embedding)
│   │   │   ├── model_downloader.py          # For AI model downloads
│   │   │   └── ser_feature_extractor.py     # For openSMILE feature extraction (if Python wrapper used)
│   │   ├── native_addons/                   # C++ Node.js native addons (N-API)
│   │   │   ├── audio_io_addon/              # Wrapper for Core Audio (PortAudio)
│   │   │   │   ├── binding.gyp
│   │   │   │   └── src/audio_io.cpp
│   │   │   ├── ai_inference_addon/          # Wrapper for llama.cpp, whisper.cpp, Piper, Porcupine, openSMILE/SenseVoice
│   │   │   │   ├── binding.gyp
│   │   │   │   └── src/ai_inference.cpp
│   │   │   └── sqlite_vec_addon/            # Wrapper for sqlite-vec]
│   │   │       ├── binding.gyp
│   │   │       └── src/sqlite_vec.cpp
│   │   └── models/                          # Pre-trained AI models (downloaded by app)
│   │       ├── llm/
│   │       ├── asr/
│   │       ├── tts/
│   │       ├── ser/
│   │       └── embeddings/
│   ├── tests/                               # Jest tests for Node.js services, Pytest for Python scripts
│   └── Dockerfile                           # For local development environment setup [10, 11]
│
├── Tools/                                   # Development and utility scripts
│   └── dev_scripts/                         # Miscellaneous development scripts
│
├── .gitignore                               # Git ignore file
├── .prettierrc                              # Prettier configuration [1]
└── .eslintrc.js                             # ESLint configuration [1]
```

## 🎭 Personality Modes

Saira adapts her personality based on your needs:

- **👩‍👧‍👦 Mom Mode**: Nurturing, caring, and protective
- **💕 Girlfriend Mode**: Romantic, supportive, and intimate
- **👫 Best Friend Mode**: Casual, fun, and understanding
- **💪 Coach Mode**: Motivational, goal-oriented, and challenging

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guide](CONTRIBUTING.md) for details.

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🔒 Privacy Promise

Saira is designed with privacy as the core principle:
- All emotion detection happens locally on your device
- Personal data never leaves your control
- End-to-end encryption for device sync
- No cloud processing of personal conversations

See our [Privacy Policy](docs/privacy.md) for complete details.

## 📞 Support

- 🐛 [Report Issues](https://github.com/saurabhBatav/saira-ai-companion/issues)
- 💬 [Discussions](https://github.com/saurabhBatav/saira-ai-companion/discussions)
- 📧 Email: support@saira-ai.com

---

*Made with ❤️ for meaningful human-AI connections*
