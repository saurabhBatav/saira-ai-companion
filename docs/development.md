# Development Guide

Welcome to the Saira AI Companion development guide! This document helps new and existing contributors set up, develop, test, and maintain code effectively.

---

## 1. Prerequisites

- **Node.js:** 18+
- **Python:** 3.9+
- **macOS:** 12+ (for Mac app)
- **iOS:** 15+ (for iPhone app)
- **Recommended:** Docker (for future containerization support)

---

## 2. Setting Up Your Environment

```bash
# Clone the repository
git clone https://github.com/saurabhBatav/saira-ai-companion.git
cd saira-ai-companion

# Install dependencies
npm install
pip install -r requirements.txt

# Set up development environment (if needed)
npm run setup:dev
```

- Refer to `config/` and `.env.example` for environment variable setup.
- For iOS development, open `src/mobile/` in Xcode and install dependencies as needed.

---

## 3. Codebase Structure

```plaintext
src/
  core/         # Core AI and logic
  voice/        # Speech processing
  emotion/      # Emotion analysis
  memory/       # Memory management
  ui/           # User interface
  mobile/       # iOS app
  speaker/      # Smart speaker
docs/           # Documentation
tests/          # Tests
scripts/        # Automation/deployment
config/         # Environment configs
```

See [docs/architecture.md](architecture.md) for a detailed breakdown.

---

## 4. Coding Standards

- **JavaScript/TypeScript:** Use Prettier and ESLint.
  ```bash
  npm run lint
  npm run format
  ```
- **Python:** Follow PEP8. Use Black and Flake8.
  ```bash
  black .
  flake8 .
  ```
- Add/maintain type annotations (Python) and JSDoc/TSDoc (JS/TS).
- Keep code modular, documented, and well-tested.

---

## 5. Running & Testing

- **Start development server:**

  ```bash
  npm run dev
  ```

- **Run tests:**

  ```bash
  npm run test     # JS/TS
  pytest           # Python
  ```

- **Coverage reports:**
  - JS/TS: `npm run test:coverage`
  - Python: `pytest --cov`

---

## 6. Documentation

- All major changes must update docs in `docs/`.
- API changes: update `docs/api/`.
- Architecture or process changes: update `docs/architecture.md` and `docs/development.md`.
- Use `mkdocs serve` to preview docs locally.

---

## 7. Submitting Changes

- Follow the [CONTRIBUTING.md](contribution.md) guidelines for branching, commits, and PRs.
- Ensure all tests and linting pass before submitting a PR.
- Reference related issues in your PR description.

---

## 8. Troubleshooting

- Check [GitHub Issues](https://github.com/saurabhBatav/saira-ai-companion/issues) for common problems.
- Ask for help in Discussions or contact maintainers.

---

_Last updated: 2025-06-09_
