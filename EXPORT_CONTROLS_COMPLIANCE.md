# Export Controls Compliance Notice
## SpectreMap - Visual Reconnaissance & Threat Terrain Mapper

**Document Version:** 1.0  
**Effective Date:** January 28, 2026  
**Software Version:** 1.0.0  
**Prepared by:** Lackadaisical Security  

---

## 1. Executive Summary

SpectreMap is a professional-grade cybersecurity reconnaissance platform that may be subject to export control regulations under United States and Japanese law. This document outlines the applicable regulatory frameworks and compliance requirements for distribution, export, and use of this software.

**⚠️ CRITICAL NOTICE:** Users, distributors, and developers are solely responsible for ensuring compliance with all applicable export control laws and regulations in their jurisdiction.

---

## 2. Applicable US Export Control Regulations

### 2.1 Export Administration Regulations (EAR)

**Controlling Agency:** Bureau of Industry and Security (BIS), U.S. Department of Commerce

SpectreMap contains technologies that are likely controlled under the EAR, specifically:

#### **Encryption Controls (ECCN 5D002)**
- **AES-256-GCM encryption** (production-grade implementation)
- **ChaCha20-Poly1305 AEAD cipher**
- **Triple-layer hybrid encryption**
- **Post-Quantum Cryptography** (Kyber/Dilithium algorithms)
- **Hardware-accelerated cryptographic operations** (AES-NI support)
- **OpenSSL integration** with cryptographically secure random generation

**Classification:** Likely **ECCN 5D002** - "Information Security" software  
**License Exception:** May qualify for **License Exception ENC** under 15 CFR § 740.17 if:
- The software is publicly available (open source), OR
- A one-time self-classification report and annual sales reports are submitted to BIS

#### **Intrusion Software Controls (ECCN 4D004 / 4E001)**
- **Network reconnaissance capabilities** (port scanning, service enumeration)
- **Anti-debugging and anti-VM detection** techniques
- **Memory manipulation and code injection** capabilities
- **Vulnerability assessment** and exploit correlation
- **Process hiding and obfuscation** techniques
- **Anti-forensics** capabilities (secure wiping, memory scrubbing)
- **MAC address spoofing** and TTL fingerprint manipulation

**Classification:** May fall under **ECCN 4D004.a** - "Intrusion software"  
**Risk Assessment:** High - The software's capabilities for:
- Defeating protective countermeasures
- Network intrusion and reconnaissance
- Anti-analysis/anti-forensics
- Process hiding and evasion techniques

These features may classify SpectreMap as "intrusion software" or "cybersecurity items."

#### **Telecommunications Equipment (ECCN 5A002)**
- **SDR (Software-Defined Radio) integration** (RTL-SDR support)
- **Multi-spectrum signal analysis** (WiFi/BLE/Zigbee/LTE)
- **RF signal classification and decoding**
- **Signal Intelligence (SIGINT) modules**

**Classification:** Components may fall under **ECCN 5A002** - Telecommunications equipment

### 2.2 International Traffic in Arms Regulations (ITAR)

**Controlling Agency:** Directorate of Defense Trade Controls (DDTC), U.S. Department of State

**Applicability Assessment:**

SpectreMap is **unlikely** to be an ITAR-controlled defense article unless:
1. It was specifically developed for military or intelligence applications
2. It incorporates classified or controlled defense technologies
3. It is designed for offensive cyber warfare operations
4. The U.S. government has designated it as a defense article

**Categories of Potential Concern:**
- **USML Category XI(a)** - Military electronics (if designed for military SIGINT)
- **USML Category XIII(b)** - Auxiliary military equipment (if used in military cyber operations)

**Current Assessment:** Likely **NOT ITAR-controlled** if used for commercial cybersecurity purposes. However, **custom military variants or government contracts** may trigger ITAR jurisdiction.

### 2.3 Office of Foreign Assets Control (OFAC) Sanctions

