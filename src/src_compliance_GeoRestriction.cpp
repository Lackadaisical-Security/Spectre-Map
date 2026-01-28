/**
 * @file GeoRestriction.cpp
 * @brief Implementation of geographic access restrictions for export compliance
 */

#include "GeoRestriction.hpp"
#include "../core/Logger.hpp"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

using json = nlohmann::json;

namespace SpectreMap::Compliance {

// ============================================================================
// OFAC Comprehensive Sanctions (31 CFR) - COMPLETE BLOCK
// ============================================================================
const std::unordered_set<std::string> GeoRestriction::OFAC_SANCTIONED_COUNTRIES = {
    "CU",  // Cuba - 31 CFR Part 515
    "IR",  // Iran - 31 CFR Part 560
    "KP",  // North Korea (DPRK) - 31 CFR Part 510
    "SY",  // Syria - 31 CFR Part 542
    
    // Crimea and specific regions of Ukraine (31 CFR Part 589)
    "XCR", // Crimea region (special code)
    "XDO", // Donetsk region (special code)
    "XLU", // Luhansk region (special code)
};

// ============================================================================
// OFAC Partial/Sectoral Sanctions - HIGH RISK (Manual Review Required)
// ============================================================================
const std::unordered_set<std::string> GeoRestriction::OFAC_PARTIAL_SANCTIONS = {
    "RU",  // Russia - 31 CFR Part 589 (Sectoral sanctions, especially tech sector)
    "BY",  // Belarus - 31 CFR Part 548 (Sectoral sanctions)
};

// ============================================================================
// UN/EU Arms Embargoes and State Department Restrictions
// ============================================================================
const std::unordered_set<std::string> GeoRestriction::ARMS_EMBARGO_COUNTRIES = {
    "SO",  // Somalia - UN arms embargo
    "SS",  // South Sudan - UN arms embargo
    "SD",  // Sudan - UN/US arms embargo
    "LY",  // Libya - UN arms embargo
    "CF",  // Central African Republic - UN arms embargo
    "VE",  // Venezuela - US arms embargo
    "MM",  // Myanmar (Burma) - US/EU restrictions
    "YE",  // Yemen - UN arms embargo (partial)
    "LB",  // Lebanon - Arms embargo (Hezbollah)
    "CD",  // Democratic Republic of Congo - UN arms embargo (partial)
    "ER",  // Eritrea - UN arms embargo
};

// ============================================================================
// High-Risk Countries (BIS Entity List concentrations, export license likely needed)
// ============================================================================
const std::unordered_set<std::string> GeoRestriction::HIGH_RISK_COUNTRIES = {
    "CN",  // China - Many entities on BIS Entity List (tech sector)
    "HK",  // Hong Kong - Export control concerns
    "PK",  // Pakistan - Proliferation concerns
    "AF",  // Afghanistan - Security concerns
    "IQ",  // Iraq - Security and proliferation concerns
    
    // Countries with weak export control enforcement
    "AE",  // UAE - Transshipment risk
    "TR",  // Turkey - Transshipment concerns
    "EG",  // Egypt - Some restrictions
};

// ============================================================================
// Implementation Class
// ============================================================================
class GeoRestriction::Impl {
public:
    bool strict_mode = true;
    std::string audit_log_path = "logs/compliance_audit.log";
    
    // GeoIP service configuration
    std::string geoip_api_url = "http://ip-api.com/json/";
    bool use_offline_db = false;
    
    std::optional<GeoLocation> queryGeoIP(const std::string& ip_address) {
        if (use_offline_db) {
            return queryOfflineDatabase(ip_address);
        }
        return queryOnlineService(ip_address);
    }
    
