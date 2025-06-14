## Feature Specifications (UI-Focused)

### Feature: Onboarding Flow

**Feature Goal (UI-specific)**
To guide new users through an intuitive, multi-step setup process, collecting essential preferences and obtaining necessary consents to personalize their Saira experience from the first interaction.

**Any API Relationships (UI-specific)**

  * **`UserManager` (Frontend Service):** Calls `createUser` with collected preferences and consent data.
  * **`PersonalityManager` (Frontend Service):** Fetches pre-defined personality profiles for selection.
  * **`DataStoreService` (Frontend Service):** Persists initial user data locally.

**Detailed Feature Requirements (UI-specific)**

1.  **Welcome Screen (`OnboardingScreen.tsx` - Step 1):**

      * **Visuals:** Full-screen splash with Saira logo, a welcoming tagline (e.g., "Your Emotion-Aware Life Companion"), and a brief, compelling description of Saira's purpose.
      * **Elements:**
          * Large, centered Saira logo/icon.
          * Headline text: "Welcome to Saira."
          * Body text: "An AI that understands your emotions, grows with you, and helps you manage your mental, emotional, and personal life through intelligent, natural conversations."
          * Primary Call-to-Action (CTA) button: "Get Started" (or "Begin Your Journey").
      * **Interactions:** Tapping "Get Started" navigates to the Consent Screen.
      * **States:** Initial load state.

2.  **Consent Screen (`OnboardingScreen.tsx` - Step 2):**

      * **Visuals:** A clear, concise screen presenting privacy commitments and requiring explicit user consent for sensitive data processing.
      * **Elements:**
          * Headline: "Your Privacy, Our Priority."
          * Body text explaining Saira's privacy-first approach (local processing, E2EE sync).
          * Checkbox: "I agree to Saira's Privacy Policy and Terms of Service." (Link to full policy).
          * Checkbox: "Allow Saira to record and analyze my emotional tone from voice for personalized support." (Optional, with clear explanation).
          * Checkbox: "Allow Saira to record and store memories from our conversations to build long-term context." (Optional, with clear explanation).
          * Primary CTA button: "Continue" (disabled until mandatory consents are checked).
          * Secondary button: "Learn More About Privacy" (opens external link or in-app modal).
      * **Interactions:**
          * Tapping checkboxes toggles their state.
          * "Continue" button enables only when "Privacy Policy" checkbox is checked.
          * Tapping "Continue" navigates to Personality Selection.
      * **States:** Button disabled/enabled states.

3.  **Personality Selection Screen (`OnboardingScreen.tsx` - Step 3):**

      * **Visuals:** A grid or carousel of pre-defined personality profiles with brief descriptions.
      * **Elements:**
          * Headline: "Choose Saira's Initial Personality."
          * Description: "You can change this anytime in settings."
          * List/Grid of `PersonalityProfileCard` components:
              * Each card displays: Personality Name (e.g., "The Coach," "The Best Friend," "The Mom").
              * Short description of personality traits and interaction style.
              * Visual indicator for selection (e.g., border, checkmark).
          * Primary CTA button: "Next".
      * **Interactions:**
          * Tapping a `PersonalityProfileCard` selects it. Only one can be active.
          * "Next" button navigates to Goal Setting.
      * **States:** Selected/unselected card states.

4.  **Goal Setting Screen (`OnboardingScreen.tsx` - Step 4):**

      * **Visuals:** A screen for users to define initial personal goals.
      * **Elements:**
          * Headline: "What are your initial goals with Saira?"
          * Description: "Saira can help you track and achieve personal goals. You can add more later."
          * `TextInput` field: "Add a new goal..." (e.g., "Improve sleep," "Reduce stress," "Learn a new skill").
          * Button: "Add Goal" (adds text from input to a list).
          * `FlatList` or `ScrollView` displaying added goals:
              * Each goal item: Text of the goal, small "x" button to remove.
          * Primary CTA button: "Next".
          * Secondary button: "Skip for now".
      * **Interactions:**
          * Typing in `TextInput` updates its value.
          * Tapping "Add Goal" adds the goal to the list.
          * Tapping "x" removes a goal.
          * "Next" navigates to Tone Style Preference.
          * "Skip for now" navigates to Tone Style Preference.
      * **States:** Empty input, populated list.

5.  **Tone Style Preference Screen (`OnboardingScreen.tsx` - Step 5):**

      * **Visuals:** A screen for users to select Saira's preferred response tone.
      * **Elements:**
          * Headline: "How should Saira speak to you?"
          * Description: "Choose a general tone style for Saira's responses."
          * Radio buttons or segmented control for tone options: "Empathetic," "Direct," "Neutral," "Playful."
          * Short example text for each tone option.
          * Primary CTA button: "Finish Setup".
      * **Interactions:** Tapping a radio button selects the tone. "Finish Setup" button navigates to the Main Application.
      * **States:** Selected/unselected tone options.

6.  **Onboarding Complete Screen (`OnboardingScreen.tsx` - Final Step):**

      * **Visuals:** A celebratory screen confirming setup completion.
      * **Elements:**
          * Large success icon/animation.
          * Headline: "You're All Set\!"
          * Body text: "Saira is ready to begin your journey together."
          * Primary CTA button: "Start Talking to Saira".
      * **Interactions:** Tapping "Start Talking to Saira" dismisses the onboarding flow and navigates to the `ConversationScreen`.
      * **States:** Success animation.

**Detailed Implementation Guide (UI-specific)**

1.  **Frontend Architecture:**

      * **Component Hierarchy:** `OnboardingScreen.tsx` will be a single React Native component that manages the state for which step of the onboarding the user is on. It will conditionally render sub-components for each step (e.g., `WelcomeStep`, `ConsentStep`, `PersonalityStep`, `GoalStep`, `ToneStep`, `CompletionStep`).
      * **Reusable Component Library:** Utilize `Button`, `TextInput`, `Checkbox`, `RadioGroup`, `Card` components from a shared library.
      * **State Management:**
          * `useState` hook within `OnboardingScreen.tsx` to manage the `currentStep` (integer).
          * `useState` for form inputs (e.g., `userName`, `selectedPersonalityId`, `goalsList`, `selectedTone`).
          * `useState` for consent checkbox states.
          * `useEffect` to enable/disable "Continue" buttons based on validation.
          * Global state (e.g., `Zustand` store) to persist onboarding data temporarily before final submission.
      * **Routing:**
          * `AppNavigator.tsx` will check an `onboarding_completed` flag (from `UserManager`) on app launch. If `false`, it navigates to `OnboardingScreen`.
          * Internal navigation within `OnboardingScreen` will update `currentStep` state.
          * Upon "Finish Setup," `AppNavigator` will replace the onboarding stack with the `MainTabView` stack.
      * **Responsive Design:** Use `Flexbox` for layout. Ensure content scrolls on smaller window sizes if necessary. Text sizes should scale appropriately.

2.  **CRUD Operations (UI Perspective):**

      * **Create User:** The entire onboarding flow is a "Create" operation for the `User` entity. Data is collected across multiple screens and submitted once on "Finish Setup."
          * **Validation:** Frontend validation for required fields (e.g., name not empty, consent checked).
          * **Flow:**
            1.  User inputs data in each step.
            2.  On "Finish Setup," `OnboardingScreen` collects all `useState` data.
            3.  Calls `UserManager.createUser(collectedData)`.
            4.  `UserManager` sends this data via `IPCService` to the Node.js `data_manager.ts` to insert into the `Users` table.
            5.  `UserManager` updates the `onboarding_completed` flag in local storage.
      * **Read Personality Profiles:** `PersonalitySelectionScreen` performs a "Read" operation to fetch available `PersonalityProfiles` from `PersonalityManager`.
          * **Flow:** `PersonalitySelectionScreen` `useEffect` calls `PersonalityManager.getPersonalityProfiles()` -\> `IPCService` to `data_manager.ts` to query `PersonalityProfiles` table.

3.  **User Experience Flow (UI Perspective):**

      * **Visual Progress:** A simple progress indicator (e.g., "Step X of Y" or a progress bar) at the top of each onboarding screen.
      * **Clear Instructions:** Concise headings and body text to guide the user.
      * **Feedback:** Immediate visual feedback on button presses (e.g., loading spinner on "Finish Setup").
      * **Error Handling:** If `UserManager.createUser` fails (e.g., database error), display a user-friendly error message (e.g., "Setup failed. Please try again.") and allow retries.

4.  **Security Considerations (UI Perspective):**

      * **Consent Display:** Clearly present privacy policy and consent checkboxes. Ensure they are prominent and require explicit interaction.
      * **Input Masking:** If any sensitive input (e.g., future password for sync) is added, ensure it's masked.
      * **No Sensitive Data in UI State:** Avoid storing sensitive user data directly in easily inspectable UI state. Pass it to backend services immediately.

5.  **Testing Strategy (UI Perspective):**

      * **Unit Tests:** Test individual `OnboardingScreen` sub-components for rendering, state updates, and button interactions.
      * **Integration Tests:** Test the full multi-step flow, ensuring data is correctly collected and passed between steps. Mock `UserManager` calls.
      * **End-to-End Tests:** Simulate a full user onboarding from app launch to `MainTabView` display, verifying all UI elements and interactions.

6.  **Error Handling & Logging (UI Perspective):**

      * **Frontend Validation Errors:** Display inline error messages for invalid inputs (e.g., "Name cannot be empty").
      * **Backend Errors:** If `createUser` API call fails, display a generic error message (e.g., "Failed to save preferences. Please try again.") in a toast or alert. Log detailed error to `Logger.ts`.

-----

### Feature: Main Application Navigation

**Feature Goal (UI-specific)**
To provide a clear, intuitive, and persistent navigation structure that allows users to easily switch between the primary sections of the Saira application.

**Any API Relationships (UI-specific)**

  * **`AppStateManager` (Frontend Service):** May update global state based on active tab (e.g., to pause/resume background processes).

**Detailed Feature Requirements (UI-specific)**

1.  **Tab Bar Display:**

      * **Visuals:** A persistent tab bar at the bottom (or left sidebar for macOS desktop feel) of the main application window.
      * **Elements:**
          * Icons and text labels for each primary section: "Conversation," "Journal," "Deep Talk," "Profile."
          * Visual indication of the currently active tab.
      * **Interactions:** Tapping a tab icon/label switches to the corresponding screen.
      * **States:** Active/inactive tab states.

2.  **Screen Switching:**

      * **Visuals:** Smooth transitions between screens when switching tabs.
      * **Behavior:** Each tab maintains its own navigation stack (e.g., navigating deep within "Journal" and then switching to "Conversation" and back, returns to the deep state in "Journal").

**Detailed Implementation Guide (UI-specific)**

1.  **Frontend Architecture:**

      * **Component Hierarchy:** `App.tsx` (root) renders `AppNavigator.tsx`. `AppNavigator.tsx` uses `React Navigation`'s `createBottomTabNavigator` (for mobile) or `createMaterialTopTabNavigator` (can be styled for desktop sidebar) to define the main tab structure. Each tab will render its own root screen component (e.g., `ConversationScreen`, `JournalingScreen`).
      * **Reusable Component Library:** Standard React Native `Tab.Navigator` and `Tab.Screen` components. Custom icons for tabs.
      * **State Management:** `React Navigation` handles internal state for active tab and navigation stacks.
      * **Routing:** `React Navigation`'s declarative API defines the tab routes.

