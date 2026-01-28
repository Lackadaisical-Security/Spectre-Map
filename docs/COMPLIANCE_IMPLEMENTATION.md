# Export Compliance Implementation Guide

## Overview

SpectreMap implements comprehensive geographic access restrictions to comply with US export control laws, including:

- **OFAC Comprehensive Sanctions** (Cuba, Iran, North Korea, Syria, Crimea)
- **OFAC Sectoral Sanctions** (Russia, Belarus)
- **UN/US Arms Embargoes** (Venezuela, Myanmar, Libya, etc.)
- **High-Risk Jurisdictions** (China, Pakistan, etc.)

## Blocked Countries (Complete List)

### Tier 1: Comprehensively Sanctioned (OFAC) - COMPLETE BLOCK
- ❌ **Cuba** (CU) - 31 CFR Part 515
- ❌ **Iran** (IR) - 31 CFR Part 560
- ❌ **North Korea** (KP) - 31 CFR Part 510
- ❌ **Syria** (SY) - 31 CFR Part 542
- ❌ **Crimea Region** (XCR) - 31 CFR Part 589
- ❌ **Donetsk Region** (XDO) - 31 CFR Part 589
- ❌ **Luhansk Region** (XLU) - 31 CFR Part 589

### Tier 2: Sectoral Sanctions - BLOCKED
- ❌ **Russia** (RU) - 31 CFR Part 589, EAR Part 746
- ❌ **Belarus** (BY) - 31 CFR Part 548

### Tier 3: Arms Embargo Countries - BLOCKED
- ❌ **Venezuela** (VE)
- ❌ **Myanmar/Burma** (MM)
- ❌ **Libya** (LY)
- ❌ **Somalia** (SO)
- ❌ **South Sudan** (SS)
- ❌ **Sudan** (SD)
- ❌ **Central African Republic** (CF)
- ❌ **Yemen** (YE)
- ❌ **Democratic Republic of Congo** (CD)
- ❌ **Eritrea** (ER)
- ❌ **Lebanon** (LB) - specific entities

### Tier 4: High-Risk (Allowed with Logging)
- ⚠️ **China** (CN) - BIS Entity List concerns
- ⚠️ **Hong Kong** (HK)
- ⚠️ **Pakistan** (PK)
- ⚠️ **Afghanistan** (AF)
- ⚠️ **Iraq** (IQ)
- ⚠️ **UAE** (AE) - transshipment risk
- ⚠️ **Turkey** (TR)
- ⚠️ **Egypt** (EG)

## Technical Implementation

### 1. Compile with Compliance Module

```bash
cd build
cmake -DENABLE_EXPORT_COMPLIANCE=ON ..
make
```

### 2. Dependencies Required

```bash
# Install libcurl for GeoIP queries
sudo apt install libcurl4-openssl-dev

# Install JSON library
sudo apt install nlohmann-json3-dev
```

### 3. Runtime Configuration

Edit `config/sanctioned_countries.json` to update sanctions list (must match OFAC current list).

### 4. Audit Logging

All access attempts are logged to `logs/compliance_audit.log`:
```
2026-01-28 14:30:15 | IP: 1.2.3.4 | Country: RU (Russia) | Action: BLOCKED | Level: 2 | Reason: Sectoral sanctions
```

### 5. VPN/Proxy Detection

Strict mode blocks VPN/Proxy/Tor from ALL countries to prevent circumvention:
```cpp
geoRestriction.setStrictMode(true); // Recommended for compliance
```

## Offline Mode (MaxMind GeoIP2)

For production deployment without internet access:

1. Download MaxMind GeoLite2 database
2. Place in `data/GeoLite2-Country.mmdb`
3. Enable offline mode in code:
```cpp
pImpl->use_offline_db = true;
```

## Update Procedures

**CRITICAL:** Sanctions lists change frequently. Update quarterly at minimum:

1. Check OFAC website: https://www.treasury.gov/ofac
2. Check BIS website: https://www.bis.doc.gov
3. Update `config/sanctioned_countries.json`
4. Recompile and redeploy

## Legal Compliance Notes

- This implementation provides **technical enforcement** only
- You are still responsible for legal compliance
- Consult export control attorney before international distribution
- Maintain audit logs for 5+ years
- Report violations to appropriate authorities

## GitHub Distribution

GitHub automatically blocks sanctioned countries, but you should:
- Include `EXPORT_CONTROLS_COMPLIANCE.md` in repository root
- Add export warning to README
- Consider private repository for sensitive versions
- Review GitHub's trade controls: https://docs.github.com/en/site-policy/other-site-policies/github-and-trade-controls

## Contact

For compliance questions:
- Email: lackadaisicalresearch@pm.me
- Legal: Consult export control counsel
- US Government: BIS (202) 482-4811, OFAC (800) 540-6322

---

**Disclaimer:** This implementation is provided as-is. Lackadaisical Security assumes no liability for your compliance with export control laws.