    std::optional<GeoLocation> queryOnlineService(const std::string& ip) {
        CURL* curl = curl_easy_init();
        if (!curl) return std::nullopt;
        
        std::string response_data;
        std::string url = geoip_api_url + ip + "?fields=status,message,country,countryCode,region,city,lat,lon,isp,as,proxy,hosting";
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
        
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        if (res != CURLE_OK) {
            Logger::warning("GeoIP query failed for " + ip);
            return std::nullopt;
        }
        
        try {
            json j = json::parse(response_data);
            
            if (j["status"] == "fail") {
                Logger::warning("GeoIP lookup failed: " + j.value("message", "Unknown error"));
                return std::nullopt;
            }
            
            GeoLocation loc;
            loc.ip_address = ip;
            loc.country_code = j.value("countryCode", "");
            loc.country_name = j.value("country", "");
            loc.region = j.value("region", "");
            loc.city = j.value("city", "");
            loc.latitude = j.value("lat", 0.0);
            loc.longitude = j.value("lon", 0.0);
            loc.asn = j.value("as", "");
            loc.org = j.value("isp", "");
            loc.is_proxy = j.value("proxy", false);
            loc.is_vpn = false; // Would need enhanced API
            loc.is_tor = false;  // Would need Tor exit node list
            loc.is_hosting = j.value("hosting", false);
            
            return loc;
            
        } catch (const json::exception& e) {
            Logger::error("Failed to parse GeoIP response: " + std::string(e.what()));
            return std::nullopt;
        }
    }
    