2.  **CRUD Operations (UI Perspective):**

      * This feature is purely navigational and does not directly involve CRUD operations on data entities. It facilitates access to other features that perform CRUD.

3.  **User Experience Flow (UI Perspective):**

      * **Immediate Feedback:** Tapping a tab should instantly switch the view.
      * **Consistency:** Tab bar remains visible and in the same position across all main screens.

4.  **Security Considerations (UI Perspective):**

      * No direct security implications for the navigation component itself. Access to sensitive tabs (e.g., Profile Settings) is implicitly protected by the overall app's local authentication.

5.  **Testing Strategy (UI Perspective):**

      * **Unit Tests:** Test `AppNavigator` component for correct tab rendering and initial route.
      * **Integration Tests:** Verify that tapping tabs correctly switches screens and that navigation stacks are maintained.
      * **End-to-End Tests:** Simulate user navigating between all main tabs.

6.  **Error Handling & Logging (UI Perspective):**

      * No specific error handling for navigation itself, beyond standard React Native error boundaries.

-----

### Feature: Conversation Screen

**Feature Goal (UI-specific)**
To provide a dynamic and intuitive chat interface for real-time voice and text interaction with Saira, displaying conversational history, real-time transcription, and AI responses.

**Any API Relationships (UI-specific)**

  * **`IPCService` (Frontend Service):** Sends audio chunks, text input, and receives transcription updates, emotion data, LLM text, and TTS audio.
  * **`MessageManager` (Frontend Service):** Adds new messages (user and AI) to the local database.
  * **`ConversationManager` (Frontend Service):** Manages the current conversation session (e.g., starting a new one, updating title).
  * **`MemoryManager` (Frontend Service):** Triggers memory formation based on conversation turns.

**Detailed Feature Requirements (UI-specific)**

1.  **Chat History Display:**

      * **Visuals:** A scrollable list of chat bubbles, visually distinguishing between user messages and AI responses.
      * **Elements:**
          * `FlatList` or `ScrollView` to display `MessageBubble` components.
          * Each `MessageBubble` displays text content.
          * User messages aligned right, AI messages aligned left.
          * Timestamps for messages (optional, on hover or grouped).
      * **Interactions:** Auto-scroll to bottom on new message. User can manually scroll up to view history.
      * **States:** Empty state (e.g., "Say 'Hey Saira' to begin\!"), loading state for initial history.

2.  **Voice Input Indicator:**

      * **Visuals:** A prominent, dynamic indicator (e.g., a pulsing microphone icon, a waveform visualization) that changes based on the AI's listening/processing state.
      * **Elements:**
          * Microphone icon.
          * Optional: Simple waveform animation or pulsating circle.
          * Text status: "Listening...", "Thinking...", "Speaking...", "Idle."
      * **Interactions:** Tapping the microphone icon can manually toggle listening (if not using wake word).
      * **States:** Idle, Listening, Processing (AI thinking), Speaking (AI responding).

3.  **Real-time Transcription Display:**

      * **Visuals:** Text area above the input bar that updates as the user speaks.
      * **Elements:**
          * `Text` component displaying the current partial or final transcription.
          * Text color/style might change to indicate finality.
      * **Interactions:** Updates dynamically.
      * **States:** Empty, partial transcription, final transcription.

4.  **Input Bar:**

      * **Visuals:** A persistent input area at the bottom of the screen.
      * **Elements:**
          * `TextInput` for typing messages.
          * Microphone button (to initiate voice input if wake word is off, or to manually stop/start recording).
          * Send button (for text input).
      * **Interactions:**
          * Typing in `TextInput` updates its value.
          * Tapping microphone button toggles voice input.
          * Tapping send button sends text message.
      * **States:** Empty, text entered, sending.

5.  **AI Response Playback:**

      * **Behavior:** Audio plays automatically as AI response text appears.
      * **Visuals:** No explicit UI for playback, but the `VoiceInputIndicator` should show "Speaking..." state.

**Detailed Implementation Guide (UI-specific)**

1.  **Frontend Architecture:**

      * **Component Hierarchy:** `ConversationScreen.tsx` will be the main screen. It will contain `MessageList` (a `FlatList` of `MessageBubble` components), `VoiceInputIndicator`, and `InputBar`.
      * **Reusable Component Library:** `MessageBubble`, `VoiceInputIndicator`, `InputBar` components.
      * **State Management:**
          * `useState` for `currentTranscription`, `aiResponseText`, `inputMessageText`.
          * `useState` for `conversationState` (e.g., 'idle', 'listening', 'processing', 'speaking').
          * `useState` for `messages` array (local display cache).
          * `useEffect` to manage WebSocket connection to `ai_inference_server.ts`.
          * `useEffect` to auto-scroll `FlatList` when new messages arrive.
          * Global state (e.g., `Zustand` store) for `currentConversationId`, `activePersonalityId`.
      * **Routing:** `ConversationScreen` is the default tab in `MainTabView`.

2.  **CRUD Operations (UI Perspective):**

      * **Read Messages:** `ConversationScreen` performs a "Read" operation to fetch initial conversation history.
          * **Flow:** On component mount, `ConversationScreen` calls `MessageManager.getMessages(currentConversationId, pagination)` -\> `IPCService` to `data_manager.ts` to query `Messages` table.
      * **Create Message (User):**
          * **Flow (Voice):** `audio_processor.ts` streams audio to `ai_inference_server.ts` -\> `ai_inference_server.ts` sends `transcription_update` via WebSocket -\> `ConversationScreen` updates `currentTranscription`. When `isFinal` is true, `MessageManager.addMessage` is called.
          * **Flow (Text):** User types and presses send -\> `MessageManager.addMessage` is called.
          * `MessageManager` sends message data via `IPCService` to `data_manager.ts` to insert into `Messages` table.
      * **Create Message (AI):**
          * **Flow:** `ai_inference_server.ts` sends `ai_response_text` via WebSocket -\> `ConversationScreen` updates UI. Once full response received, `MessageManager.addMessage` is called to store AI's message.
          * `MessageManager` sends message data via `IPCService` to `data_manager.ts` to insert into `Messages` table.

3.  **User Experience Flow (UI Perspective):**

      * **Real-time Feedback:** Visual and textual indicators for AI's state (listening, thinking, speaking).
      * **Smooth Scrolling:** Ensure `FlatList` performs well with many messages.
      * **Typing vs. Voice:** Seamless switch between typing and voice input modes.

4.  **Security Considerations (UI Perspective):**

      * **Microphone Permission:** React Native will trigger the macOS system prompt for microphone access. The UI should guide the user if permission is denied.
      * **No Raw Audio Display:** Raw audio data is processed by the backend and never displayed in the UI.
      * **Consent Adherence:** If emotion/memory recording consent is denied, the UI should reflect this (e.g., disable related indicators or features).

5.  **Testing Strategy (UI Perspective):**

      * **Unit Tests:** Test `MessageBubble`, `VoiceInputIndicator`, `InputBar` components for rendering and basic interactions.
      * **Integration Tests:** Test WebSocket connection, real-time transcription updates, and message display. Mock backend responses.
      * **End-to-End Tests:** Simulate full voice conversations, verifying UI updates, message persistence, and AI response playback.

6.  **Error Handling & Logging (UI Perspective):**

      * **Connection Errors:** If WebSocket connection to backend fails, display a prominent error message (e.g., "Saira's brain is offline. Please restart the app.") and disable voice input.
      * **Transcription Errors:** If ASR fails, display "Could not understand. Please try again."
      * **LLM Errors:** If LLM fails to generate a response, display "Saira is having trouble thinking. Please try again."
      * **Audio Playback Errors:** Log errors if TTS audio fails to play.
      * **Logging:** Detailed logs of audio stream events, AI processing steps, and message storage.

-----

### Feature: Daily Check-ins & Journaling Screen

**Feature Goal (UI-specific)**
To provide a dedicated space for users to reflect on their emotional state, log daily moods, and create personal journal entries, with visual summaries of emotional patterns over time.

**Any API Relationships (UI-specific)**

  * **`JournalManager` (Frontend Service):** Creates, reads, updates, and deletes journal entries and mood summaries.
  * **`MessageManager` (Frontend Service):** May retrieve emotion data from past messages for mood summaries.
  * **`MemoryManager` (Frontend Service):** Journal entries can trigger memory formation.

**Detailed Feature Requirements (UI-specific)**

1.  **Daily Mood Summary (`JournalingScreen.tsx` - Main View):**

      * **Visuals:** A calendar-like view or a series of daily cards displaying aggregated mood data.
      * **Elements:**
          * Date navigation (e.g., left/right arrows to change day/week/month).
          * For each day:
              * Date display.
              * Aggregated mood representation (e.g., a dominant emoji, a color gradient, or a simple text summary like "Mostly Neutral").
              * Count of journal entries for that day.
              * Link/button to view/add journal entry for that day.
      * **Interactions:** Tapping a day navigates to its journal entry list/detail.
      * **States:** Loading state, empty state for days with no data.

2.  **Emotional Check-in Interface (`JournalingScreen.tsx` - Button/Modal):**

      * **Visuals:** A prominent button on the main journaling screen, or a modal that appears when triggered.
      * **Elements:**
          * Button: "How are you feeling today?"
          * **Modal/Screen:**
              * Headline: "Log Your Mood."
              * Mood picker: A visual slider for Arousal (Calm to Excited) and Valence (Negative to Positive), or a selection of emotion emojis/categories (e.g., Happy, Sad, Angry, Neutral).
              * Optional `TextInput`: "Add a note about your mood..."
              * Button: "Save Mood".
      * **Interactions:** Tapping the button opens the modal. Interacting with sliders/pickers updates mood selection. Tapping "Save Mood" submits the data.
      * **States:** Default, selected mood, saving.

3.  **Journal Entry List (`JournalingScreen.tsx` - Sub-section/Screen):**

      * **Visuals:** A scrollable list of journal entries, ordered by date.
      * **Elements:**
          * `FlatList` displaying `JournalEntryCard` components.
          * Each `JournalEntryCard` displays: Date, a snippet of the entry content, and a small mood indicator (if available).
          * Button: "New Journal Entry" (floating action button or prominent header button).
      * **Interactions:** Tapping a `JournalEntryCard` navigates to `JournalEntryDetailView`. Tapping "New Journal Entry" navigates to `JournalEntryCreationView`.
      * **States:** Loading, empty list.

4.  **Journal Entry Creation/Detail (`JournalEntryCreationView.tsx`/`JournalEntryDetailView.tsx`):**

      * **Visuals:** A dedicated screen for writing/editing a journal entry.
      * **Elements:**
          * Date/Time display (auto-filled, editable).
          * Large `TextInput` for journal content.
          * Optional: Mood picker (similar to check-in) if not already set.
          * Button: "Save Entry".
          * For detail view: "Edit" button, "Delete" button.
      * **Interactions:** Typing updates content. Tapping "Save Entry" persists. "Edit" makes content editable. "Delete" prompts confirmation then deletes.
      * **States:** Editing, viewing, saving, deleting.

