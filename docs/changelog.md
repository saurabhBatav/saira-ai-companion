# 📘 Changelog

All notable changes to the **Saira – Emotion-Aware AI Companion** project will be documented in this file.

This project adheres to [Semantic Versioning](https://semver.org/) and follows the [Keep a Changelog](https://keepachangelog.com/en/1.0.0/) principles.

---

## [Unreleased]

### Added

- Initialized monorepo structure with `SairaReactNativeApp` and `SairaBackendServices`
- Set up React Native for macOS with TypeScript and ESLint
- Implemented initial folder structure for frontend (components, screens, services)
- Integrated React Navigation with macOS support
- Created reusable `Button` and `TextInput` components
- Implemented basic theme provider (light theme)
- Added root-level error boundary handling for UI errors

- Set up Node.js backend with Express, TypeScript, and dotenv
- Implemented `/api/v1/health` endpoint for server readiness check
- Added Winston logging and error-handling middleware
- Configured ts-node-dev for live reload during development
- Established service architecture: `ai_inference_server`, `data_manager`, `ipc_handler`, etc.
- Stubbed Python services for model downloading and RAG ingestion

- Integrated MkDocs for project documentation
- Added GitHub Actions workflow for automated docs build and deployment

---

## [0.1.0] – 2025-06-26

### Initial Milestone

✅ **Frontend:**

- React Native macOS project bootstrapped
- TypeScript, ESLint, Prettier integrated
- Functional Hello World screen added

✅ **Backend:**

- Node.js project initialized with TypeScript support
- Express server with health check endpoint working
- Development config and logger set up

✅ **Documentation:**

- MkDocs configured for technical documentation
- CI/CD set up to deploy docs to GitHub Pages

---

## [0.0.1] – 2025-06-17

### Project Bootstrap

- Initialized Git repository and project structure
- Added `README.md`, `LICENSE`, and `.gitignore`
- Set up initial `docs/` folder and MkDocs YAML config

---

> ℹ️ Upcoming versions will include model integration, voice pipeline, journaling, emotional memory features, and cross-device sync.
