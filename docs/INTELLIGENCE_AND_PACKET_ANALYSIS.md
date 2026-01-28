# SpectreMap - Intelligence Gathering & Packet Analysis Guide

## 🔍 OSINT API Integration (15+ Public Sources)

### Overview
SpectreMap integrates with 15+ free and commercial intelligence APIs for comprehensive threat research and reconnaissance.

### Supported APIs

#### 1. **Shodan** (Device Search)
```cpp
connector->setAPIKey("shodan", "YOUR_API_KEY");
auto result = connector->queryShodan("192.168.1.1");
// Returns: ports, hostnames, organization, ISP, vulnerabilities
```
- **Get API Key**: https://account.shodan.io/
- **Free Tier**: 100 queries/month
- **Use Case**: IoT device discovery, service enumeration

#### 2. **VirusTotal** (File/URL/Domain/IP Analysis)
```cpp
connector->setAPIKey("virustotal", "YOUR_API_KEY");
auto result = connector->queryVirusTotal("malware.exe", "file");
// Returns: detection ratio, AV vendor results, scan date
```
- **Get API Key**: https://www.virustotal.com/gui/my-apikey
- **Free Tier**: 4 requests/minute
- **Use Case**: Malware analysis, URL reputation

#### 3. **AbuseIPDB** (IP Reputation)
```cpp
connector->setAPIKey("abuseipdb", "YOUR_API_KEY");
auto result = connector->queryAbuseIPDB("1.2.3.4");
// Returns: abuse confidence score, reports, categories
```
- **Get API Key**: https://www.abuseipdb.com/api
- **Free Tier**: 1000 queries/day
- **Use Case**: IP reputation, abuse detection

#### 4. **AlienVault OTX** (Threat Intelligence)
```cpp
connector->setAPIKey("alienvault", "YOUR_API_KEY");
auto result = connector->queryAlienVault("evil.com");
// Returns: pulse count, tags, reputation
```
- **Get API Key**: https://otx.alienvault.com/api
- **Free Tier**: Unlimited (registration required)
- **Use Case**: IOC correlation, threat feeds

#### 5. **HaveIBeenPwned** (Breach Monitoring)
```cpp
connector->setAPIKey("haveibeenpwned", "YOUR_API_KEY");
auto result = connector->queryHaveIBeenPwned("email@example.com");
// Returns: breaches, pastes, most recent breach
```
- **Get API Key**: https://haveibeenpwned.com/API/Key
- **API**: https://haveibeenpwned.com/API/v3
- **Free Tier**: API key required (reasonable pricing)
- **Use Case**: Credential breach detection

#### 6. **URLScan.io** (URL Analysis)
```cpp
connector->setAPIKey("urlscan", "YOUR_API_KEY");
auto result = connector->queryURLScan("http://suspicious-site.com");
// Returns: screenshot, IP addresses, domains, verdict
```
- **Get API Key**: https://urlscan.io/user/signup
- **Free Tier**: Unlimited scans
- **Use Case**: Phishing detection, URL sandbox

#### 7. **GreyNoise** (Internet Scanner Detection)
```cpp
connector->setAPIKey("greynoise", "YOUR_API_KEY");
auto result = connector->queryGreyNoise("1.2.3.4");
// Returns: classification (benign/malicious), intent, tags
```
- **Get API Key**: https://www.greynoise.io/
- **Free Tier**: 50 queries/day
- **Use Case**: Distinguish targeted attacks from background noise

#### 8. **Censys** (Certificate/Host Search)
```cpp
connector->setAPIKey("censys", "YOUR_API_KEY");
auto result = connector->queryCensys("443.https");
// Returns: protocols, certificates, autonomous system
```
- **Get API Key**: https://censys.io/register
- **Free Tier**: 250 queries/month
- **Use Case**: Certificate transparency, TLS/SSL analysis

#### 9. **IPQualityScore** (Fraud/Proxy Detection)
```cpp
connector->setAPIKey("ipqs", "YOUR_API_KEY");
auto result = connector->queryIPQualityScore("1.2.3.4");
// Returns: proxy detection, VPN, Tor, fraud score
```
- **Get API Key**: https://www.ipqualityscore.com/create-account
- **Free Tier**: 5000 requests/month
- **Use Case**: Fraud prevention, VPN/proxy detection