**Detailed Implementation Guide (UI-specific)**

1.  **Frontend Architecture:**

      * **Component Hierarchy:** `JournalingScreen.tsx` will be the main tab screen. It will contain `MoodSummaryCalendar` and `JournalEntryList` components. `JournalEntryCreationView.tsx` and `JournalEntryDetailView.tsx` will be separate screens navigated to from `JournalingScreen`.
      * **Reusable Component Library:** `MoodSummaryCard`, `JournalEntryCard`, `DatePicker`, `Slider`, `EmojiPicker` (custom).
      * **State Management:**
          * `useState` for `selectedDate`, `journalEntries` array, `moodSummaries` array.
          * `useState` for `currentJournalContent`, `selectedMood`.
          * `useEffect` to fetch data from `JournalManager` based on `selectedDate` or filters.
          * Global state for `userId`.
      * **Routing:** `JournalingScreen` is a tab in `MainTabView`. `JournalEntryCreationView` and `JournalEntryDetailView` are pushed onto the `JournalingScreen`'s navigation stack.

2.  **CRUD Operations (UI Perspective):**

      * **Create Journal Entry:**
          * **Flow:** User types in `JournalEntryCreationView` -\> taps "Save Entry" -\> `JournalManager.createJournalEntry` is called.
          * `JournalManager` sends data via `IPCService` to `data_manager.ts` to insert into `JournalEntries` table.
          * Also triggers `JournalManager.generateMoodSummary` for the relevant date.
      * **Read Journal Entries:**
          * **Flow:** `JournalingScreen` or `JournalEntryList` mounts -\> `JournalManager.getJournalEntries` is called (with date range/pagination) -\> `IPCService` to `data_manager.ts` to query `JournalEntries`.
          * `JournalManager.getMoodSummaries` is called for the calendar view.
      * **Update Journal Entry:**
          * **Flow:** User edits in `JournalEntryDetailView` -\> taps "Save" -\> `JournalManager.updateJournalEntry` is called.
          * `JournalManager` sends data via `IPCService` to `data_manager.ts` to update `JournalEntries` table.
      * **Delete Journal Entry:**
          * **Flow:** User taps "Delete" in `JournalEntryDetailView` -\> confirmation dialog -\> `JournalManager.deleteJournalEntry` is called.
          * `JournalManager` sends data via `IPCService` to `data_manager.ts` to delete from `JournalEntries` table.

3.  **User Experience Flow (UI Perspective):**

      * **Intuitive Logging:** Easy access to mood check-in and new journal entry creation.
      * **Visual Summaries:** Mood calendar provides a quick overview of emotional trends.
      * **Seamless Editing:** Smooth transition from viewing to editing journal entries.

4.  **Security Considerations (UI Perspective):**

      * **Data Privacy:** Remind users about the privacy of their journal entries.
      * **Consent Adherence:** Ensure emotion data is only recorded/displayed if consent was given.

5.  **Testing Strategy (UI Perspective):**

      * **Unit Tests:** Test `MoodSummaryCard`, `JournalEntryCard`, `MoodPicker` components.
      * **Integration Tests:** Test the full flow of creating, viewing, editing, and deleting journal entries. Verify mood summary generation.
      * **End-to-End Tests:** Simulate a user logging moods and creating multiple journal entries over several days.

6.  **Error Handling & Logging (UI Perspective):**

      * **Save Errors:** If saving a journal entry fails, display "Failed to save entry. Please try again."
      * **Load Errors:** If journal entries fail to load, display "Could not load journal entries."
      * **Logging:** Log all CRUD operations on journal entries and mood summaries.

-----

### Feature: Deep Talk Screen

**Feature Goal (UI-specific)**
To provide a specialized conversational mode that encourages deeper exploration of complex personal topics, leveraging Saira's long-term memory (RAG) to provide more insightful and context-rich responses.

**Any API Relationships (UI-specific)**

  * **`IPCService` (Frontend Service):** Sends audio/text input, receives AI responses, specifically optimized for RAG queries.
  * **`MemoryManager` (Frontend Service):** Triggers semantic search for relevant memories based on conversation context.
  * **`ConversationManager` (Frontend Service):** Manages the conversation session, potentially tagging it as a "Deep Talk" session.

**Detailed Feature Requirements (UI-specific)**

1.  **Specialized Conversation Interface:**

      * **Visuals:** Similar to the `ConversationScreen`, but with subtle visual cues indicating "Deep Talk Mode" (e.g., a different background color, a unique icon in the header).
      * **Elements:**
          * Chat history display (same as `ConversationScreen`).
          * Voice input indicator (same as `ConversationScreen`).
          * Real-time transcription display (same as `ConversationScreen`).
          * Input bar (same as `ConversationScreen`).
          * Optional: "Suggested Topics" or "Memory Prompts" area (e.g., a carousel of buttons with memory snippets or questions like "Tell me more about X event").
      * **Interactions:** Standard voice/text interaction. Tapping suggested topics injects them as a prompt.
      * **States:** Active Deep Talk session.

2.  **Memory Integration Indicators (Subtle):**

      * **Visuals:** When Saira's response is heavily influenced by a retrieved memory, a subtle visual indicator might appear (e.g., a small "memory" icon next to the AI's message, or a tooltip on hover revealing the source memory snippet). This is for transparency and to highlight Saira's RAG capability.
      * **Elements:** Small icon, tooltip/popover.
      * **Interactions:** Hovering/tapping the icon reveals the source memory.
      * **States:** Memory-augmented response, non-augmented response.

**Detailed Implementation Guide (UI-specific)**

1.  **Frontend Architecture:**

      * **Component Hierarchy:** `DeepTalkScreen.tsx` will largely reuse components from `ConversationScreen.tsx` (e.g., `MessageList`, `VoiceInputIndicator`, `InputBar`). It will wrap these in a container that applies Deep Talk specific styling.
      * **Reusable Component Library:** Existing chat components. New `MemoryHint` component.
      * **State Management:**
          * Inherits `conversationState` and `messages` state from a shared context or uses its own.
          * `useState` for `suggestedTopics` (populated by AI or based on recent memories).
          * Global state for `currentConversationId`.
      * **Routing:** `DeepTalkScreen` is a tab in `MainTabView`.

2.  **CRUD Operations (UI Perspective):**

      * **Read Memories (for RAG):** This is the core "Read" operation.
          * **Flow:** When a user speaks/types in Deep Talk mode, the `ConversationScreen`'s ViewModel (or a dedicated `DeepTalkViewModel`) will:
            1.  Send the user's query to `ai_inference_server.ts`'s `/ai/embeddings/generate` to get an embedding.
            2.  Send the embedding to `ai_inference_server.ts`'s `/data/search_vectors` to retrieve relevant `Memories` from `sqlite-vec`.
            3.  These retrieved memories are then included in the prompt sent to the LLM.
      * **Create/Read Messages:** Same as `ConversationScreen`.

3.  **User Experience Flow (UI Perspective):**

      * **Focused Interaction:** The UI should encourage deeper, more reflective conversations.
      * **Transparency:** Subtle indicators help the user understand when Saira is drawing from its memory.

4.  **Security Considerations (UI Perspective):**

      * **Memory Visibility:** Ensure that only memories marked `is_active` and allowed by `memory_visibility_rules` are retrieved and used for RAG. The UI should reflect these settings.

5.  **Testing Strategy (UI Perspective):**

      * **Integration Tests:** Test the RAG pipeline: simulate a query, verify that relevant memories are retrieved from the mocked backend, and that the LLM response incorporates them.
      * **End-to-End Tests:** Simulate a Deep Talk session where the user asks about a past event, and Saira responds with details from a previously ingested memory.

6.  **Error Handling & Logging (UI Perspective):**

      * **RAG Failure:** If memory retrieval or embedding generation fails, the LLM should still attempt to respond, but the UI might show a subtle warning that "Saira couldn't access all its memories."
      * **Performance:** Monitor RAG query latency. If too slow, provide feedback (e.g., "Saira is thinking deeply...").

-----

### Feature: Profile Settings Screen

**Feature Goal (UI-specific)**
To provide a centralized hub for users to customize Saira's behavior, manage their data, configure privacy settings, and update AI models.

**Any API Relationships (UI-specific)**

  * **`UserManager` (Frontend Service):** Reads/updates user preferences, privacy settings, and triggers data export/deletion.
  * **`PersonalityManager` (Frontend Service):** Reads/updates personality profiles.
  * **`ModelManager` (Frontend Service):** Reads model versions, triggers model downloads.
  * **`SyncService` (Frontend Service):** Configures sync, initiates sync, handles recovery keys.
  * **`NudgeManager` (Frontend Service):** Reads/updates nudge preferences.

**Detailed Feature Requirements (UI-specific)**

1.  **Main Settings Navigation (`ProfileSettingsScreen.tsx`):**

      * **Visuals:** A list of categories (e.g., "General," "Personality," "Privacy & Data," "AI Models," "Notifications," "Sync").
      * **Elements:**
          * `FlatList` of `SettingsCategoryItem` components.
          * Each item: Icon, Category Name, disclosure indicator ("\>").
      * **Interactions:** Tapping a category navigates to its dedicated sub-screen.
      * **States:** Loading, default.

2.  **General Settings (`GeneralSettingsScreen.tsx`):**

      * **Visuals:** Basic user profile information.
      * **Elements:**
          * User's Name (`TextInput`).
          * Profile Picture (display, button to change).
          * Preferred Tone Style (radio buttons/dropdown).
      * **Interactions:** Editing fields updates user data.
      * **States:** Editing, saving.

3.  **Personality Settings (`PersonalitySettingsScreen.tsx`):**

      * **Visuals:** List of available personality profiles, with the active one highlighted.
      * **Elements:**
          * Headline: "Saira's Personality."
          * `FlatList` of `PersonalityProfileCard` components:
              * Each card: Name, description, "Activate" button (if not active).
              * Active card has a distinct visual style.
          * Button: "Create Custom Personality" (navigates to `CustomPersonalityCreationScreen`).
      * **Interactions:** Tapping "Activate" changes Saira's active personality.
      * **States:** Loading, active/inactive profiles.

4.  **Privacy & Data Settings (`PrivacyDashboardScreen.tsx`):**

      * **Visuals:** A dashboard for managing data consents and privacy actions.
      * **Elements:**
          * Toggle: "Allow emotion recording from voice."
          * Toggle: "Allow memory recording from conversations."
          * Button: "View Audit Logs" (opens `AuditLogsScreen`).
          * Button: "Export All My Data" (triggers data export).
          * Button: "Delete All My Data" (triggers data deletion, with confirmation).
          * Link to Privacy Policy.
      * **Interactions:** Toggling changes consent. Buttons trigger respective actions.
      * **States:** Toggles on/off, processing states for export/delete.

5.  **AI Models Settings (`AIModelManagementScreen.tsx`):**

      * **Visuals:** List of currently loaded AI models and their versions.
      * **Elements:**
          * For each model (LLM, ASR, TTS, SER, Embedding):
              * Model Name (e.g., "Mistral 7B," "Whisper.cpp").
              * Current Version.
              * Status (e.g., "Loaded," "Updating," "Available Update").
              * Button: "Check for Updates" (for all models).
              * Button: "Download Update" (if available for a specific model).
              * Button: "Rollback to Previous Version" (if applicable).
      * **Interactions:** Tapping "Download Update" initiates download.
      * **States:** Loading, up-to-date, update available, downloading, installing, error.

