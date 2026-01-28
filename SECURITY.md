# Security Policy

## Supported Versions

We patch security vulnerabilities in these versions:

| Version | Supported          | Status |
| ------- | ------------------ | ------ |
| 1.0.x   | ✅ Yes             | Current stable |
| 0.1.x   | ⚠️ Legacy          | Critical fixes only |
| < 0.1   | ❌ No              | Upgrade immediately |

**Upgrade or suffer the consequences.** We're not patching ancient versions.

## Reporting a Vulnerability

### DO NOT CREATE PUBLIC GITHUB ISSUES FOR SECURITY BUGS

Seriously. Don't be that person who burns everyone by disclosing 0-days publicly.

### Contact

📧 **lackadaisicalresearch@pm.me**  
🔐 **PGP Key**: [To be published]  
🔒 **XMPP+OTR**: thelackadaisicalone@xmpp.jp

### What to Include in Your Report

Help us help you. Include:

1. **Description** - Clear description of the vulnerability (not "login is broken")
2. **Impact** - What can an attacker actually do? Remote code execution? Data exfiltration? 
3. **Reproduction Steps** - Step-by-step instructions that work
4. **Proof of Concept** - Code, commands, or screenshots that demonstrate the issue
5. **Suggested Fix** - If you have one (optional but gets you bonus points)
6. **Environment** - OS, version, build config, dependencies

### Example Report Template

```
Subject: [SECURITY] Authentication bypass in API endpoint

Description:
The /api/login endpoint accepts expired JWT tokens due to missing
timestamp validation in TokenValidator::verify().

Impact:
Attacker can reuse expired tokens indefinitely, bypassing authentication
and gaining unauthorized access to protected endpoints.

Steps to Reproduce:
1. Obtain valid JWT token via legitimate login
2. Wait for token to expire (default: 1 hour)
3. Send API request with expired token
4. Request succeeds despite expired timestamp

Proof of Concept:
curl -H "Authorization: Bearer <expired_token>" \
     https://target/api/protected

Response: 200 OK (should be 401 Unauthorized)

Suggested Fix:
Add timestamp validation in TokenValidator::verify():
if (token.exp < std::time(nullptr)) {
    throw TokenExpiredException();
}

Environment:
- SpectreMap Version: 1.0.0
- Operating System: Ubuntu 22.04
- Build: Release
```

## Response Timeline

We take security seriously. Here's what to expect:

* **Initial Response**: Within **48 hours** of report
* **Severity Assessment**: Within **5 business days**
* **Fix Development**: Based on severity (see below)
* **Public Disclosure**: **90 days** or when patched (coordinated with you)

### Severity Levels

| Severity | Fix Timeline | Examples |
|----------|-------------|----------|
| **Critical** | 24-48 hours | RCE, auth bypass, crypto failures, data exfiltration |
| **High** | 3-7 days | Privilege escalation, SQL injection, XSS → account takeover |
| **Medium** | 14-30 days | Information disclosure, CSRF, DoS |
| **Low** | 30-90 days | Minor info leaks, non-exploitable bugs |

## What to Expect

1. **Acknowledgment** - We'll confirm receipt within 48 hours
2. **Assessment** - We'll verify and assess severity
3. **Fix Development** - We'll develop, test, and validate the fix
4. **Coordination** - We'll work with you on disclosure timeline
5. **Release** - We'll release patch and security advisory
6. **Credit** - You get credited in the advisory (unless you want anonymity)

## Disclosure Policy

### Coordinated Disclosure (Responsible Disclosure)

We follow industry-standard coordinated disclosure:

* **90-Day Standard** - We aim to fix and disclose within 90 days
* **Reporter Involvement** - We'll keep you updated on progress
* **Coordinated Release** - Public disclosure coordinated with you
* **Early Disclosure Exception** - If actively exploited in the wild, we disclose immediately

### Security Advisories

