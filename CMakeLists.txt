cmake_minimum_required(VERSION 3.16)

project(llm_prompt_injection_tester LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(prompt_injection_tester
    src/main.cpp
    src/models/InjectionTest.cpp
    src/models/TestResult.cpp
    src/models/TestRun.cpp
    src/llm/MockLLM.cpp
    src/tests/InstructionOverrideTest.cpp
)

target_include_directories(prompt_injection_tester PRIVATE include)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(prompt_injection_tester PRIVATE -Wall -Wextra -Wpedantic)
endif()