6.  **Notifications Settings (`NotificationSettingsScreen.tsx`):**

      * **Visuals:** Controls for proactive nudges.
      * **Elements:**
          * Toggle: "Enable Proactive Nudges."
          * List of Nudge Types (e.g., "Reminders," "Positive Reinforcement," "Wellness Suggestions").
          * For each type: Toggle to enable/disable, frequency picker (Daily, Weekly, Event-based), time picker.
      * **Interactions:** Toggling enables/disables nudges. Adjusting frequency/time updates preferences.
      * **States:** Enabled/disabled, configured.

7.  **Sync Settings (`SyncSettingsScreen.tsx`):**

      * **Visuals:** Controls for optional cloud synchronization.
      * **Elements:**
          * Toggle: "Enable Cloud Sync."
          * Input fields for cloud service credentials (if using a generic E2EE service like EteSync).
          * Dropdown: "Sync Frequency" (Manual, Daily, Weekly, On App Close).
          * Display: "Last Synced At:"
          * Display: "Current Status:"
          * Button: "Sync Now".
          * Button: "Generate Recovery Key" (for E2EE data).
          * Button: "Resolve Conflicts" (if conflicts detected).
      * **Interactions:** Toggling enables/disables sync. Buttons trigger sync, key generation, or conflict resolution.
      * **States:** Enabled/disabled, syncing, synced, conflicts, error.

**Detailed Implementation Guide (UI-specific)**

1.  **Frontend Architecture:**

      * **Component Hierarchy:** `ProfileSettingsScreen.tsx` will be the root of the settings tab, using `React Navigation`'s stack navigator to push sub-screens (e.g., `GeneralSettingsScreen`, `PrivacyDashboardScreen`).
      * **Reusable Component Library:** `ToggleSwitch`, `TextInput`, `Button`, `Picker`, `List` components.
      * **State Management:**
          * `useState` for local form inputs within each settings sub-screen.
          * `useEffect` to load initial settings data from relevant managers (`UserManager`, `PersonalityManager`, etc.).
          * `useCallback` for debouncing input changes before saving to backend.
          * Global state for `userId`, `currentPersonalityId`, `syncStatus`.
      * **Routing:** `ProfileSettingsScreen` is a tab in `MainTabView`. Sub-screens are pushed onto its own navigation stack.

2.  **CRUD Operations (UI Perspective):**

      * **User Preferences (Update `Users` table):**
          * **Flow:** User changes name, tone, sync settings, nudge preferences -\> `UserManager.updateUser` or `NudgeManager.updateNudgePreference` is called.
          * `IPCService` sends updates to `data_manager.ts` to update `Users` or `NudgePreferences` table.
      * **Personality Profiles (Read/Update `PersonalityProfiles` table):**
          * **Flow:** `PersonalitySettingsScreen` loads `PersonalityManager.getPersonalityProfiles()`. User taps "Activate" -\> `PersonalityManager.activatePersonalityProfile` updates `Users.current_personality_profile_id`.
      * **Privacy Consents (Update `Users` table):**
          * **Flow:** Toggling consent switches calls `UserManager.updatePrivacySettings`.
      * **Data Export/Deletion (Trigger Backend Process):**
          * **Flow:** User clicks "Export" -\> `UserManager.exportData()` calls `IPCService` to trigger a Python script (`data_exporter.py`) in the backend.
          * User clicks "Delete" -\> confirmation -\> `UserManager.deleteUser()` calls `IPCService` to `data_manager.ts` to delete user data.
      * **AI Model Management (Read/Update Model Files):**
          * **Flow:** `AIModelManagementScreen` loads `ModelManager.getLoadedModels()`. User clicks "Download Update" -\> `ModelManager.downloadModelUpdate()` calls `IPCService` to `model_manager.ts` (Node.js) which uses `model_downloader.py` (Python) to download the model.
          * `model_manager.ts` then loads the new model into the `ai_inference_addon`.

3.  **User Experience Flow (UI Perspective):**

      * **Clear Categorization:** Settings are logically grouped to prevent overwhelming the user.
      * **Instant Feedback:** Toggles and input fields update immediately.
      * **Confirmation:** Critical actions (e.g., data deletion) require explicit confirmation.
      * **Progress Indicators:** Show progress for long-running operations like model downloads or data exports.

4.  **Security Considerations (UI Perspective):**

      * **Sensitive Data Input:** If cloud sync requires credentials, ensure input fields are secure (e.g., password masking).
      * **Consent Visibility:** Clearly display current consent status for sensitive data processing.
      * **Confirmation for Destructive Actions:** Double-confirm data deletion.
      * **Recovery Key Display:** When generating a recovery key, display it prominently with warnings about secure storage.

5.  **Testing Strategy (UI Perspective):**

      * **Unit Tests:** Test individual settings components (e.g., `ToggleSwitch`, `Picker`).
      * **Integration Tests:** Test data loading and saving for each settings section. Simulate model downloads and sync processes.
      * **End-to-End Tests:** Simulate a user changing various settings, verifying persistence and impact on app behavior (e.g., personality change affects LLM response).

6.  **Error Handling & Logging (UI Perspective):**

      * **Save Errors:** Display "Failed to save settings. Please try again." for backend save failures.
      * **Download Errors:** Display "Failed to download model update." for model download failures.
      * **Sync Errors:** Display "Sync failed. Check network or credentials." for sync issues.
      * **Deletion Errors:** Display "Failed to delete data."
      * **Logging:** Log all settings changes, sync events, model updates, and data export/deletion attempts.

-----

### Feature: Proactive Nudges & Notifications

**Feature Goal (UI-specific)**
To proactively engage the user with timely reminders, positive reinforcement, and wellness suggestions, delivered through macOS system notifications and an in-app history.

**Any API Relationships (UI-specific)**

  * **`NotificationService` (Frontend Service):** Registers for and displays macOS system notifications.
  * **`NudgeManager` (Frontend Service):** Manages nudge preferences and records nudge history.
  * **`ai_inference_server.ts` (Node.js Backend):** The LLM in the backend will generate nudge content based on user data and preferences.
  * **`data_manager.ts` (Node.js Backend):** Stores nudge preferences and history.

**Detailed Feature Requirements (UI-specific)**

1.  **Notification Display (macOS System Level):**

      * **Visuals:** Standard macOS notification banners/alerts.
      * **Elements:**
          * App icon.
          * Title (e.g., "Saira Check-in," "Saira Motivation").
          * Body text (the nudge message, e.g., "How are you feeling today?").
          * Optional: Action buttons (e.g., "Log Mood," "Dismiss").
      * **Interactions:** User can click on the notification to open the app to a relevant screen (e.g., Journaling screen for mood check-in).
      * **States:** Delivered, interacted.

2.  **In-App Nudge History (`NotificationSettingsScreen.tsx` - Sub-section):**

      * **Visuals:** A scrollable list of past nudges.
      * **Elements:**
          * `FlatList` displaying `NudgeHistoryItem` components.
          * Each item: Date/Time, Nudge Type, Message Content.
          * Optional: Icon indicating if user interacted with it.
      * **Interactions:** User can review past nudges.
      * **States:** Loading, empty list.

3.  **Nudge Configuration (Part of `ProfileSettingsScreen.tsx` -\> `NotificationSettingsScreen.tsx`):**

      * **Visuals:** Toggles and selectors for customizing nudge behavior.
      * **Elements:**
          * Toggle: "Enable Proactive Nudges."
          * Section for "Nudge Types":
              * For each type (e.g., "Reminders," "Positive Reinforcement," "Wellness Suggestions"):
                  * Toggle to enable/disable.
                  * Dropdown/Picker for "Frequency" (Daily, Weekly, Event-based).
                  * Time picker for daily/weekly nudges.
          * Button: "Customize Nudge Content" (future feature, opens a modal for prompt templates).
      * **Interactions:** Toggling enables/disables. Selecting frequency/time updates preferences.
      * **States:** Enabled/disabled, configured.

**Detailed Implementation Guide (UI-specific)**

1.  **System Architecture Overview:**

      * **High-level Architecture:** Nudge generation logic resides in the Node.js backend (LLM). The Node.js backend will schedule nudges and send them to the React Native frontend via IPC. The React Native frontend will then use macOS native modules to display system notifications.
      * **Technology Stack:**
          * **Frontend (UI):** React Native for macOS (TypeScript) for `NotificationSettingsScreen` and handling incoming notifications.
          * **Backend (Nudge Generation & Scheduling):** Node.js (`ai_inference_server.ts` for LLM, `nudge_scheduler.ts` for scheduling).
          * **Local Database:** SQLite for `NudgePreferences` and `NudgeHistory`.
          * **macOS Notifications:** React Native native module (Objective-C/Swift) to interact with `UNUserNotificationCenter` for system notifications.
          * **IPC:** Local HTTP/WebSocket for backend to send nudge content to frontend.

2.  **Database Schema Design:**
    (Refer to "Core Application Framework" feature for `NudgePreferences` and `NudgeHistory` tables.)

3.  **Comprehensive API Design:**

      * **Frontend (React Native) -\> Backend (Node.js) IPC (HTTP Endpoints on `ai_inference_server.ts`):**
          * `POST /nudges/preferences`: Update nudge preferences.
              * Request: `{ userId: string, preferences: NudgePreferenceDTO }`
              * Response: `{ success: boolean }`
          * `GET /nudges/history`: Retrieve nudge history.
              * Request: `{ userId: string, pagination: PaginationDTO }`
              * Response: `{ history: NudgeHistoryDTO }`
      * **Backend (Node.js) -\> Frontend (React Native) IPC (WebSocket `ai_inference_server.ts` or custom local IPC):**
          * `nudge_delivered`: Event sent when a nudge is generated and ready for display.
              * Payload: `{ nudgeId: string, message: string, actionType: string }`
      * **Node.js Backend (Internal APIs):**
          * **`NudgeScheduler` (TypeScript Class):**
              * `scheduleNudges(userId: string, preferences: NudgePreferenceDTO)`: Sets up timers/cron jobs.
              * `generateNudgeContent(userId: string, type: string): Promise<string>`: Calls LLM to generate content.
              * `recordNudgeDelivery(nudgeId: string, userId: string, message: string)`: Inserts into `NudgeHistory`.
          * **`ai_inference_server.ts`:** Exposes LLM for nudge content generation.

4.  **Frontend Architecture (React Native for macOS):**

      * **`NotificationSettingsScreen.tsx`:**
          * Displays nudge configuration UI.
          * Fetches `NudgePreferences` and `NudgeHistory` from `NudgeManager`.
          * Sends updates to `NudgeManager`.
      * **`App.tsx` (or `AppStateManager.ts`):** Listens for `nudge_delivered` events from the Node.js backend.
      * **Native Module (Objective-C/Swift):** A custom React Native native module (e.g., `NativeNotificationModule`) will be developed to interact with macOS `UNUserNotificationCenter` to display system notifications.
          * `NativeNotificationModule.displayNotification(title: string, body: string, userInfo: object)`
          * `NativeNotificationModule.onNotificationClicked(callback: (userInfo: object) => void)`
      * **State Management:** `useState` for nudge preferences and history. Global state to manage notification permissions.
      * **Routing:** `NotificationSettingsScreen` is a sub-screen of `ProfileSettingsScreen`.

