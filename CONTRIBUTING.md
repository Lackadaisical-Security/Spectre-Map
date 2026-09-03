# Contributing to SpectreMap

Thank you for your interest in contributing to SpectreMap! This document provides guidelines for contributing to the project.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [Development Process](#development-process)
- [Pull Request Process](#pull-request-process)
- [Coding Standards](#coding-standards)
- [Testing Guidelines](#testing-guidelines)
- [Documentation](#documentation)
- [Security](#security)
- [License](#license)

## Code of Conduct

This project adheres to a [Code of Conduct](CODE_OF_CONDUCT.md). By participating, you are expected to uphold this code. Please report unacceptable behavior to lackadaisicalresearch@pm.me.

## Getting Started

### Prerequisites

Before contributing, ensure you have:

* C++17 compatible compiler (GCC 8+, Clang 7+, MSVC 2019+)
* CMake 3.16 or higher
* Qt 6.6.0 or higher
* OpenSSL 3.x
* SQLite 3.x
* Git for version control

### Setting Up Development Environment

1. **Fork the Repository**
   ```bash
   # Fork via GitHub UI, then clone your fork
   git clone https://github.com/YOUR_USERNAME/SpectreMap.git
   cd SpectreMap
   ```

2. **Add Upstream Remote**
   ```bash
   git remote add upstream https://github.com/Lackadaisical-Security/SpectreMap.git
   ```

3. **Install Dependencies**
   ```bash
   # Ubuntu/Debian
   sudo apt install build-essential cmake qt6-base-dev qt6-tools-dev \
                    libqt6opengl6-dev libssl-dev libsqlite3-dev

   # macOS
   brew install cmake qt6 openssl sqlite3

   # Windows
   # See docs/WINDOWS_BUILD.md
   ```

4. **Build in Debug Mode**
   ```bash
   mkdir build && cd build
   cmake -DCMAKE_BUILD_TYPE=Debug ..
   make -j$(nproc)
   ```

5. **Run Tests**
   ```bash
   make test
   ```

## Development Process

### Branching Strategy

* `main` - Stable production releases
* `develop` - Integration branch for features
* `feature/feature-name` - Feature branches
* `bugfix/bug-description` - Bug fix branches
* `security/cve-id` - Security patches

### Workflow

1. **Create a Feature Branch**
   ```bash
   git checkout -b feature/amazing-feature develop
   ```

2. **Make Changes**
   * Write code following [Coding Standards](#coding-standards)
   * Add tests for new functionality
   * Update documentation as needed

3. **Commit Changes**
   ```bash
   git add .
   git commit -m "feat: add amazing feature"
   ```

4. **Keep Your Branch Updated**
   ```bash
   git fetch upstream
   git rebase upstream/develop
   ```

5. **Push Changes**
   ```bash
   git push origin feature/amazing-feature
   ```

6. **Create Pull Request**
   * Open a PR against the `develop` branch
   * Fill out the PR template completely
   * Link related issues

### Commit Message Guidelines

Follow [Conventional Commits](https://www.conventionalcommits.org/):

```
<type>(<scope>): <subject>

<body>

<footer>
```

**Types:**
* `feat`: New feature
* `fix`: Bug fix
* `docs`: Documentation only
* `style`: Code style changes (formatting, etc.)
* `refactor`: Code refactoring
* `perf`: Performance improvements
* `test`: Adding or updating tests
* `chore`: Build process or auxiliary tool changes
* `security`: Security-related changes

**Examples:**
```
feat(api): add REST API endpoint for data queries

Add new /api/query endpoint that allows filtering data
by multiple criteria including date range and metadata.

Closes #123
```

```
fix(crypto): resolve memory leak in encryption manager

Fixed memory leak caused by improper cleanup of
OpenSSL contexts in error paths.

Fixes #456
```

```
security(auth): patch authentication bypass vulnerability

Implement proper token validation to prevent authentication
bypass. This addresses a critical security issue where
expired tokens were still being accepted.

CVE-2025-XXXXX
```

## Pull Request Process

### Before Submitting

- [ ] Code follows project style guidelines
- [ ] All tests pass
- [ ] New tests added for new features
- [ ] Documentation updated
- [ ] Commit messages follow convention
- [ ] No merge conflicts with develop branch
- [ ] Security implications considered

### PR Checklist

1. **Title**: Clear, descriptive title
2. **Description**: What, why, and how
3. **Type**: Bug fix, feature, documentation, etc.
4. **Testing**: How was it tested?
5. **Screenshots**: For UI changes
6. **Breaking Changes**: Note any breaking changes
7. **Related Issues**: Link related issues

### Review Process

1. **Automated Checks**: CI/CD pipeline must pass
2. **Code Review**: At least one maintainer approval required
3. **Security Review**: Security-sensitive changes require additional review
4. **Testing**: Reviewers may request additional tests
5. **Documentation**: Reviewers may request documentation updates

### Merge Requirements

* All CI checks passing
* At least one approving review
* No unresolved conversations
* Up-to-date with target branch
* Commit messages follow convention

## Coding Standards

### C++ Style

Follow [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) with modifications:

* **Indentation**: 4 spaces (no tabs)
* **Line Length**: 120 characters max
* **Naming**:
  * Classes: `PascalCase`
  * Functions/Methods: `camelCase`
  * Variables: `camelCase`
  * Constants: `UPPER_SNAKE_CASE`
  * Private members: `m_camelCase`

### Example

```cpp
class NetworkScanner {
public:
    NetworkScanner();
    ~NetworkScanner();
    
    bool initialize();
    void shutdown();
    
    std::vector<ScanResult> scanNetwork(const std::string& cidr);

private:
    bool m_initialized;
    std::mutex m_scanMutex;
    
    bool validateCIDR(const std::string& cidr) const;
};
```

### Security Considerations

* **Input Validation**: Always validate and sanitize input
* **Error Handling**: Proper error handling, no exceptions in destructors
* **Memory Safety**: Use RAII, smart pointers, avoid raw `new`/`delete`
* **Thread Safety**: Document thread safety, use mutexes appropriately
* **Cryptography**: Use established libraries (OpenSSL), never roll your own crypto
* **Logging**: Log security events, avoid logging sensitive data

### Code Quality

* **Comments**: Explain *why*, not *what*
* **Documentation**: Doxygen-style comments for public APIs
* **Complexity**: Keep functions under 50 lines when possible
* **DRY**: Don't Repeat Yourself
* **SOLID**: Follow SOLID principles

## Testing Guidelines

### Test Structure

```
tests/
├── unit/          # Unit tests
├── integration/   # Integration tests
├── security/      # Security tests
└── performance/   # Performance benchmarks
```

### Writing Tests

Use Google Test framework:

```cpp
#include <gtest/gtest.h>
#include "core/network_scanner.h"

class NetworkScannerTest : public ::testing::Test {
protected:
    void SetUp() override {
        scanner = std::make_unique<NetworkScanner>();
        ASSERT_TRUE(scanner->initialize());
    }
    
    void TearDown() override {
        scanner->shutdown();
    }
    
    std::unique_ptr<NetworkScanner> scanner;
};

TEST_F(NetworkScannerTest, ValidCIDR) {
    auto results = scanner->scanNetwork("192.168.1.0/24");
    EXPECT_FALSE(results.empty());
}

TEST_F(NetworkScannerTest, InvalidCIDR) {
    auto results = scanner->scanNetwork("invalid");
    EXPECT_TRUE(results.empty());
}
```

### Test Coverage

* **Minimum**: 70% code coverage
* **Critical Paths**: 90%+ coverage for security-critical code
* **New Features**: 80%+ coverage required

### Running Tests

```bash
# All tests
make test

# Specific test
./tests/unit/network_scanner_test

# With coverage
cmake -DENABLE_COVERAGE=ON ..
make coverage
```

## Documentation

### Code Documentation

Use Doxygen format:

```cpp
/**
 * @brief Scans a network for active hosts
 * 
 * Performs a TCP SYN scan on the specified CIDR range to identify
 * active hosts and open ports.
 * 
 * @param cidr Network range in CIDR notation (e.g., "192.168.1.0/24")
 * @param ports Port list to scan (default: common ports)
 * @param timeout Scan timeout in milliseconds (default: 1000)
 * @return Vector of scan results with discovered hosts and ports
 * 
 * @throws std::invalid_argument if CIDR format is invalid
 * 
 * @note Requires administrator/root privileges
 * @warning May trigger IDS/IPS systems
 * 
 * @example
 * NetworkScanner scanner;
 * auto results = scanner.scanNetwork("10.0.0.0/24");
 * for (const auto& result : results) {
 *     std::cout << "Host: " << result.ip << std::endl;
 * }
 */
std::vector<ScanResult> scanNetwork(const std::string& cidr,
                                     const std::vector<uint16_t>& ports = {},
                                     int timeout = 1000);
```

### README Updates

Update README.md for:
* New features
* Changed APIs
* Updated requirements
* New dependencies

### Documentation Files

* `README.md` - Project overview
* `docs/API_DOCUMENTATION.md` - API reference
* `docs/WINDOWS_BUILD.md` - Windows build guide
* `docs/USER_MANUAL.md` - User manual
* `CHANGELOG.md` - Version history

## Security

### Security-Sensitive Changes

Changes affecting security require:

1. **Threat Model**: Document potential threats
2. **Risk Assessment**: Evaluate security impact
3. **Security Review**: Additional review by security team
4. **Testing**: Security-specific tests
5. **Audit Logging**: Log security events

### Reporting Vulnerabilities

**DO NOT** create public issues for security vulnerabilities.

Email: lackadaisicalresearch@pm.me

See [SECURITY.md](SECURITY.md) for details.

### Security Checklist

- [ ] Input validation implemented
- [ ] Authentication/authorization checked
- [ ] Encryption used for sensitive data
- [ ] No hardcoded secrets
- [ ] SQL injection prevention
- [ ] XSS prevention (if applicable)
- [ ] CSRF protection (if applicable)
- [ ] Security logging implemented

## Performance

### Performance Considerations

* Profile before optimizing
* Document performance requirements
* Include performance tests for critical paths
* Avoid premature optimization
* Consider memory usage

### Benchmarking

```cpp
#include <benchmark/benchmark.h>

static void BM_NetworkScan(benchmark::State& state) {
    NetworkScanner scanner;
    scanner.initialize();
    
    for (auto _ : state) {
        scanner.scanNetwork("192.168.1.0/24");
    }
    
    scanner.shutdown();
}

BENCHMARK(BM_NetworkScan);
```

## Module Development

### Creating a New Module

1. **Interface**: Define in `include/modules/your_module.h`
2. **Implementation**: Create in `src/modules/your_module/`
3. **Registration**: Register with ModuleRegistry
4. **Tests**: Add tests in `tests/modules/`
5. **Documentation**: Document in README and user manual

### Module Template

See `docs/module-development.md` for detailed guide.

## Database Changes

### Schema Migrations

1. **Version**: Increment schema version
2. **Migration Script**: Create SQL migration
3. **Backwards Compatibility**: Consider compatibility
4. **Testing**: Test migration thoroughly

## API Changes

### Breaking Changes

* Increment major version
* Document in CHANGELOG
* Provide migration guide
* Deprecation period (when possible)

### Adding Endpoints

1. **Design**: RESTful design
2. **Documentation**: Update API_DOCUMENTATION.md
3. **Tests**: Add API tests
4. **Examples**: Provide code examples

## Release Process

1. **Version Bump**: Update version in CMakeLists.txt
2. **Changelog**: Update CHANGELOG.md
3. **Testing**: Full test suite
4. **Documentation**: Verify documentation
5. **Tag**: Create git tag
6. **Release Notes**: Write release notes
7. **Build**: Build release artifacts
8. **Publish**: Publish to GitHub Releases

## Questions?

* **Email**: lackadaisicalresearch@pm.me
* **GitHub Issues**: https://github.com/Lackadaisical-Security/SpectreMap/issues
* **Discussions**: https://github.com/Lackadaisical-Security/SpectreMap/discussions

## Recognition

Contributors will be recognized in:
* CONTRIBUTORS.md
* Release notes
* Project website (when available)

## License

By contributing, you agree that your contributions will be licensed under the same license as the project. See [LICENSE](LICENSE) for details.

---

**Thank you for contributing to SpectreMap!**

**Copyright © 2025 Lackadaisical Security. All rights reserved.**
