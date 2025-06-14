# Granular insights and step-by-step implementation guidance for each feature :-

---

## File System

The project will adopt a monorepo structure to manage the React Native for macOS frontend application and the Node.js/Python backend services, facilitating integration and streamlined dependency management.

```
saira-app/
├──.git/                                    # Git repository
├──.github/                                 # GitHub specific configurations
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
├── SairaReactNativeApp/                     # Main macOS/iOS application (React Native + TypeScript)
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
│   │   │   └── SyncService.ts               # Manages cloud synchronization logic
│   │   ├── models/                          # TypeScript data models (interfaces, types)
│   │   │   ├── AppModels.ts                 # User, Message, Memory, Goal, etc.
│   │   │   └── DTOs.ts                      # Data Transfer Objects for IPC
│   │   └── utils/                           # Utility functions and helpers
│   │       ├── Constants.ts
│   │       ├── Logger.ts                    # Structured logging utility
│   │       └── Permissions.ts               # Handles system permissions
│   ├── ios/                                 # iOS native project (Objective-C/Swift)
│   │   ├── SairaReactNativeApp.xcodeproj/
│   │   ├── SairaReactNativeApp/
│   │   │   ├── AppDelegate.mm               # Objective-C++ for native module bridging [7, 8, 9]
│   │   │   └── Info.plist
│   │   └── Podfile                          # CocoaPods for iOS dependencies [1]
│   ├── macos/                               # macOS native project (Objective-C/Swift)
│   │   ├── SairaReactNativeApp.xcodeproj/
│   │   ├── SairaReactNativeApp/
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
│   │   │   └── ipc_handler.ts               # Handles IPC messages from frontend
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
├──.gitignore                               # Git ignore file
├──.prettierrc                               # Prettier configuration [1]
└──.eslintrc.js                             # ESLint configuration [1]
```

## Feature Specifications

### Feature: Core Application Framework (UI & App Logic)

**Feature Goal**
To provide the foundational native-like macOS user interface and the core application logic that orchestrates interactions between the UI, local data storage, and the underlying Node.js/Python backend services. This feature encompasses the initial user onboarding, general navigation, and the display of core application data.

**Any API Relationships**
This feature serves as the central hub, interacting with almost all other features:
*   **Real-time Voice Interaction:** Initiates and receives data from ASR, TTS, Wake Word, and SER services via `IPCService` (communicating with `ai_inference_server.ts` and `audio_processor.ts`).
*   **Local Long-Term Memory (RAG):** Manages CRUD operations for memories and goals through `DataStoreService`, which interacts with `data_manager.ts` (Node.js) and potentially `rag_ingestion.py` (Python).
*   **Offline-First Data Sync:** Triggers and monitors synchronization processes via `SyncService`.
*   **Personality Modes & Customization:** Loads and applies personality profiles and user settings, influencing LLM behavior via `IPCService`.
*   **Daily Check-ins & Journaling:** Provides UI for creating, viewing, and managing journal entries and mood summaries, interacting with `DataStoreService`.
*   **Proactive Nudges & Notifications:** Configures and displays notifications via `NotificationService`.

**Detailed Feature Requirements**

1.  **User Onboarding Flow:**
    *   **Initial Setup:** Guide new users through personality preferences, initial goals, and desired tone style.
    *   **Data Collection:** Securely collect initial user data (e.g., name, preferred AI personality, initial goals).
    *   **Consent Management:** Clearly present privacy policy and obtain explicit consent for data collection (e.g., emotion/memory recording) and optional cloud sync, adhering to GDPR and CCPA.
    *   **Progress Tracking:** Visually indicate onboarding progress.
2.  **Main Application Navigation:**
    *   **Tab-based Navigation:** Implement a clear tab bar for primary sections: Conversation, Daily Check-ins/Journal, Deep Talk, and Profile Settings.
    *   **Responsive Layout:** Ensure the UI adapts gracefully to various macOS window sizes and future iOS screen sizes.
3.  **Conversation View (MVP - Voice Interaction Only):**
    *   **Voice Input Indicator:** Display a visual indicator (e.g., waveform, microphone icon) when the app is actively listening or processing voice input.
    *   **Real-time Transcription Display:** Show transcribed text as the user speaks.
    *   **AI Response Display:** Present AI's spoken responses as text in a chat-like interface.
    *   **Basic Chat History:** Display a scrollable history of the current conversation session.
4.  **Daily Check-ins & Journaling Tab:**
    *   **Mood Summary Display:** Show a daily summary of detected moods and emotional patterns.
    *   **Emotional Check-in Interface:** Allow users to manually log their emotional state.
    *   **Journal Entry Creation/Viewing:** Provide an interface for creating, viewing, and editing journal entries.
5.  **Deep Talk Tab:**
    *   **Dedicated Conversation Mode:** Offer a specialized conversational mode for deeper exploration of life events, emotional patterns, or relationship issues. This mode will leverage the RAG system more heavily.
6.  **Profile Settings Tab:**
    *   **Personality Preferences:** Allow users to configure AI personality styles (e.g., "Mom," "Coach," "Best Friend").
    *   **Memory Visibility:** Provide controls for users to review and manage what memories the AI retains.
    *   **Privacy Settings:** Centralized dashboard for managing data consent, deletion rights, and audit logs.
    *   **Emotional Tone Preferences:** Allow users to fine-tune how the AI perceives and responds to their emotional tone.
    *   **Offline Sync Configuration:** Settings for enabling/disabling cloud sync, frequency, and conflict resolution preferences.
    *   **Model Management:** Display currently loaded AI models and provide options for in-app updates.
7.  **Proactive Nudges & Notifications:**
    *   **Notification Display:** Receive and display proactive nudges (reminders, positive reinforcement, wellness suggestions) via macOS Notification Center.
    *   **Configuration:** Allow users to enable/disable and customize types/frequency of nudges in settings.

**Detailed Implementation Guide**

1.  **System Architecture Overview**
    *   **High-level Architecture:** The application will consist of a React Native for macOS frontend (`SairaReactNativeApp/`) and a Node.js/Python backend (`SairaBackendServices/`). The frontend handles the UI and high-level application logic. The backend handles all performance-critical AI inference, low-level audio I/O, and local data management. Communication between the frontend and backend will primarily occur via Inter-Process Communication (IPC) using local HTTP/WebSocket servers or Node.js `child_process` module.
    *   **Technology Stack:**
        *   **Frontend UI:** React Native for macOS (with TypeScript). Justification: Allows for JavaScript/React-based UI development, enabling code reuse for future iOS expansion. TypeScript enhances code quality and maintainability for large projects. React Native renders native components for a near-native experience.
        *   **Backend Services (Orchestration):** Node.js (with TypeScript). Justification: Node.js is well-suited for I/O-intensive tasks and building scalable APIs. It can manage concurrent requests efficiently due to its event-driven, non-blocking architecture. It also has a large package ecosystem (npm).
        *   **Backend Services (AI Inference & Low-Level Operations):** Python and C++ native addons for Node.js. Justification: While Node.js and Python can wrap C++ libraries, the underlying AI models (`llama.cpp`, `whisper.cpp`, Piper, Porcupine, `openSMILE`, SenseVoice) are highly optimized C/C++ implementations.
            *   **C++ Native Addons (N-API):** For direct, low-latency interaction with macOS Core Audio and for wrapping performance-critical AI libraries. This is crucial to mitigate the performance overhead of pure JavaScript/Python for real-time AI inference. N-API allows C++ code to be exposed to Node.js.[9]
            *   **Python:** For tasks like RAG document ingestion (chunking, embedding generation) where its rich ecosystem of ML libraries is beneficial. Python can also be used for specific AI model inference if a robust Node.js binding is unavailable or less performant, exposed via a local HTTP server. Python is generally slower for CPU-intensive tasks than C++.
        *   **Local Data Storage:** SQLite with `sqlite-vec` extension. Justification: Embedded, serverless, and cross-platform, ideal for local data persistence and vector search. Node.js has bindings for SQLite and `sqlite-vec`]. `op-sqlite` for React Native also supports `sqlite-vec`].
    *   **Deployment Architecture:** The React Native application will be bundled as a standard macOS `.app` package. The Node.js backend services will run as a separate process, potentially launched as a child process by the React Native app or as a background service. C++ native addons will be compiled and bundled with the Node.js services. Python scripts will be bundled and executed by the Node.js process.
    *   **Integration Points:**
        *   **macOS Core Audio:** Via C++ native addon (PortAudio wrapper or direct Core Audio calls) for Node.js.
        *   **macOS Notification Center:** React Native modules for native notifications.
        *   **Local File System:** For RAG document ingestion and AI model storage.
        *   **Cloud Sync Service (Future):** Custom E2EE protocol for optional data synchronization].