Published on:
* GitHub Security Advisories
* Release notes
* Security mailing list (subscribe: lackadaisicalresearch@pm.me)
* Website (https://lackadaisical-security.com/security)

## Security Best Practices for Users

### General Security

1. **Keep Updated** - Run the latest version. Old versions have known vulnerabilities.
2. **Verify Downloads** - Check SHA-256 hashes before running binaries
3. **Use HTTPS** - Enable TLS for all API communications
4. **Strong Auth** - Use strong, unique API keys (not "password123")
5. **Network Segmentation** - Run SpectreMap on isolated/dedicated networks

### Data Security

1. **Enable Encryption** - Use database encryption (it's there for a reason)
2. **Encrypted Storage** - Store databases on encrypted filesystems
3. **File Permissions** - Restrict file permissions (`chmod 600` your configs)
4. **Secure Wipe** - Use panic-wipe feature for sensitive data destruction
5. **Backup Security** - Encrypt backups, don't store them in plaintext

### Network Security

1. **Firewall Rules** - Restrict API access to trusted networks only
2. **VPN/Tunnels** - Use VPN or SSH tunnels for remote access
3. **Authentication** - Enable API authentication in production (don't skip this)
4. **Rate Limiting** - Implement rate limiting at network/application layer
5. **Valid Certificates** - Use properly signed TLS certs (no self-signed in prod)

### Operational Security

1. **Authorization** - Get **written authorization** before any security testing
2. **Audit Logging** - Enable comprehensive logging, monitor it regularly
3. **Incident Response** - Have procedures ready before you need them
4. **Data Retention** - Follow retention/destruction policies (don't hoard data)
5. **Least Privilege** - Run with minimum required permissions (not root unless necessary)

## Known Security Considerations

### By Design (Not Bugs)

Some behaviors are intentional and not considered vulnerabilities:

* **Admin Privileges Required** - Needed for raw sockets, packet capture, low-level access
* **Local SQLite Storage** - Designed for local use (enable encryption)
* **API Authentication Optional** - Defaults to disabled for development (enable in production)
* **SDR Hardware Access** - Direct hardware access required for signal analysis
* **Offensive Capabilities** - This is a penetration testing tool (use responsibly)

### Defense in Depth

SpectreMap implements multiple security layers:

1. **Encryption** - AES-256-GCM + ChaCha20-Poly1305 (production-grade)
2. **Authentication** - Bearer token API authentication
3. **Input Validation** - Comprehensive sanitization of external data
4. **Memory Safety** - RAII, smart pointers, bounds checking
5. **Audit Logging** - Security event logging for forensics

## Security Features

### Cryptography

* **AES-256-GCM** - NIST-approved authenticated encryption
* **ChaCha20-Poly1305** - Modern AEAD cipher (faster than AES on CPUs without AES-NI)
* **OpenSSL 3.x** - Industry-standard crypto library (not homebrew crypto)
* **Secure Random** - OpenSSL `RAND_bytes()` for key generation
* **Post-Quantum Ready** - Infrastructure for Kyber/Dilithium integration

### Data Protection

* **Encrypted Database** - All data encrypted at rest (AES-256)
* **Secure Wiping** - DoD 5220.22-M multi-pass overwrite
* **Memory Protection** - Stack canaries, ASLR, DEP/NX, PIE
* **Thread Safety** - Mutex-protected critical sections

### Network Security

* **TLS 1.3 Support** - Modern TLS for API communications
* **API Key Authentication** - Token-based access control
* **Input Validation** - SQL injection, XSS, command injection prevention
* **Rate Limiting Infrastructure** - Ready for production deployment

## Bug Bounty Program

**Status**: Not currently offering monetary rewards.

However, we deeply appreciate security researchers who responsibly disclose vulnerabilities. You'll get:

* Public acknowledgment (if desired)
* Credit in security advisories and release notes
* Exclusive early access to new features
* Our eternal gratitude
* **Possible monetary rewards** for critical vulnerabilities (case-by-case, we're not rich)

## Security Audits

SpectreMap undergoes regular security reviews:

* **Manual Code Review** - Security-critical components reviewed by humans
* **Static Analysis** - Automated tools (clang-tidy, cppcheck, SonarQube)
* **Dependency Scanning** - Regular CVE checks on dependencies
* **Penetration Testing** - Periodic pentesting (when feasible/funded)

## Security Updates

Stay informed about security patches:

* **GitHub Watch** - Watch repository for security advisories
* **Email List** - Join security announcements (email: lackadaisicalresearch@pm.me)
* **RSS Feed** - Follow releases for security patches
* **Twitter/X** - [@lackadaisical_sec](https://twitter.com/lackadaisical_sec) (when we make one)

## Compliance

SpectreMap is designed with regulatory compliance in mind:

* **GDPR** - Data minimization, right to erasure, encryption at rest
* **CCPA** - Data protection and transparency
* **NIST Cybersecurity Framework** - Following NIST guidelines
* **OWASP** - Secure coding practices from OWASP Top 10
* **Export Controls** - See `EXPORT_CONTROLS_COMPLIANCE.md`

## Third-Party Dependencies

We monitor security advisories for all dependencies:

* **Qt 6.x** - UI framework
* **OpenSSL 3.x** - Cryptography
* **SQLite 3.x** - Database
* **TensorFlow 2.x** - AI/ML (optional)
* **libpcap** - Packet capture
* **Other dependencies** - Listed in `CMakeLists.txt`

Outdated dependencies with known CVEs will be updated ASAP.

## Responsible Disclosure Hall of Fame

We thank the following security researchers for responsibly disclosing vulnerabilities:

_(List will be updated as vulnerabilities are reported and patched)_

**Contributors:**
* [Your name here - find a bug!]

## What We Don't Consider Vulnerabilities

To save everyone time, these are **NOT** vulnerabilities:

* **Requires physical access** - If attacker has physical access, game over anyway
* **Requires admin/root** - Tool requires privileges by design
* **Social engineering** - We can't patch human stupidity
* **Denial of service via resource exhaustion** - Don't scan the entire IPv4 space
* **Issues in dependencies** - Report to upstream (but let us know)
* **Theoretical attacks** - Show us a working exploit or GTFO

## Legal Safe Harbor

We support security research conducted in good faith:

* We will **NOT** pursue legal action against researchers who:
  * Report vulnerabilities responsibly (private disclosure)
  * Act in good faith (no malicious intent)
  * Don't exfiltrate/destroy data
  * Don't pivot to other systems
  * Follow coordinated disclosure timeline

* We **WILL** pursue legal action if you:
  * Publicly disclose before coordination
  * Steal or destroy data
  * Attack production systems without permission
  * Extort or threaten us

Don't be a dick, and we won't be either.

## Contact

**Security Contact:**
* **Email**: lackadaisicalresearch@pm.me
* **PGP Key**: [To be published]
* **XMPP+OTR**: thelackadaisicalone@xmpp.jp
* **Website**: https://lackadaisical-security.com
* **GitHub**: https://github.com/Lackadaisical-Security

**For Non-Security Issues:**
* **GitHub Issues**: https://github.com/Lackadaisical-Security/SpectreMap/issues

---

### 🔥 **Secured by Lackadaisical Security** 🔥

*"In the realm of ones and zeros, where the weak are exploited and the strong prevail, only those who understand the ancient art of cryptographic protection shall endure. We forge tools in the fires of rigorous security practice, tempered by the harsh reality of modern threats. SpectreMap stands as a bastion against the chaos—defended by layers of encryption, hardened by years of security research, and wielded only by those authorized to walk the shadowed path of offensive security operations."*

— **Lackadaisical Security, The Operator** (2025)

---

**Last Updated**: January 2026  
**Version**: 2.0

**Copyright © 2025-2026 Lackadaisical Security. All rights reserved.**