**Controlling Agency:** U.S. Department of the Treasury

**Prohibited Destinations (as of 2026):**
SpectreMap and related technical data may **NOT** be exported, re-exported, or transferred to:
- **Comprehensively Sanctioned Countries:** Cuba, Iran, North Korea, Syria, Russia (partially), Belarus (partially)
- **Crimea Region of Ukraine**
- **Specially Designated Nationals (SDNs)** - Individuals/entities on OFAC sanctions lists

**Compliance Requirement:** Screen all end-users and destinations against:
- OFAC SDN List
- OFAC Consolidated Sanctions List
- BIS Denied Persons List
- BIS Entity List
- DDTC Debarred List

---

## 3. Japanese Export Control Regulations

### 3.1 Foreign Exchange and Foreign Trade Act (FEFTA)

**Controlling Agency:** Ministry of Economy, Trade and Industry (METI)

#### **Cryptographic Controls (Export Trade Control Order - List Item 5)**
Japan regulates the export of cryptographic software under the FEFTA "Catch-All" controls.

**Applicable Items:**
- **Item 5-2 (Information Security)** - Encryption software exceeding 56-bit key length
  - SpectreMap's **AES-256** and **ChaCha20** encryption fall under this category
  
**License Requirement:** Export license may be required for destinations outside of Group A countries (e.g., USA, EU, Australia, South Korea).

**Exceptions:**
- **Mass-market encryption** exemption if:
  - The software is publicly available
  - Not specifically designed for government/military use
  - Meets "General Use" criteria

#### **Intrusion/Surveillance Software Controls**
Japan has implemented **Wassenaar Arrangement** controls on intrusion and surveillance software.

**Applicable Category:** Intrusion software that:
- Defeats protective countermeasures
- Enables unauthorized access
- Conducts covert surveillance

**Export Notification:** May require notification to METI before export to non-Group A countries.

### 3.2 Wassenaar Arrangement Compliance (Japan)

Japan is a signatory to the **Wassenaar Arrangement on Export Controls for Conventional Arms and Dual-Use Goods and Technologies**.

**Dual-Use Items:**
- **5.D.2** - Information security software (encryption)
- **4.D.4** - Intrusion software

**Compliance:** SpectreMap falls under Wassenaar dual-use categories, requiring:
- Export license for non-Wassenaar member states
- End-use and end-user statements
- Compliance with national implementation measures

---

## 4. Export Compliance Recommendations

### 4.1 For Developers and Distributors

#### **Mandatory Actions:**
1. **Self-Classification:**
   - Determine the correct Export Control Classification Number (ECCN)
   - Consider engaging a trade compliance attorney or consultant
   - Document the classification decision

2. **Encryption Registration (US):**
   - If distributing internationally, submit **BIS Encryption Registration** (one-time)
   - File **Semi-Annual Sales Reports** if required
   - Maintain records for 5 years

3. **End-User Screening:**
   - Implement automated screening against:
     - OFAC SDN List
     - BIS Denied Persons List
     - BIS Entity List
   - Document all screening results
   - Deny access to sanctioned persons/countries

4. **Export License Management:**
   - Determine if exports require a license
   - Apply for licenses when required (BIS or METI)
   - Track license conditions and expiration

5. **Technical Data Controls:**
   - Source code may be controlled as "technology" or "technical data"
   - Implement access controls for non-US persons
   - Consider "deemed export" rules for foreign nationals accessing code

#### **Recommended Actions:**
- Publish export control notices in software documentation
- Include export control warnings in download pages
- Implement geolocation blocking for sanctioned countries
- Consult with legal counsel specializing in export controls
- Join industry associations (e.g., BSA, Software Alliance) for guidance

### 4.2 For End-Users

#### **Compliance Obligations:**
1. **Authorization Verification:**
   - Ensure you have legal authorization to use reconnaissance tools
   - Comply with Computer Fraud and Abuse Act (CFAA - 18 U.S.C. § 1030)
   - Respect GDPR, CCPA, and other privacy regulations