2.  **Database Schema Design**
    The local database will be SQLite, encrypted with SQLCipher. All tables will include `id` (PRIMARY KEY), `created_at` (TIMESTAMP), `updated_at` (TIMESTAMP), and `user_id` (FOREIGN KEY to `Users` table) where applicable.

    *   **`Users` Table:**
        *   `id` (TEXT, PRIMARY KEY, UUID)
        *   `name` (TEXT, NOT NULL)
        *   `onboarding_completed` (INTEGER, BOOLEAN, DEFAULT 0)
        *   `current_personality_profile_id` (TEXT, FOREIGN KEY to `PersonalityProfiles.id`)
        *   `last_active_at` (TIMESTAMP)
        *   `created_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)
        *   `updated_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)
        *   `sync_enabled` (INTEGER, BOOLEAN, DEFAULT 0)
        *   `last_synced_at` (TIMESTAMP, NULLABLE)
        *   `sync_frequency` (TEXT, ENUM: 'daily', 'weekly', 'manual', DEFAULT 'manual')
        *   `encryption_key_hash` (TEXT, NOT NULL) - Hash of user-derived key for SQLCipher.
        *   `privacy_consent_version` (TEXT, NOT NULL) - Tracks accepted privacy policy version.
        *   `gdpr_ccpa_consent` (INTEGER, BOOLEAN, NOT NULL) - Explicit consent for data processing.
        *   `audit_logging_enabled` (INTEGER, BOOLEAN, DEFAULT 1) - User preference for audit logs.
        *   `data_portability_token` (TEXT, NULLABLE) - Token for data export.
        *   `data_deletion_requested_at` (TIMESTAMP, NULLABLE) - Timestamp if deletion requested.
        *   `profile_image_path` (TEXT, NULLABLE)
        *   `preferred_tone_style` (TEXT, ENUM: 'formal', 'casual', 'empathetic', etc., DEFAULT 'empathetic')
        *   `wake_word_enabled` (INTEGER, BOOLEAN, DEFAULT 1)
        *   `proactive_nudges_enabled` (INTEGER, BOOLEAN, DEFAULT 1)
        *   `deep_talk_mode_enabled` (INTEGER, BOOLEAN, DEFAULT 1)
        *   `emotion_recording_consent` (INTEGER, BOOLEAN, NOT NULL) - Consent for emotion data recording.
        *   `memory_recording_consent` (INTEGER, BOOLEAN, NOT NULL) - Consent for memory recording.
        *   `journaling_enabled` (INTEGER, BOOLEAN, DEFAULT 1)

    *   **`Conversations` Table:**
        *   `id` (TEXT, PRIMARY KEY, UUID)
        *   `user_id` (TEXT, FOREIGN KEY to `Users.id`, NOT NULL)
        *   `start_time` (TIMESTAMP, NOT NULL)
        *   `end_time` (TIMESTAMP, NULLABLE)
        *   `title` (TEXT, NULLABLE) - Auto-generated or user-edited summary.
        *   `personality_profile_id` (TEXT, FOREIGN KEY to `PersonalityProfiles.id`) - Personality used during conversation.
        *   `created_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)
        *   `updated_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)

    *   **`Messages` Table:**
        *   `id` (TEXT, PRIMARY KEY, UUID)
        *   `conversation_id` (TEXT, FOREIGN KEY to `Conversations.id`, NOT NULL)
        *   `sender_type` (TEXT, ENUM: 'user', 'ai', NOT NULL)
        *   `content` (TEXT, NOT NULL)
        *   `timestamp` (TIMESTAMP, NOT NULL)
        *   `audio_path` (TEXT, NULLABLE) - Local path to raw audio (if stored, with consent).
        *   `emotion_arousal` (REAL, NULLABLE) - Detected arousal (0-1).
        *   `emotion_valence` (REAL, NULLABLE) - Detected valence (-1 to 1).
        *   `emotion_category` (TEXT, NULLABLE) - Categorical emotion (e.g., 'happy', 'sad').
        *   `is_proactive_nudge` (INTEGER, BOOLEAN, DEFAULT 0) - If message is a nudge.
        *   `created_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)
        *   `updated_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)

    *   **`Memories` Table:** (Semantic, Episodic, Procedural)
        *   `id` (TEXT, PRIMARY KEY, UUID)
        *   `user_id` (TEXT, FOREIGN KEY to `Users.id`, NOT NULL)
        *   `type` (TEXT, ENUM: 'semantic', 'episodic', 'procedural', NOT NULL)
        *   `content` (TEXT, NOT NULL) - The actual memory text.
        *   `embedding` (BLOB, NOT NULL) - Vector embedding of the content.
        *   `source_id` (TEXT, NULLABLE) - ID of related conversation/journal entry/document.
        *   `source_type` (TEXT, ENUM: 'conversation', 'journal', 'document', 'user_input', NULLABLE)
        *   `timestamp` (TIMESTAMP, NOT NULL) - When the memory was formed/updated.
        *   `relevance_score` (REAL, DEFAULT 0.0) - For RAG prioritization.
        *   `is_active` (INTEGER, BOOLEAN, DEFAULT 1) - Can be toggled by user for visibility.
        *   `created_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)
        *   `updated_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)

    *   **`Goals` Table:**
        *   `id` (TEXT, PRIMARY KEY, UUID)
        *   `user_id` (TEXT, FOREIGN KEY to `Users.id`, NOT NULL)
        *   `title` (TEXT, NOT NULL)
        *   `description` (TEXT, NULLABLE)
        *   `status` (TEXT, ENUM: 'active', 'completed', 'archived', NOT NULL)
        *   `due_date` (TIMESTAMP, NULLABLE)
        *   `progress` (REAL, DEFAULT 0.0) - 0.0 to 1.0.
        *   `created_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)
        *   `updated_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)

    *   **`JournalEntries` Table:**
        *   `id` (TEXT, PRIMARY KEY, UUID)
        *   `user_id` (TEXT, FOREIGN KEY to `Users.id`, NOT NULL)
        *   `timestamp` (TIMESTAMP, NOT NULL)
        *   `content` (TEXT, NOT NULL)
        *   `detected_emotions` (TEXT, NULLABLE) - JSON array of detected emotions (e.g., `[{"arousal": 0.8, "valence": 0.7, "category": "happy"}]`).
        *   `associated_memories` (TEXT, NULLABLE) - JSON array of `Memory.id`s.
        *   `created_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)
        *   `updated_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)

    *   **`MoodSummaries` Table:**
        *   `id` (TEXT, PRIMARY KEY, UUID)
        *   `user_id` (TEXT, FOREIGN KEY to `Users.id`, NOT NULL)
        *   `date` (DATE, NOT NULL, UNIQUE)
        *   `summary_text` (TEXT, NULLABLE) - AI-generated summary of daily mood.
        *   `aggregated_emotions` (TEXT, NULLABLE) - JSON object of aggregated emotion data for the day.
        *   `created_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)
        *   `updated_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)

    *   **`PersonalityProfiles` Table:**
        *   `id` (TEXT, PRIMARY KEY, UUID)
        *   `user_id` (TEXT, FOREIGN KEY to `Users.id`, NULLABLE) - NULL for system-defined profiles.
        *   `name` (TEXT, NOT NULL)
        *   `description` (TEXT, NULLABLE)
        *   `llm_prompt_template` (TEXT, NOT NULL) - Core prompt for LLM to adopt personality.
        *   `tone_preferences` (TEXT, NULLABLE) - JSON object for specific tone adjustments.
        *   `memory_visibility_rules` (TEXT, NULLABLE) - JSON object for rules on what memories are accessible.
        *   `is_custom` (INTEGER, BOOLEAN, DEFAULT 0) - Indicates if user-created.
        *   `created_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)
        *   `updated_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)

    *   **`NudgePreferences` Table:**
        *   `id` (TEXT, PRIMARY KEY, UUID)
        *   `user_id` (TEXT, FOREIGN KEY to `Users.id`, NOT NULL)
        *   `type` (TEXT, ENUM: 'reminder', 'positive_reinforcement', 'wellness_suggestion', NOT NULL)
        *   `frequency` (TEXT, ENUM: 'daily', 'weekly', 'monthly', 'event_based', NOT NULL)
        *   `time_of_day` (TEXT, NULLABLE) - e.g., "09:00", "18:30".
        *   `content_template` (TEXT, NOT NULL) - Template for nudge message.
        *   `enabled` (INTEGER, BOOLEAN, DEFAULT 1)
        *   `created_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)
        *   `updated_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)

    *   **`NudgeHistory` Table:**
        *   `id` (TEXT, PRIMARY KEY, UUID)
        *   `user_id` (TEXT, FOREIGN KEY to `Users.id`, NOT NULL)
        *   `nudge_preference_id` (TEXT, FOREIGN KEY to `NudgePreferences.id`, NOT NULL)
        *   `timestamp` (TIMESTAMP, NOT NULL) - When the nudge was delivered.
        *   `message_content` (TEXT, NOT NULL) - Actual message sent.
        *   `delivered` (INTEGER, BOOLEAN, DEFAULT 1)
        *   `interacted` (INTEGER, BOOLEAN, DEFAULT 0) - User interacted with notification.
        *   `created_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)

    *   **Indexing Strategy:**
        *   Indexes on foreign keys (`user_id`, `conversation_id`, `personality_profile_id`, `nudge_preference_id`).
        *   Indexes on `timestamp` for time-series data (Conversations, Messages, JournalEntries, NudgeHistory).
        *   Unique index on `MoodSummaries.date` per `user_id`.
        *   `sqlite-vec` virtual table for `Memories.embedding` for efficient vector search [[16, 17], S_R147, S_R153].
        *   Indexes on `name` for `PersonalityProfiles` for quick lookup.
    *   **Foreign Key Relationships:** Enforce `ON DELETE CASCADE` for `Messages` to `Conversations`, `Goals`, `JournalEntries`, `MoodSummaries`, `NudgePreferences`, `NudgeHistory` to `Users`.
    *   **Database Migration/Versioning:** Use a lightweight schema migration tool (e.g., a custom Node.js script) to manage database schema changes. Each migration will be versioned and applied sequentially on app launch.

3.  **Comprehensive API Design**
    The primary API will be internal, facilitating communication between the React Native frontend and the Node.js backend services. This will likely involve a local HTTP server or WebSocket server running within the Node.js backend process.

    *   **React Native Frontend APIs (Internal to `SairaReactNativeApp/src/services/`):** These are TypeScript interfaces and classes that define the communication contracts between the React Native UI and the backend services. They will use `fetch` for HTTP requests and `WebSocket` for real-time streaming to the local Node.js backend.
        *   **`UserManager` (TypeScript Class):**
            *   `createUser(name: string, initialPreferences: UserPreferencesDTO) => Promise<User>` (C)
            *   `getUser(id: string) => Promise<User | null>` (R)
            *   `updateUser(id: string, updates: UserUpdateDTO) => Promise<User>` (U)
            *   `deleteUser(id: string) => Promise<void>` (D)
            *   `getPrivacySettings(userId: string) => Promise<PrivacySettingsDTO>` (R)
            *   `updatePrivacySettings(userId: string, settings: PrivacySettingsDTO) => Promise<void>` (U)
        *   **`ConversationManager` (TypeScript Class):**
            *   `startConversation(userId: string, personalityId: string) => Promise<Conversation>` (C)
            *   `getConversation(id: string) => Promise<Conversation | null>` (R)
            *   `getConversations(userId: string, pagination: PaginationDTO) => Promise<Conversation>` (R)
            *   `updateConversationTitle(id: string, title: string) => Promise<Conversation>` (U)
            *   `endConversation(id: string) => Promise<Conversation>` (U)
            *   `deleteConversation(id: string) => Promise<void>` (D)
        *   **`MessageManager` (TypeScript Class):**
            *   `addMessage(conversationId: string, sender: SenderType, content: string, audioPath?: string, emotions?: EmotionDataDTO) => Promise<Message>` (C)
            *   `getMessages(conversationId: string, pagination: PaginationDTO) => Promise<Message>` (R)
            *   `updateMessage(id: string, content: string) => Promise<Message>` (U)
            *   `deleteMessage(id: string) => Promise<void>` (D)
        *   **`JournalManager` (TypeScript Class):**
            *   `createJournalEntry(userId: string, content: string, emotions?: EmotionDataDTO) => Promise<JournalEntry>` (C)
            *   `getJournalEntry(id: string) => Promise<JournalEntry | null>` (R)
            *   `getJournalEntries(userId: string, dateRange: DateRangeDTO, pagination: PaginationDTO) => Promise<JournalEntry>` (R)
            *   `updateJournalEntry(id: string, content: string) => Promise<JournalEntry>` (U)
            *   `deleteJournalEntry(id: string) => Promise<void>` (D)
            *   `generateMoodSummary(userId: string, date: Date) => Promise<MoodSummary>` (C)
            *   `getMoodSummaries(userId: string, dateRange: DateRangeDTO) => Promise<MoodSummary>` (R)
        *   **`PersonalityManager` (TypeScript Class):**
            *   `getPersonalityProfiles(userId?: string) => Promise<PersonalityProfile>` (R)
            *   `createCustomPersonality(userId: string, profile: PersonalityProfileDTO) => Promise<PersonalityProfile>` (C)
            *   `updatePersonalityProfile(id: string, updates: PersonalityProfileUpdateDTO) => Promise<PersonalityProfile>` (U)
            *   `deleteCustomPersonality(id: string) => Promise<void>` (D)
            *   `activatePersonalityProfile(userId: string, profileId: string) => Promise<void>` (U)
        *   **`NudgeManager` (TypeScript Class):**
            *   `createNudgePreference(userId: string, preference: NudgePreferenceDTO) => Promise<NudgePreference>` (C)
            *   `getNudgePreferences(userId: string) => Promise<NudgePreference>` (R)
            *   `updateNudgePreference(id: string, updates: NudgePreferenceUpdateDTO) => Promise<NudgePreference>` (U)
            *   `deleteNudgePreference(id: string) => Promise<void>` (D)
            *   `getNudgeHistory(userId: string, pagination: PaginationDTO) => Promise<NudgeHistory>` (R)
            *   `markNudgeInteracted(nudgeHistoryId: string) => Promise<void>` (U)

    *   **Node.js Backend APIs (Local HTTP/WebSocket Server in `SairaBackendServices/src/node_services/ai_inference_server.ts`):**
        *   **HTTP Endpoints (REST-like):** These endpoints will be exposed via a local HTTP server (e.g., Express.js) running within the Node.js backend process.
            *   `POST /ai/llm/generate`: Request LLM response.
                *   Request: `{ prompt: string, context: string, memories: string, personalityId: string, emotionData: EmotionDataDTO }`
                *   Response: `{ text: string }`
            *   `POST /ai/asr/transcribe_file`: Transcribe a full audio file.
                *   Request: `{ filePath: string }`
                *   Response: `{ text: string }`
            *   `POST /ai/tts/synthesize_text`: Synthesize speech from text.
                *   Request: `{ text: string }`
                *   Response: `{ audioData: string (base64 encoded PCM) }`
            *   `POST /ai/ser/detect_file`: Detect emotion from an audio file.
                *   Request: `{ filePath: string }`
                *   Response: `{ arousal: number, valence: number, category: string }`
            *   `POST /ai/embeddings/generate`: Generate text embedding.
                *   Request: `{ text: string }`
                *   Response: `{ embedding: number }`
            *   `POST /data/query`: Execute database query.
                *   Request: `{ sql: string, params: any }`
                *   Response: `{ rows: any }`
            *   `POST /data/mutate`: Execute database mutation.
                *   Request: `{ sql: string, params: any }`
                *   Response: `{ changes: number, lastInsertRowId: number }`
            *   `POST /data/search_vectors`: Perform vector search.
                *   Request: `{ embedding: number, tableName: string, limit: number }`
                *   Response: `{ results: { id: string, score: number } }`
            *   `POST /models/load`: Load AI model.
                *   Request: `{ modelType: string, modelPath: string }`
                *   Response: `{ success: boolean }`
            *   `POST /sync/initiate`: Initiate cloud sync.
                *   Request: `{ userId: string, lastSyncTimestamp: string }`
                *   Response: `{ status: string }`
            *   `POST /sync/upload`: Upload data for sync.
                *   Request: `{ userId: string, data: any, type: string }`
                *   Response: `{ success: boolean }`
            *   `POST /sync/download`: Download data for sync.
                *   Request: `{ userId: string, type: string, lastSyncTimestamp: string }`
                *   Response: `{ data: any }`
            *   `POST /sync/resolve_conflict`: Resolve sync conflict.
                *   Request: `{ conflictId: string, resolution: string }`
                *   Response: `{ success: boolean }`
            *   `POST /rag/ingest_document`: Initiates document ingestion.
                *   Request: `{ userId: string, filePath: string, autoIngest: boolean }`
                *   Response: `{ success: boolean, documentId: string }`
        *   **WebSocket Endpoints (for real-time streaming on `ai_inference_server.ts`):**
            *   `/ws/audio_stream`: Bidirectional audio streaming for ASR, SER, and TTS.
                *   Client sends raw audio chunks (e.g., PCM `ArrayBuffer`).
                *   Server sends back real-time transcription updates, emotion data, and TTS audio chunks.
            *   `/ws/wake_word`: For continuous wake word detection.
                *   Client streams raw audio.
                *   Server sends `wakeWordDetected` event.

    *   **Node.js Backend (Internal APIs using C++ Native Addons and Python `child_process`):**
        *   **`audio_io_addon` (N-API):** Wraps PortAudio or direct Core Audio calls for low-latency audio input/output.
            *   `startCapture(sampleRate: number, channels: number, callback: (buffer: ArrayBuffer) => void)`
            *   `stopCapture()`
            *   `playAudio(buffer: ArrayBuffer, sampleRate: number, channels: number)`
            *   `getDevices(): { input: AudioDevice, output: AudioDevice }`
        *   **`ai_inference_addon` (N-API):** Wraps C++ AI libraries.
            *   `loadModel(type: 'llm' | 'asr' | 'tts' | 'ser' | 'wake_word' | 'embedding', modelPath: string, config?: object)`
            *   `llmGenerate(prompt: string, context: string, memories: string, personalityPrompt: string, emotionData: EmotionDataDTO): string`
            *   `asrTranscribe(audioBuffer: ArrayBuffer): string`
            *   `ttsSynthesize(text: string): ArrayBuffer`
            *   `serDetect(audioBuffer: ArrayBuffer): EmotionDataDTO`
            *   `wakeWordProcess(audioBuffer: ArrayBuffer): boolean` (returns true if detected)
            *   `embeddingGenerate(text: string): ArrayBuffer`
        *   **`sqlite_vec_addon` (N-API):** Wraps `sqlite-vec` for vector operations.
            *   `openDatabase(path: string, encryptionKey: string)`
            *   `closeDatabase()`
            *   `executeSQL(query: string, params: any): any`
            *   `searchVectors(embedding: ArrayBuffer, tableName: string, limit: number): { id: string, score: number }`
            *   `insertVector(tableName: string, id: string, embedding: ArrayBuffer): boolean`
            *   `updateVector(tableName: string, id: string, embedding: ArrayBuffer): boolean`
            *   `deleteVector(tableName: string, id: string): boolean`
            *   `runMigrations()`
        *   **Python Scripts (spawned via Node.js `child_process`):**
            *   `rag_ingestion.py`: For document parsing, chunking, and potentially calling embedding models if Python bindings are preferred.
            *   `model_downloader.py`: For managing AI model downloads.
            *   `ser_feature_extractor.py`: If `openSMILE` Python bindings are used for feature extraction before a custom Python-based SER classifier.

    *   **Authentication & Authorization:**
        *   **Local User Authentication:** User authentication is local, based on a user-derived key (e.g., passphrase or biometric unlock) used to decrypt the SQLite database (SQLCipher). No external authentication provider for MVP.
        *   **Authorization:** All data is user-specific. Access control is implicit based on the currently authenticated local user. Fine-grained permissions for memory visibility and data recording are managed via user settings in the `Users` table. Communication between frontend and backend is assumed to be secure due to local IPC (e.g., `localhost` connections, `child_process` pipes).
    *   **Error Handling:** Standard JavaScript `Error` objects for Node.js services. HTTP endpoints will use appropriate status codes (e.g., 400 for bad requests, 500 for internal errors). WebSocket errors will be communicated via specific error messages. C++ native addons will return error codes or throw exceptions that are caught and translated into Node.js `Error` objects.
    *   **Rate Limiting/Caching:** Not applicable for local-first, single-user desktop application. Caching will be handled at the UI layer for performance (e.g., in-memory caches for frequently accessed data).

4.  **Frontend Architecture (React Native for macOS with TypeScript)**
    *   **Component Hierarchy:**
        *   `App.tsx` (Root Component)
            *   `OnboardingScreen.tsx` (Conditional on `onboarding_completed` flag)
            *   `AppNavigator.tsx` (Handles main tab navigation)
                *   `ConversationScreen.tsx` (Chat interface)
                    *   `MessageBubble.tsx`
                    *   `VoiceInputIndicator.tsx`
                *   `JournalingScreen.tsx` (Daily Check-ins, Journal Entries)
                    *   `MoodSummaryCard.tsx`
                    *   `JournalEntryList.tsx`
                    *   `JournalEntryDetailView.tsx`
                *   `DeepTalkScreen.tsx` (Specialized conversation mode)
                *   `ProfileSettingsScreen.tsx` (User settings, privacy, personality)
                    *   `PersonalitySelectionView.tsx`
                    *   `PrivacyDashboardView.tsx`
                    *   `ModelManagementView.tsx`
                *   `SharedComponents/` (e.g., `CustomButton.tsx`, `LoadingIndicator.tsx`, `AlertView.tsx`)
    *   **Reusable Component Library:** Develop a consistent set of React Native components (Views, Text, Buttons, etc.) to ensure a cohesive UI/UX. Use TypeScript for strict type checking and better developer experience.
    *   **State Management:**
        *   `useState` and `useEffect` hooks for local component state.
        *   `useContext` or a library like `Zustand`/`Jotai` for global application state (e.g., user profile, active conversation, AI service status) to avoid prop drilling.
        *   `React Query` or `SWR` for data fetching and caching from the local Node.js backend.
    *   **Routing and Navigation:**
        *   `React Navigation` library for tab-based navigation and stack navigation within tabs.[3]
        *   Programmatic navigation for onboarding flow and specific actions (e.g., opening Deep Talk from a nudge).
    *   **Responsive Design:** Utilize React Native's `Flexbox` for layout and `Dimensions` API for adapting to screen size changes. Consider `Platform.OS === 'macos'` for macOS-specific UI adjustments.

5.  **Detailed CRUD Operations**

    *   **User (CRUD via `UserManager` in Frontend, interacts with `data_manager.ts` in Backend)**
        *   **Create:** `createUser(name: string, initialPreferences: UserPreferencesDTO)`
            *   **Validation:** `name` not empty, `initialPreferences` valid.
            *   **Required Fields:** `name`, `gdpr_ccpa_consent`, `emotion_recording_consent`, `memory_recording_consent`.
            *   **Flow:** Onboarding UI collects data -> `UserManager.createUser` calls `IPCService` -> `data_manager.ts` receives request -> `data_manager.ts` uses `sqlite_vec_addon` to insert into `Users` table.
        *   **Read:** `getUser(id: string)`, `getPrivacySettings(userId: string)`
            *   **Filtering:** By `id`.
            *   **Pagination/Sorting:** Not applicable for single user retrieval.
            *   **Flow:** Profile Settings UI requests user data -> `UserManager.getUser` calls `IPCService` -> `data_manager.ts` queries `Users` table.
        *   **Update:** `updateUser(id: string, updates: UserUpdateDTO)`, `updatePrivacySettings(userId: string, settings: PrivacySettingsDTO)`
            *   **Partial Updates:** `UserUpdateDTO` allows updating specific fields (e.g., `preferred_tone_style`, `sync_enabled`).
            *   **Validation:** Ensure updates are valid (e.g., `sync_frequency` is a valid enum value).
            *   **Flow:** Profile Settings UI modifies data -> `UserManager.updateUser` calls `IPCService` -> `data_manager.ts` updates `Users` table.
        *   **Delete:** `deleteUser(id: string)`
            *   **Soft Delete:** Not applicable for primary user.
            *   **Hard Delete:** Full deletion of user and all associated data (conversations, memories, journals, etc.) from the local database.
            *   **Flow:** Privacy Dashboard UI initiates deletion (with confirmation) -> `UserManager.deleteUser` calls `IPCService` -> `data_manager.ts` deletes from `Users` table and cascades deletes.

    *   **Conversation (CRUD via `ConversationManager` in Frontend, interacts with `data_manager.ts` in Backend)**
        *   **Create:** `startConversation(userId: string, personalityId: string)`
            *   **Validation:** `userId` and `personalityId` must exist.
            *   **Required Fields:** `user_id`, `start_time`, `personality_profile_id`.
            *   **Flow:** User initiates new conversation -> `ConversationManager.startConversation` calls `IPCService` -> `data_manager.ts` inserts into `Conversations`.
        *   **Read:** `getConversation(id: string)`, `getConversations(userId: string, pagination: PaginationDTO)`
            *   **Filtering:** By `id` or `user_id`.
            *   **Pagination:** `offset`, `limit` for conversation list.
            *   **Sorting:** By `start_time` (descending).
            *   **Flow:** Conversation History UI loads list -> `ConversationManager.getConversations` calls `IPCService` -> `data_manager.ts` queries `Conversations`.
        *   **Update:** `updateConversationTitle(id: string, title: string)`, `endConversation(id: string)`
            *   **Partial Updates:** Update title, set `end_time`.
            *   **Validation:** `title` not empty.
            *   **Flow:** User edits title or ends conversation -> `ConversationManager.updateConversationTitle`/`endConversation` calls `IPCService` -> `data_manager.ts` updates `Conversations`.
        *   **Delete:** `deleteConversation(id: string)`
            *   **Soft Delete:** Not applicable.
            *   **Hard Delete:** Deletes conversation and cascades to `Messages` associated.
            *   **Flow:** User deletes conversation from history -> `ConversationManager.deleteConversation` calls `IPCService` -> `data_manager.ts` deletes from `Conversations`.

    *   **Message (CRUD via `MessageManager` in Frontend, interacts with `data_manager.ts` in Backend)**
        *   **Create:** `addMessage(conversationId: string, sender: SenderType, content: string, audioPath?: string, emotions?: EmotionDataDTO)`
            *   **Validation:** `conversationId` exists, `content` not empty.
            *   **Required Fields:** `conversation_id`, `sender_type`, `content`, `timestamp`.
            *   **Flow:** User speaks/types or AI responds -> `MessageManager.addMessage` calls `IPCService` -> `data_manager.ts` inserts into `Messages`.
        *   **Read:** `getMessages(conversationId: string, pagination: PaginationDTO)`
            *   **Filtering:** By `conversationId`.
            *   **Pagination:** `offset`, `limit` for message history.
            *   **Sorting:** By `timestamp` (ascending).
            *   **Flow:** Conversation Screen loads messages -> `MessageManager.getMessages` calls `IPCService` -> `data_manager.ts` queries `Messages`.
        *   **Update:** `updateMessage(id: string, content: string)`
            *   **Partial Updates:** Only `content` can be updated.
            *   **Validation:** `content` not empty.
            *   **Flow:** User edits their message (e.g., typo correction) -> `MessageManager.updateMessage` calls `IPCService` -> `data_manager.ts` updates `Messages`.
        *   **Delete:** `deleteMessage(id: string)`
            *   **Soft Delete:** Not applicable.
            *   **Hard Delete:** Deletes specific message.
            *   **Flow:** User deletes a specific message from history -> `MessageManager.deleteMessage` calls `IPCService` -> `data_manager.ts` deletes from `Messages`.

    *   **Memory (CRUD via `MemoryManager` in Frontend, interacts with `data_manager.ts` and `ai_inference_server.ts` in Backend)**
        *   **Create:** `createMemory(userId: string, type: MemoryType, content: string, sourceId?: string, sourceType?: SourceType)`
            *   **Validation:** `userId` exists, `content` not empty.
            *   **Required Fields:** `user_id`, `type`, `content`, `embedding`, `timestamp`.
            *   **Flow:** `ConversationManager` or `JournalManager` identifies new memory -> `MemoryManager.createMemory` calls `IPCService` to `ai_inference_server.ts` for embedding generation -> `ai_inference_server.ts` calls `data_manager.ts` to insert into `Memories` and `sqlite-vec` virtual table.
        *   **Read:** `getMemory(id: string)`, `getMemories(userId: string, type?: MemoryType, isActive?: boolean, pagination?: PaginationDTO)`, `searchMemories(userId: string, query: string, limit: number)`
            *   **Filtering:** By `id`, `user_id`, `type`, `is_active`.
            *   **Pagination:** `offset`, `limit`.
            *   **Sorting:** By `timestamp` (descending) or `relevance_score` (for search).
            *   **Flow:** Deep Talk mode or Memory Management UI requests memories -> `MemoryManager.getMemories`/`searchMemories` calls `IPCService` to `ai_inference_server.ts` for query embedding -> `ai_inference_server.ts` calls `data_manager.ts` to search `sqlite-vec` and retrieve `Memories`.
        *   **Update:** `updateMemory(id: string, content?: string, isActive?: boolean)`, `consolidateMemories(userId: string, memoryIds: string, newContent: string)`
            *   **Partial Updates:** Update `content`, `is_active`.
            *   **Consolidation:** Combine multiple memories into one, updating content and potentially re-embedding.
            *   **Validation:** `content` not empty.
            *   **Flow:** User edits memory or AI consolidates memories -> `MemoryManager.updateMemory`/`consolidateMemories` calls `IPCService` to `ai_inference_server.ts` (if content changed for re-embedding) -> `ai_inference_server.ts` calls `data_manager.ts` to update `Memories`.
        *   **Delete:** `deleteMemory(id: string)`
            *   **Soft Delete:** Not applicable.
            *   **Hard Delete:** Deletes specific memory and its vector from `sqlite-vec`.
            *   **Flow:** User deletes memory from profile -> `MemoryManager.deleteMemory` calls `IPCService` -> `data_manager.ts` deletes from `Memories` and `sqlite-vec`.

    *   **JournalEntry (CRUD via `JournalManager` in Frontend, interacts with `data_manager.ts` in Backend)**
        *   **Create:** `createJournalEntry(userId: string, content: string, emotions?: EmotionDataDTO)`
            *   **Validation:** `userId` exists, `content` not empty.
            *   **Required Fields:** `user_id`, `timestamp`, `content`.
            *   **Flow:** User creates new journal entry -> `JournalManager.createJournalEntry` calls `IPCService` -> `data_manager.ts` inserts into `JournalEntries`.
        *   **Read:** `getJournalEntry(id: string)`, `getJournalEntries(userId: string, dateRange: DateRangeDTO, pagination: PaginationDTO)`
            *   **Filtering:** By `id`, `user_id`, `dateRange`.
            *   **Pagination:** `offset`, `limit`.
            *   **Sorting:** By `timestamp` (descending).
            *   **Flow:** Journaling UI loads entries -> `JournalManager.getJournalEntries` calls `IPCService` -> `data_manager.ts` queries `JournalEntries`.
        *   **Update:** `updateJournalEntry(id: string, content: string)`
            *   **Partial Updates:** Only `content`.
            *   **Validation:** `content` not empty.
            *   **Flow:** User edits journal entry -> `JournalManager.updateJournalEntry` calls `IPCService` -> `data_manager.ts` updates `JournalEntries`.
        *   **Delete:** `deleteJournalEntry(id: string)`
            *   **Soft Delete:** Not applicable.
            *   **Hard Delete:** Deletes specific journal entry.
            *   **Flow:** User deletes journal entry -> `JournalManager.deleteJournalEntry` calls `IPCService` -> `data_manager.ts` deletes from `JournalEntries`.

6.  **User Experience Flow**

    *   **Onboarding Flow:**
        1.  **App Launch (First Time):** `SairaReactNativeApp` detects no existing user profile.
        2.  **Welcome Screen:** Displays Saira's purpose and privacy commitment.
        3.  **Consent Screen:** Presents GDPR/CCPA, emotion recording, and memory recording consents. User must explicitly accept.
        4.  **Personality Selection:** User chooses an initial personality mode (e.g., "Best Friend", "Coach") from pre-defined options.
        5.  **Goal Setting:** User defines initial personal goals (e.g., "Improve sleep", "Reduce stress").
        6.  **Tone Style Preference:** User selects preferred AI response tone (e.g., empathetic, direct).
        7.  **Onboarding Complete:** Confirmation screen, transition to `MainTabView`.
    *   **Main Interaction Loop (Voice-first):**
        1.  **Idle State:** App is running in background, `WakeWordDetector` (Node.js backend service using C++ addon) is listening for "Hey Saira".
        2.  **Wake Word Detected:** `WakeWordDetector` notifies `ai_inference_server.ts` (via internal IPC), which sends a WebSocket message to `IPCService` in the frontend.
        3.  **Listening State:** UI displays active listening indicator (e.g., pulsing microphone icon). `IPCService` instructs `audio_processor.ts` (Node.js backend using C++ addon) to start capturing audio.
        4.  **Speech Input:** User speaks. Audio stream is sent via WebSocket to `ai_inference_server.ts`. `ai_inference_server.ts` streams audio to ASR (Whisper.cpp via C++ addon) and SER (openSMILE/SenseVoice via C++ addon).
        5.  **Real-time Transcription:** Transcribed text and detected emotions (arousal/valence) are streamed back to the frontend via WebSocket and displayed in `ConversationScreen`.
        6.  **User Stops Speaking:** Silence detection or explicit "stop listening" command.
        7.  **Processing State:** UI indicates AI is thinking. Full transcribed text and aggregated emotion data are sent to `ConversationScreen`'s ViewModel.
        8.  **LLM Inference:** `ConversationScreen`'s ViewModel sends prompt (with current conversation context and relevant memories from RAG) to `ai_inference_server.ts` (LLM via C++ addon).
        9.  **Response Generation:** LLM generates text response, adapting based on detected emotion and active personality profile.
        10. **TTS Synthesis & Playback:** LLM response text sent to `ai_inference_server.ts` (Piper via C++ addon) for synthesis -> audio data streamed back to frontend via WebSocket -> `audio_processor.ts` plays audio via C++ addon.
        11. **AI Response Display:** AI's spoken response is played, and its text appears in `ConversationScreen`.
        12. **Memory Formation:** `ConversationManager` processes conversation turn to extract and store new memories (semantic, episodic) via `MemoryManager`.
        13. **Idle State:** Return to listening for wake word.
    *   **Daily Check-ins & Journaling Flow:**
        1.  **Navigate to Tab:** User taps "Journal" tab.
        2.  **Mood Check-in:** User taps "How are you feeling?" button.
        3.  **Mood Picker:** Presents a visual mood picker (e.g., a grid of emojis or a slider for arousal/valence).
        4.  **Journal Entry:** User types or dictates a journal entry.
        5.  **Save:** Entry is saved to `JournalEntries` table via `JournalManager`.
        6.  **Mood Summary:** Daily mood summary is generated/updated based on entries and conversations.
    *   **Offline Sync Flow:**
        1.  **Settings UI:** User navigates to Profile Settings -> Sync.
        2.  **Enable Sync:** User toggles "Enable Cloud Sync".
        3.  **Authentication/Setup:** If first time, prompts for cloud service credentials (e.g., EteSync account).
        4.  **Initial Sync:** `SyncService.initiateSync` is called. UI shows progress.
        5.  **Conflict Resolution:** If conflicts arise during sync, UI presents options (e.g., "Keep Local", "Keep Cloud", "Review Manually").
        6.  **Background Sync:** Once enabled, `SyncService` schedules background syncs based on user-defined frequency. UI shows subtle indicator when syncing.

7.  **Security Considerations**

    *   **Authentication Flow:**
        *   **Local-only:** User provides a passphrase or uses biometric authentication (Touch ID/Face ID) on app launch.
        *   **Key Derivation:** This passphrase/biometric data is used to derive a key for SQLCipher to decrypt the local SQLite database. The key is never stored directly.
        *   **Re-authentication:** Re-authentication may be required after a period of inactivity or on sensitive actions (e.g., accessing privacy settings, data export).
    *   **Authorization Matrix (Local User):**
        *   **User:** Has full read/write access to all their own data.
        *   **AI:** Has read access to `Memories` (based on `memory_visibility_rules`), `Conversations`, `Messages`, `Goals`, `JournalEntries` for contextual understanding and RAG. Write access to `Memories`, `MoodSummaries`, `NudgeHistory`.
    *   **Data Validation and Sanitization:**
        *   **Input Validation:** All user inputs (text fields, settings) will be validated at the UI (React Native) and application logic (Node.js backend) layers to prevent invalid data from reaching the database.
        *   **Sanitization:** Text inputs will be sanitized to prevent injection attacks (e.g., SQL injection, although less critical for local SQLite, it's good practice).
    *   **Protection against Common Vulnerabilities:**
        *   **Data at Rest Encryption:** SQLite database encrypted using SQLCipher with a user-derived key. AI model files and embeddings stored in sandboxed app directories with file-level encryption.
        *   **IPC Security:** Communication between React Native and Node.js backend will be over `localhost` (e.g., HTTP/WebSocket). While this is generally secure for local processes, ensure proper validation of incoming requests to the Node.js server. If `child_process` is used, ensure secure communication channels (e.g., pipes). For macOS-specific background services, consider using XPC services (implemented in Objective-C/Swift/C++) and communicating with them from Node.js via a native addon, as this is the Apple-recommended secure IPC mechanism.
        *   **App Sandboxing:** The macOS application will be sandboxed, limiting its access to system resources and user data to only what is explicitly permitted.
        *   **System Integrity Protection (SIP):** Rely on macOS SIP to protect system files and processes.
        *   **App Transport Security (ATS):** Enforce ATS for all network connections (for optional cloud sync and model updates) to ensure secure communication (HTTPS).
        *   **Cryptographic Signatures:** AI model files downloaded via in-app updates will be verified with cryptographic signatures and checksums to ensure integrity and authenticity.
        *   **GDPR/CCPA Compliance:**
            *   **Consent Management:** Explicit, granular consent for data processing (emotion, memory recording) during onboarding and in settings.
            *   **Right to Access/Portability:** Provide a mechanism for users to export their data in a common, machine-readable format (e.g., JSON, CSV).
            *   **Right to Erasure (Right to Be Forgotten):** Implement a clear process for users to request and confirm deletion of all their data from the device and optionally from cloud sync.
            *   **Audit Logs:** Maintain local, encrypted audit logs of sensitive actions (e.g., data export, privacy setting changes, consent updates) for user review.

8.  **Testing Strategy**

    *   **Unit Test Requirements:**
        *   **React Native (`SairaReactNativeApp/__tests__`):** Jest for all React/TypeScript components, hooks, and services. Mock backend IPC calls.
        *   **Node.js (`SairaBackendServices/tests`):** Jest/Mocha for Node.js services (AI inference server, data manager, model manager). Mock C++ native addon calls.
        *   **Python (`SairaBackendServices/tests`):** Pytest for Python scripts (RAG ingestion, model downloader).
        *   **C++ Native Addons (`SairaBackendServices/native_addons/`):** Google Test/Catch2 for C++ code within native addons.
    *   **Integration Test Scenarios:**
        *   **Frontend-Backend IPC:** Test communication between React Native `IPCService` and Node.js backend (HTTP/WebSocket endpoints).
        *   **AI Pipeline:** Test the full flow from audio input (simulated) -> ASR -> LLM -> TTS, including emotion detection and memory retrieval, ensuring data passes correctly through Node.js and C++ addons.
        *   **Data Persistence:** Test CRUD operations through `DataStoreService` to `data_manager.ts` and `sqlite_vec_addon`, including encryption and `sqlite-vec` functionality.
        *   **Background Services:** Test the launching and communication with Node.js background processes (e.g., Wake Word Detector).
        *   **Offline Sync (Future):** Test sync initiation, delta processing, and conflict resolution with a mock cloud backend.
    *   **End-to-End Test Flows (e.g., Detox for React Native):**
        *   **Onboarding:** Simulate a new user onboarding, including consent and initial setup.
        *   **Full Conversation:** Simulate a complete voice conversation, including wake word, multiple turns, memory formation, and personality adaptation.
        *   **Journaling Workflow:** Create, view, edit, and delete journal entries.
        *   **Settings Changes:** Verify that changes in privacy settings, personality modes, and nudge preferences are correctly applied and persisted.
        *   **Model Update:** Simulate an in-app model download and hot-swapping.
    *   **Performance Testing Thresholds:**
        *   **Voice Latency:** End-to-end latency (user speaks to AI responds) < 2.0 seconds on MacBook M1 (acknowledging potential overhead from Node.js/Python wrappers).
        *   **ASR Latency:** Transcription of 10 seconds of audio < 300ms.[12]
        *   **TTS Latency:** Synthesis of 50 words < 600ms.
        *   **LLM Inference:** Response generation for typical prompt < 1.5 seconds.
        *   **RAG Retrieval:** Memory retrieval for RAG context < 200ms.
        *   **App Launch Time:** Cold launch < 5 seconds.
        *   **Memory/CPU Usage:** Monitor and optimize for low resource consumption, especially for background services.

9.  **Data Management**

    *   **Data Lifecycle Policies:**
        *   **Conversation History:** Stored indefinitely locally, with user options for manual deletion or automated archival/summarization.
        *   **Raw Audio:** Not stored by default for privacy. If user explicitly consents, stored temporarily for debugging/analysis and then purged after a defined period (e.g., 24 hours).
        *   **Memories:** Stored indefinitely, with user control over visibility (`is_active` flag).
        *   **Journal Entries:** Stored indefinitely.
        *   **AI Models:** Managed via in-app updates, older versions can be purged after successful update.
    *   **Caching Strategies:**
        *   **UI Data Caching:** Use in-memory caches (e.g., `Map` objects in JavaScript, or state management libraries) for frequently accessed UI data (e.g., recent conversation messages, mood summaries) to improve responsiveness.
        *   **AI Model Caching:** AI models (LLM, ASR, TTS, SER, Embedding) will be loaded into memory by the Node.js backend on demand and kept resident for subsequent inferences, leveraging Apple Silicon's unified memory architecture.
        *   **Database Query Caching:** SQLite's internal caching mechanisms (e.g., page cache) will be utilized. WAL mode will be enabled for improved concurrency and write performance].
    *   **Pagination and Infinite Scrolling:**
        *   Implement pagination for displaying long lists of data (e.g., conversation history, journal entries, memory list) to optimize memory usage and initial load times.
        *   Use infinite scrolling in UI lists to load more data as the user scrolls, providing a smooth experience.
    *   **Real-time Data Requirements:**
        *   **Audio Stream:** Real-time, low-latency audio capture and playback via Node.js C++ native addon for Core Audio.
        *   **ASR/SER Output:** Real-time streaming of transcription and emotion data from Node.js backend to React Native frontend via WebSockets.
        *   **LLM/TTS Output:** Streaming of LLM tokens and TTS audio from Node.js backend to React Native frontend via WebSockets for immediate response.
        *   **Wake Word:** Continuous, real-time monitoring in a low-power Node.js background process (using C++ native addon).

10. **Error Handling & Logging**
    *   **Structured Logging Format:**
        *   Implement a consistent, structured logging format (e.g., JSON-based) for all layers (React Native, Node.js, Python, C++ addons).
        *   Logs will include: `timestamp`, `level` (DEBUG, INFO, WARN, ERROR, FATAL), `component` (e.g., "ASRInference", "ConversationScreen"), `message`, `error_code` (if applicable), `stack_trace` (for errors), and relevant `metadata` (e.g., `user_id`, `conversation_id`).
        *   No sensitive user data (raw audio, conversation content) will be logged, only anonymized metadata.
    *   **Error Classification and Prioritization:**
        *   **Fatal Errors:** Application crashes, unrecoverable data corruption. Trigger immediate crash reporting (if user opts-in) and prompt for restart.
        *   **Critical Errors:** AI model loading failures, database corruption, persistent audio I/O issues. Display prominent error messages to the user, suggest troubleshooting steps.
        *   **Warning Errors:** Temporary network issues for sync, minor AI inference glitches. Log, but may not require immediate user intervention.
        *   **Informational/Debug:** General operational messages, performance metrics. Used for development and optional diagnostic bundles.
    *   **Monitoring and Alerting Thresholds (Local):**
        *   **Performance Metrics:** Monitor AI inference latency, CPU/GPU usage, memory footprint. Log deviations from expected thresholds.
        *   **Resource Usage:** Alert if CPU/memory usage exceeds predefined limits for extended periods.
        *   **Error Rates:** Track frequency of specific error types.
    *   **Recovery Mechanisms:**
        *   **Graceful Degradation:** If an AI model fails to load, attempt to use a fallback (e.g., a smaller, less accurate model) or inform the user.
        *   **Database Corruption:** Implement database integrity checks on launch. If corruption detected, attempt automatic repair or prompt user to restore from backup/sync.
        *   **Offline Operation:** Ensure core functionality remains available even if optional cloud sync fails or is disabled.
        *   **User-Initiated Diagnostics:** Provide a "Diagnostic Report" feature in settings, allowing users to generate an encrypted `.zip` file of anonymized logs and system information for support purposes. This will require explicit user consent before generation and sharing.
        *   **Model Rollback:** If a new AI model update causes instability, provide an option to revert to the previous stable version.

---

### Feature: Real-time Voice Interaction (ASR, SER, LLM, TTS, Wake Word)

**Feature Goal**
To enable natural, real-time conversational interaction with Saira through voice, including always-on wake word detection, accurate speech-to-text transcription, real-time emotion detection, intelligent LLM response generation, and natural text-to-speech synthesis. This feature is the core of Saira's "emotion-first" AI.

**Any API Relationships**
*   **Core Application Framework:** Receives voice input, displays transcription and AI responses, and manages the conversation flow.
*   **Local Long-Term Memory (RAG):** LLM leverages memories for contextual responses.
*   **Personality Modes & Customization:** LLM adapts responses based on active personality and user tone preferences.
*   **Daily Check-ins & Journaling:** Emotion data from voice interaction can feed into mood summaries.

**Detailed Feature Requirements**

1.  **Wake Word Detection:**
    *   **Always-on Listening:** Continuously monitor microphone input for a pre-defined wake word ("Hey Saira") with minimal CPU/battery consumption.
    *   **Low Latency Activation:** Activate the full voice processing pipeline immediately upon wake word detection.
    *   **Accuracy:** Minimize false positives (activating without the wake word) and false negatives (failing to detect the wake word).
2.  **Speech-to-Text (ASR):**
    *   **Real-time Transcription:** Convert spoken audio into text with low latency, displaying partial results as the user speaks.
    *   **Accuracy:** High accuracy for English speech, even in varying acoustic environments.
    *   **Offline Capability:** Perform all transcription locally on the device.
3.  **Speech Emotion Recognition (SER):**
    *   **Real-time Emotion Detection:** Analyze speech audio to detect continuous emotional states (arousal and valence) in real-time.
    *   **Granular Output:** Provide continuous arousal (0-1) and valence (-1 to 1) values, and potentially categorical emotions (e.g., happy, sad, neutral).
    *   **Integration with LLM:** Feed detected emotions to the LLM to influence its response generation.
4.  **Large Language Model (LLM) Interaction:**
    *   **Natural Language Understanding:** Interpret user's intent and context from transcribed text.
    *   **Contextual Response Generation:** Generate coherent, relevant, and natural-sounding text responses.
    *   **Personality Adaptation:** Adjust response style, tone, and vocabulary based on the active personality mode (e.g., "Mom," "Coach").
    *   **Emotional Responsiveness:** Adapt LLM responses based on the user's detected emotional state (e.g., offer comfort if sadness is detected).
    *   **Long-Term Memory Integration (RAG):** Incorporate relevant memories and goals from the local knowledge base into LLM's context for personalized responses.
5.  **Text-to-Speech (TTS):**
    *   **Natural Sounding Voice:** Synthesize AI's text responses into natural-sounding speech.
    *   **Real-time Streaming:** Begin playing audio as soon as the first part of the response is generated, minimizing perceived latency.
    *   **Offline Capability:** Perform all TTS locally on the device.
    *   **Voice Adaptation:** Potentially adjust AI's voice tone/emotion based on the personality mode or user's emotional state.

**Detailed Implementation Guide**

1.  **System Architecture Overview**
    *   **High-level Architecture:** This feature is primarily handled by the `SairaBackendServices` (Node.js/Python/C++ addons) due to its performance-critical nature. The `SairaReactNativeApp` (React Native) acts as the client, sending audio input and receiving text/audio output via a local WebSocket server.
    *   **Technology Stack:**
        *   **Frontend (UI):** React Native for macOS (TypeScript) for microphone access (via native module), displaying real-time transcription, and playing back audio.
        *   **Backend (Orchestration & IPC):** Node.js (`ai_inference_server.ts`, `audio_processor.ts`). Node.js will manage the audio streams, orchestrate calls to AI models, and handle WebSocket communication with the frontend. Node.js is generally faster than Python for I/O-bound tasks and concurrent API requests.
        *   **Core AI Libraries (via C++ Native Addons or Python Bindings):**
            *   **Wake Word:** Porcupine (C library) via Node.js C++ native addon (`ai_inference_addon`) or Python binding (`pvporcupine`) exposed via a local Python server. Porcupine is compact, efficient, and cross-platform. Note: Porcupine requires a commercial license for commercial use.
            *   **ASR:** `whisper.cpp` (C/C++) via Node.js C++ native addon (`ai_inference_addon` using `nodejs-whisper`) or Python binding (`pywhispercpp`) exposed via a local Python server. `whisper.cpp` is optimized for offline use and Apple Silicon.[13, 12, 14]
            *   **SER:** `openSMILE` (C++) for feature extraction and a custom MLP model (C++ or ONNX via C++ addon) for classification. SenseVoice (C++) for direct emotion detection. All via Node.js C++ native addon (`ai_inference_addon`) or Python bindings (`openSMILE` Python package) exposed via a local Python server. SER aims for granular arousal/valence output].
            *   **LLM:** Mistral 7B (Q4_0) via `llama.cpp` (C/C++) wrapped by Node.js C++ native addon (`ai_inference_addon` using `node-llama-cpp`) or Python binding (`llama-cpp-python`) exposed via a local Python server. `llama.cpp` is optimized for local inference. Note: Python bindings can be slower than direct C++ calls.
            *   **TTS:** Piper (C++) via Node.js C++ native addon (`ai_inference_addon`) or Python binding (`RealtimeTTS` [15]) exposed via a local Python server. Piper is lightweight and real-time.
        *   **Audio I/O:** macOS Core Audio API via a Node.js C++ native addon (`audio_io_addon`) wrapping PortAudio. This is critical as Node.js/Python wrappers for low-latency audio I/O on macOS have documented stability issues or incomplete functionality.
    *   **Deployment Architecture:** The Node.js backend (`ai_inference_server.ts`, `audio_processor.ts`) will run as a persistent background process, potentially launched by the main React Native app. The C++ native addons will be compiled and bundled with the Node.js runtime. Python scripts will be bundled and executed by the Node.js process using `child_process.spawn` or `exec`.
    *   **Integration Points:**
        *   **React Native:** Uses `react-native-webrtc` or a custom native module (Objective-C/Swift) for microphone access and WebSocket client.
        *   **Node.js Backend:** Communicates with C++ native addons via N-API. Uses `ws` (WebSocket library) for real-time communication with the frontend. Spawns Python processes for specific AI tasks.

2.  **Database Schema Design**
    (Refer to the "Core Application Framework" feature for `Users`, `Conversations`, `Messages`, `Memories`, `PersonalityProfiles` tables, as they are central to storing conversational data and user preferences that influence AI behavior.)

3.  **Comprehensive API Design**
    *   **Frontend-Backend IPC (WebSocket `ai_inference_server.ts`):**
        *   **Client (Frontend) -> Server (Backend):**
            *   `start_audio_stream`: Initiates audio capture and processing.
                *   Payload: `{ userId: string, conversationId: string, personalityId: string }`
            *   `audio_chunk`: Streams raw audio data (e.g., PCM `ArrayBuffer`).
                *   Payload: `ArrayBuffer`
            *   `stop_audio_stream`: Stops audio capture and processing.
                *   Payload: `{}`
            *   `send_text_input`: Sends text input (for text-based interaction or corrections).
                *   Payload: `{ userId: string, conversationId: string, text: string }`
        *   **Server (Backend) -> Client (Frontend):**
            *   `transcription_update`: Partial or full ASR transcription.
                *   Payload: `{ text: string, isFinal: boolean }`
            *   `emotion_update`: Real-time emotion data.
                *   Payload: `{ arousal: number, valence: number, timestamp: number }`
            *   `ai_response_text`: LLM's text response.
                *   Payload: `{ text: string }`
            *   `ai_response_audio_chunk`: Streams TTS audio data.
                *   Payload: `ArrayBuffer`
            *   `wake_word_detected`: Notification that wake word was detected.
                *   Payload: `{}`
            *   `error`: General error message.
                *   Payload: `{ code: string, message: string }`
    *   **Node.js Backend (Internal APIs using C++ Native Addons and Python `child_process`):**
        *   **`audio_io_addon` (N-API):**
            *   `startCapture(sampleRate: number, channels: number, callback: (buffer: ArrayBuffer) => void)`
            *   `stopCapture()`
            *   `playAudio(buffer: ArrayBuffer, sampleRate: number, channels: number)`
            *   `getDevices(): { input: AudioDevice, output: AudioDevice }`
        *   **`ai_inference_addon` (N-API):**
            *   `loadModel(type: 'llm' | 'asr' | 'tts' | 'ser' | 'wake_word' | 'embedding', modelPath: string, config?: object)`
            *   `llmGenerate(prompt: string, context: string, memories: string, personalityPrompt: string, emotionData: EmotionDataDTO): string`
            *   `asrTranscribe(audioBuffer: ArrayBuffer): string`
            *   `ttsSynthesize(text: string): ArrayBuffer`
            *   `serDetect(audioBuffer: ArrayBuffer): EmotionDataDTO`
            *   `wakeWordProcess(audioBuffer: ArrayBuffer): boolean` (returns true if detected)
            *   `embeddingGenerate(text: string): ArrayBuffer`
    *   **Authentication & Authorization:** (Refer to "Core Application Framework" feature.)
    *   **Error Handling:** WebSocket errors will be sent to the frontend. Internal Node.js errors will be logged. C++ addon errors will be propagated as Node.js exceptions.
    *   **Rate Limiting/Caching:** Not applicable for real-time local processing.

4.  **Frontend Architecture (React Native for macOS)**
    *   **`ConversationScreen.tsx`:**
        *   Manages the UI state for the chat interface.
        *   Uses `react-native-microphone-wrapper` (or similar native module) for microphone access.
        *   Establishes a WebSocket connection to `ai_inference_server.ts`.
        *   Sends audio chunks and receives transcription/AI responses.
        *   Displays real-time transcription, AI text, and plays AI audio.
    *   **`VoiceInputIndicator.tsx`:** A reusable component to visually represent active listening, processing, and speaking states.
    *   **State Management:** Local component state for input text, chat messages. Global state for AI service status (listening, thinking, speaking).
    *   **Routing:** Direct navigation to `ConversationScreen` from `MainTabView`.

5.  **Detailed CRUD Operations**
    *   **Conversation (Interacts with `ConversationManager` in Frontend, `data_manager.ts` in Backend):**
        *   **Create:** A new conversation is implicitly created when the user starts interacting with the AI.
        *   **Read:** Messages are read from the `Messages` table to display conversation history.
        *   **Update:** Conversation title can be updated.
        *   **Delete:** Entire conversation can be deleted.
    *   **Message (Interacts with `MessageManager` in Frontend, `data_manager.ts` in Backend):**
        *   **Create:** User's spoken/typed input and AI's responses are added as new messages.
        *   **Read:** Messages are retrieved for display.
        *   **Update:** User can edit their own messages (e.g., journal entries).
        *   **Delete:** Individual messages can be deleted.
    *   **Memory (Interacts with `MemoryManager` in Frontend, `ai_inference_server.ts` and `data_manager.ts` in Backend):**
        *   **Create:** New memories are extracted from conversations and stored. This involves calling `ai_inference_server.ts` for embedding generation and then `data_manager.ts` for storage.
        *   **Read:** Memories are retrieved for RAG context and for user review in settings.
        *   **Update:** Memories can be updated (e.g., `is_active` status).
        *   **Delete:** Memories can be deleted by the user.

6.  **User Experience Flow**
    (Refer to "Core Application Framework" feature for the detailed voice interaction loop.)

7.  **Security Considerations**
    *   **Microphone Access:** React Native will request microphone permission from the user via standard macOS permission prompts.
    *   **Data Flow:** Raw audio data is streamed directly from the React Native app to the local Node.js backend via WebSocket. This data is processed locally and never leaves the device unless optional cloud sync is enabled.
    *   **AI Model Integrity:** AI models downloaded via in-app updates will be verified with checksums and cryptographic signatures to prevent tampering.
    *   **Process Isolation:** The Node.js backend process and its C++ addons will run in a sandboxed environment where possible, limiting their access to system resources.
    *   **Privacy:** Explicit user consent for emotion and memory recording is paramount. If consent is not given, these features will be disabled, and relevant data will not be processed or stored.

8.  **Testing Strategy**
    *   **Unit Tests:**
        *   React Native: Test UI components, state management, and service calls in isolation.
        *   Node.js: Test individual backend service modules (e.g., `ai_inference_server.ts` functions, `data_manager.ts` methods).
        *   Python: Test Python scripts (RAG ingestion, model downloader).
        *   C++ Addons: Test C++ functions within addons for correctness and performance.
    *   **Integration Tests:**
        *   **Audio Pipeline:** Simulate audio input, verify ASR output, SER output, LLM response, and TTS audio output.
        *   **IPC:** Test WebSocket communication between frontend and backend.
        *   **AI Model Loading:** Verify models load correctly and perform basic inference.
    *   **End-to-End Tests:** Simulate full voice conversations, including wake word detection, multi-turn interactions, and verification of correct AI responses and memory formation.
    *   **Performance Tests:** Measure end-to-end latency for voice interactions, ASR/TTS/LLM inference times, and resource consumption on target MacBook M1 devices.

9.  **Data Management**
    *   **Audio Data:** Raw audio is processed in real-time and generally not persisted. If explicit user consent is given for audio recording (e.g., for debugging or future features), it will be stored temporarily and securely, then purged.
    *   **AI Model Storage:** Models are stored in a dedicated, sandboxed application directory.
    *   **Memory Management:** LLM context (short-term memory) is managed in-memory by the Node.js backend. Long-term memories are stored in SQLite with `sqlite-vec`.
    *   **Real-time Data Flow:** Audio streams, ASR/SER outputs, and TTS audio are handled as continuous data streams via WebSockets for low latency.

10. **Error Handling & Logging**
    *   **Structured Logging:** Implement structured logging across all layers (React Native, Node.js, Python, C++ addons). Logs will be stored locally and encrypted.
    *   **Error Propagation:** Errors from C++ addons will be caught in Node.js, translated, and propagated to the React Native frontend via WebSocket messages.
    *   **User Feedback:** Clear, user-friendly error messages will be displayed in the UI for critical issues (e.g., "Microphone not found," "AI model failed to load").
    *   **Diagnostic Bundles:** Allow users to generate encrypted diagnostic bundles containing anonymized logs for support.

---
## Feature Specifications (Continued)

### Feature: Local Long-Term Memory (RAG)

**Feature Goal**
To enable Saira to remember past conversations, track user goals, and build a comprehensive, evolving long-term memory about the user's life. This memory will be used to ground LLM responses, providing personalized and contextually relevant interactions.

**Any API Relationships**
*   **Core Application Framework:** Provides UI for memory visibility, goal management, and RAG document ingestion.
*   **Real-time Voice Interaction:** LLM leverages memories for contextual responses. New memories are formed from conversations.
*   **Daily Check-ins & Journaling:** Journal entries can be sources for new memories.

**Detailed Feature Requirements**

1.  **Memory Formation:**
    *   **Automatic Extraction:** Automatically extract key facts, preferences, and significant events from user conversations and journal entries.
    *   **Categorization:** Classify extracted memories into types (semantic, episodic, procedural).
    *   **Embedding Generation:** Generate vector embeddings for each memory using a local embedding model.
2.  **Memory Storage and Retrieval:**
    *   **Local Vector Database:** Store memories and their embeddings in a local SQLite database with `sqlite-vec` extension.
    *   **Semantic Search:** Enable efficient retrieval of relevant memories based on semantic similarity to the current conversation context or user query.
    *   **Filtering:** Allow filtering memories by type, source, or user-defined tags.
3.  **LLM Integration (Retrieval-Augmented Generation - RAG):**
    *   **Context Augmentation:** Dynamically retrieve a small set of highly relevant memories based on the current conversation turn.
    *   **Prompt Injection:** Inject retrieved memories into the LLM's prompt to provide additional context and ground its responses.
    *   **Relevance Scoring:** Prioritize memories based on a relevance score (e.g., cosine similarity).
4.  **User Control over Memory:**
    *   **Memory Visibility Dashboard:** Provide a UI for users to view, search, and manage their stored memories.
    *   **Edit/Delete Memories:** Allow users to edit the content of memories or delete them.
    *   **Active/Inactive Toggle:** Enable users to toggle the `is_active` status of memories, controlling whether they are used by the LLM.
5.  **Goal Tracking:**
    *   **Goal Creation/Editing:** Allow users to define, edit, and track personal goals.
    *   **Progress Updates:** Enable manual or AI-assisted updates to goal progress.
    *   **AI Integration:** LLM can proactively ask about goals, offer motivation, or suggest relevant actions based on goals.
6.  **RAG Document Ingestion:**
    *   **Manual Import:** Allow users to manually import documents (PDFs, text files, web clippings) to expand the knowledge base.
    *   **Optional Auto-Ingestion:** With explicit user consent, allow the app to scan and process local files from user-configured folders.
    *   **Background Processing:** Chunking and embedding generation for new documents will run asynchronously in the background.

**Detailed Implementation Guide**

1.  **System Architecture Overview**
    *   **High-level Architecture:** This feature spans both the React Native frontend (for UI management of memories/goals) and the Node.js/Python backend. The Node.js backend orchestrates the RAG process, utilizing Python for heavy data processing (chunking, embedding generation) and Node.js C++ addons for SQLite/vector search.
    *   **Technology Stack:**
        *   **Frontend (UI):** React Native for macOS (TypeScript) for Memory Visibility Dashboard, Goal Management UI, and Document Ingestion UI.
        *   **Backend (Orchestration):** Node.js (`ai_inference_server.ts`, `data_manager.ts`, `model_manager.ts`).
        *   **Embedding Generation:** Local embedding model (e.g., MiniLM) via Node.js C++ native addon (`ai_inference_addon`) or a Python script (`EmbeddingGenerator.py`) called by Node.js. `llama.cpp` can be used to generate embeddings via its server mode, which can be called from Node.js or Python.[3]
        *   **Vector Database:** SQLite with `sqlite-vec` extension via Node.js C++ native addon (`sqlite_vec_addon`). `sqlite-vec` is a C library that extends SQLite for vector search. Node.js packages like `better-sqlite3` can load `sqlite-vec`. `op-sqlite` for React Native also supports `sqlite-vec`.[4, 5, 6]
        *   **Document Processing (Chunking):** Python (`rag_ingestion.py`) for parsing and chunking documents. Python's rich ecosystem of libraries (e.g., `LangChain` for document loaders and text splitters, `NLTK` for text processing) makes it well-suited for this task.
        *   **IPC:** Local HTTP/WebSocket for real-time RAG queries, `child_process` for spawning Python scripts for background ingestion.
    *   **Deployment Architecture:** Python scripts will be bundled with the Node.js backend. The `sqlite-vec` extension will be loaded by the Node.js SQLite binding.
    *   **Integration Points:**
        *   **React Native:** Calls `MemoryManager` and `GoalManager` services.
        *   **Node.js Backend:** Calls C++ addons for embedding and vector search. Spawns Python processes for document ingestion.

2.  **Database Schema Design**
    (Refer to the "Core Application Framework" feature for `Memories` and `Goals` tables. The `Memories` table includes an `embedding` BLOB column and is linked to a `sqlite-vec` virtual table.)

3.  **Comprehensive API Design**
    *   **Frontend-Backend IPC (HTTP Endpoints on `ai_inference_server.ts`):**
        *   **`POST /ai/embeddings/generate`:** (Already defined in Voice Interaction)
        *   **`POST /data/search_vectors`:** (Already defined in Voice Interaction)
        *   **`POST /rag/ingest_document`:** Initiates document ingestion.
            *   Request: `{ userId: string, filePath: string, autoIngest: boolean }`
            *   Response: `{ success: boolean, documentId: string }`
        *   **`GET /memories/search`:** Semantic search for memories.
            *   Request: `{ userId: string, query: string, limit: number }`
            *   Response: `{ memories: MemoryDTO }`
    *   **Node.js Backend (Internal APIs using C++ Native Addons and Python `child_process`):**
        *   **`ai_inference_addon` (N-API):**
            *   `embeddingGenerate(text: string): ArrayBuffer` (wraps `llama.cpp` embedding server or other C++ embedding model).
        *   **`sqlite_vec_addon` (N-API):**
            *   `searchVectors(embedding: ArrayBuffer, tableName: string, limit: number): { id: string, score: number }`
            *   `insertVector(tableName: string, id: string, embedding: ArrayBuffer): boolean`
            *   `updateVector(tableName: string, id: string, embedding: ArrayBuffer): boolean`
            *   `deleteVector(tableName: string, id: string): boolean`
        *   **`rag_ingestion.py` (Python script, spawned by Node.js `child_process`):**
            *   This script will receive `filePath` and `userId` as command-line arguments.
            *   It will read the document, chunk it, and then make HTTP calls back to the Node.js `ai_inference_server.ts` to generate embeddings and store memories.
            *   Pseudocode:
                ```python
                # rag_ingestion.py
                import sys
                import json
                import requests # For HTTP calls back to Node.js server
                # Assuming document parsing and chunking libraries (e.g., LangChain, NLTK)
                
                NODE_SERVER_URL = "http://localhost:XXXX" # Replace with actual Node.js server URL
                
                def process_document(file_path, user_id):
                    # 1. Read document content
                    content = read_file(file_path) # Implement read_file based on file_type (PDF, TXT, etc.)
                    
                    # 2. Chunk text
                    # Example using a hypothetical chunking function
                    chunks = chunk_text(content, chunk_size=500, overlap=50) 
                    
                    # 3. Process each chunk
                    for chunk in chunks:
                        # Call Node.js backend for embedding generation
                        embedding_response = requests.post(f"{NODE_SERVER_URL}/ai/embeddings/generate", json={"text": chunk})
                        embedding_response.raise_for_status()
                        embedding_data = embedding_response.json()["embedding"]
                        
                        # Call Node.js backend to store memory (chunk + embedding)
                        memory_payload = {
                            "userId": user_id,
                            "type": "semantic", # Or derive type
                            "content": chunk,
                            "embedding": embedding_data,
                            "sourceType": "document",
                            "sourceId": file_path # Or a unique document ID
                        }
                        store_memory_response = requests.post(f"{NODE_SERVER_URL}/data/create_memory", json=memory_payload)
                        store_memory_response.raise_for_status()
                        print(f"Stored memory for chunk: {chunk[:50]}...")
                
                if __name__ == "__main__":
                    file_path = sys.argv[1]
                    user_id = sys.argv[2]
                    process_document(file_path, user_id)
                ```
    *   **Authentication & Authorization:** (Refer to "Core Application Framework" feature.)
    *   **Error Handling:** Errors during embedding generation or vector search will be logged and potentially surfaced to the user if they impact core functionality. Document ingestion errors (e.g., malformed PDF) will be logged and reported in the UI.
    *   **Rate Limiting/Caching:** Not applicable for local-first.

4.  **Frontend Architecture (React Native for macOS)**
    *   **`DeepTalkScreen.tsx`:**
        *   A specialized chat interface that emphasizes RAG.
        *   When user asks a question, it first performs a semantic search on memories by calling `IPCService` to `ai_inference_server.ts`'s `/memories/search` endpoint.
        *   The retrieved memories are then passed as context to the LLM.
    *   **`ProfileSettingsScreen.tsx` (Memory Visibility & Goal Management):**
        *   Displays lists of memories and goals.
        *   Provides search/filter functionality for memories.
        *   Allows editing/deleting memories and goals.
        *   Includes a "Document Ingestion" section for manual import and auto-ingestion settings.
        *   Uses `react-native-document-picker` or similar for file selection.
    *   **State Management:** Local state for search queries, selected memories/goals. Global state for RAG processing status (e.g., "Indexing documents...").
    *   **Routing:** Direct navigation to `DeepTalkScreen` and `ProfileSettingsScreen`.

5.  **Detailed CRUD Operations**
    *   **Memory (Interacts with `MemoryManager` in Frontend, `ai_inference_server.ts` and `data_manager.ts` in Backend):**
        *   **Create:**
            *   **Automatic:** Triggered by `ConversationManager` or `JournalManager` after a conversation turn or journal entry. Calls `IPCService` to `ai_inference_server.ts`'s `/ai/embeddings/generate` and then `data_manager.ts` to insert into `Memories` and `sqlite-vec`.
            *   **Manual (via Document Ingestion):** User imports a document. Frontend calls `ai_inference_server.ts`'s `/rag/ingest_document`. Backend spawns `rag_ingestion.py` which then calls back to `ai_inference_server.ts` to create memories.
            *   **Validation:** `userId` exists, `content` not empty.
            *   **Required Fields:** `user_id`, `type`, `content`, `embedding`, `timestamp`.
        *   **Read:** `getMemories`, `searchMemories` for display in UI and for RAG.
            *   **Filtering:** By `id`, `user_id`, `type`, `is_active`.
            *   **Pagination:** `offset`, `limit`.
            *   **Sorting:** By `timestamp` (descending) or `relevance_score` (for search).
            *   **Flow:** UI requests memories -> `MemoryManager.getMemories`/`searchMemories` calls `IPCService` to `ai_inference_server.ts` for query embedding (if search) -> `ai_inference_server.ts` calls `data_manager.ts` to search `sqlite-vec` and retrieve `Memories`.
        *   **Update:** `updateMemory(id: string, content?: string, isActive?: boolean)`, `consolidateMemories(userId: string, memoryIds: string, newContent: string)`
            *   **Partial Updates:** Update `content`, `is_active`.
            *   **Consolidation:** Combine multiple memories into one, updating content and potentially re-embedding.
            *   **Validation:** `content` not empty.
            *   **Flow:** User edits memory or AI consolidates memories -> `MemoryManager.updateMemory`/`consolidateMemories` calls `IPCService` to `ai_inference_server.ts` (if content changed for re-embedding) -> `ai_inference_server.ts` calls `data_manager.ts` to update `Memories`.
        *   **Delete:** `deleteMemory(id: string)`
            *   **Soft Delete:** Not applicable.
            *   **Hard Delete:** Deletes specific memory and its vector from `sqlite-vec`.
            *   **Flow:** User deletes memory from profile -> `MemoryManager.deleteMemory` calls `IPCService` -> `data_manager.ts` deletes from `Memories` and `sqlite-vec`.
    *   **Goal (Interacts with `GoalManager` in Frontend, `data_manager.ts` in Backend):**
        *   **Create:** `createGoal` via UI.
        *   **Read:** `getGoals` for display.
        *   **Update:** `updateGoal` (e.g., status, progress, description).
        *   **Delete:** `deleteGoal` (hard delete).

6.  **User Experience Flow**
    *   **RAG-Enhanced Conversation:**
        1.  User asks a question in `ConversationScreen` or `DeepTalkScreen`.
        2.  Frontend sends query to `ai_inference_server.ts`.
        3.  Backend generates embedding for query.
        4.  Backend performs `sqlite-vec` search on `Memories` table. Performance for `sqlite-vec` with 250,000 records on M1 Max MacBook can be slow, requiring performance tuning.
        5.  Top-k relevant memories are retrieved.
        6.  These memories are injected into the LLM prompt.
        7.  LLM generates response, grounded by retrieved memories.
    *   **Memory Management:**
        1.  User navigates to Profile Settings -> Memories.
        2.  Displays a list of all memories.
        3.  User can search, filter, or toggle `is_active` for memories.
        4.  User can tap on a memory to view/edit its content.
    *   **Document Ingestion:**
        1.  User navigates to Profile Settings -> Document Ingestion.
        2.  User selects files for manual import or configures auto-ingestion folders.
        3.  Frontend sends request to `ai_inference_server.ts`'s `/rag/ingest_document` endpoint.
        4.  Backend spawns `rag_ingestion.py` in a child process.
        5.  Python script processes documents, sends chunks to Node.js for embedding and storage.
        6.  UI displays "Indexing..." status and completion notification.

7.  **Security Considerations**
    *   **Data Encryption:** All memories and embeddings stored in SQLite will be encrypted using SQLCipher.
    *   **File System Access:** Auto-ingestion will require explicit user consent for file system access to specified directories. The app will operate within macOS Sandbox entitlements.
    *   **IPC for RAG:** Communication between Node.js and Python for RAG processing will use secure `child_process` pipes or local sockets.
    *   **Privacy:** Ensure that only user-consented data is used for memory formation and RAG. Memory visibility controls are critical for user privacy.

8.  **Testing Strategy**
    *   **Unit Tests:** Test `rag_ingestion.py` for correct chunking and embedding generation (mocking embedding service). Test `data_manager.ts` for `sqlite-vec` interactions.
    *   **Integration Tests:**
        *   **Full RAG Pipeline:** Test from document ingestion -> embedding -> storage -> retrieval -> LLM context injection.
        *   **Memory CRUD:** Verify all memory CRUD operations function correctly, including `sqlite-vec` updates.
    *   **End-to-End Tests:** Simulate user importing documents, asking questions that require RAG, and verifying the LLM's grounded responses.
    *   **Performance Tests:** Measure latency for RAG queries (embedding query + vector search), and throughput for document ingestion. Monitor memory usage during large ingestion tasks.

9.  **Data Management**
    *   **Memory Storage:** Memories and their embeddings are stored persistently in the encrypted SQLite database.
    *   **RAG Document Storage:** Original documents are not necessarily stored in the database; only their chunked text and embeddings are.
    *   **Indexing Strategy:** `sqlite-vec` provides efficient brute-force vector search. For very large datasets (e.g., 250,000+ records), performance tuning may be required.
    *   **Data Lifecycle:** Users have control over deleting memories. Old or less relevant memories could potentially be archived or summarized by the AI over time (future feature).

10. **Error Handling & Logging**
    *   **RAG-Specific Errors:** Log errors during document parsing, embedding generation failures, or `sqlite-vec` issues.
    *   **User Feedback:** Inform users about failed document imports or indexing issues.
    *   **Performance Monitoring:** Log RAG query times and memory consumption to identify bottlenecks.

---

### Feature: Offline-First Data Synchronization

**Feature Goal**
To provide seamless data continuity across user devices (Mac, future iOS) by offering optional, end-to-end encrypted cloud synchronization of user data (memories, preferences, emotional data), ensuring privacy and data availability even when offline.

**Any API Relationships**
*   **Core Application Framework:** Provides UI for sync configuration and status.
*   **Local Long-Term Memory (RAG):** Memories and goals are key data points for synchronization.
*   **Daily Check-ins & Journaling:** Journal entries and mood summaries are synchronized.
*   **Personality Modes & Customization:** Personality profiles and user preferences are synchronized.

**Detailed Feature Requirements**

1.  **Optional Cloud Sync:**
    *   **User Opt-in:** Sync is strictly opt-in, requiring explicit user consent.
    *   **Privacy-First:** All data synchronized must be end-to-end encrypted (E2EE), ensuring zero-knowledge for the cloud provider.
2.  **Data Selection for Sync:**
    *   **Core Data:** Synchronize user profiles, conversation summaries (not full content by default), memories, goals, journal entries, mood summaries, and personality profiles.
    *   **Exclusions:** Raw audio data and full conversation transcripts are *not* synced by default due to privacy and size concerns, unless explicitly configured by the user (future feature).
3.  **Synchronization Protocol:**
    *   **Delta Sync:** Only synchronize changes (deltas) to minimize bandwidth and improve efficiency.
    *   **Change Journal:** Maintain a local change journal to track modifications for efficient delta calculation.
    *   **Conflict Resolution:** Implement conflict resolution strategies (e.g., timestamp-based "last write wins," or user-guided manual review for critical conflicts).
4.  **User Control & Transparency:**
    *   **Sync Frequency:** Allow users to configure sync frequency (e.g., manual, daily, weekly, on app close).
    *   **Sync Status:** Display clear sync status indicators (e.g., "Synced," "Syncing," "Offline," "Conflicts").
    *   **Audit Logs:** Record sync events in local audit logs for user review.
5.  **Error Handling & Recovery:**
    *   **Robustness:** Handle network interruptions gracefully, with retry mechanisms.
    *   **Data Integrity:** Ensure data integrity during sync, preventing data loss or corruption.
    *   **Recovery Key:** Provide a mechanism for users to generate and securely store a recovery key for their E2EE data.

**Detailed Implementation Guide**

1.  **System Architecture Overview**
    *   **High-level Architecture:** The `SyncService.ts` in the React Native frontend will orchestrate the sync process. It will communicate with a local Node.js `SyncManager` service (within `SairaBackendServices/src/node_services/`) which handles the E2EE and interaction with the chosen cloud sync provider.
    *   **Technology Stack:**
        *   **Frontend (UI):** React Native for macOS (TypeScript) for sync settings UI, status indicators, and conflict resolution modals.
        *   **Backend (Orchestration & E2EE):** Node.js (TypeScript) for managing the sync process, including E2EE logic. Node.js has robust cryptographic libraries (e.g., Node.js `crypto` module, `libsodium-wrappers` for advanced crypto).
        *   **Local Database:** SQLite with SQLCipher for encrypted local data storage.
        *   **Cloud Sync Protocol:** Utilize an existing open-source E2EE sync protocol like EteSync (which offers an SDK and backend) or implement a custom protocol. EteSync is open-source, provides zero-knowledge E2EE, and maintains a change journal.[7, 8, 9] Dropbox also offers E2EE for sensitive files.[10, 11]
        *   **IPC:** Local HTTP/WebSocket between React Native and Node.js for triggering syncs and receiving status updates.
    *   **Deployment Architecture:** The Node.js `SyncManager` will run as a background process, potentially as a `child_process` spawned by the main React Native app, or as a separate daemon if more persistent background operation is needed.
    *   **Integration Points:**
        *   **React Native:** Calls `SyncService` methods.
        *   **Node.js Backend:** Interacts with the local SQLite database (`data_manager.ts`) to read/write data and change logs. Communicates with the external E2EE cloud service API (e.g., EteSync's API) over HTTPS.

2.  **Database Schema Design**
    (Refer to "Core Application Framework" feature for `Users` table, specifically `sync_enabled`, `last_synced_at`, `sync_frequency` fields.)

    *   **`ChangeLog` Table:** This table is crucial for tracking local modifications for delta synchronization.
        *   `id` (TEXT, PRIMARY KEY, UUID)
        *   `user_id` (TEXT, FOREIGN KEY to `Users.id`, NOT NULL)
        *   `entity_type` (TEXT, ENUM: 'conversation', 'message', 'memory', 'goal', 'journal_entry', 'mood_summary', 'personality_profile', 'user_preference', NOT NULL)
        *   `entity_id` (TEXT, NOT NULL) - ID of the record that was changed.
        *   `change_type` (TEXT, ENUM: 'CREATE', 'UPDATE', 'DELETE', NOT NULL)
        *   `timestamp` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)
        *   `payload` (BLOB, NULLABLE) - Encrypted JSON representation of the changed fields (for UPDATE) or the full new record (for CREATE). For DELETE, payload might be empty or contain just the ID.
        *   `synced` (INTEGER, BOOLEAN, DEFAULT 0) - Flag to indicate if this change has been successfully synced.
        *   `sync_version` (TEXT, NULLABLE) - Version identifier from the cloud sync for this change.
        *   `conflict_resolved_at` (TIMESTAMP, NULLABLE) - Timestamp if this change was part of a conflict resolution.

    *   **`SyncState` Table:** To store metadata about sync sessions and the last known state from the cloud.
        *   `user_id` (TEXT, PRIMARY KEY, FOREIGN KEY to `Users.id`)
        *   `last_successful_sync_timestamp` (TIMESTAMP, NULLABLE)
        *   `last_sync_token` (TEXT, NULLABLE) - A token or cursor provided by the cloud service to indicate the last synced state.
        *   `current_sync_status` (TEXT, ENUM: 'idle', 'syncing', 'conflicts', 'error', NOT NULL, DEFAULT 'idle')
        *   `recovery_key_hash` (TEXT, NULLABLE) - Hash of the user's E2EE recovery key.
        *   `created_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)
        *   `updated_at` (TIMESTAMP, NOT NULL, DEFAULT CURRENT_TIMESTAMP)

    *   **Indexing Strategy:**
        *   Indexes on `ChangeLog.user_id`, `ChangeLog.synced`, `ChangeLog.timestamp` for efficient retrieval of pending changes.
        *   Index on `SyncState.user_id`.
    *   **Foreign Key Relationships:** Enforce `ON DELETE CASCADE` for `ChangeLog` and `SyncState` to `Users`.
    *   **Database Migration/Versioning:** (Refer to "Core Application Framework" feature.)