5.  **Detailed CRUD Operations:**

      * **Create Nudge Preference:** `NudgeManager.createNudgePreference` (via UI).
      * **Read Nudge Preferences:** `NudgeManager.getNudgePreferences` (for UI display).
      * **Update Nudge Preference:** `NudgeManager.updateNudgePreference` (via UI toggles/pickers).
      * **Delete Nudge Preference:** `NudgeManager.deleteNudgePreference` (if user removes a custom nudge type).
      * **Create Nudge History:** `NudgeScheduler.recordNudgeDelivery` (backend-initiated).
      * **Read Nudge History:** `NudgeManager.getNudgeHistory` (for UI display).
      * **Update Nudge History:** `NudgeManager.markNudgeInteracted` (when user clicks a notification).

6.  **User Experience Flow (UI Perspective):**

      * **Opt-in:** User explicitly enables proactive nudges in settings.
      * **System Notifications:** Nudges appear as standard macOS notifications.
      * **Click-through:** Clicking a notification opens Saira to a relevant screen (e.g., Journaling for a mood check-in nudge).
      * **In-app Review:** Users can review past nudges in settings.

7.  **Security Considerations (UI Perspective):**

      * **Notification Permissions:** The app will request macOS notification permissions.
      * **Privacy:** Nudge content should be general and not expose sensitive user data in the notification itself.
      * **Consent Adherence:** Nudges related to emotion/memory will only be sent if the user has given consent for those data types.

8.  **Testing Strategy (UI Perspective):**

      * **Unit Tests:** Test `NotificationSettingsScreen` components.
      * **Integration Tests:** Test the flow from backend nudge generation -\> IPC -\> frontend notification display. Test click-through behavior.
      * **End-to-End Tests:** Simulate scheduled nudges appearing and user interaction.

9.  **Data Management:**

      * **Nudge Preferences:** Stored in `NudgePreferences` table.
      * **Nudge History:** Stored in `NudgeHistory` table. Consider purging old history after a certain period to manage database size.

10. **Error Handling & Logging (UI Perspective):**

      * **Notification Delivery Failures:** Log if macOS fails to display a notification.
      * **Nudge Generation Errors:** If LLM fails to generate nudge content, log the error and skip that nudge.
      * **User Feedback:** If nudge scheduling fails, inform the user in settings.

-----

This concludes the UI-focused feature specification, providing a granular breakdown of each screen and its associated requirements and implementation considerations. This level of detail should be highly beneficial for your task planning.\<ctrl95\>\#\# Feature Specifications (UI-Focused)

### Feature: Onboarding Flow

**Feature Goal (UI-specific)**
To guide new users through an intuitive, multi-step setup process, collecting essential preferences and obtaining necessary consents to personalize their Saira experience from the first interaction.

**Any API Relationships (UI-specific)**

  * **`UserManager` (Frontend Service):** Calls `createUser` with collected preferences and consent data.
  * **`PersonalityManager` (Frontend Service):** Fetches pre-defined personality profiles for selection.
  * **`DataStoreService` (Frontend Service):** Persists initial user data locally.

**Detailed Feature Requirements (UI-specific)**

1.  **Welcome Screen (`OnboardingScreen.tsx` - Step 1):**

      * **Visuals:** Full-screen splash with Saira logo, a welcoming tagline (e.g., "Your Emotion-Aware Life Companion"), and a brief, compelling description of Saira's purpose.
      * **Elements:**
          * Large, centered Saira logo/icon.
          * Headline text: "Welcome to Saira."
          * Body text: "An AI that understands your emotions, grows with you, and helps you manage your mental, emotional, and personal life through intelligent, natural conversations."
          * Primary Call-to-Action (CTA) button: "Get Started" (or "Begin Your Journey").
      * **Interactions:** Tapping "Get Started" navigates to the Consent Screen.
      * **States:** Initial load state.

2.  **Consent Screen (`OnboardingScreen.tsx` - Step 2):**

      * **Visuals:** A clear, concise screen presenting privacy commitments and requiring explicit user consent for sensitive data processing.
      * **Elements:**
          * Headline: "Your Privacy, Our Priority."
          * Body text explaining Saira's privacy-first approach (local processing, E2EE sync).
          * Checkbox: "I agree to Saira's Privacy Policy and Terms of Service." (Link to full policy).
          * Checkbox: "Allow Saira to record and analyze my emotional tone from voice for personalized support." (Optional, with clear explanation).
          * Checkbox: "Allow Saira to record and store memories from our conversations to build long-term context." (Optional, with clear explanation).
          * Primary CTA button: "Continue" (disabled until mandatory consents are checked).
          * Secondary button: "Learn More About Privacy" (opens external link or in-app modal).
      * **Interactions:**
          * Tapping checkboxes toggles their state.
          * "Continue" button enables only when "Privacy Policy" checkbox is checked.
          * Tapping "Continue" navigates to Personality Selection.
      * **States:** Button disabled/enabled states.

3.  **Personality Selection Screen (`OnboardingScreen.tsx` - Step 3):**

      * **Visuals:** A grid or carousel of pre-defined personality profiles with brief descriptions.
      * **Elements:**
          * Headline: "Choose Saira's Initial Personality."
          * Description: "You can change this anytime in settings."
          * List/Grid of `PersonalityProfileCard` components:
              * Each card displays: Personality Name (e.g., "The Coach," "The Best Friend," "The Mom").
              * Short description of personality traits and interaction style.
              * Visual indicator for selection (e.g., border, checkmark).
          * Primary CTA button: "Next".
      * **Interactions:**
          * Tapping a `PersonalityProfileCard` selects it. Only one can be active.
          * "Next" button navigates to Goal Setting.
      * **States:** Selected/unselected card states.

4.  **Goal Setting Screen (`OnboardingScreen.tsx` - Step 4):**

      * **Visuals:** A screen for users to define initial personal goals.
      * **Elements:**
          * Headline: "What are your initial goals with Saira?"
          * Description: "Saira can help you track and achieve personal goals. You can add more later."
          * `TextInput` field: "Add a new goal..." (e.g., "Improve sleep," "Reduce stress," "Learn a new skill").
          * Button: "Add Goal" (adds text from input to a list).
          * `FlatList` or `ScrollView` displaying added goals:
              * Each goal item: Text of the goal, small "x" button to remove.
          * Primary CTA button: "Next".
          * Secondary button: "Skip for now".
      * **Interactions:**
          * Typing in `TextInput` updates its value.
          * Tapping "Add Goal" adds the goal to the list.
          * Tapping "x" removes a goal.
          * "Next" navigates to Tone Style Preference.
          * "Skip for now" navigates to Tone Style Preference.
      * **States:** Empty input, populated list.

5.  **Tone Style Preference Screen (`OnboardingScreen.tsx` - Step 5):**

      * **Visuals:** A screen for users to select Saira's preferred response tone.
      * **Elements:**
          * Headline: "How should Saira speak to you?"
          * Description: "Choose a general tone style for Saira's responses."
          * Radio buttons or segmented control for tone options: "Empathetic," "Direct," "Neutral," "Playful."
          * Short example text for each tone option.
          * Primary CTA button: "Finish Setup".
      * **Interactions:** Tapping a radio button selects the tone. "Finish Setup" button navigates to the Main Application.
      * **States:** Selected/unselected tone options.

6.  **Onboarding Complete Screen (`OnboardingScreen.tsx` - Final Step):**

      * **Visuals:** A celebratory screen confirming setup completion.
      * **Elements:**
          * Large success icon/animation.
          * Headline: "You're All Set\!"
          * Body text: "Saira is ready to begin your journey together."
          * Primary CTA button: "Start Talking to Saira".
      * **Interactions:** Tapping "Start Talking to Saira" dismisses the onboarding flow and navigates to the `ConversationScreen`.
      * **States:** Success animation.

**Detailed Implementation Guide (UI-specific)**

1.  **Frontend Architecture:**

      * **Component Hierarchy:** `OnboardingScreen.tsx` will be a single React Native component that manages the state for which step of the onboarding the user is on. It will conditionally render sub-components for each step (e.g., `WelcomeStep`, `ConsentStep`, `PersonalityStep`, `GoalStep`, `ToneStep`, `CompletionStep`).
      * **Reusable Component Library:** Utilize `Button`, `TextInput`, `Checkbox`, `RadioGroup`, `Card` components from a shared library.
      * **State Management:**
          * `useState` hook within `OnboardingScreen.tsx` to manage the `currentStep` (integer).
          * `useState` for form inputs (e.g., `userName`, `selectedPersonalityId`, `goalsList`, `selectedTone`).
          * `useState` for consent checkbox states.
          * `useEffect` to enable/disable "Continue" buttons based on validation.
          * Global state (e.g., `Zustand` store) to persist onboarding data temporarily before final submission.
      * **Routing:**
          * `AppNavigator.tsx` will check an `onboarding_completed` flag (from `UserManager`) on app launch. If `false`, it navigates to `OnboardingScreen`.
          * Internal navigation within `OnboardingScreen` will update `currentStep` state.
          * Upon "Finish Setup," `AppNavigator` will replace the onboarding stack with the `MainTabView` stack.
      * **Responsive Design:** Use `Flexbox` for layout. Ensure content scrolls on smaller window sizes if necessary. Text sizes should scale appropriately.

2.  **CRUD Operations (UI Perspective):**

      * **Create User:** The entire onboarding flow is a "Create" operation for the `User` entity. Data is collected across multiple screens and submitted once on "Finish Setup."
          * **Validation:** Frontend validation for required fields (e.g., name not empty, consent checked).
          * **Required Fields:** `name`, `gdpr_ccpa_consent`, `emotion_recording_consent`, `memory_recording_consent` (from `Users` table schema).
          * **Flow:**
            1.  User inputs data in each step.
            2.  On "Finish Setup," `OnboardingScreen` collects all `useState` data.
            3.  Calls `UserManager.createUser(collectedData)`.
            4.  `UserManager` sends this data via `IPCService` to the Node.js `data_manager.ts` to insert into the `Users` table.
            5.  `UserManager` updates the `onboarding_completed` flag in local storage.
      * **Read Personality Profiles:** `PersonalitySelectionScreen` performs a "Read" operation to fetch available `PersonalityProfiles` from `PersonalityManager`.
          * **Flow:** `PersonalitySelectionScreen` `useEffect` calls `PersonalityManager.getPersonalityProfiles()` -\> `IPCService` to `data_manager.ts` to query `PersonalityProfiles` table.

3.  **User Experience Flow (UI Perspective):**

      * **Visual Progress:** A simple progress indicator (e.g., "Step X of Y" or a progress bar) at the top of each onboarding screen.
      * **Clear Instructions:** Concise headings and body text to guide the user.
      * **Feedback:** Immediate visual feedback on button presses (e.g., loading spinner on "Finish Setup").
      * **Error Handling:** If `UserManager.createUser` fails (e.g., database error), display a user-friendly error message (e.g., "Setup failed. Please try again.") and allow retries.