    std::optional<GeoLocation> queryOfflineDatabase(const std::string& ip) {
        // TODO: Implement MaxMind GeoIP2 or similar offline database
        // For production use, integrate GeoLite2 database
        Logger::warning("Offline GeoIP database not yet implemented");
        return std::nullopt;
    }
    
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
        userp->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
};

// ============================================================================
// GeoRestriction Public Methods
// ============================================================================

GeoRestriction::GeoRestriction() : pImpl(std::make_unique<Impl>()) {
    Logger::info("Export Compliance: Geographic restriction engine initialized");
    Logger::info("OFAC Sanctioned Countries: " + std::to_string(OFAC_SANCTIONED_COUNTRIES.size()));
    Logger::info("Partial Sanctions (High Risk): " + std::to_string(OFAC_PARTIAL_SANCTIONS.size()));
    Logger::info("Total Restricted Countries: " + std::to_string(
        OFAC_SANCTIONED_COUNTRIES.size() + 
        OFAC_PARTIAL_SANCTIONS.size() + 
        ARMS_EMBARGO_COUNTRIES.size()
    ));
}

GeoRestriction::~GeoRestriction() = default;

RestrictionResult GeoRestriction::checkAccess(const std::string& ip_address) {
    auto geo_opt = pImpl->queryGeoIP(ip_address);
    
    if (!geo_opt) {
        // Failed to determine location - DENY by default (fail-secure)
        Logger::warning("Failed to determine geolocation for " + ip_address + " - BLOCKING");
        return RestrictionResult{
            .allowed = false,
            .level = RestrictionLevel::RESTRICTED,
            .country_code = "UNKNOWN",
            .country_name = "Unknown",
            .reason = "Unable to determine geographic location - access denied for compliance",
            .applicable_regulations = {"US EAR", "OFAC"}
        };
    }
    
    GeoLocation geo = geo_opt.value();
    
    // Check VPN/Proxy/Tor in strict mode
    if (pImpl->strict_mode) {
        if (geo.is_proxy || geo.is_vpn || geo.is_tor) {
            Logger::warning("Blocking VPN/Proxy/Tor access from " + ip_address);
            return RestrictionResult{
                .allowed = false,
                .level = RestrictionLevel::RESTRICTED,
                .country_code = geo.country_code,
                .country_name = geo.country_name,
                .reason = "VPN/Proxy/Tor access blocked for export compliance verification",
                .applicable_regulations = {"Export Compliance Policy"}
            };
        }
    }
    
    return checkCountry(geo.country_code);
}

RestrictionResult GeoRestriction::checkCountry(const std::string& country_code) {
    // Check OFAC Comprehensive Sanctions - IMMEDIATE BLOCK
    if (OFAC_SANCTIONED_COUNTRIES.count(country_code)) {
        std::string country_name = CountryDatabase::getCountryName(country_code);
        Logger::warning("BLOCKED: Access attempt from OFAC sanctioned country: " + country_name);
        
        return RestrictionResult{
            .allowed = false,
            .level = RestrictionLevel::COMPREHENSIVELY_SANCTIONED,
            .country_code = country_code,
            .country_name = country_name,
            .reason = "Comprehensive OFAC sanctions - export prohibited under US law",
            .applicable_regulations = CountryDatabase::getApplicableRegulations(country_code)
        };
    }
    
    // Check Partial Sanctions - HIGH RISK (could allow with manual review)
    if (OFAC_PARTIAL_SANCTIONS.count(country_code)) {
        std::string country_name = CountryDatabase::getCountryName(country_code);
        Logger::warning("BLOCKED: Access attempt from partially sanctioned country: " + country_name);
        
        return RestrictionResult{
            .allowed = false,  // BLOCKING Russia and Belarus as requested
            .level = RestrictionLevel::RESTRICTED,
            .country_code = country_code,
            .country_name = country_name,
            .reason = "Sectoral sanctions - technology exports restricted under US law",
            .applicable_regulations = CountryDatabase::getApplicableRegulations(country_code)
        };
    }
    
    // Check Arms Embargo Countries - BLOCK
    if (ARMS_EMBARGO_COUNTRIES.count(country_code)) {
        std::string country_name = CountryDatabase::getCountryName(country_code);
        Logger::warning("BLOCKED: Access attempt from arms embargo country: " + country_name);
        
        return RestrictionResult{
            .allowed = false,
            .level = RestrictionLevel::RESTRICTED,
            .country_code = country_code,
            .country_name = country_name,
            .reason = "UN/US arms embargo - dual-use technology export restricted",
            .applicable_regulations = {"US Arms Export Control Act", "UN Security Council Resolutions"}
        };
    }
    
    // Check High-Risk Countries - ALLOW but LOG
    if (HIGH_RISK_COUNTRIES.count(country_code)) {
        std::string country_name = CountryDatabase::getCountryName(country_code);
        Logger::info("HIGH RISK: Access from " + country_name + " - monitoring required");
        
        return RestrictionResult{
            .allowed = true,  // Allow but flag for review
            .level = RestrictionLevel::HIGH_RISK,
            .country_code = country_code,
            .country_name = country_name,
            .reason = "High-risk jurisdiction - access logged for compliance review",
            .applicable_regulations = {"BIS Entity List Review"}
        };
    }
    
    // Default: ALLOWED
    return RestrictionResult{
        .allowed = true,
        .level = RestrictionLevel::ALLOWED,
        .country_code = country_code,
        .country_name = CountryDatabase::getCountryName(country_code),
        .reason = "No export restrictions",
        .applicable_regulations = {}
    };
}

std::optional<GeoLocation> GeoRestriction::getGeoLocation(const std::string& ip_address) {
    return pImpl->queryGeoIP(ip_address);
}

std::vector<std::string> GeoRestriction::getSanctionedCountries() const {
    std::vector<std::string> result;
    
    result.insert(result.end(), 
                  OFAC_SANCTIONED_COUNTRIES.begin(), 
                  OFAC_SANCTIONED_COUNTRIES.end());
    
    result.insert(result.end(), 
                  OFAC_PARTIAL_SANCTIONS.begin(), 
                  OFAC_PARTIAL_SANCTIONS.end());
    
    result.insert(result.end(), 
                  ARMS_EMBARGO_COUNTRIES.begin(), 
                  ARMS_EMBARGO_COUNTRIES.end());
    
    return result;
}

std::vector<std::string> GeoRestriction::getHighRiskCountries() const {
    return std::vector<std::string>(HIGH_RISK_COUNTRIES.begin(), 
                                   HIGH_RISK_COUNTRIES.end());
}

void GeoRestriction::logAccessAttempt(const std::string& ip_address,
                                      const RestrictionResult& result,
                                      const std::string& action_taken) {
    // Create audit log entry
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    
    std::ostringstream log_entry;
    log_entry << std::put_time(local_time, "%Y-%m-%d %H:%M:%S") << " | "
              << "IP: " << ip_address << " | "
              << "Country: " << result.country_code << " (" << result.country_name << ") | "
              << "Action: " << action_taken << " | "
              << "Level: " << static_cast<int>(result.level) << " | "
              << "Reason: " << result.reason << "\n";
    
    // Write to audit log file
    std::ofstream audit_log(pImpl->audit_log_path, std::ios::app);
    if (audit_log.is_open()) {
        audit_log << log_entry.str();
        audit_log.close();
    }
    
    // Also log to main logger
    if (!result.allowed) {
        Logger::warning("COMPLIANCE BLOCK: " + log_entry.str());
    } else if (result.level == RestrictionLevel::HIGH_RISK) {
        Logger::info("COMPLIANCE MONITOR: " + log_entry.str());
    }
}

void GeoRestriction::setStrictMode(bool strict) {
    pImpl->strict_mode = strict;
    Logger::info("Geographic restriction strict mode: " + std::string(strict ? "ENABLED" : "DISABLED"));
}

bool GeoRestriction::loadSanctionsList(const std::string& filepath) {
    // TODO: Load custom sanctions from JSON file
    // Allows for dynamic updates without recompilation
    Logger::info("Loading custom sanctions list from: " + filepath);
    return true;
}

// ============================================================================
// CountryDatabase Implementation
// ============================================================================

std::string CountryDatabase::getCountryName(const std::string& code) {
    static const std::unordered_map<std::string, std::string> country_names = {
        // OFAC Comprehensive Sanctions
        {"CU", "Cuba"},
        {"IR", "Iran"},
        {"KP", "North Korea (DPRK)"},
        {"SY", "Syria"},
        {"XCR", "Crimea Region (Ukraine)"},
        {"XDO", "Donetsk Region (Ukraine)"},
        {"XLU", "Luhansk Region (Ukraine)"},
        
        // Partial Sanctions
        {"RU", "Russia"},
        {"BY", "Belarus"},
        
        // Arms Embargoes
        {"SO", "Somalia"},
        {"SS", "South Sudan"},
        {"SD", "Sudan"},
        {"LY", "Libya"},
        {"CF", "Central African Republic"},
        {"VE", "Venezuela"},
        {"MM", "Myanmar (Burma)"},
        {"YE", "Yemen"},
        {"LB", "Lebanon"},
        {"CD", "Democratic Republic of Congo"},
        {"ER", "Eritrea"},
        
        // High Risk
        {"CN", "China"},
        {"HK", "Hong Kong"},
        {"PK", "Pakistan"},
        {"AF", "Afghanistan"},
        {"IQ", "Iraq"},
        {"AE", "United Arab Emirates"},
        {"TR", "Turkey"},
        {"EG", "Egypt"},
        
        // Fallback
        {"UNKNOWN", "Unknown Country"}
    };
    
    auto it = country_names.find(code);
    return (it != country_names.end()) ? it->second : code;
}

RestrictionLevel CountryDatabase::getRestrictionLevel(const std::string& code) {
    if (GeoRestriction::OFAC_SANCTIONED_COUNTRIES.count(code)) {
        return RestrictionLevel::COMPREHENSIVELY_SANCTIONED;
    }
    if (GeoRestriction::OFAC_PARTIAL_SANCTIONS.count(code) ||
        GeoRestriction::ARMS_EMBARGO_COUNTRIES.count(code)) {
        return RestrictionLevel::RESTRICTED;
    }
    if (GeoRestriction::HIGH_RISK_COUNTRIES.count(code)) {
        return RestrictionLevel::HIGH_RISK;
    }
    return RestrictionLevel::ALLOWED;
}

std::vector<std::string> CountryDatabase::getApplicableRegulations(const std::string& code) {
    std::vector<std::string> regulations;
    
    if (code == "CU") {
        regulations = {"31 CFR Part 515 (Cuban Assets Control Regulations)", "US EAR"};
    } else if (code == "IR") {
        regulations = {"31 CFR Part 560 (Iranian Transactions and Sanctions Regulations)", "US EAR"};
    } else if (code == "KP") {
        regulations = {"31 CFR Part 510 (North Korea Sanctions Regulations)", "US EAR"};
    } else if (code == "SY") {
        regulations = {"31 CFR Part 542 (Syrian Sanctions Regulations)", "US EAR"};
    } else if (code == "RU" || code == "XCR" || code == "XDO" || code == "XLU") {
        regulations = {"31 CFR Part 589 (Ukraine-Related Sanctions)", "US EAR 15 CFR Part 746"};
    } else if (code == "BY") {
        regulations = {"31 CFR Part 548 (Belarus Sanctions Regulations)", "US EAR"};
    } else if (GeoRestriction::ARMS_EMBARGO_COUNTRIES.count(code)) {
        regulations = {"US Arms Export Control Act", "22 CFR § 126.1", "UN Security Council Resolutions"};
    } else if (GeoRestriction::HIGH_RISK_COUNTRIES.count(code)) {
        regulations = {"BIS Entity List (15 CFR Part 744)", "EAR Country Groups"};
    }
    
    return regulations;
}

} // namespace SpectreMap::Compliance