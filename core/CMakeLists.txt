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
set(GENERATED_DIR "${CMAKE_SOURCE_DIR}/src/antlr/generated")
set(SOURCES_DIR "${CMAKE_SOURCE_DIR}/src")
set(TESTS_DIR "${CMAKE_SOURCE_DIR}/tests")
set(LIBS_DIR "${CMAKE_SOURCE_DIR}/libs")

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
    IF (ENABLE_TESTING_FOR_TYPES_HINTS)
        file(GLOB_RECURSE PROD_SOURCES
                "${SOURCES_DIR}/*.cpp"
                "${GENERATED_DIR}/*.cpp"
                "${TESTS_DIR}/*.cpp"
        )
        add_executable(past ${PROD_SOURCES})
    ENDIF ()

    IF (NOT ENABLE_TESTING_FOR_TYPES_HINTS)
        file(GLOB_RECURSE PROD_SOURCES
                "${SOURCES_DIR}/*.cpp"
                "${GENERATED_DIR}/*.cpp"
        )
        add_executable(past ${PROD_SOURCES})
    ENDIF ()


    target_include_directories(past PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${SOURCES_DIR}
            ${GENERATED_DIR}
            ${LIBS_DIR}
            ${LLVM_INCLUDE_DIRS}
            ${LLVM_ROOT}/include
            ${LIBS_DIR}/uni-algo/include
    )

    target_link_directories(past PRIVATE
            ${LLVM_ROOT}/lib
    )

    target_link_options(past PRIVATE "LINKER:-no_warn_duplicate_libraries")

    target_link_libraries(past
            ${llvm_libs}
    )

    # ============================================================
    #                       RUN TARGET
    # ============================================================
    add_custom_target(run
            DEPENDS past
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif ()

# ============================================================
#                     TEST EXECUTABLE
# ============================================================
if (ENABLE_TESTING)
    file(GLOB TEST_SOURCES "${TESTS_DIR}/*.cpp")

    # Get all production sources except the file with main()
    file(GLOB_RECURSE PROD_SOURCES_NO_MAIN
            "${SOURCES_DIR}/*.cpp"
            "${GENERATED_DIR}/*.cpp"
            "${TESTS_DIR}/*.cpp"
    )
    # Exclude both main.cpp and past.cpp (whichever contains main)
    list(FILTER PROD_SOURCES_NO_MAIN EXCLUDE REGEX ".*(main|past)\\.cpp$")

    add_executable(past_tests
            ${TEST_SOURCES}
            ${PROD_SOURCES_NO_MAIN}
            ${CMAKE_SOURCE_DIR}/libs/catch2/catch_amalgamated.cpp
    )

    target_include_directories(past_tests PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${SOURCES_DIR}
            ${TESTS_DIR}
            ${GENERATED_DIR}
            ${LIBS_DIR}
            ${CMAKE_SOURCE_DIR}/external/catch2
            ${LLVM_INCLUDE_DIRS}
            ${LLVM_ROOT}/include
            ${LIBS_DIR}/uni-algo/include
    )

    target_link_directories(past_tests PRIVATE
            ${LLVM_ROOT}/lib
    )

    target_link_options(past_tests PRIVATE "LINKER:-no_warn_duplicate_libraries")

    target_link_libraries(past_tests
            ${llvm_libs}
    )

    add_custom_target(run-tests
            COMMAND past_tests
            DEPENDS past_tests
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif ()