# LLM Prompt Injection Vulnerability Tester

## Overview

LLM Prompt Injection Vulnerability Tester is a C++ and C project for exercising
LLM-like behavior against selected prompt-injection techniques. It provides a
small, testable engine that executes injection tests, assesses responses, and
tracks results by integer ID.

The current implementation uses `MockLLM`, a deterministic local implementation
of the LLM interface. It makes no network requests and does not contact a real
LLM. The project is intended for testing systems that you own or are authorized
to assess.

## Features

- Four implemented injection test types:
  - Instruction Override
  - Prompt Extraction
  - Role Manipulation
  - Context Manipulation
- Polymorphic `InjectionTest` architecture with dependency injection through
  `LLMInterface`.
- Technique-specific response assessments with `PASS`, `FAIL`, and `PARTIAL`
  outcomes.
- Severity values supplied by each assessment, including `LOW`, `MEDIUM`, and
  `HIGH` in the current tests.
- Execution timing, timestamped `TestResult` creation, generated result IDs,
  and result lookup.
- C data structures and algorithms integrated with the C++ engine:
  circular queue, stack, linear search, binary search, and five sorting
  algorithms.
- CMake/CTest build and test configuration with C++17 and C11 targets.

## Architecture

```text
Concrete InjectionTest objects
  ├─ InstructionOverrideTest
  ├─ PromptExtractionTest
  ├─ RoleManipulationTest
  └─ ContextManipulationTest
           │ execute() / assessResponse()
           ▼
      LLMInterface
           │
           ▼
        MockLLM
           │ response
           ▼
       TestRunner ──► ResponseAnalyzer ──► TestResult
           │                                      │
           └──────── TestExecutionCoordinator ────┘
                         │             │
                         │             └─ C stack of result IDs
                         └─ C queue of pending test IDs
                                      │
                         C search and sort result-ID arrays
```

| Component | Responsibility |
| --- | --- |
| `InjectionTest` | Abstract base class holding test metadata, a prompt, `execute()`, and a virtual `assessResponse()` extension point. Its default assessment is `PARTIAL`. |
| Concrete injection tests | Define their own prompt, expected behavior, injected `LLMInterface` dependency, execution behavior, and narrowly scoped assessment criteria. |
| `LLMInterface` | Defines the `sendPrompt()` contract used by test classes. |
| `MockLLM` | Deterministic local `LLMInterface` implementation that returns safe responses for the four built-in prompt shapes. |
| `ResponseAssessment` | Value type containing a status, severity, and analysis message returned by a test's assessment logic. |
| `ResponseAnalyzer` | Requests the assessment from the polymorphic test, adds timestamp metadata, and creates a `TestResult`. |
| `TestRunner` | Executes one test, measures elapsed time, invokes the analyzer, and records execution time in the result. |
| `TestExecutionCoordinator` | Resolves queued test IDs through a non-owning C++ registry, executes valid tests FIFO, assigns result IDs, stores results, and exposes stack/search/sort operations. |
| `TestResult` | Stores result ID, test ID, run ID, raw response, assessment fields, execution time, and timestamp. |
| `TestRun` | Data model for run metadata (`runId`, model ID, timestamps, and total tests). It is not yet connected to the executable workflow or persistence. |
| C Queue | Fixed-capacity circular queue of pending integer test IDs. |
| C Stack | Fixed-capacity stack of integer result IDs, used to demonstrate LIFO behavior. |
| C Searching and Sorting | Integer-array linear/binary search plus bubble, selection, insertion, merge, and quick sort. Sorted IDs are resolved back to C++ `TestResult` objects. |

The C modules operate only on integers and integer arrays. The C++ coordinator
maintains the mappings between IDs and C++ test/result objects, preserving the
association after searching or sorting.

## Technology Stack

| Technology | Usage |
| --- | --- |
| C++17 | Object-oriented test engine, analysis, result models, and application entry point. |
| C11 | Queue, stack, searching, and sorting modules. |
| CMake | Build configuration for C and C++ targets. |
| CTest | Automated test execution. |

## Project Structure

```text
.
├── CMakeLists.txt
├── README.md
├── include
│   ├── analysis
│   │   └── ResponseAnalyzer.h
│   ├── data_structures
│   │   ├── Queue.h
│   │   ├── Search.h
│   │   ├── Sort.h
│   │   └── Stack.h
│   ├── engine
│   │   ├── TestExecutionCoordinator.h
│   │   └── TestRunner.h
│   ├── llm
│   │   ├── LLMInterface.h
│   │   └── MockLLM.h
│   ├── models
│   │   ├── InjectionTest.h
│   │   ├── ResponseAssessment.h
│   │   ├── TestResult.h
│   │   └── TestRun.h
│   └── tests
│       ├── ContextManipulationTest.h
│       ├── InstructionOverrideTest.h
│       ├── PromptExtractionTest.h
│       └── RoleManipulationTest.h
├── src
│   ├── analysis
│   ├── data_structures
│   ├── engine
│   ├── llm
│   ├── models
│   ├── tests
│   └── main.cpp
└── tests
    ├── test_engine_integration.cpp
    ├── test_queue.c
    ├── test_response_assessment.cpp
    ├── test_search.c
    ├── test_sort.c
    └── test_stack.c
```

## Build and Run

```sh
cd ~/GitHub/llm-prompt-injection-tester
cmake -S . -B build
cmake --build build --parallel
./build/prompt_injection_tester
```

The application demonstrates FIFO test execution, handling of an unresolved
test ID, result-ID searching and quick sorting, retrieval of corresponding
results, and LIFO result-ID popping.

## Run Tests

After building, run the complete CTest suite:

```sh
ctest --test-dir build --output-on-failure
```

The configured suite includes C tests for queue, stack, search, and sort
modules, plus C++ tests for response assessment and engine integration.

## Current Limitations

- `MockLLM` is deterministic and does not contact a real LLM or external API.
- Response assessment uses intentionally narrow, phrase-based criteria for each
  technique; unfamiliar response wording may be classified as `PARTIAL`.
- The fixed C queue and stack each have a capacity of 10 integer IDs. The
  coordinator records stack overflow, while still retaining created results in
  its C++ result registry.
- The coordinator stores non-owning raw pointers to registered tests; callers
  must keep those test objects alive during execution.
- Result IDs are generated in memory by the coordinator and are not persistent
  across application runs.
- `TestRun` is currently only a data model; database-backed run history is not
  implemented.

## Development Status

Completed project steps:

1. C++ object-oriented foundation.
2. `LLMInterface` and deterministic `MockLLM`.
3. `ResponseAnalyzer` and `TestRunner`.
4. C queue, stack, searching, and sorting modules.
5. C/C++ integration through `TestExecutionCoordinator`.
6. Additional polymorphic injection tests and technique-specific response assessment.

Future work includes real LLM integration, DBMS integration, and frontend
development. The current project is a local educational prototype and is not
production-ready.
