# LLM Prompt Injection Vulnerability Tester

A C++ project for testing authorized or owned LLMs for prompt injection
vulnerabilities. The C++ portion contains the OOP/security engine, C will
later contain data structures, Python will later handle LLM/API integration,
and SQL will later handle persistence.

Current architecture:

- `InjectionTest` is the abstract base class for injection tests.
- `LLMInterface` defines the LLM communication contract.
- `MockLLM` is a deterministic, local `LLMInterface` implementation.
- `InstructionOverrideTest` is the first concrete injection test.

Current stage: core data models plus a local mock LLM flow. Real LLM
integration will be added later; no networking, API, database, test runner, or
frontend functionality is implemented.