3.  **Comprehensive API Design**
    *   **Frontend (React Native) -> Backend (Node.js) IPC (HTTP Endpoints on `ai_inference_server.ts`):**
        *   `POST /sync/start`: Initiate a synchronization cycle.
            *   Request: `{ userId: string }`
            *   Response: `{ status: string, message: string }`
        *   `GET /sync/status`: Get the current synchronization status.
            *   Request: `{ userId: string }`
            *   Response: `{ status: string, lastSyncedAt: string | null, pendingChanges: number, conflicts: number }`
        *   `POST /sync/configure`: Update synchronization settings.
            *   Request: `{ userId: string, syncEnabled: boolean, syncFrequency: string, cloudCredentials?: object }`
            *   Response: `{ success: boolean }`
        *   `POST /sync/resolve_conflict`: Resolve a specific data conflict.
            *   Request: `{ userId: string, conflictId: string, resolution: 'keep_local' | 'keep_cloud' | 'merge', mergedData?: object }`
            *   Response: `{ success: boolean }`
        *   `POST /sync/generate_recovery_key`: Generate and store an E2EE recovery key.
            *   Request: `{ userId: string }`
            *   Response: `{ recoveryKey: string }`
        *   `POST /sync/export_data`: Export all user data for portability.
            *   Request: `{ userId: string, format: 'json' | 'csv' }`
            *   Response: `{ filePath: string }`
        *   `POST /sync/delete_all_data`: Request deletion of all user data.
            *   Request: `{ userId: string, confirmationToken: string }`
            *   Response: `{ success: boolean }`

    *   **Node.js Backend (Internal APIs using Node.js `crypto` and external cloud service SDK/API):**
        *   **`SyncManager` (TypeScript Class in `SairaBackendServices/src/node_services/`):**
            *   `initiateSync(userId: string)`: Main sync orchestration method.
            *   `uploadChanges(userId: string)`: Reads `ChangeLog`, encrypts, sends to cloud.
            *   `downloadChanges(userId: string)`: Fetches deltas from cloud, decrypts, applies locally.
            *   `handleConflicts(userId: string, conflicts: any)`: Manages conflict detection and resolution.
            *   `encryptData(data: object, encryptionKey: Buffer): Buffer`: Uses E2EE library.
            *   `decryptData(encryptedData: Buffer, encryptionKey: Buffer): object`: Uses E2EE library.
            *   `generateE2EEKeys(passphrase: string): { publicKey: Buffer, privateKey: Buffer }`: Key derivation.
            *   `connectToCloudService(credentials: object)`: Establishes connection to the chosen cloud sync provider (e.g., EteSync API client).
        *   **`data_manager.ts`:** (Already defined, but will be extended to interact with `ChangeLog` and `SyncState` tables).
            *   `recordChange(userId: string, entityType: string, entityId: string, changeType: string, payload: object)`: Inserts into `ChangeLog`.
            *   `getPendingChanges(userId: string): ChangeLogEntry`: Retrieves unsynced changes.
            *   `markChangesAsSynced(changeIds: string): void`: Updates `synced` flag in `ChangeLog`.
            *   `getSyncState(userId: string): SyncState | null`: Retrieves current sync state.
            *   `updateSyncState(userId: string, updates: SyncStateUpdateDTO): void`: Updates sync state.

    *   **Authentication & Authorization:** (Refer to "Core Application Framework" feature.)
    *   **Error Handling:** Network errors, E2EE failures, and data integrity issues will be caught and logged. Sync status will be updated to 'error' and communicated to the frontend.
    *   **Rate Limiting/Caching:** Not applicable for local-first. Cloud sync service might have its own rate limits, which the `SyncManager` should respect with retry-after headers and exponential backoff.