4.  **Security Considerations (UI Perspective):**

      * **Consent Display:** Clearly present privacy policy and consent checkboxes. Ensure they are prominent and require explicit interaction.
      * **Input Masking:** If any sensitive input (e.g., future password for sync) is added, ensure it's masked.
      * **No Sensitive Data in UI State:** Avoid storing sensitive user data directly in easily inspectable UI state. Pass it to backend services immediately.

5.  **Testing Strategy (UI Perspective):**

      * **Unit Tests:** Test individual `OnboardingScreen` sub-components for rendering, state updates, and button interactions.
      * **Integration Tests:** Test the full multi-step flow, ensuring data is correctly collected and passed between steps. Mock `UserManager` calls.
      * **End-to-End Tests:** Simulate a full user onboarding from app launch to `MainTabView` display, verifying all UI elements and interactions.

6.  **Error Handling & Logging (UI Perspective):**

      * **Frontend Validation Errors:** Display inline error messages for invalid inputs (e.g., "Name cannot be empty").
      * **Backend Errors:** If `createUser` API call fails, display a generic error message (e.g., "Failed to save preferences. Please try again.") in a toast or alert. Log detailed error to `Logger.ts`.

-----

### Feature: Main Application Navigation

**Feature Goal (UI-specific)**
To provide a clear, intuitive, and persistent navigation structure that allows users to easily switch between the primary sections of the Saira application.

**Any API Relationships (UI-specific)**

  * **`AppStateManager` (Frontend Service):** May update global state based on active tab (e.g., to pause/resume background processes).

**Detailed Feature Requirements (UI-specific)**

1.  **Tab Bar Display:**

      * **Visuals:** A persistent tab bar at the bottom (or left sidebar for macOS desktop feel) of the main application window.
      * **Elements:**
          * Icons and text labels for each primary section: "Conversation," "Journal," "Deep Talk," "Profile."
          * Visual indication of the currently active tab.
      * **Interactions:** Tapping a tab icon/label switches to the corresponding screen.
      * **States:** Active/inactive tab states.

2.  **Screen Switching:**

      * **Visuals:** Smooth transitions between screens when switching tabs.
      * **Behavior:** Each tab maintains its own navigation stack (e.g., navigating deep within "Journal" and then switching to "Conversation" and back, returns to the deep state in "Journal").

**Detailed Implementation Guide (UI-specific)**

1.  **Frontend Architecture:**

      * **Component Hierarchy:** `App.tsx` (root) renders `AppNavigator.tsx`. `AppNavigator.tsx` uses `React Navigation`'s `createBottomTabNavigator` (for mobile) or `createMaterialTopTabNavigator` (can be styled for desktop sidebar) to define the main tab structure. Each tab will render its own root screen component (e.g., `ConversationScreen`, `JournalingScreen`).
      * **Reusable Component Library:** Standard React Native `Tab.Navigator` and `Tab.Screen` components. Custom icons for tabs.
      * **State Management:** `React Navigation` handles internal state for active tab and navigation stacks.
      * **Routing:** `React Navigation`'s declarative API defines the tab routes.

2.  **CRUD Operations (UI Perspective):**

      * This feature is purely navigational and does not directly involve CRUD operations on data entities. It facilitates access to other features that perform CRUD.

3.  **User Experience Flow (UI Perspective):**

      * **Immediate Feedback:** Tapping a tab should instantly switch the view.
      * **Consistency:** Tab bar remains visible and in the same position across all main screens.

4.  **Security Considerations (UI Perspective):**

      * No direct security implications for the navigation component itself. Access to sensitive tabs (e.g., Profile Settings) is implicitly protected by the overall app's local authentication.

5.  **Testing Strategy (UI Perspective):**

      * **Unit Tests:** Test `AppNavigator` component for correct tab rendering and initial route.
      * **Integration Tests:** Verify that tapping tabs correctly switches screens and that navigation stacks are maintained.
      * **End-to-End Tests:** Simulate user navigating between all main tabs.

6.  **Error Handling & Logging (UI Perspective):**

      * No specific error handling for navigation itself, beyond standard React Native error boundaries.

-----

### Feature: Conversation Screen

**Feature Goal (UI-specific)**
To provide a dynamic and intuitive chat interface for real-time voice and text interaction with Saira, displaying conversational history, real-time transcription, and AI responses.

**Any API Relationships (UI-specific)**

  * **`IPCService` (Frontend Service):** Sends audio chunks, text input, and receives transcription updates, emotion data, LLM text, and TTS audio.
  * **`MessageManager` (Frontend Service):** Adds new messages (user and AI) to the local database.
  * **`ConversationManager` (Frontend Service):** Manages the current conversation session (e.g., starting a new one, updating title).
  * **`MemoryManager` (Frontend Service):** Triggers memory formation based on conversation turns.

**Detailed Feature Requirements (UI-specific)**

1.  **Chat History Display:**

      * **Visuals:** A scrollable list of chat bubbles, visually distinguishing between user messages and AI responses.
      * **Elements:**
          * `FlatList` or `ScrollView` to display `MessageBubble` components.
          * Each `MessageBubble` displays text content.
          * User messages aligned right, AI messages aligned left.
          * Timestamps for messages (optional, on hover or grouped).
      * **Interactions:** Auto-scroll to bottom on new message. User can manually scroll up to view history.
      * **States:** Empty state (e.g., "Say 'Hey Saira' to begin\!"), loading state for initial history.

2.  **Voice Input Indicator:**

      * **Visuals:** A prominent, dynamic indicator (e.g., a pulsing microphone icon, a waveform visualization) that changes based on the AI's listening/processing state.
      * **Elements:**
          * Microphone icon.
          * Optional: Simple waveform animation or pulsating circle.
          * Text status: "Listening...", "Thinking...", "Speaking...", "Idle."
      * **Interactions:** Tapping the microphone icon can manually toggle listening (if not using wake word).
      * **States:** Idle, Listening, Processing (AI thinking), Speaking (AI responding).

3.  **Real-time Transcription Display:**

      * **Visuals:** Text area above the input bar that updates as the user speaks.
      * **Elements:**
          * `Text` component displaying the current partial or final transcription.
          * Text color/style might change to indicate finality.
      * **Interactions:** Updates dynamically.
      * **States:** Empty, partial transcription, final transcription.

4.  **Input Bar:**

      * **Visuals:** A persistent input area at the bottom of the screen.
      * **Elements:**
          * `TextInput` for typing messages.
          * Microphone button (to initiate voice input if wake word is off, or to manually stop/start recording).
          * Send button (for text input).
      * **Interactions:**
          * Typing in `TextInput` updates its value.
          * Tapping microphone button toggles voice input.
          * Tapping send button sends text message.
      * **States:** Empty, text entered, sending.

5.  **AI Response Playback:**

      * **Behavior:** Audio plays automatically as AI response text appears.
      * **Visuals:** No explicit UI for playback, but the `VoiceInputIndicator` should show "Speaking..." state.

**Detailed Implementation Guide (UI-specific)**

1.  **Frontend Architecture:**

      * **Component Hierarchy:** `ConversationScreen.tsx` will be the main screen. It will contain `MessageList` (a `FlatList` of `MessageBubble` components), `VoiceInputIndicator`, and `InputBar`.
      * **Reusable Component Library:** `MessageBubble`, `VoiceInputIndicator`, `InputBar` components.
      * **State Management:**
          * `useState` for `currentTranscription`, `aiResponseText`, `inputMessageText`.
          * `useState` for `conversationState` (e.g., 'idle', 'listening', 'processing', 'speaking').
          * `useState` for `messages` array (local display cache).
          * `useEffect` to manage WebSocket connection to `ai_inference_server.ts`.
          * `useEffect` to auto-scroll `FlatList` when new messages arrive.
          * Global state (e.g., `Zustand` store) for `currentConversationId`, `activePersonalityId`.
      * **Routing:** `ConversationScreen` is the default tab in `MainTabView`.

2.  **CRUD Operations (UI Perspective):**

      * **Read Messages:** `ConversationScreen` performs a "Read" operation to fetch initial conversation history.
          * **Flow:** On component mount, `ConversationScreen` calls `MessageManager.getMessages(currentConversationId, pagination)` -\> `IPCService` to `data_manager.ts` to query `Messages` table.
      * **Create Message (User):**
          * **Flow (Voice):** `audio_processor.ts` streams audio to `ai_inference_server.ts` -\> `ai_inference_server.ts` sends `transcription_update` via WebSocket -\> `ConversationScreen` updates `currentTranscription`. When `isFinal` is true, `MessageManager.addMessage` is called.
          * **Flow (Text):** User types and presses send -\> `MessageManager.addMessage` is called.
          * `MessageManager` sends message data via `IPCService` to `data_manager.ts` to insert into `Messages` table.
      * **Create Message (AI):**
          * **Flow:** `ai_inference_server.ts` sends `ai_response_text` via WebSocket -\> `ConversationScreen` updates UI. Once full response received, `MessageManager.addMessage` is called to store AI's message.
          * `MessageManager` sends message data via `IPCService` to `data_manager.ts` to insert into `Messages` table.

3.  **User Experience Flow (UI Perspective):**

      * **Real-time Feedback:** Visual and textual indicators for AI's state (listening, thinking, speaking).
      * **Smooth Scrolling:** Ensure `FlatList` performs well with many messages.
      * **Typing vs. Voice:** Seamless switch between typing and voice input modes.

4.  **Security Considerations (UI Perspective):**

      * **Microphone Permission:** React Native will trigger the macOS system prompt for microphone access. The UI should guide the user if permission is denied.
      * **No Raw Audio Display:** Raw audio data is processed by the backend and never displayed in the UI.
      * **Consent Adherence:** If emotion/memory recording consent is denied, the UI should reflect this (e.g., disable related indicators or features).

5.  **Testing Strategy (UI Perspective):**

      * **Unit Tests:** Test `MessageBubble`, `VoiceInputIndicator`, `InputBar` components for rendering and basic interactions.
      * **Integration Tests:** Test WebSocket connection, real-time transcription updates, and message display. Mock backend responses.
      * **End-to-End Tests:** Simulate full voice conversations, verifying UI updates, message persistence, and AI response playback.

6.  **Error Handling & Logging (UI Perspective):**

      * **Connection Errors:** If WebSocket connection to backend fails, display a prominent error message (e.g., "Saira's brain is offline. Please restart the app.") and disable voice input.
      * **Transcription Errors:** If ASR fails, display "Could not understand. Please try again."
      * **LLM Errors:** If LLM fails to generate a response, display "Saira is having trouble thinking. Please try again."
      * **Audio Playback Errors:** Log errors if TTS audio fails to play.
      * **Logging:** Detailed logs of audio stream events, AI processing steps, and message storage.

-----

### Feature: Daily Check-ins & Journaling Screen

**Feature Goal (UI-specific)**
To provide a dedicated space for users to reflect on their emotional state, log daily moods, and create personal journal entries, with visual summaries of emotional patterns over time.

