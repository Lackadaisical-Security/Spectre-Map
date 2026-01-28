# SpectreMap Assembly (ASM) Components Documentation

**Lackadaisical Security 2025**  
Website: https://lackadaisical-security.com  
Contact: lackadaisicalresearch@pm.me

---

## Table of Contents

1. [Overview](#overview)
2. [Architecture Support](#architecture-support)
3. [Security Components](#security-components)
4. [Cryptographic Components](#cryptographic-components)
5. [Anti-Analysis Components](#anti-analysis-components)
6. [Building ASM Components](#building-asm-components)
7. [API Reference](#api-reference)
8. [Security Considerations](#security-considerations)

---

## Overview

SpectreMap includes highly optimized assembly language components for security-critical operations. These components provide:

- **Performance**: Near-hardware-level execution speed for cryptographic operations
- **Security**: Direct CPU instruction access for secure operations (AES-NI, RDRAND, etc.)
- **Reliability**: Deterministic behavior without compiler optimizations interfering
- **Platform-Specific Optimization**: Tailored implementations for x86, x64, and ARM64

---

## Architecture Support

### Dual Architecture (32-bit and 64-bit)

All security-critical ASM modules are available in both 32-bit and 64-bit versions:

| 32-bit File | 64-bit File | Purpose |
|-------------|-------------|---------|
| `secure_random.asm` | `secure_random_x64.asm` | Cryptographically secure random number generation |
| `secure_prng.asm` | `secure_prng_x64.asm` | ChaCha20-based PRNG |
| `secure_memory.asm` | `secure_memory_x64.asm` | Secure memory allocation and wiping |
| `secure_boot.asm` | `secure_boot_x64.asm` | Secure boot verification (in development) |
| `aes_gcm.asm` | `aes_gcm_x64.asm` | AES-GCM authenticated encryption |
| `encryption.asm` | `encryption_x64.asm` | AES-256 CBC encryption |
| `memory_protection.asm` | `memory_protect_x64.asm` | Memory protection and guarding |

### Calling Conventions

**32-bit (x86 - cdecl)**:
- Parameters pushed on stack right-to-left
- Caller cleans up stack
- Return value in EAX

**64-bit (x64 - Windows ABI)**:
- First 4 parameters: RCX, RDX, R8, R9
- Additional parameters on stack
- 32-byte shadow space required
- Return value in RAX
- Non-volatile: RBX, RBP, RDI, RSI, R12-R15

---

## Security Components

### Secure Random (`secure_random.asm` / `secure_random_x64.asm`)

Provides cryptographically secure random number generation using hardware entropy sources.

**Features**:
- RDRAND/RDSEED instruction support with automatic detection
- TSC-based fallback for systems without hardware RNG
- Entropy pool with mixing
- Secure memory allocation and deallocation

**Functions**:
```c
// Initialize the secure random generator
int secure_random_init(void);

// Generate secure random bytes
size_t secure_random_bytes(void* buffer, size_t count);

// Allocate zeroed secure memory
void* secure_memory_alloc(size_t size);

// Securely free memory (wipes before freeing)
int secure_memory_free(void* ptr, size_t size);
```

### Secure PRNG (`secure_prng.asm` / `secure_prng_x64.asm`)

ChaCha20-based cryptographically secure pseudo-random number generator.

**Features**:
- ChaCha20 cipher for stream generation
- Automatic reseeding after 1MB of output
- SHA3-256 for key derivation
- Multiple entropy sources

**Functions**:
```c
// Initialize the PRNG
int initialize_secure_prng(void);       // 32-bit
int initialize_secure_prng_x64(void);   // 64-bit

// Generate random bytes
size_t secure_random_bytes(void* buffer, size_t count);       // 32-bit
size_t secure_random_bytes_x64(void* buffer, size_t count);   // 64-bit

// Generate random integer in range [0, max)
uint64_t secure_random_integer_x64(uint64_t max);

// Seed with external entropy
int secure_prng_seed(void* entropy, size_t size);       // 32-bit
int secure_prng_seed_x64(void* entropy, size_t size);   // 64-bit

// Force reseed
int secure_prng_reseed(void);       // 32-bit
int secure_prng_reseed_x64(void);   // 64-bit
```

### Secure Memory (`secure_memory.asm` / `secure_memory_x64.asm`)

Provides secure memory management with protection against:
- Memory disclosure via swapping
- Stack buffer overflows (canary protection)
- Residual data in freed memory

**Features**:
- 3-pass secure memory wiping (DoD 5220.22-M compliant)
- Memory locking to prevent swapping
- Random canary generation for stack protection
- Block tracking for automatic cleanup

**Functions**:
```c
// Initialize secure memory subsystem
int SecureMemory_Init_x64(void);

// Shutdown and wipe all allocations
void SecureMemory_Shutdown_x64(void);

// Allocate secure memory
void* SecureMemory_Alloc_x64(size_t size);

// Free secure memory (automatically wipes)
int SecureMemory_Free_x64(void* ptr);

// Wipe memory (3-pass)
void SecureMemory_Wipe_x64(void* ptr, size_t size);

// Lock memory to prevent swapping
int SecureMemory_Lock_x64(void* ptr, size_t size);

// Unlock memory
int SecureMemory_Unlock_x64(void* ptr, size_t size);

// Get current canary value
uint64_t SecureMemory_GetCanary_x64(void);
```

---

## Cryptographic Components

### AES-GCM (`aes_gcm.asm` / `aes_gcm_x64.asm`)

Hardware-accelerated AES-GCM authenticated encryption using AES-NI instructions.

**Features**:
- 128, 192, and 256-bit key support
- AESNI acceleration with automatic detection
- PCLMULQDQ for GHASH acceleration
- Constant-time implementation

**Functions**:
```c
// Check for AES-NI support
int aes_check_hardware_support(void);

// Key expansion
void aes_key_expand_128(const uint8_t* key, uint8_t* round_keys);
void aes_key_expand_256(const uint8_t* key, uint8_t* round_keys);

// AES-GCM encryption
int aes_gcm_encrypt(
    const uint8_t* plaintext, size_t plaintext_len,
    const uint8_t* key, size_t key_len,
    const uint8_t* iv, size_t iv_len,
    const uint8_t* aad, size_t aad_len,
    uint8_t* ciphertext,
    uint8_t* tag, size_t tag_len
);

// AES-GCM decryption with authentication
int aes_gcm_decrypt(
    const uint8_t* ciphertext, size_t ciphertext_len,
    const uint8_t* key, size_t key_len,
    const uint8_t* iv, size_t iv_len,
    const uint8_t* aad, size_t aad_len,
    const uint8_t* tag, size_t tag_len,
    uint8_t* plaintext
);
```

### AES-256 CBC (`encryption.asm` / `encryption_x64.asm`)

AES-256 in CBC mode with PKCS#7 padding.

**Features**:
- RDRAND-based key generation
- IV generation using hardware RNG
- Multi-layer encryption support
- Secure key wiping

**Functions**:
```c
// Generate encryption key using hardware RNG
int generate_encryption_key(uint8_t* key, size_t key_len);

// Encrypt data
int aes256_cbc_encrypt(
    const uint8_t* plaintext, size_t plaintext_len,
    const uint8_t* key,
    const uint8_t* iv,
    uint8_t* ciphertext, size_t* ciphertext_len
);

// Decrypt data
int aes256_cbc_decrypt(
    const uint8_t* ciphertext, size_t ciphertext_len,
    const uint8_t* key,
    const uint8_t* iv,
    uint8_t* plaintext, size_t* plaintext_len
);
```

---

## Anti-Analysis Components

### Secure Boot (`secure_boot.asm` / `secure_boot_x64.asm`)

Provides secure boot verification and anti-debugging measures.

**Features**:
- OS version verification
- Secure configuration loading
- Anti-debugging detection
- Controlled termination on debugger detection

**Important Notes**:
- Anti-debugging measures only trigger on positive debugger detection
- Controlled termination via ExitProcess (no stack corruption)
- Debug register clearing for hardware breakpoint protection

### Anti-Debug (`anti_debug.asm`)

Various anti-debugging and anti-analysis techniques.

**Techniques**:
- IsDebuggerPresent detection
- NtQueryInformationProcess checks
- PEB BeingDebugged flag
- Hardware breakpoint detection
- Timing-based detection

---

## Building ASM Components

### Prerequisites

- **NASM** (Netwide Assembler) 2.15 or later
- **Visual Studio 2022** Build Tools (for linking)
- **CMake** 3.16 or later

### Build Commands

**Using CMake (Recommended)**:
```cmd
mkdir build && cd build
cmake .. -DENABLE_ASM=ON -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

**Manual NASM Build (64-bit)**:
```cmd
nasm -f win64 -o secure_random_x64.obj secure_random_x64.asm
nasm -f win64 -o secure_prng_x64.obj secure_prng_x64.asm
nasm -f win64 -o secure_memory_x64.obj secure_memory_x64.asm
nasm -f win64 -o aes_gcm_x64.obj aes_gcm_x64.asm
```

**Manual NASM Build (32-bit)**:
```cmd
nasm -f win32 -o secure_random.obj secure_random.asm
nasm -f win32 -o secure_prng.obj secure_prng.asm
nasm -f win32 -o secure_memory.obj secure_memory.asm
nasm -f win32 -o aes_gcm.obj aes_gcm.asm
```

### CMake Configuration

The CMakeLists.txt in the `asm/` directory handles:
- NASM detection and configuration
- Architecture-specific file selection
- Fallback to C stubs when NASM is unavailable

---

## API Reference

### Error Codes

| Code | Meaning |
|------|---------|
| 0 | Success |
| 1 | Invalid size/parameter |
| 2 | Not initialized |
| 3 | No free slots available |
| 4 | Allocation failed |
| 5 | Invalid pointer / Unknown size |
| 6 | Free operation failed |
| 10 | Entropy generation failed |

### Return Values

Most functions return:
- `1` (non-zero) on success
- `0` on failure
- Pointer functions return `NULL` on failure

### Thread Safety

- **secure_random_bytes**: Thread-safe (uses per-call state)
- **secure_prng_***: NOT thread-safe (global state)
- **SecureMemory_***: Thread-safe (uses atomic operations)
- **aes_gcm_***: Thread-safe (no global state)

---

## Security Considerations

### Hardware Requirements

For optimal security, the target CPU should support:
- **RDRAND**: Hardware random number generation
- **RDSEED**: True random seeding
- **AES-NI**: Hardware AES acceleration
- **PCLMULQDQ**: Carry-less multiplication for GHASH

### Fallback Behavior

When hardware features are unavailable:
- RDRAND/RDSEED → TSC-based entropy (reduced security)
- AES-NI → Software AES (slower but functional)
- PCLMULQDQ → Software GHASH (slower but functional)

### Memory Security

- Always call `SecureMemory_Shutdown_x64()` before process exit
- Use `SecureMemory_Lock_x64()` for sensitive keys
- Memory wiping uses 3-pass overwrite with memory barriers

### Anti-Debugging Notes

- Anti-debugging only activates when debugger is positively detected
- Uses controlled termination (ExitProcess) not stack corruption
- Clears debug registers to disable hardware breakpoints
- Wipes sensitive memory before termination

---

## License

This software is proprietary. See the LICENSE file for terms.

**Copyright © 2025 Lackadaisical Security. All rights reserved.**