#### 10. **SecurityTrails** (DNS/WHOIS History)
```cpp
connector->setAPIKey("securitytrails", "YOUR_API_KEY");
auto result = connector->querySecurityTrails("example.com");
// Returns: DNS history, subdomains, WHOIS, associated IPs
```
- **Get API Key**: https://securitytrails.com/
- **Free Tier**: 50 queries/month
- **Use Case**: Domain reconnaissance, infrastructure mapping

#### 11-15. **Additional Free APIs** (No Key Required)

**IP Geolocation**:
```cpp
auto result = connector->queryGeolocation("1.2.3.4");
// Uses: ip-api.com, ipapi.co, ipinfo.io
// Returns: country, city, ISP, coordinates
```

**BGP/ASN Data**:
```cpp
auto result = connector->queryBGPView("AS15169");
// Uses: bgpview.io
// Returns: prefix, ASN, upstreams, downstreams
```

### Multi-Source Aggregation

Combine data from multiple sources for comprehensive intelligence:

```cpp
auto aggregated = connector->queryMultiSource("target.com");
// Queries: Shodan, VirusTotal, AbuseIPDB, Geolocation, BGP
// Returns: Unified threat assessment with all data sources
```

### Rate Limiting & Caching

```cpp
// Set custom rate limits (requests per minute)
connector->setRateLimit("shodan", 1);  // 1 req/min
connector->setRateLimit("virustotal", 4);  // 4 req/min

// Enable caching to avoid duplicate queries
connector->enableCaching(true);

// Clear cache when needed
connector->clearCache();
```

### Async Operations

For non-blocking queries:

```cpp
connector->queryAsync("shodan", "192.168.1.1", [](const std::string& query, bool success) {
    if (success) {
        qDebug() << "Query completed:" << query;
    }
});
```

---

## 📦 Packet Capture & Analysis (Wireshark-Compatible)

### Overview
SpectreMap includes a production-grade packet analyzer with Wireshark-compatible output, supporting live capture and PCAP file analysis.

### Requirements

**Linux/Mac**:
```bash
sudo apt-get install libpcap-dev  # Ubuntu/Debian
brew install libpcap              # macOS
```

**Windows**:
- Download Npcap: https://npcap.com/
- Install with "WinPcap API-compatible mode"

### Basic Usage

#### 1. **List Network Interfaces**
```cpp
PacketAnalyzer analyzer;
auto interfaces = analyzer.listInterfaces();

for (const auto& iface : interfaces) {
    qDebug() << "Interface:" << iface.name;
    qDebug() << "Description:" << iface.description;
    qDebug() << "Addresses:" << iface.addresses;
}
```

#### 2. **Start Live Capture**
```cpp
if (analyzer.startCapture("eth0")) {
    qDebug() << "Capture started successfully";
} else {
    qDebug() << "Capture failed - check permissions";
}

// Stop capture
analyzer.stopCapture();
```

#### 3. **Apply BPF Filter**
```cpp
// Capture only HTTP traffic
analyzer.setBPFFilter("tcp port 80 or tcp port 443");

// Capture specific host
analyzer.setBPFFilter("host 192.168.1.100");

// Capture DNS queries
analyzer.setBPFFilter("udp port 53");
```

#### 4. **Load PCAP File**
```cpp
if (analyzer.startCaptureFromFile("/path/to/capture.pcap")) {
    auto packets = analyzer.getPacketList();
    qDebug() << "Loaded" << packets.size() << "packets";
}
```

### Packet Analysis

#### Get Packet List
```cpp
auto packets = analyzer.getPacketList();

for (const auto& packet : packets) {
    qDebug() << "Packet #" << packet.number;
    qDebug() << "  Source:" << packet.source_ip << ":" << packet.source_port;
    qDebug() << "  Destination:" << packet.dest_ip << ":" << packet.dest_port;
    qDebug() << "  Protocol:" << packet.protocol;
    qDebug() << "  Length:" << packet.length << "bytes";
}
```

