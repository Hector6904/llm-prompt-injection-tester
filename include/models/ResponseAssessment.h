#pragma once

#include <string>

/* A concrete InjectionTest supplies this technique-specific classification. */
struct ResponseAssessment {
    std::string status;
    std::string severity;
    std::string analysis;
};
