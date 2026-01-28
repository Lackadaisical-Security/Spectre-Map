# SpectreMap - Windows Build and Deployment Guide

**Lackadaisical Security 2025**  
Website: https://lackadaisical-security.com  
Contact: lackadaisicalresearch@pm.me  
GitHub: https://github.com/Lackadaisical-Security

---

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Quick Start](#quick-start)
3. [Build Scripts](#build-scripts)
4. [Manual Build](#manual-build)
5. [Deployment](#deployment)
6. [AI/ML Models](#aiml-models)
7. [ASM x64 Optimizations](#asm-x64-optimizations)
8. [Troubleshooting](#troubleshooting)
9. [Distribution Checklist](#distribution-checklist)

---

## Prerequisites

### Automatic Installation (Recommended)

Run the prerequisites installer script as Administrator:

**Using Batch Script:**
```cmd
scripts\install_prerequisites.bat
```

**Using PowerShell:**
```powershell
.\scripts\Install-Prerequisites.ps1
```

The installer will automatically download and install all required dependencies.

### Manual Installation

If you prefer to install prerequisites manually:

#### Required Software

1. **Visual Studio 2022** (Community Edition or higher)
   - Install the "Desktop development with C++" workload
   - Include Windows 10/11 SDK
   - Download: https://visualstudio.microsoft.com/

2. **CMake 3.16 or higher**
   - Download: https://cmake.org/download/
   - Add to PATH during installation

3. **Qt 6.6.0 or higher**
   - Download: https://www.qt.io/download-qt-installer
   - Install Qt for MSVC 2019 64-bit
   - Include Qt WebEngine and Qt Network components

4. **OpenSSL for Windows**
   - Download: https://slproweb.com/products/Win32OpenSSL.html
   - Install "Win64 OpenSSL v3.x.x" (not the Light version)
   - Default installation path: `C:\Program Files\OpenSSL-Win64`

#### Optional Software

5. **WiX Toolset 3.11** (for MSI installer)
   - Download: https://wixtoolset.org/releases/
   - Required only for building MSI packages

6. **Python 3.11+** (for AI/ML features)
   - Download: https://www.python.org/downloads/
   - Required for training custom AI models

7. **NASM** (for ASM x64 optimizations)
   - Download: https://www.nasm.us/
   - Enables AES-NI hardware acceleration

### System Requirements

- **OS**: Windows 10 (1809+) or Windows 11
- **RAM**: 8 GB minimum, 16 GB recommended
- **Disk**: 2 GB for application, 15 GB for build environment
- **Processor**: x64 compatible CPU with AES-NI support (recommended)

---

## Quick Start

### Option 1: Build Everything (Recommended)

```cmd
scripts\build_all.bat
```

This creates:
- Standalone EXE with all dependencies
- Portable ZIP package
- MSI installer (if WiX is installed)

### Option 2: Build EXE Only

```cmd
scripts\build_exe.bat
```

### Option 3: Build MSI Only

```cmd
scripts\build_msi.bat
```

### Option 4: PowerShell Build Script

```powershell
# Build all packages
.\scripts\Build-SpectreMap.ps1 -Target All

# Build EXE only with clean
.\scripts\Build-SpectreMap.ps1 -Target Exe -Clean

# Build MSI with custom Qt path
.\scripts\Build-SpectreMap.ps1 -Target Msi -QtPath "C:\Qt\6.6.0\msvc2019_64"

# Debug build
.\scripts\Build-SpectreMap.ps1 -BuildType Debug
```

---

## Build Scripts

SpectreMap includes several build scripts for different scenarios:

| Script | Purpose | Output |
|--------|---------|--------|
| `scripts\install_prerequisites.bat` | Install all dependencies | N/A |
| `scripts\Install-Prerequisites.ps1` | Install dependencies (PowerShell) | N/A |
| `scripts\build_exe.bat` | Build standalone EXE | `dist\bin\SpectreMap.exe` |
| `scripts\build_msi.bat` | Build MSI installer | `SpectreMap-x.x.x-win64.msi` |
| `scripts\build_all.bat` | Build EXE, MSI, and ZIP | All packages |
| `scripts\Build-SpectreMap.ps1` | PowerShell build script | Configurable |
| `scripts\build_windows.bat` | Legacy build script | EXE + Packages |

### PowerShell Build Script Parameters

```powershell
Build-SpectreMap.ps1 [-BuildType <Release|Debug>]
                     [-Target <Exe|Msi|Zip|All>]
                     [-Clean]
                     [-SkipTests]
                     [-QtPath <path>]
                     [-OpenSSLPath <path>]
                     [-Version <version>]
```

---

## Manual Build

If you prefer to build manually without using the scripts:

1. Open **Developer Command Prompt for VS 2022** (as Administrator)

2. Create and enter build directory:
   ```cmd
   mkdir build_windows
   cd build_windows
   ```

3. Configure CMake:
   ```cmd
   cmake .. -G "Visual Studio 17 2022" -A x64 ^
       -DCMAKE_BUILD_TYPE=Release ^
       -DCMAKE_PREFIX_PATH="C:/Qt/6.6.0/msvc2019_64" ^
       -DOPENSSL_ROOT_DIR="C:/Program Files/OpenSSL-Win64" ^
       -DBUILD_MSI_INSTALLER=ON
   ```

4. Build the project:
   ```cmd
   cmake --build . --config Release --parallel
   ```

5. Install to distribution folder:
   ```cmd
   cmake --install . --config Release
   ```

6. Create packages:
   ```cmd
   cpack -G WIX -C Release
   cpack -G ZIP -C Release
   ```

---

## Deployment

### Standalone Executable

After building, the standalone executable will be located at:
```
dist\bin\SpectreMap.exe
```

This executable includes all necessary components and can be distributed as-is.

### ZIP Package

A portable ZIP package will be created at:
```
SpectreMap-1.0.0-win64-portable.zip
```

Users can extract and run without installation. The ZIP includes:
- SpectreMap.exe
- All Qt and OpenSSL dependencies
- AI/ML models (spectremap-models/)
- Resources and configuration files

### MSI Installer

The Windows Installer (MSI) package will be created at:
```
SpectreMap-1.0.0-win64.msi
```

Features:
- Professional installation with Start Menu shortcuts
- Desktop shortcut creation (optional)
- Add/Remove Programs integration
- Application icons and branding
- ASLR, DEP, and High Entropy VA security
- Automatic file associations
- Clean uninstall support

Installation commands:
```cmd
REM Install silently
msiexec /i SpectreMap-1.0.0-win64.msi /quiet

REM Install with UI
msiexec /i SpectreMap-1.0.0-win64.msi

REM Uninstall
msiexec /x SpectreMap-1.0.0-win64.msi
```

---

## AI/ML Models

SpectreMap includes bundled TensorFlow models for threat detection and analysis.

### Included Models

| Model | Description | Use Case |
|-------|-------------|----------|
| `anomaly_detector` | CNN-based network anomaly detection | Port scans, DDoS, protocol violations |
| `behavior_analyzer` | Bidirectional LSTM | Lateral movement, insider threats |
| `signal_classifier` | Deep CNN for RF signals | WiFi/BLE/Zigbee/SDR classification |
| `cnn_model` | General-purpose CNN | Image-based security analysis |
| `rnn_model` | Recurrent neural network | Sequential threat data |

### Model Location

Models are located in the `spectremap-models/` directory and are automatically bundled with the installation.

### Training Custom Models

1. Ensure Python 3.11+ is installed with TensorFlow:
   ```cmd
   pip install tensorflow numpy scipy scikit-learn
   ```

2. Use the training scripts:
   ```cmd
   cd spectremap-models
   python examples/export_for_spectremap.py
   ```

3. Trained models will be exported to `spectremap_exported_models/`

### Model Manager

The application includes a Model Manager (accessible via AI Settings) for:
- Loading pre-trained models
- Training custom models on your data
- Hardware selection (CPU/GPU)
- Model performance monitoring

---

## ASM x64 Optimizations

SpectreMap includes assembly-optimized cryptographic routines for maximum performance.

### Features

- **AES-NI Acceleration**: Hardware-accelerated AES-256-GCM encryption
- **RDRAND Integration**: Hardware random number generation
- **ChaCha20-Poly1305**: High-performance AEAD cipher
- **Multi-block Processing**: Efficient bulk encryption

### Files

| File | Description |
|------|-------------|
| `asm/aes_gcm_x64.asm` | AES-NI accelerated AES-GCM implementation |
| `asm/encryption_x64.asm` | AES-256 CBC with RDRAND key generation |
| `asm/asm_stub.c` | C fallback when NASM is not available |

### Building with ASM Support

If NASM is installed, assembly optimizations are automatically enabled:

```cmd
where nasm
REM If NASM is found, ASM support is enabled
```

Without NASM, the build uses C fallback implementations with identical functionality.

### Performance Comparison

| Operation | C Implementation | ASM + AES-NI |
|-----------|-----------------|--------------|
| AES-256-GCM (1MB) | ~45 ms | ~8 ms |
| Key Generation | ~2 ms | ~0.3 ms |
| ChaCha20 (1MB) | ~35 ms | ~12 ms |

---

## Troubleshooting

### Prerequisites Not Found

**Solution**: Run the prerequisites installer:
```cmd
scripts\install_prerequisites.bat
```

### Qt Not Found

**Error**: `Could not find a package configuration file provided by "Qt6"`

**Solution**: 
1. Verify Qt is installed at `C:\Qt\6.6.0\msvc2019_64`
2. Update `CMAKE_PREFIX_PATH` in build script to match your Qt installation
3. Ensure Qt bin directory is in PATH

### OpenSSL Not Found

**Error**: `Could not find OpenSSL`

**Solution**:
1. Install OpenSSL from https://slproweb.com/products/Win32OpenSSL.html
2. Choose "Win64 OpenSSL v3.x.x" (full version, not Light)
3. Install to default location or update `OPENSSL_ROOT_DIR` in build script

### MSI Build Fails

**Error**: `WiX Toolset not found`

**Solution**:
1. Install WiX Toolset 3.11 from https://wixtoolset.org/
2. Add WiX bin directory to PATH
3. Reopen command prompt and rebuild

### Missing DLLs

**Error**: Application fails to start with "DLL not found" error

**Solution**:
1. Run `windeployqt` on the executable:
   ```cmd
   C:\Qt\6.6.0\msvc2019_64\bin\windeployqt.exe build_windows\Release\SpectreMap.exe
   ```
2. Copy OpenSSL DLLs if needed:
   - `libssl-3-x64.dll`
   - `libcrypto-3-x64.dll`

### Administrator Rights Required

SpectreMap requires administrator privileges for network scanning operations. The application will automatically request elevation on Windows 10/11.

---

## Static Build (Advanced)

For a fully self-contained executable with no external dependencies:

1. Build Qt statically (time-consuming)
2. Use static OpenSSL libraries
3. Configure CMake with:
   ```cmd
   -DQt6_USE_STATIC_LIBS=ON
   -DOPENSSL_USE_STATIC_LIBS=ON
   ```

This creates a larger executable (~50-80 MB) but eliminates all DLL dependencies.

---

## Digital Signing (Recommended)

For professional distribution, sign the executable and MSI:

1. Obtain a code signing certificate
2. Use `signtool.exe`:
   ```cmd
   signtool sign /f certificate.pfx /p password /t http://timestamp.digicert.com SpectreMap.exe
   signtool sign /f certificate.pfx /p password /t http://timestamp.digicert.com SpectreMap.msi
   ```

---

## Distribution Checklist

Before distributing SpectreMap:

### Build Verification
- [ ] Build in Release mode for optimal performance
- [ ] Verify no debug symbols in release build
- [ ] Test executable starts without errors
- [ ] Check file size is reasonable (~50-100 MB with dependencies)

### Functionality Testing
- [ ] Test on clean Windows 10/11 installation
- [ ] Verify administrator privileges prompt appears
- [ ] Test all themes (80s Cosmic, 90s Cyber, Normal, Dark, Custom)
- [ ] Confirm network scanning functionality
- [ ] Validate encryption/decryption operations
- [ ] Test AI/ML model loading and inference
- [ ] Check all modules load correctly

### Installer Testing
- [ ] Test MSI installation (standard and silent)
- [ ] Verify Start Menu shortcuts work
- [ ] Test uninstallation is clean
- [ ] Verify portable ZIP extraction works
- [ ] Check file associations (if any)

### Security
- [ ] Code-sign the executable and MSI
- [ ] Verify ASLR/DEP/HIGHENTROPYVA enabled
- [ ] Scan with antivirus to ensure no false positives
- [ ] Test on Windows Defender

### Documentation
- [ ] Update version numbers
- [ ] Update changelog
- [ ] Verify README is current
- [ ] Include license file

---

## Support

For build issues or questions:

- **Email**: lackadaisicalresearch@pm.me
- **XMPP+OTR**: thelackadaisicalone@xmpp.jp
- **Website**: https://lackadaisical-security.com
- **GitHub**: https://github.com/Lackadaisical-Security

---

**Copyright © 2025 Lackadaisical Security. All rights reserved.**

SpectreMap™ is a trademark of Lackadaisical Security.
