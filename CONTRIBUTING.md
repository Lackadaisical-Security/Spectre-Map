# Contributing to SpectreMap

So you want to contribute to SpectreMap? Good. We need people who can code, not people who can talk about coding.

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

Read [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md). TL;DR: Be competent, be honest, don't be a criminal. Your code speaks louder than anything else. If you can't handle direct technical criticism, this isn't for you.

## Getting Started

### Prerequisites

Before you waste anyone's time, make sure you have:

* **C++17 compatible compiler** (GCC 8+, Clang 7+, MSVC 2019+)
* **CMake 3.16+**
* **Qt 6.6.0+**
* **OpenSSL 3.x**
* **SQLite 3.x**
* **Git** (obviously)
* **Brain** (not optional)

### Setting Up Development Environment

#### 1. Fork the Repository
```bash
# Fork via GitHub UI, then clone your fork
git clone https://github.com/YOUR_USERNAME/SpectreMap.git
cd SpectreMap
```

#### 2. Add Upstream Remote
```bash
git remote add upstream https://github.com/Lackadaisical-Security/SpectreMap.git
```

#### 3. Install Dependencies

**Ubuntu/Debian:**
```bash
sudo apt install build-essential cmake qt6-base-dev qt6-tools-dev \
                 libqt6opengl6-dev libssl-dev libsqlite3-dev
```

**macOS:**
```bash
brew install cmake qt6 openssl sqlite3
```

**Windows:**
See `docs/WINDOWS_BUILD.md` and pray.

#### 4. Build in Debug Mode
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)
```

#### 5. Run Tests
```bash
make test
```

If this fails, fix your environment before opening an issue.

## Development Process

### Branching Strategy

* `main` - Stable production releases (don't touch unless you're a maintainer)
* `develop` - Integration branch for features
* `feature/your-feature` - Your feature branch
* `bugfix/bug-description` - Bug fix branches
* `security/cve-id` - Security patches (highest priority)

### Workflow

#### 1. Create a Feature Branch
```bash
git checkout -b feature/sick-new-exploit develop
```

#### 2. Make Changes
* Write clean code (see [Coding Standards](#coding-standards))
* Add tests - if you don't test your code, we won't merge it
* Update documentation - if you change behavior, document it

#### 3. Commit Changes
```bash
git add .
git commit -m "feat: add sick new exploit detection"
```

#### 4. Keep Your Branch Updated
```bash
git fetch upstream
git rebase upstream/develop
```

If you don't know how to resolve merge conflicts, learn. We won't do it for you.

#### 5. Push Changes
```bash
git push origin feature/sick-new-exploit
```

#### 6. Create Pull Request
* Open a PR against `develop` branch
* Fill out the template completely (don't half-ass it)
* Link related issues
* Wait for review

### Commit Message Guidelines

Follow [Conventional Commits](https://www.conventionalcommits.org/):

```
<type>(<scope>): <subject>

<body>

<footer>
```

**Types:**
* `feat` - New feature
* `fix` - Bug fix
* `docs` - Documentation only
* `style` - Code formatting (doesn't change functionality)
* `refactor` - Code refactoring
* `perf` - Performance improvements
* `test` - Tests
* `chore` - Build/tooling changes
* `security` - Security fixes (mark these clearly)

**Examples:**
```
feat(scanner): add multi-threaded port scanning

Implemented threaded TCP SYN scanner with configurable
thread pool size. Reduces scan time by ~70% on gigabit networks.

Closes #123
```

```
fix(crypto): patch buffer overflow in AES decryption

Fixed stack buffer overflow when decrypting malformed
ciphertext. Added bounds checking and input validation.

CVE-2025-XXXXX
```

```
security(auth): close authentication bypass vulnerability

Enforced token expiration validation. Previous implementation
accepted expired tokens due to missing time check.

Fixes #666
```

## Pull Request Process

### Before Submitting

Don't submit garbage. Check this list:

- [ ] Code compiles without warnings
- [ ] All tests pass
- [ ] Added tests for new functionality
- [ ] Documentation updated
- [ ] Commit messages follow convention
- [ ] No merge conflicts with develop
- [ ] Security implications considered
- [ ] You actually tested it (not just compiled)

### PR Checklist

Your PR better include:

1. **Clear title** - "Fixed stuff" is not a title
2. **Description** - What you changed, why, and how
3. **Type** - Bug fix? Feature? Breaking change?
4. **Testing** - How did you test it? "It compiled" is not testing.
5. **Screenshots** - For UI changes
6. **Breaking Changes** - Clearly marked if applicable
7. **Related Issues** - Link them

### Review Process

1. **Automated Checks** - CI/CD must pass (green checkmarks or GTFO)
2. **Code Review** - Maintainer will review your code
3. **Feedback** - Address feedback or defend your approach with logic
4. **Security Review** - Security-sensitive changes get extra scrutiny
5. **Merge** - If everything passes, we'll merge it

### Merge Requirements

* All CI checks passing (obviously)
* At least one approving review
* No unresolved conversations
* Up-to-date with target branch
* Maintainer approval

## Coding Standards

### C++ Style

We follow [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) with modifications:

* **Indentation**: 4 spaces (tabs are for psychopaths)
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

This is a security tool. Act like it.

* **Input Validation** - ALWAYS validate and sanitize input
* **Error Handling** - Proper error handling, no exceptions in destructors
* **Memory Safety** - Use RAII, smart pointers, avoid raw `new`/`delete`
* **Thread Safety** - Document thread safety guarantees, use mutexes
* **Cryptography** - Use OpenSSL. **NEVER** roll your own crypto (seriously, don't)
* **Logging** - Log security events, **NEVER** log passwords/keys/sensitive data

### Code Quality

* **Comments** - Explain **WHY**, not **WHAT**. We can read code.
* **Documentation** - Doxygen-style comments for public APIs
* **Complexity** - Keep functions under 50 lines when possible
* **DRY** - Don't Repeat Yourself
* **SOLID** - Follow SOLID principles (Google them if you don't know)

### What We Don't Want

* Magic numbers (use constants)
* God classes (huge classes that do everything)
* Global variables (unless you have a damn good reason)
* Copy-paste code (use functions)
* Commented-out code (delete it, Git remembers)
* "TODO" comments without issue numbers (create an issue)

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

TEST_F(NetworkScannerTest, InvalidCIDRThrowsException) {
    EXPECT_THROW(scanner->scanNetwork("invalid"), std::invalid_argument);
}
```

