// Add to main.cpp startup sequence

#include "compliance/GeoRestriction.hpp"

int main(int argc, char* argv[]) {
    using namespace SpectreMap;
    
    // Initialize export compliance system FIRST
    Compliance::GeoRestriction geoRestriction;
    geoRestriction.setStrictMode(true);
    geoRestriction.loadSanctionsList("config/sanctioned_countries.json");
    
    // Get user's IP address (implement detection)
    std::string user_ip = detectUserIPAddress();
    
    // Check export compliance
    auto result = geoRestriction.checkAccess(user_ip);
    geoRestriction.logAccessAttempt(user_ip, result, result.allowed ? "ALLOWED" : "BLOCKED");
    
    if (!result.allowed) {
        // Display compliance block message
        std::cerr << "╔════════════════════════════════════════════════════════════════╗\n";
        std::cerr << "║          EXPORT CONTROL COMPLIANCE NOTICE                      ║\n";
        std::cerr << "╠════════════════════════════════════════════════════════════════╣\n";
        std::cerr << "║ Access Denied: " << result.country_name << " (" << result.country_code << ")\n";
        std::cerr << "║                                                                ║\n";
        std::cerr << "║ Reason: " << result.reason << "\n";
        std::cerr << "║                                                                ║\n";
        std::cerr << "║ Applicable Regulations:                                        ║\n";
        for (const auto& reg : result.applicable_regulations) {
            std::cerr << "║   • " << reg << "\n";
        }
        std::cerr << "║                                                                ║\n";
        std::cerr << "║ SpectreMap is subject to US export control laws including:     ║\n";
        std::cerr << "║   • Export Administration Regulations (EAR)                    ║\n";
        std::cerr << "║   • Office of Foreign Assets Control (OFAC) Sanctions          ║\n";
        std::cerr << "║   • International Traffic in Arms Regulations (ITAR)           ║\n";
        std::cerr << "║                                                                ║\n";
        std::cerr << "║ For questions, contact:                                        ║\n";
        std::cerr << "║   lackadaisicalresearch@pm.me                                  ║\n";
        std::cerr << "║   https://lackadaisical-security.com/compliance                ║\n";
        std::cerr << "╚════════════════════════════════════════════════════════════════╝\n";
        
        return 1; // Exit application
    }
    
    // If high-risk country, show warning but allow
    if (result.level == Compliance::RestrictionLevel::HIGH_RISK) {
        std::cout << "⚠️  HIGH-RISK JURISDICTION NOTICE\n";
        std::cout << "Your access from " << result.country_name << " has been logged for compliance review.\n";
        std::cout << "Ensure you have proper authorization for use of this software.\n\n";
    }
    
    // Continue with normal startup...
    Logger::info("Export compliance check passed for " + result.country_name);
    
    // Rest of your application initialization
    // ...
}