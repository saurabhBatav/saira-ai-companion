# 🤝 Contributing to Saira

Thank you for your interest in contributing to Saira! This document provides comprehensive guidelines for contributing to the project.

## 🚀 Getting Started

### Prerequisites
- Node.js 18+ and npm 8+
- Python 3.9+ and pip
- Git
- GitHub CLI (recommended)

### Development Setup
1. **Fork the repository**
   ```bash
   gh repo fork saurabhBatav/saira-ai-companion --clone
   ```

2. **Navigate to the project**
   ```bash
   cd saira-ai-companion
   ```

3. **Install dependencies**
   ```bash
   npm install
   pip install -r requirements.txt
   ```

4. **Set up development environment**
   ```bash
   npm run setup:dev
   ```

5. **Create a new branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

## 📋 Development Workflow

### Branch Naming Convention
- `feature/feature-name` - New features
- `bugfix/bug-description` - Bug fixes
- `docs/documentation-update` - Documentation changes
- `refactor/component-name` - Code refactoring
- `test/test-description` - Test additions/updates

### Commit Message Format
Follow the [Conventional Commits](https://www.conventionalcommits.org/) specification:

```
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

**Types:**
- `feat`: A new feature
- `fix`: A bug fix
- `docs`: Documentation only changes
- `style`: Changes that do not affect the meaning of the code
- `refactor`: A code change that neither fixes a bug nor adds a feature
- `test`: Adding missing tests or correcting existing tests
- `chore`: Changes to the build process or auxiliary tools

**Examples:**
```bash
feat(voice): add wake word detection
fix(emotion): resolve emotion classification accuracy
docs: update API documentation
test(memory): add vector database tests
```

## 🧪 Testing

### Running Tests
```bash
# Run all tests
npm test

# Run tests in watch mode
npm run test:watch

# Run E2E tests
npm run test:e2e

# Run Python tests
python -m pytest tests/
```

### Writing Tests
- Write unit tests for all new functions
- Add integration tests for new features
- Update existing tests when modifying functionality
- Ensure all tests pass before submitting PR

## 🎨 Code Style

### JavaScript/TypeScript
- Use ESLint configuration provided
- Follow Prettier formatting
- Use meaningful variable names
- Add JSDoc comments for functions

### Python
- Follow PEP 8 style guide
- Use Black for formatting
- Add type hints where appropriate
- Use docstrings for functions and classes

### General Guidelines
- Keep functions small and focused
- Use descriptive commit messages
- Comment complex logic
- Remove unused code and imports

## 📚 Documentation

### Code Documentation
- Add JSDoc/docstring comments for all public functions
- Include parameter and return type information
- Provide usage examples for complex functions

### README Updates
- Update README.md if your changes affect setup or usage
- Add new features to the features list
- Update installation instructions if needed

## 🔍 Pull Request Process

### Before Submitting
1. **Test your changes**
   ```bash
   npm test
   npm run lint
   python -m pytest
   ```

2. **Update documentation**
   - Update relevant documentation files
   - Add inline code comments
   - Update README if necessary

3. **Check your branch**
   ```bash
   git checkout main
   git pull origin main
   git checkout your-feature-branch
   git rebase main
   ```

### Submitting Your PR
1. **Push your branch**
   ```bash
   git push origin feature/your-feature-name
   ```

2. **Create Pull Request**
   - Use the provided PR template
   - Write a clear description of changes
   - Reference related issues
   - Add screenshots if UI changes are involved

3. **Address Review Feedback**
   - Respond to reviewer comments
   - Make requested changes
   - Push updates to the same branch

## 🐛 Reporting Issues

### Bug Reports
Use the bug report template and include:
- Clear description of the issue
- Steps to reproduce
- Expected vs actual behavior
- Environment details (OS, version, device)
- Screenshots or error logs

### Feature Requests
Use the feature request template and include:
- Clear description of the proposed feature
- Problem it solves
- Proposed solution
- Alternative approaches considered

## 🏷️ Issue Labels

### Priority Labels
- `critical` - Urgent issues that block functionality
- `high-priority` - Important issues to address soon
- `medium-priority` - Standard priority issues
- `low-priority` - Nice-to-have improvements

### Type Labels
- `bug` - Something isn't working
- `enhancement` - New feature or request
- `documentation` - Improvements to documentation
- `question` - Further information is requested

### Component Labels
- `voice` - Voice processing related
- `emotion` - Emotion detection related
- `memory` - Memory system related
- `ui-ux` - User interface/experience
- `mobile` - iOS app related
- `speaker` - Smart speaker related

## 🎯 Project Phases

We're currently working through these phases:

1. **Phase 1**: Planning & Setup (Current)
2. **Phase 2**: Core Architecture Development
3. **Phase 3**: Feature Integration & Proactive Intelligence
4. **Phase 4**: Multi-Modal Output & Emotional UX
5. **Phase 5**: UI/UX Polish & Feedback Loops
6. **Phase 6**: Cross-Platform Support & Device Sync
7. **Phase 7**: Launch & Iteration Cycles

See our [Project Board](https://github.com/saurabhBatav/saira-ai-companion/projects) for current status.

## 🔒 Security

### Reporting Security Issues
Please do not report security vulnerabilities through public GitHub issues.
Instead, email security@saira-ai.com with:
- Description of the vulnerability
- Steps to reproduce
- Potential impact
- Any suggested fixes

### Security Guidelines
- Never commit sensitive data (API keys, passwords, etc.)
- Use environment variables for configuration
- Follow secure coding practices
- Validate all user inputs

## 📞 Getting Help

### Communication Channels
- 💬 [GitHub Discussions](https://github.com/saurabhBatav/saira-ai-companion/discussions)
- 🐛 [GitHub Issues](https://github.com/saurabhBatav/saira-ai-companion/issues)
- 📧 Email: contributors@saira-ai.com

### Resources
- [Project Documentation](docs/)
- [API Reference](docs/api/)
- [Architecture Guide](docs/architecture/)
- [Development Setup](docs/development.md)

## 🏆 Recognition

Contributors will be recognized in:
- README.md contributors section
- Release notes for significant contributions
- Annual contributor appreciation posts

## 📜 License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

Thank you for contributing to Saira! Your efforts help make AI more human and accessible. 🙏