**Any API Relationships (UI-specific)**

  * **`JournalManager` (Frontend Service):** Creates, reads, updates, and deletes journal entries and mood summaries.
  * **`MessageManager` (Frontend Service):** May retrieve emotion data from past messages for mood summaries.
  * **`MemoryManager` (Frontend Service):** Journal entries can trigger memory formation.

**Detailed Feature Requirements (UI-specific)**

1.  **Daily Mood Summary (`JournalingScreen.tsx` - Main View):**

      * **Visuals:** A calendar-like view or a series of daily cards displaying aggregated mood data.
      * **Elements:**
          * Date navigation (e.g., left/right arrows to change day/week/month).
          * For each day:
              * Date display.
              * Aggregated mood representation (e.g., a dominant emoji, a color gradient, or a simple text summary like "Mostly Neutral").
              * Count of journal entries for that day.
              * Link/button to view/add journal entry for that day.
      * **Interactions:** Tapping a day navigates to its journal entry list/detail.
      * **States:** Loading state, empty state for days with no data.

2.  **Emotional Check-in Interface (`JournalingScreen.tsx` - Button/Modal):**

      * **Visuals:** A prominent button on the main journaling screen, or a modal that appears when triggered.
      * **Elements:**
          * Button: "How are you feeling today?"
          * **Modal/Screen:**
              * Headline: "Log Your Mood."
              * Mood picker: A visual slider for Arousal (Calm to Excited) and Valence (Negative to Positive), or a selection of emotion emojis/categories (e.g., Happy, Sad, Angry, Neutral).
              * Optional `TextInput`: "Add a note about your mood..."
              * Button: "Save Mood".
      * **Interactions:** Tapping the button opens the modal. Interacting with sliders/pickers updates mood selection. Tapping "Save Mood" submits the data.
      * **States:** Default, selected mood, saving.

3.  **Journal Entry List (`JournalingScreen.tsx` - Sub-section/Screen):**

      * **Visuals:** A scrollable list of journal entries, ordered by date.
      * **Elements:**
          * `FlatList` displaying `JournalEntryCard` components.
          * Each `JournalEntryCard` displays: Date, a snippet of the entry content, and a small mood indicator (if available).
          * Button: "New Journal Entry" (floating action button or prominent header button).
      * **Interactions:** Tapping a `JournalEntryCard` navigates to `JournalEntryDetailView`. Tapping "New Journal Entry" navigates to `JournalEntryCreationView`.
      * **States:** Loading, empty list.

4.  **Journal Entry Creation/Detail (`JournalEntryCreationView.tsx`/`JournalEntryDetailView.tsx`):**

      * **Visuals:** A dedicated screen for writing/editing a journal entry.
      * **Elements:**
          * Date/Time display (auto-filled, editable).
          * Large `TextInput` for journal content.
          * Optional: Mood picker (similar to check-in) if not already set.
          * Button: "Save Entry".
          * For detail view: "Edit" button, "Delete" button.
      * **Interactions:** Typing updates content. Tapping "Save Entry" persists. "Edit" makes content editable. "Delete" prompts confirmation then deletes.
      * **States:** Editing, viewing, saving, deleting.

**Detailed Implementation Guide (UI-specific)**

1.  **Frontend Architecture:**

      * **Component Hierarchy:** `JournalingScreen.tsx` will be the main tab screen. It will contain `MoodSummaryCalendar` and `JournalEntryList` components. `JournalEntryCreationView.tsx` and `JournalEntryDetailView.tsx` will be separate screens navigated to from `JournalingScreen`.
      * **Reusable Component Library:** `MoodSummaryCard`, `JournalEntryCard`, `DatePicker`, `Slider`, `EmojiPicker` (custom).
      * **State Management:**
          * `useState` for `selectedDate`, `journalEntries` array, `moodSummaries` array.
          * `useState` for `currentJournalContent`, `selectedMood`.
          * `useEffect` to fetch data from `JournalManager` based on `selectedDate` or filters.
          * Global state for `userId`.
      * **Routing:** `JournalingScreen` is a tab in `MainTabView`. `JournalEntryCreationView` and `JournalEntryDetailView` are pushed onto the `JournalingScreen`'s navigation stack.

2.  **CRUD Operations (UI Perspective):**

      * **Create Journal Entry:**
          * **Flow:** User types in `JournalEntryCreationView` -\> taps "Save Entry" -\> `JournalManager.createJournalEntry` is called.
          * `JournalManager` sends data via `IPCService` to `data_manager.ts` to insert into `JournalEntries` table.
          * Also triggers `JournalManager.generateMoodSummary` for the relevant date.
      * **Read Journal Entries:**
          * **Flow:** `JournalingScreen` or `JournalEntryList` mounts -\> `JournalManager.getJournalEntries` is called (with date range/pagination) -\> `IPCService` to `data_manager.ts` to query `JournalEntries`.
          * `JournalManager.getMoodSummaries` is called for the calendar view.
      * **Update Journal Entry:**
          * **Flow:** User edits in `JournalEntryDetailView` -\> taps "Save" -\> `JournalManager.updateJournalEntry` is called.
          * `JournalManager` sends data via `IPCService` to `data_manager.ts` to update `JournalEntries` table.
      * **Delete Journal Entry:**
          * **Flow:** User taps "Delete" in `JournalEntryDetailView` -\> confirmation dialog -\> `JournalManager.deleteJournalEntry` is called.
          * `JournalManager` sends data via `IPCService` to `data_manager.ts` to delete from `JournalEntries` table.

3.  **User Experience Flow (UI Perspective):**

      * **Intuitive Logging:** Easy access to mood check-in and new journal entry creation.
      * **Visual Summaries:** Mood calendar provides a quick overview of emotional trends.
      * **Seamless Editing:** Smooth transition from viewing to editing journal entries.

4.  **Security Considerations (UI Perspective):**

      * **Data Privacy:** Remind users about the privacy of their journal entries.
      * **Consent Adherence:** Ensure emotion data is only recorded/displayed if consent was given.

5.  **Testing Strategy (UI Perspective):**

      * **Unit Tests:** Test `MoodSummaryCard`, `JournalEntryCard`, `MoodPicker` components.
      * **Integration Tests:** Test the full flow of creating, viewing, editing, and deleting journal entries. Verify mood summary generation.
      * **End-to-End Tests:** Simulate a user logging moods and creating multiple journal entries over several days.

6.  **Error Handling & Logging (UI Perspective):**

      * **Save Errors:** Display "Failed to save entry. Please try again."
      * **Load Errors:** Display "Could not load journal entries."
      * **Logging:** Log all CRUD operations on journal entries and mood summaries.

-----

### Feature: Deep Talk Screen

**Feature Goal (UI-specific)**
To provide a specialized conversational mode that encourages deeper exploration of complex personal topics, leveraging Saira's long-term memory (RAG) to provide more insightful and context-rich responses.

**Any API Relationships (UI-specific)**

  * **`IPCService` (Frontend Service):** Sends audio/text input, receives AI responses, specifically optimized for RAG queries.
  * **`MemoryManager` (Frontend Service):** Triggers semantic search for relevant memories based on conversation context.
  * **`ConversationManager` (Frontend Service):** Manages the conversation session, potentially tagging it as a "Deep Talk" session.

**Detailed Feature Requirements (UI-specific)**

1.  **Specialized Conversation Interface:**

      * **Visuals:** Similar to the `ConversationScreen`, but with subtle visual cues indicating "Deep Talk Mode" (e.g., a different background color, a unique icon in the header).
      * **Elements:**
          * Chat history display (same as `ConversationScreen`).
          * Voice input indicator (same as `ConversationScreen`).
          * Real-time transcription display (same as `ConversationScreen`).
          * Input bar (same as `ConversationScreen`).
          * Optional: "Suggested Topics" or "Memory Prompts" area (e.g., a carousel of buttons with memory snippets or questions like "Tell me more about X event").
      * **Interactions:** Standard voice/text interaction. Tapping suggested topics injects them as a prompt.
      * **States:** Active Deep Talk session.

2.  **Memory Integration Indicators (Subtle):**

      * **Visuals:** When Saira's response is heavily influenced by a retrieved memory, a subtle visual indicator might appear (e.g., a small "memory" icon next to the AI's message, or a tooltip on hover revealing the source memory snippet). This is for transparency and to highlight Saira's RAG capability.
      * **Elements:** Small icon, tooltip/popover.
      * **Interactions:** Hovering/tapping the icon reveals the source memory.
      * **States:** Memory-augmented response, non-augmented response.

**Detailed Implementation Guide (UI-specific)**

1.  **Frontend Architecture:**

      * **Component Hierarchy:** `DeepTalkScreen.tsx` will largely reuse components from `ConversationScreen.tsx` (e.g., `MessageList`, `VoiceInputIndicator`, `InputBar`). It will wrap these in a container that applies Deep Talk specific styling.
      * **Reusable Component Library:** Existing chat components. New `MemoryHint` component.
      * **State Management:**
          * Inherits `conversationState` and `messages` state from a shared context or uses its own.
          * `useState` for `suggestedTopics` (populated by AI or based on recent memories).
          * Global state for `userId`, `currentConversationId`.
      * **Routing:** `DeepTalkScreen` is a tab in `MainTabView`.

2.  **CRUD Operations (UI Perspective):**

      * **Read Memories (for RAG):** This is the core "Read" operation.
          * **Flow:** When a user speaks/types in Deep Talk mode, the `ConversationScreen`'s ViewModel (or a dedicated `DeepTalkViewModel`) will:
            1.  Send the user's query to `ai_inference_server.ts`'s `/ai/embeddings/generate` to get an embedding.
            2.  Send the embedding to `ai_inference_server.ts`'s `/data/search_vectors` to retrieve relevant `Memories` from `sqlite-vec`.
            3.  These retrieved memories are then included in the LLM's prompt.
      * **Create/Read Messages:** Same as `ConversationScreen`.

3.  **User Experience Flow (UI Perspective):**

      * **Focused Interaction:** The UI should encourage deeper, more reflective conversations.
      * **Transparency:** Subtle indicators help the user understand when Saira is drawing from its memory.

4.  **Security Considerations (UI Perspective):**

      * **Memory Visibility:** Ensure that only memories marked `is_active` and allowed by `memory_visibility_rules` are retrieved and used for RAG. The UI should reflect these settings.

5.  **Testing Strategy (UI Perspective):**

      * **Integration Tests:** Test the RAG pipeline: simulate a query, verify that relevant memories are retrieved from the mocked backend, and that the LLM response incorporates them.
      * **End-to-End Tests:** Simulate a Deep Talk session where the user asks about a past event, and Saira responds with details from a previously ingested memory.

6.  **Error Handling & Logging (UI Perspective):**

      * **RAG Failure:** If memory retrieval or embedding generation fails, the LLM should still attempt to respond, but the UI might show a subtle warning that "Saira couldn't access all its memories."
      * **Performance:** Monitor RAG query latency. If too slow, provide feedback (e.g., "Saira is thinking deeply...").

-----

### Feature: Profile Settings Screen

**Feature Goal (UI-specific)**
To provide a centralized hub for users to customize Saira's behavior, manage their data, configure privacy settings, and update AI models.

