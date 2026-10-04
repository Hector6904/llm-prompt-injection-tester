cmake_minimum_required(VERSION 3.16)

project(llm_prompt_injection_tester LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(data_structures
    src/data_structures/Queue.c
    src/data_structures/Search.c
    src/data_structures/Sort.c
    src/data_structures/Stack.c
)

target_include_directories(data_structures PUBLIC include)

add_executable(prompt_injection_tester
    src/main.cpp
    src/database/DatabaseManager.cpp
    src/models/InjectionTest.cpp
    src/models/TestResult.cpp
    src/models/TestRun.cpp
    src/llm/MockLLM.cpp
    src/tests/InstructionOverrideTest.cpp
    src/tests/PromptExtractionTest.cpp
    src/tests/RoleManipulationTest.cpp
    src/tests/ContextManipulationTest.cpp
    src/analysis/ResponseAnalyzer.cpp
    src/engine/TestRunner.cpp
    src/engine/TestExecutionCoordinator.cpp
)

target_include_directories(prompt_injection_tester PRIVATE include)
target_link_libraries(prompt_injection_tester PRIVATE data_structures)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(prompt_injection_tester PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(data_structures PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()

add_executable(queue_tests
    tests/test_queue.c
)

target_link_libraries(queue_tests PRIVATE data_structures)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(queue_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME queue_tests COMMAND queue_tests)

add_executable(stack_tests
    tests/test_stack.c
)

target_link_libraries(stack_tests PRIVATE data_structures)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(stack_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME stack_tests COMMAND stack_tests)

add_executable(search_tests
    tests/test_search.c
)

target_link_libraries(search_tests PRIVATE data_structures)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(search_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME search_tests COMMAND search_tests)

add_executable(sort_tests
    tests/test_sort.c
)

target_link_libraries(sort_tests PRIVATE data_structures)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(sort_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME sort_tests COMMAND sort_tests)

add_executable(engine_integration_tests
    tests/test_engine_integration.cpp
    src/models/InjectionTest.cpp
    src/models/TestResult.cpp
    src/models/TestRun.cpp
    src/analysis/ResponseAnalyzer.cpp
    src/engine/TestRunner.cpp
    src/engine/TestExecutionCoordinator.cpp
    src/llm/MockLLM.cpp
    src/tests/InstructionOverrideTest.cpp
    src/tests/PromptExtractionTest.cpp
    src/tests/RoleManipulationTest.cpp
    src/tests/ContextManipulationTest.cpp
)

target_include_directories(engine_integration_tests PRIVATE include)
target_link_libraries(engine_integration_tests PRIVATE data_structures)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(engine_integration_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME engine_integration_tests COMMAND engine_integration_tests)

add_executable(response_assessment_tests
    tests/test_response_assessment.cpp
    src/models/InjectionTest.cpp
    src/models/TestResult.cpp
    src/analysis/ResponseAnalyzer.cpp
    src/engine/TestRunner.cpp
    src/tests/InstructionOverrideTest.cpp
    src/tests/PromptExtractionTest.cpp
    src/tests/RoleManipulationTest.cpp
    src/tests/ContextManipulationTest.cpp
)

target_include_directories(response_assessment_tests PRIVATE include)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(response_assessment_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME response_assessment_tests COMMAND response_assessment_tests)

find_package(Threads REQUIRED)
add_executable(tester_web
    web/server.cpp
    web/engine_bridge.cpp
    src/models/InjectionTest.cpp
    src/models/TestResult.cpp
    src/models/TestRun.cpp
    src/llm/MockLLM.cpp
    src/tests/InstructionOverrideTest.cpp
    src/tests/PromptExtractionTest.cpp
    src/tests/RoleManipulationTest.cpp
    src/tests/ContextManipulationTest.cpp
    src/analysis/ResponseAnalyzer.cpp
    src/engine/TestRunner.cpp
    src/engine/TestExecutionCoordinator.cpp
)
target_include_directories(tester_web PRIVATE include)
target_link_libraries(tester_web PRIVATE data_structures Threads::Threads)
add_custom_command(TARGET tester_web POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/web $<TARGET_FILE_DIR:tester_web>/web)



# MySQL Connector/C++
target_include_directories(prompt_injection_tester PRIVATE
    D:/mysql-connector-c++-26.7.0-winx64/include/jdbc
)

target_link_directories(prompt_injection_tester PRIVATE
    D:/mysql-connector-c++-26.7.0-winx64/lib64/vs14
)

target_link_libraries(prompt_injection_tester PRIVATE
    mysqlcppconn
)