2. **Export/Re-Export Restrictions:**
   - Do NOT re-export SpectreMap to sanctioned countries
   - Do NOT provide to SDNs or denied parties
   - Do NOT use for unauthorized intrusion or espionage

3. **Government/Military Use:**
   - If using in a government or military context, additional controls may apply
   - Consult with your organization's export compliance officer
   - Consider ITAR implications for defense applications

4. **International Use:**
   - Check local laws regarding cybersecurity tools
   - Some countries prohibit encryption or intrusion software
   - Obtain necessary permits or licenses in your jurisdiction

---

## 5. Country-Specific Restrictions

### 5.1 Prohibited Destinations (No Export/Re-Export)

**OFAC Comprehensive Sanctions:**
- ❌ **Cuba** - Comprehensive embargo (31 CFR Part 515)
- ❌ **Iran** - Comprehensive embargo (31 CFR Part 560)
- ❌ **North Korea** - Comprehensive embargo (31 CFR Part 510)
- ❌ **Syria** - Comprehensive embargo (31 CFR Part 542)
- ❌ **Crimea, Donetsk, Luhansk (Ukraine)** - Regional sanctions (31 CFR Part 589)

**Partial Sanctions (High Risk):**
- ⚠️ **Russia** - Sectoral sanctions (31 CFR Part 589) - Consult legal counsel
- ⚠️ **Belarus** - Sectoral sanctions (31 CFR Part 548) - Consult legal counsel

### 5.2 High-Risk Destinations (License Likely Required)

**Countries of Concern (State Sponsors of Terrorism):**
- **Cuba** - Already under embargo
- **Iran** - Already under embargo
- **North Korea** - Already under embargo
- **Syria** - Already under embargo

**Arms Embargo Countries (UN/EU):**
- Somalia, Sudan, South Sudan, Libya, Central African Republic
- Venezuela (US arms embargo)
- Myanmar (Burma) - US/EU restrictions

**BIS Entity List Considerations:**
- China, Russia - Many entities on BIS Entity List (high-tech sector)
- Verify end-users against Entity List before export

### 5.3 License Exception Eligible Destinations

**Group A Countries (Japan FEFTA):**
- United States, Canada, EU member states, United Kingdom
- Australia, New Zealand, South Korea, Norway, Switzerland
- These countries generally allow encryption exports with fewer restrictions

**License Exception ENC (US EAR):**
- May apply to certain encryption exports after BIS notification
- Still prohibited to sanctioned countries

---

## 6. Technical Data and Source Code Controls

### 6.1 Source Code Classification

**Export Control Status:**
- Source code is controlled as **"technology"** or **"software"** under EAR
- **ECCN 5D002** likely applies to encryption source code
- **ECCN 4D004** may apply to intrusion software source code

**Public Release Considerations:**
- **Publicly available** software may qualify for exclusions
- Must meet criteria: no restrictions on further dissemination, available to the public
- Consider **License Exception TSU** (Technology and Software Unrestricted)

### 6.2 Open Source Implications

**Current Status:** Proprietary software (according to README)

**If Open-Sourced:**
- May qualify for **"publicly available"** exclusions
- Still subject to sanctioned country restrictions
- Must not be re-exported to prohibited end-users
- Consider **Publicly Available Encryption Source Code (PAESC)** exemption

**GitHub Hosting:**
- GitHub implements US export controls (blocks access from sanctioned countries)
- Public repositories may still require export compliance
- Developer remains responsible for compliance

### 6.3 "Deemed Export" Considerations

**Definition:** Release of controlled technology to foreign nationals in the US

**Applicability:**
- Sharing source code with non-US persons may constitute an "export"
- Development teams with foreign nationals require screening
- May need export license for technology sharing within US borders

**Mitigation:**
- Implement access controls for sensitive code sections
- Screen development team members' nationalities
- Consider segregating controlled components

