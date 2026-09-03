# ASM Architecture Compatibility Notes

## Current State

This folder contains 261 assembly files that provide low-level functionality for SpectreMap including cryptography, anti-analysis, memory protection, and obfuscation.

## Architecture Support

### Files with Both 32-bit and 64-bit Versions

The following files have optimized versions for both architectures:

| 32-bit Version | 64-bit Version | Purpose |
|----------------|----------------|---------|
| `aes_gcm.asm` | `aes_gcm_x64.asm` | AES-GCM encryption |
| `encryption.asm` | `encryption_x64.asm` | Multi-layer encryption |
| `secure_random.asm` | `secure_random_x64.asm` | Random number generation |
| `secure_prng.asm` | `secure_prng_x64.asm` | Pseudo-random generator |
| `secure_memory.asm` | `secure_memory_x64.asm` | Memory protection |
| `polymorphic_stub.asm` | `polymorphic_stub_x64.asm` | Polymorphic decryption stub |
| `virtualization_stub.asm` | `virtualization_stub_x64.asm` | VM-based protection stub |
| `metamorphic_stub.asm` | `metamorphic_stub_x64.asm` | Metamorphic self-modifying stub |
| `advanced_stub.asm` | `advanced_stub_x64.asm` | Advanced stub with anti-debug/anti-VM |
| `quantum_crypto.asm` | `quantum_crypto_x64.asm` | Quantum-resistant cryptography (Kyber/NTRU/SPHINCS+) |
| `ultra_encryption.asm` | `ultra_encryption_x64.asm` | 15-layer hybrid encryption (30 algorithms) |
| `homomorphic_crypto.asm` | `homomorphic_crypto_x64.asm` | Homomorphic encryption (BFV/TFHE) |
| `metamorphic_engine.asm` | `metamorphic_engine_x64.asm` | Metamorphic code transformation engine |
| `antidebug.asm` | `antidebug_x64.asm` | Anti-debugging detection (INT3, SEH, HW breakpoints) |
| `extreme_anti_analysis.asm` | `extreme_anti_analysis_x64.asm` | VM/debugger detection (CPUID, RDTSC, IDT/GDT) |
| `standalone_crypto.asm` | `standalone_crypto_x64.asm` | Full crypto suite (SHA-256, HMAC, PBKDF2, AES-256-CTR, RDRAND) |
| `self_modifying_code.asm` | `self_modifying_code_x64.asm` | SMC engine (code gen, metamorphic transform, integrity verify) |
| `pqc_obfuscation.asm` | `pqc_obfuscation_x64.asm` | PQC obfuscation (instruction decoder, metamorphic, code VM) |
| `hsm_integration.asm` | `hsm_integration_x64.asm` | HSM hardware (TPM 2.0, YubiKey, NitroKey, AES-NI) |
| `zk_proofs.asm` | `zk_proofs_x64.asm` | Zero-knowledge proofs (Lyubashevsky, Fiat-Shamir) |
| `kyber_nist.asm` | `kyber_nist_x64.asm` | ML-KEM Kyber-768 (NTT, Barrett, CBD, keygen/encap/decap) |
| `post_quantum.asm` | `post_quantum_x64.asm` | Post-quantum crypto (Kyber KEM, NTRU, NTT/INTT) |
| `crypto_hooks.asm` | `crypto_hooks_x64.asm` | Crypto monitoring hooks (timing, hook table, stats) |

### Large Multi-Algorithm Files (32-bit registers)

These large files currently use 32-bit registers (`eax`, `ebx`, `esp`, `ebp`) and work on 64-bit systems through NASM's object format conversion:

| File | Lines | Purpose | Notes |
|------|-------|---------|-------|
| `quantum_crypto.asm` | 2,959 | Quantum cryptography algorithms | Multiple Kyber/quantum algorithms, may have redundancy |
| `ultra_encryption.asm` | 3,271 | Ultra-secure encryption | Multiple encryption layers, consider optimization |
| `homomorphic_crypto.asm` | 3,283 | Homomorphic encryption | BFV/CKKS schemes, complex operations |
| `metamorphic_engine.asm` | 1,034 | Code morphing | Polymorphic transformations |

### Other Architecture-Specific Files

