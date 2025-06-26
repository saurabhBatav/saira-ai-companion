# 🧠 SairaBackendServices

This directory houses the backend services for **Saira – The Emotion-Aware Life Companion AI**. It provides Node.js (TypeScript) and Python-based services to handle AI inference, audio I/O, SQLite data operations, and native addon integrations. Designed for cross-process communication with the macOS frontend, this backend acts as the brain and memory core of the assistant.

---

## 🚀 Getting Started

### 1. Clone the Repository (if needed)

```bash
git clone https://github.com/your-org/saira-ai-companion.git
cd saira-ai-companion/SairaBackendServices
```

### 2. Install Node.js Dependencies

```bash
npm install
```

### 3. Setup Environment Variables

Create a `.env` file at the root of `SairaBackendServices/` with the following content:

```env
PORT=5000
LOG_LEVEL=debug
```

You can extend this for dev/staging/production environments later.

### 4. Start the Backend in Development Mode

```bash
npm run dev
```

This uses `ts-node-dev` for hot reloading with TypeScript.

---

## 🧱 Project Structure

```
SairaBackendServices/
├── package.json                 # Node.js dependencies and scripts
├── tsconfig.json               # TypeScript configuration
├── Dockerfile                  # Dev environment setup (optional)
├── .env                        # Environment variables
├── tests/                      # Jest/Pytest test suites

├── src/
│   ├── node_services/          # Core Node.js services (TypeScript)
│   │   ├── main.ts             # App entry point
│   │   ├── ai_inference_server.ts
│   │   ├── audio_processor.ts
│   │   ├── data_manager.ts
│   │   ├── model_manager.ts
│   │   ├── ipc_handler.ts
│   │   ├── task_manager.ts
│   │   ├── routes/             # REST API routes
│   │   ├── controllers/        # HTTP logic
│   │   ├── services/           # Business logic modules
│   │   ├── middleware/         # Logging, error handling
│   │   └── utils/              # Logging, validation, helpers

│   ├── python_services/        # Python scripts for AI workflows
│   │   ├── rag_ingestion.py
│   │   ├── model_downloader.py
│   │   └── ser_feature_extractor.py

│   ├── native_addons/          # C++ addons (built using N-API)
│   │   ├── audio_io_addon/
│   │   │   ├── binding.gyp
│   │   │   └── src/audio_io.cpp
│   │   ├── ai_inference_addon/
│   │   │   └── src/ai_inference.cpp
│   │   └── sqlite_vec_addon/
│   │       └── src/sqlite_vec.cpp

│   └── models/                 # Pretrained model downloads
│       ├── llm/
│       ├── asr/
│       ├── tts/
│       ├── ser/
│       └── embeddings/
```

---

## 🔌 Available API Endpoints

### Health Check

```
GET /api/v1/health
```

**Response:**

```json
{
  "status": "ok",
  "service": "SairaBackend",
  "timestamp": "2025-06-26T14:15:22Z"
}
```

All APIs are versioned using `/api/v1/...` route prefixes.

---

## 🧪 Running Tests

### Node.js Services (Jest)

```bash
npm run test
```

### Python Services (Pytest)

```bash
cd src/python_services
pytest
```

Test folders and configs will be expanded in future phases.

---

## 🔧 Tooling & Libraries

| Purpose             | Tool / Library       |
| ------------------- | -------------------- |
| HTTP Server         | Express.js           |
| TypeScript          | ts-node-dev, tsc     |
| Environment Config  | dotenv               |
| Logging             | Winston              |
| Hot Reloading       | ts-node-dev          |
| Python AI Scripts   | PyTorch, HuggingFace |
| Native Addons (C++) | Node-API / N-API     |

---

## ✅ Development Scripts

| Command         | Description                        |
| --------------- | ---------------------------------- |
| `npm run dev`   | Start server with hot-reloading    |
| `npm run build` | Compile TS files to JS (dist/)     |
| `npm start`     | Start server from compiled JS      |
| `npm run test`  | Run Jest tests                     |
| `npm run lint`  | Run ESLint on all TypeScript files |

---

## 🛡️ Error Handling

- Errors are caught by centralized error-handling middleware (`src/node_services/middleware/errorHandler.ts`).
- Friendly error messages and HTTP status codes are returned to clients.
- Errors are also logged via Winston for diagnostics.

---

## 📦 Environment Variables

Add your secrets to `.env`:

```env
PORT=5000
LOG_LEVEL=debug
DATABASE_URL=/path/to/sqlite.db
OPENAI_API_KEY=your-api-key
```

---

## 🧠 Future Enhancements

- AI inference API (chat, TTS, SER, etc.)
- SQLite vector search support
- WebSocket server for real-time streaming
- Auth + secure session tokens
- Async task queue for model loading

---

## 👥 Contributors

Maintained by the Saira AI Team(@saurabhbatav).

---

## 📝 License

MIT

---
