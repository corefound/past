cmake_minimum_required(VERSION 3.10)

project(past VERSION 0.0.1 LANGUAGES C CXX)

# ============================================================
#                       OPTIONS
# ============================================================
option(ENABLE_TESTING "Build test executable" OFF)
option(ENABLE_TESTING_FOR_TYPES_HINTS "Build test executable" ON)

# ============================================================
#                  MACOS & LLVM SETUP
# ============================================================
set(CMAKE_OSX_DEPLOYMENT_TARGET "26.0")

set(LLVM_ROOT "/opt/homebrew/opt/llvm")
list(APPEND CMAKE_PREFIX_PATH "${LLVM_ROOT}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

# ============================================================
#                       PATHS
# ============================================================
set(TESTS_DIR "${CMAKE_SOURCE_DIR}/tests")
set(LIBS_DIR "${CMAKE_SOURCE_DIR}/libs")
set(SRC_DIR "${CMAKE_SOURCE_DIR}")

# ============================================================
#                       LLVM
# ============================================================
cmake_policy(SET CMP0075 NEW)
cmake_policy(SET CMP0074 NEW)

set(LLVM_ENABLE_RTTI ON)
find_package(LLVM REQUIRED CONFIG)

llvm_map_components_to_libnames(llvm_libs
        core
        support
        native
        irreader
        linker
        bitreader
        bitwriter
        target
        targetparser
        mc
        mcparser
        x86codegen
        aarch64codegen
)

add_definitions(${LLVM_DEFINITIONS})

# ============================================================
#                PRODUCTION SOURCES & EXECUTABLE
# ============================================================
if (NOT ENABLE_TESTING)

    add_executable(past
            ${SRC_DIR}/main.cpp
            ${SRC_DIR}/emitter/emitter.cpp
            ${SRC_DIR}/ir/ir.cpp
            ${SRC_DIR}/ir/expressions.cpp
            ${SRC_DIR}/ir/statements.cpp
            ${SRC_DIR}/ir/variables.cpp
    )

    target_include_directories(past PRIVATE
            ${SRC_DIR}
            ${LIBS_DIR}
            ${LLVM_INCLUDE_DIRS}
            ${LLVM_ROOT}/include
    )

    target_link_directories(past PRIVATE
            ${LLVM_ROOT}/lib
    )

    target_link_libraries(past PRIVATE ${llvm_libs})

    # ============================================================
    # Silence macOS linker warnings for duplicate / reexported libs
    # Must be AFTER add_executable
    if(APPLE)
        target_link_options(past PRIVATE
                "LINKER:-w"
                "LINKER:-no_warn_duplicate_libraries"
        )
    endif()

    # ============================================================
    #                       RUN TARGET
    add_custom_target(run
            COMMAND past
            DEPENDS past
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

endif()

# ============================================================
#                     TEST EXECUTABLE
# ============================================================
if (ENABLE_TESTING)

    file(GLOB_RECURSE TEST_SOURCES "${TESTS_DIR}/*.cpp")

    # Explicitly list production sources (excluding main.cpp)
    set(PROD_SOURCES_NO_MAIN
            ${SRC_DIR}/emitter/emitter.cpp
            ${SRC_DIR}/ir/ir.cpp
            ${SRC_DIR}/ir/expressions.cpp
            ${SRC_DIR}/ir/statements.cpp
            ${SRC_DIR}/ir/variables.cpp
    )

    add_executable(past_tests
            ${TEST_SOURCES}
            ${PROD_SOURCES_NO_MAIN}
            ${LIBS_DIR}/catch2/catch_amalgamated.cpp
    )

    target_include_directories(past_tests PRIVATE
            ${SRC_DIR}
            ${TESTS_DIR}
            ${LIBS_DIR}
            ${SRC_DIR}/external/catch2
            ${LLVM_INCLUDE_DIRS}
            ${LLVM_ROOT}/include
    )

    target_link_directories(past_tests PRIVATE
            ${LLVM_ROOT}/lib
    )

    target_link_libraries(past_tests PRIVATE ${llvm_libs})

    # Silence macOS linker warnings for test executable
    if(APPLE)
        target_link_options(past_tests PRIVATE
                "LINKER:-w"
                "LINKER:-no_warn_duplicate_libraries"
        )
    endif()

    # ============================================================
    #                       RUN TESTS TARGET
    add_custom_target(run-tests
            COMMAND past_tests
            DEPENDS past_tests
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

endif()