#### Core x64 Files (6 files)
- `memory_protect_x64.asm` - Memory protection with x64 registers
- `anti_debug.asm` - Anti-debugging checks (x64 PEB access)
- `direct_syscall.asm` - Direct syscall invocation
- `direct_syscall_executor.asm` - Syscall executor
- `enhanced_syscall.asm` - Enhanced syscall interface
- `syscall_dynamic_resolver.asm` - Dynamic syscall resolution

#### ARM64 Support
- `memory_protect_arm64.s` - ARM64 memory protection

## Build System Behavior

### 64-bit Builds (Default)
When building for x64 (most modern systems):
- Uses all x64-specific files (`*_x64.asm`)
- Includes all other 130+ files (they compile with 64-bit object format)
- 32-bit-only files (`aes_gcm.asm`, `main.asm`, `encryption.asm`, etc.) are **excluded** when x64 variant exists

### 32-bit Builds
When building for x86:
- Uses 32-bit-specific files
- Includes all architecture-agnostic files
- Excludes x64-specific files

## Recommendations

### For Production Use
✅ **Current setup is production-ready** for 64-bit systems
- All functionality is available through x64 files + converted 32-bit files
- Performance is good for most use cases

### For Optimal Performance
Consider creating 64-bit versions of large files:

1. **`quantum_crypto_x64.asm`**
   - Use 64-bit registers (`rax`, `rbx`, `r8-r15`)
   - Optimize large integer operations
   - Reduce redundant algorithm implementations

2. **`ultra_encryption_x64.asm`**
   - Utilize 64-bit pointer operations
   - Streamline encryption layers
   - Remove redundant code paths

3. **`homomorphic_crypto_x64.asm`**
   - Optimize polynomial operations with 64-bit
   - Better memory addressing
   - SIMD optimizations

4. **`metamorphic_engine_x64.asm`**
   - 64-bit code generation
   - Extended register usage
   - Modern instruction support

## Testing

To verify ASM files compile correctly:
```bash
# Configure with ASM enabled
cmake -DENABLE_ASM=ON ..

# Check build messages
cmake --build . 2>&1 | grep "ASM:"

# Look for:
# - Number of files included
# - x64/x86 specific file counts
# - Any compilation errors
```

## Future Work

### Priority 1: Create 64-bit Versions
- [x] `polymorphic_stub_x64.asm`
- [x] `virtualization_stub_x64.asm`
- [x] `metamorphic_stub_x64.asm`
- [x] `advanced_stub_x64.asm`
- [x] `quantum_crypto_x64.asm` (1,330 lines, Kyber NTT optimized)
- [x] `ultra_encryption_x64.asm` (925 lines, 15-layer dispatch table)
- [x] `homomorphic_crypto_x64.asm` (1,407 lines, BFV + TFHE schemes)
- [x] `metamorphic_engine_x64.asm` (1,213 lines, xoshiro256** RNG)
- [x] `standalone_crypto_x64.asm` (1,490 lines, SHA-256/HMAC/PBKDF2/AES-256-CTR)
- [x] `self_modifying_code_x64.asm` (901 lines, SMC engine + metamorphic)
- [x] `extreme_anti_analysis_x64.asm` (803 lines, CPUID/RDTSC/IDT/GDT VM detection)
- [x] `antidebug_x64.asm` (372 lines, timing/BP/INT3 detection)
- [x] `pqc_obfuscation_x64.asm` (1,126 lines, instruction decoder/metamorphic/VM)
- [x] `hsm_integration_x64.asm` (989 lines, TPM 2.0/YubiKey/NitroKey/AES-NI)
- [x] `zk_proofs_x64.asm` (659 lines, Lyubashevsky ZKP/Fiat-Shamir)
- [x] `kyber_nist_x64.asm` (794 lines, ML-KEM NTT/INTT/Barrett/CBD)

### Priority 2: Code Cleanup
- [x] Optimize hot code paths
- [x] Add comprehensive function documentation
- [x] Create unit tests for critical functions

### Priority 3: Architecture Expansion
- [x] More ARM64 implementations
- [x] All remaining missing x64 asm files custom coded - 
- [ ] RISC-V support consideration
- [ ] Apple Silicon optimizations

## Notes

- NASM handles object format conversion automatically
- 32-bit register code works on 64-bit systems but may be less efficient
- The current implementation prioritizes functionality over optimal performance
- All 261 files can be compiled and linked successfully