#### Get Detailed Packet Information
```cpp
auto details = analyzer.getPacketDetails(1);  // Packet #1

// Ethernet layer
qDebug() << "Source MAC:" << details.ethernet.src_mac;
qDebug() << "Dest MAC:" << details.ethernet.dst_mac;

// IP layer
qDebug() << "Source IP:" << details.ip.src_ip;
qDebug() << "Dest IP:" << details.ip.dst_ip;
qDebug() << "TTL:" << details.ip.ttl;

// TCP layer
if (details.basic_info.protocol == "TCP") {
    qDebug() << "SYN:" << details.tcp.syn;
    qDebug() << "ACK:" << details.tcp.ack;
    qDebug() << "Seq:" << details.tcp.seq_number;
}
```

### Wireshark-Style Output

#### Hierarchical Tree View
```cpp
std::string tree = analyzer.getPacketTreeView(1);
// Output:
// Frame 1: 74 bytes
// ├─ Ethernet II
// │  ├─ Source: 00:11:22:33:44:55
// │  └─ Destination: aa:bb:cc:dd:ee:ff
// ├─ Internet Protocol Version 4
// │  ├─ Source: 192.168.1.100
// │  ├─ Destination: 93.184.216.34
// │  └─ TTL: 64
// └─ Transmission Control Protocol
//    ├─ Source Port: 54321
//    ├─ Destination Port: 80
//    └─ Flags: SYN
```

#### Hex Dump
```cpp
std::string hex = analyzer.getHexDump(1);
// Output:
// 0000  aa bb cc dd ee ff 00 11 22 33 44 55 08 00 45 00  ........"3DU..E.
// 0010  00 3c 1c 46 40 00 40 06 b1 e6 c0 a8 01 64 5d b8  .<.F@.@......d].
// 0020  d8 22 d4 31 00 50 38 af 52 01 00 00 00 00 a0 02  .".1.P8.R.......
```

#### ASCII Representation
```cpp
std::string ascii = analyzer.getASCIIDump(1);
```

### Protocol Extraction

#### Extract HTTP Hosts
```cpp
auto hosts = analyzer.extractHTTPHosts();
for (const auto& host : hosts) {
    qDebug() << "HTTP Host:" << host;
}
```

#### Extract DNS Queries
```cpp
auto queries = analyzer.extractDNSQueries();
for (const auto& query : queries) {
    qDebug() << "DNS Query:" << query;
}
```

#### Extract Credentials (Insecure Protocols)
```cpp
auto creds = analyzer.extractCredentials();
// Finds credentials in HTTP, FTP, Telnet, etc.
```

### Export Functions

```cpp
// Export to PCAP (Wireshark-compatible)
analyzer.exportToPCAP("/path/to/output.pcap");

// Export to PCAPNG (Next-generation PCAP)
analyzer.exportToPCAPNG("/path/to/output.pcapng");

// Export to CSV (for analysis in Excel/Python)
analyzer.exportToCSV("/path/to/output.csv");

// Export to JSON
analyzer.exportToJSON("/path/to/output.json");
```

### Statistics

```cpp
auto stats = analyzer.getStatistics();

qDebug() << "Total Packets:" << stats.total_packets;
qDebug() << "Total Bytes:" << stats.total_bytes;
qDebug() << "Duration:" << stats.duration_seconds << "seconds";
qDebug() << "Packets/sec:" << stats.packets_per_second;

// Protocol distribution
for (const auto& [protocol, count] : stats.protocol_counts) {
    qDebug() << protocol << ":" << count << "packets";
}
```

### Flow Analysis

```cpp
auto flows = analyzer.getFlows();

for (const auto& flow : flows) {
    qDebug() << "Flow:" << flow.src_ip << ":" << flow.src_port
             << "->" << flow.dst_ip << ":" << flow.dst_port;
    qDebug() << "  Packets:" << flow.packet_count;
    qDebug() << "  Bytes:" << flow.byte_count;
    qDebug() << "  Duration:" << (flow.end_time - flow.start_time) << "s";
}
```

### Real-Time Packet Callback