**Any API Relationships (UI-specific)**

  * **`UserManager` (Frontend Service):** Reads/updates user preferences, privacy settings, and triggers data export/deletion.
  * **`PersonalityManager` (Frontend Service):):** Reads/updates personality profiles.
  * **`ModelManager` (Frontend Service):** Reads model versions, triggers model downloads.
  * **`SyncService` (Frontend Service):** Configures sync, initiates sync, handles recovery keys.
  * **`NudgeManager` (Frontend Service):** Reads/updates nudge preferences.

**Detailed Feature Requirements (UI-specific)**

1.  **Main Settings Navigation (`ProfileSettingsScreen.tsx`):**

      * **Visuals:** A list of categories (e.g., "General," "Personality," "Privacy & Data," "AI Models," "Notifications," "Sync").
      * **Elements:**
          * `FlatList` of `SettingsCategoryItem` components.
          * Each item: Icon, Category Name, disclosure indicator ("\>").
      * **Interactions:** Tapping a category navigates to its dedicated sub-screen.
      * **States:** Loading, default.

2.  **General Settings (`GeneralSettingsScreen.tsx`):**

      * **Visuals:** Basic user profile information.
      * **Elements:**
          * User's Name (`TextInput`).
          * Profile Picture (display, button to change).
          * Preferred Tone Style (radio buttons/dropdown).
      * **Interactions:** Editing fields updates user data.
      * **States:** Editing, saving.

3.  **Personality Settings (`PersonalitySettingsScreen.tsx`):**

      * **Visuals:** List of available personality profiles, with the active one highlighted.
      * **Elements:**
          * Headline: "Saira's Personality."
          * `FlatList` of `PersonalityProfileCard` components:
              * Each card: Name, description, "Activate" button (if not active).
              * Active card has a distinct visual style.
          * Button: "Create Custom Personality" (navigates to `CustomPersonalityCreationScreen`).
      * **Interactions:** Tapping "Activate" changes Saira's active personality.
      * **States:** Loading, active/inactive profiles.

4.  **Privacy & Data Settings (`PrivacyDashboardScreen.tsx`):**

      * **Visuals:** A dashboard for managing data consents and privacy actions.
      * **Elements:**
          * Toggle: "Allow emotion recording from voice."
          * Toggle: "Allow memory recording from conversations."
          * Button: "View Audit Logs" (opens `AuditLogsScreen`).
          * Button: "Export All My Data" (triggers data export).
          * Button: "Delete All My Data" (triggers data deletion, with confirmation).
          * Link to Privacy Policy.
      * **Interactions:** Toggling changes consent. Buttons trigger respective actions.
      * **States:** Toggles on/off, processing states for export/delete.

5.  **AI Models Settings (`AIModelManagementScreen.tsx`):**

      * **Visuals:** List of currently loaded AI models and their versions.
      * **Elements:**
          * For each model (LLM, ASR, TTS, SER, Embedding):
              * Model Name (e.g., "Mistral 7B," "Whisper.cpp").
              * Current Version.
              * Status (e.g., "Loaded," "Updating," "Available Update").
              * Button: "Check for Updates" (for all models).
              * Button: "Download Update" (if available for a specific model).
              * Button: "Rollback to Previous Version" (if applicable).
      * **Interactions:** Tapping "Download Update" initiates download.
      * **States:** Loading, up-to-date, update available, downloading, installing, error.

6.  **Notifications Settings (`NotificationSettingsScreen.tsx`):**

      * **Visuals:** Controls for proactive nudges.
      * **Elements:**
          * Toggle: "Enable Proactive Nudges."
          * List of Nudge Types (e.g., "Reminders," "Positive Reinforcement," "Wellness Suggestions").
          * For each type: Toggle to enable/disable, frequency picker (Daily, Weekly, Event-based), time picker.
      * **Interactions:** Toggling enables/disables nudges. Adjusting frequency/time updates preferences.
      * **States:** Enabled/disabled, configured.

7.  **Sync Settings (`SyncSettingsScreen.tsx`):**

      * **Visuals:** Controls for optional cloud synchronization.
      * **Elements:**
          * Toggle: "Enable Cloud Sync."
          * Input fields for cloud service credentials (if using a generic E2EE service like EteSync).
          * Dropdown: "Sync Frequency" (Manual, Daily, Weekly, On App Close).
          * Display: "Last Synced At:"
          * Display: "Current Status:"
          * Button: "Sync Now".
          * Button: "Generate Recovery Key" (for E2EE data).
          * Button: "Resolve Conflicts" (if conflicts detected).
      * **Interactions:** Toggling enables/disables sync. Buttons trigger sync, key generation, or conflict resolution.
      * **States:** Enabled/disabled, syncing, synced, conflicts, error.

**Detailed Implementation Guide (UI-specific)**

1.  **Frontend Architecture:**

      * **Component Hierarchy:** `ProfileSettingsScreen.tsx` will be the root of the settings tab, using `React Navigation`'s stack navigator to push sub-screens (e.g., `GeneralSettingsScreen`, `PrivacyDashboardScreen`).
      * **Reusable Component Library:** `ToggleSwitch`, `TextInput`, `Button`, `Picker`, `List` components.
      * **State Management:**
          * `useState` for local form inputs within each settings sub-screen.
          * `useEffect` to load initial settings data from relevant managers (`UserManager`, `PersonalityManager`, etc.).
          * `useCallback` for debouncing input changes before saving to backend.
          * Global state for `userId`, `currentPersonalityId`, `syncStatus`.
      * **Routing:** `ProfileSettingsScreen` is a tab in `MainTabView`. Sub-screens are pushed onto its own navigation stack.

2.  **CRUD Operations (UI Perspective):**

      * **User Preferences (Update `Users` table):**
          * **Flow:** User changes name, tone, sync settings, nudge preferences -\> `UserManager.updateUser` or `NudgeManager.updateNudgePreference` is called.
          * `IPCService` sends updates to `data_manager.ts` to update `Users` or `NudgePreferences` table.
      * **Personality Profiles (Read/Update `PersonalityProfiles` table):**
          * **Flow:** `PersonalitySettingsScreen` loads `PersonalityManager.getPersonalityProfiles()`. User taps "Activate" -\> `PersonalityManager.activatePersonalityProfile` updates `Users.current_personality_profile_id`.
      * **Privacy Consents (Update `Users` table):**
          * **Flow:** Toggling consent switches calls `UserManager.updatePrivacySettings`.
      * **Data Export/Deletion (Trigger Backend Process):**
          * **Flow:** User clicks "Export" -\> `UserManager.exportData()` calls `IPCService` to trigger a Python script (`data_exporter.py`) in the backend.
          * User clicks "Delete" -\> confirmation -\> `UserManager.deleteUser()` calls `IPCService` to `data_manager.ts` to delete user data.
      * **AI Model Management (Read/Update Model Files):**
          * **Flow:** `AIModelManagementScreen` loads `ModelManager.getLoadedModels()`. User clicks "Download Update" -\> `ModelManager.downloadModelUpdate()` calls `IPCService` to `model_manager.ts` (Node.js) which uses `model_downloader.py` (Python) to download the model.
          * `model_manager.ts` then loads the new model into the `ai_inference_addon`.

3.  **User Experience Flow (UI Perspective):**

      * **Clear Categorization:** Settings are logically grouped to prevent overwhelming the user.
      * **Instant Feedback:** Toggles and input fields update immediately.
      * **Confirmation:** Critical actions (e.g., data deletion) require explicit confirmation.
      * **Progress Indicators:** Show progress for long-running operations like model downloads or data exports.

4.  **Security Considerations (UI Perspective):**

      * **Sensitive Data Input:** If cloud sync requires credentials, ensure input fields are secure (e.g., password masking).
      * **Consent Visibility:** Clearly display current consent status for sensitive data processing.
      * **Confirmation for Destructive Actions:** Double-confirm data deletion.
      * **Recovery Key Display:** When generating a recovery key, display it prominently with warnings about secure storage.

5.  **Testing Strategy (UI Perspective):**

      * **Unit Tests:** Test individual settings components (e.g., `ToggleSwitch`, `Picker`).
      * **Integration Tests:** Test data loading and saving for each settings section. Simulate model downloads and sync processes.
      * **End-to-End Tests:** Simulate a user changing various settings, verifying persistence and impact on app behavior (e.g., personality change affects LLM response).

6.  **Error Handling & Logging (UI Perspective):**

      * **Save Errors:** Display "Failed to save settings. Please try again." for backend save failures.
      * **Download Errors:** Display "Failed to download model update." for model download failures.
      * **Sync Errors:** Display "Sync failed. Check network or credentials." for sync issues.
      * **Deletion Errors:** Display "Failed to delete data."
      * **Logging:** Log all settings changes, sync events, model updates, and data export/deletion attempts.

-----

### Feature: Proactive Nudges & Notifications

**Feature Goal (UI-specific)**
To proactively engage the user with timely reminders, positive reinforcement, and wellness suggestions, delivered through macOS system notifications and an in-app history.

**Any API Relationships (UI-specific)**

  * **`NotificationService` (Frontend Service):** Registers for and displays macOS system notifications.
  * **`NudgeManager` (Frontend Service):** Manages nudge preferences and records nudge history.
  * **`ai_inference_server.ts` (Node.js Backend):** The LLM in the backend will generate nudge content based on user data and preferences.
  * **`data_manager.ts` (Node.js Backend):** Stores nudge preferences and history.

**Detailed Feature Requirements (UI-specific)**

1.  **Notification Display (macOS System Level):**

      * **Visuals:** Standard macOS notification banners/alerts.
      * **Elements:**
          * App icon.
          * Title (e.g., "Saira Check-in," "Saira Motivation").
          * Body text (the nudge message, e.g., "How are you feeling today?").
          * Optional: Action buttons (e.g., "Log Mood," "Dismiss").
      * **Interactions:** User can click on the notification to open the app to a relevant screen (e.g., Journaling screen for mood check-in).
      * **States:** Delivered, interacted.

2.  **In-App Nudge History (`NotificationSettingsScreen.tsx` - Sub-section):**

      * **Visuals:** A scrollable list of past nudges.
      * **Elements:**
          * `FlatList` displaying `NudgeHistoryItem` components.
          * Each item: Date/Time, Nudge Type, Message Content.
          * Optional: Icon indicating if user interacted with it.
      * **Interactions:** User can review past nudges.
      * **States:** Loading, empty list.

3.  **Nudge Configuration (Part of `ProfileSettingsScreen.tsx` -\> `NotificationSettingsScreen.tsx`):**

      * **Visuals:** Toggles and selectors for customizing nudge behavior.
      * **Elements:**
          * Toggle: "Enable Proactive Nudges."
          * Section for "Nudge Types":
              * For each type (e.g., "Reminders," "Positive Reinforcement," "Wellness Suggestions"):
                  * Toggle to enable/disable.
                  * Dropdown/Picker for "Frequency" (Daily, Weekly, Event-based).
                  * Time picker for daily/weekly nudges.
          * Button: "Customize Nudge Content" (future feature, opens a modal for prompt templates).
      * **Interactions:** Toggling enables/disables. Selecting frequency/time updates preferences.
      * **States:** Enabled/disabled, configured.

**Detailed Implementation Guide (UI-specific)**

1.  **System Architecture Overview:**
      * **High-level Architecture:** Nudge generation logic resides in the Node.js