---

## 7. Specific Technology Considerations

### 7.1 Cryptographic Components

**Controlled Technologies:**
1. **AES-256-GCM** - Exceeds 56-bit threshold (controlled)
2. **ChaCha20-Poly1305** - Modern AEAD cipher (controlled)
3. **Post-Quantum Crypto** (Kyber, Dilithium) - Emerging standards (controlled)
4. **Triple-layer hybrid encryption** - Cascading ciphers (controlled)
5. **Hardware acceleration** (AES-NI) - May increase control level

**Compliance Path:**
- **One-time BIS notification** for encryption (if publicly available)
- **License Exception ENC** after classification report submission
- **Publicly Available Encryption Source Code** exemption (if open-sourced)

### 7.2 Intrusion Software Features

**High-Risk Capabilities (ECCN 4D004.a):**
1. **Anti-debugging** - Defeats protective countermeasures ✓
2. **Anti-VM detection** - Evasion techniques ✓
3. **Process hiding/obfuscation** - Concealment capabilities ✓
4. **Memory manipulation** - Code injection potential ✓
5. **Network reconnaissance** - Unauthorized access enablement ✓
6. **Anti-forensics** - Evidence destruction ✓
7. **MAC spoofing, TTL manipulation** - Identity concealment ✓

**Control Implications:**
- May require **individual export licenses** for certain destinations
- **Presumption of denial** for intrusion software to many countries
- End-use statements and compliance documentation required

### 7.3 Signal Intelligence (SIGINT) Capabilities

**Controlled Technologies:**
1. **Multi-spectrum analysis** (WiFi/BLE/Zigbee/LTE)
2. **SDR integration** (RTL-SDR compatible)
3. **Signal classification** with deep learning
4. **Device fingerprinting** and metadata correlation
5. **Passive surveillance** capabilities

**Potential Classification:**
- **ECCN 5A002** (Telecommunications equipment)
- **ECCN 3A001** (Electronic equipment for signal analysis)
- May require license for non-Wassenaar countries

---

## 8. Compliance Procedures

### 8.1 Pre-Export Checklist

**Before ANY export, re-export, or transfer:**

- [ ] **Determine ECCN** - Self-classify or obtain Commodity Classification
- [ ] **Screen End-User** - Check against all sanctions/denied party lists
- [ ] **Screen Destination** - Verify country is not under embargo/sanctions
- [ ] **Verify End-Use** - Ensure legitimate cybersecurity purpose (not malicious)
- [ ] **Check License Requirement** - Determine if export license needed
- [ ] **Apply for License** (if required) - BIS or METI application
- [ ] **Document Everything** - Maintain records for 5+ years
- [ ] **Obtain End-Use Statement** - Written certification from recipient
- [ ] **Implement Technical Controls** - Geoblocking, access restrictions
- [ ] **Review Annually** - Regulations change frequently

### 8.2 Recordkeeping Requirements

**Required Documentation (retain 5 years):**
1. Export license applications and approvals
2. Commodity classification determinations
3. Screening results (denied party checks)
4. End-use/end-user statements
5. Shipping documentation and invoices
6. Technical specifications and datasheets
7. Correspondence with regulators
8. Training records for export compliance

### 8.3 Reporting Requirements

**US (BIS):**
- **Encryption Registration** - One-time notification (if using License Exception ENC)
- **Semi-Annual Sales Reports** - For certain encryption exports
- **Unusual Activity Reports** - Suspicious export inquiries

**Japan (METI):**
- **Export Notifications** - Prior notification for controlled exports
- **Post-Shipment Verification** - May be requested by authorities

---

## 9. Penalties for Non-Compliance

### 9.1 United States Penalties

**Civil Penalties (EAR):**
- Up to **$368,136 per violation** (adjusted annually for inflation)
- Enhanced penalties: up to **$1,840,681 or 2x transaction value**

