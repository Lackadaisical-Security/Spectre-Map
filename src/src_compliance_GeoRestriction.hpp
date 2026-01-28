/**
 * @file GeoRestriction.hpp
 * @brief Export control compliance - Geographic access restrictions
 * @copyright Copyright © 2025-2026 Lackadaisical Security
 * 
 * Implements US export control regulations including:
 * - OFAC comprehensive sanctions
 * - EAR export restrictions  
 * - BIS Entity List countries
 */

#ifndef SPECTREMAP_GEORESTRICTION_HPP
#define SPECTREMAP_GEORESTRICTION_HPP

#include <string>
#include <vector>
#include <unordered_set>
#include <memory>
#include <optional>

namespace SpectreMap::Compliance {

/**
 * @brief Restriction level for countries/regions
 */
enum class RestrictionLevel {
    ALLOWED,              ///< No restrictions
    HIGH_RISK,           ///< Extra verification required
    RESTRICTED,          ///< Requires export license
    COMPREHENSIVELY_SANCTIONED  ///< Completely blocked (OFAC)
};

/**
 * @brief Geographic location information
 */
struct GeoLocation {
    std::string ip_address;
    std::string country_code;  ///< ISO 3166-1 alpha-2 code
    std::string country_name;
    std::string region;
    std::string city;
    double latitude;
    double longitude;
    std::string asn;           ///< Autonomous System Number
    std::string org;           ///< Organization name
    bool is_proxy;
    bool is_vpn;
    bool is_tor;
    bool is_hosting;
};

/**
 * @brief Result of geographic restriction check
 */
struct RestrictionResult {
    bool allowed;
    RestrictionLevel level;
    std::string country_code;
    std::string country_name;
    std::string reason;
    std::vector<std::string> applicable_regulations;
};

/**
 * @brief Geographic access restriction engine for export compliance
 */
class GeoRestriction {
public:
    GeoRestriction();
    ~GeoRestriction();

    /**
     * @brief Check if access from IP address is allowed
     * @param ip_address IPv4 or IPv6 address
     * @return Restriction result with details
     */
    RestrictionResult checkAccess(const std::string& ip_address);

    /**
     * @brief Check if country code is allowed
     * @param country_code ISO 3166-1 alpha-2 code (e.g., "US", "JP")
     * @return Restriction result
     */
    RestrictionResult checkCountry(const std::string& country_code);

    /**
     * @brief Get geolocation information for IP address
     * @param ip_address IPv4 or IPv6 address
     * @return Optional geolocation data
     */
    std::optional<GeoLocation> getGeoLocation(const std::string& ip_address);

    /**
     * @brief Get list of all sanctioned countries
     * @return Vector of country codes
     */
    std::vector<std::string> getSanctionedCountries() const;

    /**
     * @brief Get list of high-risk countries (extra verification needed)
     * @return Vector of country codes
     */
    std::vector<std::string> getHighRiskCountries() const;

    /**
     * @brief Log access attempt for compliance audit trail
     * @param ip_address Source IP
     * @param result Restriction result
     * @param action_taken Action (allowed/blocked)
     */
    void logAccessAttempt(const std::string& ip_address, 
                          const RestrictionResult& result,
                          const std::string& action_taken);

    /**
     * @brief Enable/disable strict compliance mode
     * @param strict If true, blocks VPN/proxy/Tor even from allowed countries
     */
    void setStrictMode(bool strict);

    /**
     * @brief Load custom sanctions list from file
     * @param filepath Path to JSON sanctions configuration
     * @return True if loaded successfully
     */
    bool loadSanctionsList(const std::string& filepath);

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;

    // OFAC Comprehensive Sanctions (31 CFR)
    static const std::unordered_set<std::string> OFAC_SANCTIONED_COUNTRIES;
    
    // Partial/Sectoral Sanctions (high risk)
    static const std::unordered_set<std::string> OFAC_PARTIAL_SANCTIONS;
    
    // UN/EU Arms Embargoes
    static const std::unordered_set<std::string> ARMS_EMBARGO_COUNTRIES;
    
    // High-risk for BIS Entity List
    static const std::unordered_set<std::string> HIGH_RISK_COUNTRIES;
};

/**
 * @brief Country code to name mapping for sanctioned countries
 */
class CountryDatabase {
public:
    static std::string getCountryName(const std::string& code);
    static RestrictionLevel getRestrictionLevel(const std::string& code);
    static std::vector<std::string> getApplicableRegulations(const std::string& code);
};

} // namespace SpectreMap::Compliance

#endif // SPECTREMAP_GEORESTRICTION_HPP