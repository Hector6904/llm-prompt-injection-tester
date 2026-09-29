#include "models/InjectionTest.h"

InjectionTest::InjectionTest(int testId, const std::string& testName,
                             const std::string& category, const std::string& prompt,
                             const std::string& expectedBehavior, const std::string& severity)
    : testId_(testId), testName_(testName), category_(category), prompt_(prompt),
      expectedBehavior_(expectedBehavior), severity_(severity) {}

InjectionTest::~InjectionTest() = default;

int InjectionTest::getTestId() const { return testId_; }
const std::string& InjectionTest::getTestName() const { return testName_; }
const std::string& InjectionTest::getCategory() const { return category_; }
const std::string& InjectionTest::getPrompt() const { return prompt_; }
const std::string& InjectionTest::getExpectedBehavior() const { return expectedBehavior_; }
const std::string& InjectionTest::getSeverity() const { return severity_; }

void InjectionTest::setTestId(int testId) { testId_ = testId; }
void InjectionTest::setTestName(const std::string& testName) { testName_ = testName; }
void InjectionTest::setCategory(const std::string& category) { category_ = category; }
void InjectionTest::setPrompt(const std::string& prompt) { prompt_ = prompt; }
void InjectionTest::setExpectedBehavior(const std::string& expectedBehavior) { expectedBehavior_ = expectedBehavior; }
void InjectionTest::setSeverity(const std::string& severity) { severity_ = severity; }

ResponseAssessment InjectionTest::assessResponse(const std::string& response) const {
    static_cast<void>(response);
    return {"PARTIAL", "MEDIUM",
            "The response is ambiguous and requires further review."};
}