**Criminal Penalties (EAR):**
- Fines up to **$1,000,000 per violation**
- Imprisonment up to **20 years**
- Both individuals and corporations liable

**ITAR Violations:**
- Civil penalties: up to **$1,281,141 per violation**
- Criminal penalties: up to **$1,000,000** and **20 years imprisonment**

**OFAC Violations:**
- Civil penalties: up to **$368,136 per violation** (strict liability)
- Criminal penalties: up to **$1,000,000** and **20 years imprisonment**

**Additional Consequences:**
- **Export privilege denial** - Loss of ability to export
- **Debarment** - Exclusion from government contracts
- **Seizure of goods** - Forfeiture of exported items
- **Reputation damage** - Public disclosure of violations

### 9.2 Japanese Penalties

**FEFTA Violations:**
- **Criminal penalties:** Imprisonment up to **10 years** and/or fines up to **¥10,000,000** (corporations: up to **¥1,000,000,000**)
- **Administrative sanctions:** License revocation, export prohibition orders
- **International cooperation:** Japan coordinates with US/EU on enforcement

---

## 10. Liability Disclaimer

### 10.1 Developer Disclaimer

**LACKADAISICAL SECURITY EXPRESSLY DISCLAIMS ALL LIABILITY FOR:**
- Unauthorized export or re-export of SpectreMap
- User non-compliance with applicable export control laws
- Misuse of the software for illegal purposes
- Damages arising from export control violations
- Legal fees, penalties, or sanctions incurred by users

**Users acknowledge and agree that:**
1. They are solely responsible for export compliance
2. They will not export/re-export to sanctioned countries or persons
3. They will obtain all necessary licenses and authorizations
4. They will use the software only for lawful, authorized purposes

### 10.2 "Know Your Customer" (KYC) Requirements

**Distributors must:**
- Implement due diligence procedures for customers
- Obtain certifications of authorized use
- Screen against denied party lists
- Report suspicious inquiries or orders
- Refuse service to high-risk customers

**Red Flags (potential illegal activity):**
- Vague or evasive end-use descriptions
- Unwillingness to provide end-user information
- Cash payment or unusual financial arrangements
- Delivery to freight forwarders or transshipment points
- Customer lacks technical knowledge of product
- Request for obsolete or incompatible configurations

---

## 11. Best Practices and Recommendations

### 11.1 For Developers

1. **Engage Export Counsel:** Consult with attorneys specializing in export controls
2. **Implement Compliance Program:** Written policies, training, audits
3. **Use License Exceptions:** Maximize use of ENC, TSU, and other exceptions
4. **Document Decisions:** Maintain detailed classification and licensing records
5. **Technology Segmentation:** Separate controlled components from non-controlled
6. **Access Controls:** Implement technical measures to prevent unauthorized access
7. **Regular Audits:** Review compliance program annually
8. **Stay Informed:** Monitor regulatory changes (BIS, DDTC, OFAC updates)

### 11.2 For Users

1. **Verify Authorization:** Ensure written permission for all reconnaissance activities
2. **Comply with Local Laws:** Check regulations in your jurisdiction
3. **Screen Transactions:** Do not transfer to sanctioned parties
4. **Maintain Records:** Document legitimate use and compliance efforts
5. **Report Violations:** Voluntary self-disclosure may reduce penalties
6. **Training:** Ensure personnel understand export control obligations
7. **Incident Response:** Have procedures for suspected violations

### 11.3 For International Distributors

1. **Foreign Importer Authorization:** Verify import licenses in destination country
2. **Re-Export Controls:** Ensure downstream recipients comply with US/Japanese law
3. **Contract Clauses:** Include export control provisions in agreements
4. **Certificate of End-Use:** Obtain from all customers
5. **Diversion Risk Assessment:** Evaluate transshipment and re-export risks
6. **Jurisdictional Analysis:** Determine if US/Japanese law applies to your transactions

---

## 12. Encryption Notification Template

### 12.1 BIS Encryption Registration (Sample)