4.  **Frontend Architecture (React Native for macOS)**
    *   **`ProfileSettingsScreen.tsx` (Sync Configuration Section):**
        *   Toggle for "Enable Cloud Sync".
        *   Input fields for cloud service credentials (if applicable).
        *   Dropdown for "Sync Frequency" (Manual, Daily, Weekly).
        *   Display of "Last Synced At" timestamp and current sync status.
        *   Button for "Sync Now".
        *   Button for "Generate Recovery Key".
        *   Button for "Export All Data".
        *   Button for "Delete All My Data".
    *   **`SyncStatusIndicator.tsx`:** A small, persistent UI component (e.g., in the app's menu bar or a corner of the main window) that shows the current sync status (e.g., green checkmark for synced, spinning icon for syncing, red exclamation for error/conflicts).
    *   **`ConflictResolutionModal.tsx`:** A modal dialog that appears when sync conflicts are detected, presenting the user with options to resolve them (e.g., "Keep Local Version," "Keep Cloud Version," "Merge Manually").
    *   **State Management:** Global state for `syncStatus`, `lastSyncedAt`, `pendingChangesCount`, `conflictsCount`.
    *   **Routing:** Direct navigation to `ProfileSettingsScreen`.

5.  **Detailed CRUD Operations**
    *   **Sync Initiation (Read/Update `ChangeLog`, `SyncState`):**
        *   **Flow:** User clicks "Sync Now" or scheduled sync triggers -> `SyncService.initiateSync(userId)` is called.
        *   `SyncManager` reads `SyncState` to get `last_successful_sync_timestamp` and `last_sync_token`.
        *   `SyncManager` reads `ChangeLog` to get all `synced = 0` entries.
        *   UI updates `syncStatus` to 'syncing'.
    *   **Data Upload (Create/Update/Delete via `ChangeLog`):**
        *   **Flow:** `SyncManager.uploadChanges(userId)` iterates through pending `ChangeLog` entries.
        *   For each entry:
            *   Retrieves `payload`.
            *   Encrypts `payload` using E2EE keys.
            *   Sends encrypted data to the cloud sync service API (e.g., `POST /cloud/delta_upload`).
            *   On successful upload, `data_manager.ts.markChangesAsSynced(changeId)` updates the `ChangeLog` entry.
        *   **Validation:** Ensure `payload` is valid JSON/BLOB. Cloud service will validate E2EE integrity.
    *   **Data Download (Read from Cloud, Create/Update/Delete Local DB):**
        *   **Flow:** `SyncManager.downloadChanges(userId)` calls cloud sync service API (e.g., `GET /cloud/delta_download?since=last_sync_token`).
        *   Receives encrypted deltas from cloud.
        *   Decrypts each delta.
        *   For each decrypted delta:
            *   Identifies `entity_type`, `entity_id`, `change_type`, `payload`.
            *   Applies change to local SQLite database via `data_manager.ts` (e.g., `INSERT`, `UPDATE`, `DELETE` on relevant tables).
            *   If a conflict is detected (e.g., local record modified since last sync, and cloud also has a conflicting update), the conflict is recorded in a temporary in-memory store or a `Conflicts` table.
        *   Updates `SyncState.last_successful_sync_timestamp` and `last_sync_token`.
    *   **Conflict Resolution (Read/Update `Conflicts` table, Update Local DB):**
        *   **Flow:** If conflicts exist after download, `SyncManager.handleConflicts(userId, conflicts)` is called.
        *   `ConflictResolutionModal.tsx` is displayed in the frontend.
        *   User selects resolution for each conflict.
        *   Frontend sends resolution choice to `ai_inference_server.ts`'s `/sync/resolve_conflict`.
        *   Backend applies the chosen resolution to the local database and updates the `ChangeLog` (e.g., marking the original conflicting local change as resolved).
        *   If "Merge Manually" is chosen, the UI provides an editor for the user to combine versions, and the merged data is sent back as an update.

6.  **User Experience Flow**
    *   **Initial Sync Setup:**
        1.  User navigates to Profile Settings -> Sync.
        2.  Toggles "Enable Cloud Sync".
        3.  A modal appears for cloud service authentication (e.g., EteSync username/password).
        4.  Upon successful authentication, the app performs an initial full sync. UI shows a progress bar or "Syncing..." status.
        5.  Upon completion, status changes to "Synced".
    *   **Background Sync:**
        1.  App runs in background.
        2.  At configured frequency (e.g., daily), `SyncManager` initiates a background sync.
        3.  `SyncStatusIndicator` changes to "Syncing".
        4.  If successful, reverts to "Synced".
        5.  If network error, status changes to "Offline" or "Error", with a retry mechanism.
    *   **Conflict Resolution:**
        1.  During a sync, if a conflict is detected (e.g., same memory edited locally and on another device).
        2.  `SyncStatusIndicator` changes to "Conflicts Detected".
        3.  `ConflictResolutionModal.tsx` appears, listing conflicts.
        4.  For each conflict, user sees both versions and chooses "Keep Local," "Keep Cloud," or "Merge."
        5.  After resolving all, sync completes.
    *   **Data Portability/Deletion:**
        1.  User navigates to Privacy Dashboard.
        2.  Clicks "Export All Data". App generates encrypted `.zip` file of data and provides download path.
        3.  Clicks "Delete All My Data". App prompts for confirmation (e.g., re-enter password). Upon confirmation, all local and synced cloud data is purged.

7.  **Security Considerations**
    *   **End-to-End Encryption (E2EE):**
        *   **Key Management:** Encryption keys for E2EE will be derived locally from a user-provided passphrase (or biometric unlock) using a strong Key Derivation Function (KDF) like PBKDF2 or Argon2. These keys are never sent to the cloud.
        *   **Data Encryption:** All data sent to the cloud will be encrypted on the client-side (Node.js backend) before transmission, using a robust symmetric encryption algorithm (e.g., AES-256 in GCM mode). The EteSync protocol is a strong reference for this, providing zero-knowledge security.[7, 8, 9]
        *   **Integrity:** Use authenticated encryption (e.g., AES-GCM) to ensure data integrity and authenticity during transit and at rest in the cloud.
    *   **Local Data at Rest:** The entire SQLite database will be encrypted using SQLCipher, with the encryption key derived from the user's local authentication.
    *   **GDPR/CCPA Compliance:**
        *   **Consent:** Explicit consent for sync and data types synced.
        *   **Right to Access/Portability:** The "Export All Data" feature provides data portability. The exported data will be encrypted and require the user's recovery key to decrypt.
        *   **Right to Erasure:** The "Delete All My Data" feature ensures all user data is purged locally and from the cloud sync service.
        *   **Audit Logs:** Local, encrypted audit logs will record sync events, data exports, and deletion requests.
    *   **Network Security:** All communication with the cloud sync service will use HTTPS with strict TLS certificate pinning (if feasible for a desktop app) to prevent Man-in-the-Middle attacks.
    *   **Recovery Key:** Users will be prompted to generate and securely store a recovery key (e.g., a mnemonic phrase or a long alphanumeric string) that can be used to restore access to their encrypted data if they forget their passphrase. This key must be generated and stored *locally* by the user, never by Saira.

8.  **Testing Strategy**
    *   **Unit Tests:**
        *   Node.js: Test `SyncManager` logic, E2EE encryption/decryption functions, delta calculation, and conflict resolution algorithms in isolation.
        *   React Native: Test UI components for sync settings, status display, and conflict resolution modals.
    *   **Integration Tests:**
        *   **Local-to-Cloud Sync:** Test full sync cycles with a mock cloud service, simulating various scenarios: initial sync, delta syncs, offline modifications, network interruptions, and concurrent modifications from multiple simulated devices.
        *   **E2EE Verification:** Test that data is correctly encrypted before upload and decrypted after download, and that the cloud service cannot access plaintext data.
        *   **Conflict Scenarios:** Develop specific test cases for different conflict types (e.g., same record updated by two devices, one deleted and one updated) and verify chosen resolution strategies.
        *   **Data Integrity:** Verify that data remains consistent and uncorrupted after multiple sync cycles and error conditions.
    *   **End-to-End Tests:**
        *   Simulate a user enabling sync, making changes offline, going online, and verifying data consistency across multiple simulated instances of Saira.
        *   Test data export and deletion workflows.
    *   **Performance Tests:**
        *   Measure sync duration for various data volumes (e.g., initial sync of 1000 memories, daily delta sync of 10 memories).
        *   Measure bandwidth usage during sync.
        *   Monitor CPU/memory impact of background sync processes.

9.  **Data Management**
    *   **Change Journal Management:** The `ChangeLog` table will grow over time. Implement a policy to periodically prune or summarize old, synced `ChangeLog` entries to prevent the database from becoming excessively large. For example, entries older than 30 days and marked `synced=1` could be deleted.
    *   **Data Purging:** When a user requests data deletion, ensure all associated data in the local SQLite database is securely wiped (e.g., by deleting the database file and recreating it, or using SQLite's `VACUUM` command after deletion).
    *   **Handling Large Data Volumes:** For initial syncs or large document imports, implement chunking and streaming mechanisms to avoid memory exhaustion.
    *   **Offline Data Consistency:** Ensure that local data remains consistent and usable even if the sync service is temporarily unavailable or disabled.

10. **Error Handling & Logging**
    *   **Structured Logging:** (Refer to "Core Application Framework" feature.) Log sync events, including start/end times, data volumes, and any errors.
    *   **Error Classification:**
        *   **Network Errors:** Transient, trigger retries with exponential backoff.
        *   **Authentication Errors:** Require user re-authentication.
        *   **Data Integrity Errors:** Critical, may require user intervention or a full re-sync.
        *   **Conflict Errors:** Handled by the conflict resolution flow.
    *   **User Notifications:** Provide clear, actionable notifications to the user for sync failures, conflicts, or successful completion.
    *   **Recovery Mechanisms:**
        *   **Retry Logic:** Automatic retries for transient network issues.
        *   **Conflict Resolution:** User-guided resolution for data conflicts.
        *   **Recovery Key:** Mechanism to restore access to encrypted data.
        *   **Full Re-sync Option:** Provide a manual option in settings to force a full re-sync from the cloud, as a last resort for data inconsistencies.

---
This concludes the detailed technical specification for the core features of Saira, adhering to your requirements for using Node.js, Python, and JavaScript frameworks, with C++ only for critical native bindings. This document should provide a highly granular foundation for your upcoming task planning.