```cpp
analyzer.setPacketCallback([](const PacketDetails& packet) {
    qDebug() << "New packet:" << packet.basic_info.source_ip
             << "->" << packet.basic_info.dest_ip;
    
    // Process packet in real-time
});
```

### Color Coding (Like Wireshark)

```cpp
auto color = analyzer.getPacketColor(1);

switch (color) {
    case PacketColor::TCP_SYN:
        // Light blue - TCP connection initiation
        break;
    case PacketColor::TCP_RST:
        // Red - TCP reset
        break;
    case PacketColor::HTTP:
        // Green - HTTP traffic
        break;
    case PacketColor::DNS:
        // Blue - DNS queries
        break;
    // ... etc
}
```

---

## 🔗 Integration Examples

### Combined Intelligence & Packet Analysis

```cpp
// Analyze network traffic and enrich with threat intelligence
PacketAnalyzer packetAnalyzer;
OSINTAPIConnector osintConnector;

packetAnalyzer.startCapture("eth0");

// Extract unique IPs from captured traffic
std::set<std::string> unique_ips;
for (const auto& packet : packetAnalyzer.getPacketList()) {
    unique_ips.insert(packet.source_ip);
    unique_ips.insert(packet.dest_ip);
}

// Query threat intelligence for each IP
for (const auto& ip : unique_ips) {
    auto abuse_data = osintConnector.queryAbuseIPDB(ip);
    auto geo_data = osintConnector.queryGeolocation(ip);
    
    if (abuse_data.abuse_confidence_score > 75) {
        qDebug() << "HIGH RISK IP:" << ip;
        qDebug() << "  Confidence:" << abuse_data.abuse_confidence_score;
        qDebug() << "  Location:" << geo_data.city << "," << geo_data.country;
        qDebug() << "  ISP:" << geo_data.isp;
    }
}
```

### Automated Threat Detection Pipeline

```cpp
void runThreatDetectionPipeline(const std::string& pcap_file) {
    PacketAnalyzer analyzer;
    OSINTAPIConnector connector;
    
    // Load capture file
    analyzer.startCaptureFromFile(pcap_file);
    
    // Extract indicators
    auto http_hosts = analyzer.extractHTTPHosts();
    auto dns_queries = analyzer.extractDNSQueries();
    
    // Check URLs against VirusTotal
    for (const auto& host : http_hosts) {
        auto vt_result = connector.queryVirusTotal(host, "url");
        if (vt_result.positives > 0) {
            qDebug() << "Malicious URL detected:" << host;
            qDebug() << "  Detections:" << vt_result.positives << "/"
                     << vt_result.total;
        }
    }
    
    // Analyze DNS for DGA/C2
    for (const auto& domain : dns_queries) {
        auto otx_result = connector.queryAlienVault(domain);
        if (otx_result.pulse_count > 0) {
            qDebug() << "Suspicious domain:" << domain;
            qDebug() << "  Threat pulses:" << otx_result.pulse_count;
        }
    }
}
```

---

## 📋 Best Practices

### API Key Management
- Store API keys in encrypted configuration
- Use environment variables for sensitive keys
- Rotate keys regularly
- Monitor API quota usage

### Rate Limiting
- Respect API rate limits
- Implement exponential backoff
- Cache results to minimize queries
- Use batch endpoints when available

### Packet Capture
- Run with appropriate permissions (root/administrator)
- Apply BPF filters to reduce noise
- Monitor disk space for long captures
- Use ring buffers to prevent memory exhaustion

### Performance
- Use async operations for non-blocking queries
- Implement connection pooling for HTTP requests
- Cache DNS resolutions
- Optimize packet processing pipeline

---

## 🔒 Security Considerations

- **Never log API keys** in plain text
- **Sanitize user input** before API queries
- **Validate API responses** before processing
- **Use HTTPS** for all API communications
- **Implement timeouts** to prevent hanging requests
- **Handle errors gracefully** without exposing sensitive data
- **Respect data privacy** when capturing packets
- **Comply with** terms of service for each API

---

**Lackadaisical Security 2025**  
🌐 https://lackadaisical-security.com  
📧 lackadaisicalresearch@pm.me  
🐙 https://github.com/Lackadaisical-Security