**To:** Bureau of Industry and Security, Encryption Request Coordinator  
**Email:** crypt@bis.doc.gov

**Subject:** Encryption Registration - SpectreMap v1.0.0

**Product Information:**
- **Product Name:** SpectreMap - Visual Reconnaissance & Threat Terrain Mapper
- **Manufacturer:** Lackadaisical Security
- **Version:** 1.0.0
- **ECCN (Self-Classified):** 5D002.c.1
- **Cryptographic Functionality:**
  - AES-256-GCM (authenticated encryption)
  - ChaCha20-Poly1305 (AEAD cipher)
  - OpenSSL integration
  - Key length: 256 bits
  - Authentication: HMAC-SHA256, Poly1305

**License Exception Claimed:** ENC (15 CFR § 740.17(b)(1))

**Publicly Available:** [Yes/No] - (Select based on distribution model)

**Technical Description:** [Include detailed cryptographic specifications]

**Point of Contact:**
- Name: [Your Name]
- Email: lackadaisicalresearch@pm.me
- Phone: [Your Phone]

---

## 13. Additional Resources

### 13.1 US Government Resources

**Bureau of Industry and Security (BIS):**
- Website: https://www.bis.doc.gov
- Encryption: https://www.bis.doc.gov/encryption
- ECCN Tool: https://www.bis.doc.gov/index.php/licensing/commerce-control-list-classification

**Directorate of Defense Trade Controls (DDTC):**
- Website: https://www.pmddtc.state.gov
- ITAR: 22 CFR Parts 120-130

**Office of Foreign Assets Control (OFAC):**
- Website: https://www.treasury.gov/ofac
- Sanctions Lists: https://sanctionssearch.ofac.treas.gov

**Wassenaar Arrangement:**
- Website: https://www.wassenaar.org

### 13.2 Japanese Government Resources

**Ministry of Economy, Trade and Industry (METI):**
- Website: https://www.meti.go.jp/english
- Export Control: https://www.meti.go.jp/policy/anpo/englishpage.html

**Center for Information on Security Trade Control (CISTEC):**
- Website: https://www.cistec.or.jp/english

### 13.3 Industry Organizations

- **BSA | The Software Alliance:** https://www.bsa.org
- **CompTIA:** https://www.comptia.org (IT industry association)
- **NCBFAA:** National Customs Brokers & Forwarders Association of America

---

## 14. Revision History

| Version | Date       | Changes                     | Author                |
|---------|------------|-----------------------------|------------------------|
| 1.0     | 2026-01-28 | Initial release            | Lackadaisical Security |

---

## 15. Contact Information for Compliance Questions

**Lackadaisical Security Export Compliance:**
- **Email:** lackadaisicalresearch@pm.me
- **Website:** https://lackadaisical-security.com
- **XMPP+OTR:** thelackadaisicalone@xmpp.jp

**For specific export license questions, contact:**
- **US (BIS):** Outreach and Educational Services Division - (202) 482-4811
- **US (DDTC):** Office of Defense Trade Controls Policy - (202) 663-2980
- **US (OFAC):** Compliance Hotline - (800) 540-6322
- **Japan (METI):** Trade Control Policy Division - +81-3-3501-1511

---

## ⚠️ FINAL WARNING

**THIS DOCUMENT IS FOR INFORMATIONAL PURPOSES ONLY AND DOES NOT CONSTITUTE LEGAL ADVICE.**

Export control laws are complex, frequently changing, and carry severe penalties for violations. **You must consult with a qualified export control attorney or compliance professional** before:
- Exporting or re-exporting SpectreMap
- Distributing to non-US persons
- Publishing source code publicly
- Engaging in international transactions
- Using in government/military contexts

**Lackadaisical Security assumes no responsibility for your compliance with export control laws. You use this software at your own risk and legal responsibility.**

---

**Copyright © 2026 Lackadaisical Security. All rights reserved.**

---