### Test Coverage

* **Minimum**: 70% code coverage (we check this)
* **Critical Paths**: 90%+ for security-critical code
* **New Features**: 80%+ coverage required

If your PR drops coverage, it better have a good explanation.

### Running Tests

```bash
# All tests
make test

# Specific test
./tests/unit/network_scanner_test

# With coverage report
cmake -DENABLE_COVERAGE=ON ..
make coverage
```

## Documentation

### Code Documentation

Use Doxygen format for public APIs:

```cpp
/**
 * @brief Scans a network for active hosts
 * 
 * Performs TCP SYN scan on specified CIDR range to identify
 * active hosts and open ports.
 * 
 * @param cidr Network range in CIDR notation (e.g., "192.168.1.0/24")
 * @param ports Port list to scan (default: common ports)
 * @param timeout Scan timeout in milliseconds (default: 1000)
 * @return Vector of scan results with discovered hosts/ports
 * 
 * @throws std::invalid_argument if CIDR format is invalid
 * 
 * @note Requires administrator/root privileges for raw sockets
 * @warning May trigger IDS/IPS systems - use responsibly
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

### Documentation Files

Update these when relevant:

* `README.md` - Project overview
* `docs/API_DOCUMENTATION.md` - API reference
* `docs/WINDOWS_BUILD.md` - Windows build instructions
* `docs/USER_MANUAL.md` - User manual
* `CHANGELOG.md` - Version history

## Security

### Security-Sensitive Changes

If you're touching anything security-related, these requirements apply:

1. **Threat Model** - Document what you're protecting against
2. **Risk Assessment** - Evaluate security impact
3. **Security Review** - Additional review required
4. **Testing** - Security-specific tests mandatory
5. **Audit Logging** - Log security events

### Reporting Vulnerabilities

**DO NOT** create public GitHub issues for security vulnerabilities.

Email: **lackadaisicalresearch@pm.me**

See [SECURITY.md](SECURITY.md) for responsible disclosure process.

### Security Checklist

Before submitting security-related changes:

- [ ] Input validation implemented
- [ ] Authentication/authorization checked
- [ ] Encryption for sensitive data
- [ ] No hardcoded secrets/credentials
- [ ] SQL injection prevention
- [ ] XSS prevention (if applicable)
- [ ] CSRF protection (if applicable)
- [ ] Security event logging

## Performance

### Performance Considerations

* Profile **BEFORE** optimizing (don't guess)
* Document performance requirements
* Include benchmarks for critical paths
* Avoid premature optimization (make it work, then make it fast)
* Consider memory usage (memory leaks will be rejected)

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

1. **Interface** - Define in `include/modules/your_module.h`
2. **Implementation** - Create in `src/modules/your_module/`
3. **Registration** - Register with ModuleRegistry
4. **Tests** - Add tests in `tests/modules/`
5. **Documentation** - Document in README and manual

See `docs/module-development.md` for detailed guide.

## Database Changes

### Schema Migrations

If you change the database schema:

1. **Version** - Increment schema version number
2. **Migration Script** - Write SQL migration script
3. **Backwards Compatibility** - Consider upgrade path
4. **Testing** - Test migration with production-like data

Don't break existing databases. People will be pissed.

## API Changes

### Breaking Changes

If you break the API:

* Increment **major** version (semver)
* Document in `CHANGELOG.md` with big warnings
* Provide migration guide
* Deprecation period if possible (give users time to update)

### Adding API Endpoints

1. **RESTful Design** - Follow REST conventions
2. **Documentation** - Update `API_DOCUMENTATION.md`
3. **Tests** - Add comprehensive API tests
4. **Examples** - Provide working code examples

## Release Process

(For maintainers - but good to know)

1. **Version Bump** - Update version in `CMakeLists.txt`
2. **Changelog** - Update `CHANGELOG.md`
3. **Testing** - Full test suite passes
4. **Documentation** - Verify all docs updated
5. **Tag** - Create git tag (`v1.0.0`)
6. **Release Notes** - Write detailed release notes
7. **Build** - Build release artifacts
8. **Publish** - Publish to GitHub Releases

## Questions?

* **Email**: lackadaisicalresearch@pm.me
* **GitHub Issues**: https://github.com/Lackadaisical-Security/SpectreMap/issues (for bugs/features, NOT security)
* **Discussions**: https://github.com/Lackadaisical-Security/SpectreMap/discussions

## Recognition

Quality contributors get recognized in:
* `CONTRIBUTORS.md`
* Release notes
* Project website (when it exists)

## License

By contributing, you agree that your contributions will be licensed under the same license as the project. See [LICENSE](LICENSE) for details.

You retain copyright to your contributions, but you grant us a perpetual license to use them.

---

### 🔥 **Built by Lackadaisical Security** 🔥

*"Code speaks louder than credentials. Merit over everything."*

**Copyright © 2025 Lackadaisical Security. All rights reserved.**