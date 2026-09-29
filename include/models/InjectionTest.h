#pragma once

#include <string>

#include "models/ResponseAssessment.h"

class InjectionTest {
public:
    InjectionTest(int testId, const std::string& testName, const std::string& category,
                  const std::string& prompt, const std::string& expectedBehavior,
                  const std::string& severity);
    virtual ~InjectionTest();

    int getTestId() const;
    const std::string& getTestName() const;
    const std::string& getCategory() const;
    const std::string& getPrompt() const;
    const std::string& getExpectedBehavior() const;
    const std::string& getSeverity() const;

    void setTestId(int testId);
    void setTestName(const std::string& testName);
    void setCategory(const std::string& category);
    void setPrompt(const std::string& prompt);
    void setExpectedBehavior(const std::string& expectedBehavior);
    void setSeverity(const std::string& severity);

    // Concrete test types will provide their own execution behavior.
    virtual std::string execute() = 0;

    /*
     * The default is deliberately inconclusive. Concrete tests override this
     * with narrowly scoped criteria for their own injection technique.
     */
    virtual ResponseAssessment assessResponse(const std::string& response) const;

private:
    int testId_;
    std::string testName_;
    std::string category_;
    std::string prompt_;
    std::string expectedBehavior_;
    std::string severity_;
};
