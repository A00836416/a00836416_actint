cmake_minimum_required(VERSION 3.30)

project(sonarqube_analysis VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
    main.cpp
    analysis.cpp
    analysis.h
)

add_executable(main ${SOURCES})

option(ENABLE_TESTING "Enable a Unit Testing build." ON)
option(ENABLE_COVERAGE "Enable coverage reporting" ON)

if (ENABLE_COVERAGE)
    message(STATUS "Enabling coverage flags for GCC/Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)

if(ENABLE_TESTING)
    enable_testing()

    function(add_test_executable name source)
        add_executable(${name} ${source} analysis.cpp)
        target_link_libraries(${name} PRIVATE gtest gtest_main)
        if (ENABLE_COVERAGE)
            target_link_libraries(${name} PRIVATE gcov)
            target_compile_options(${name} PRIVATE --coverage -fprofile-arcs -ftest-coverage)
            target_link_options(${name} PRIVATE --coverage)
        endif()
        add_test(NAME ${name} COMMAND ${name})
    endfunction()

    # Solo agregamos tu test
    add_test_executable(test_analysis test/test_analysis.cpp)

    if (ENABLE_COVERAGE)
        find_program(LCOV lcov)
        if (LCOV)
            add_custom_target(coverage
                COMMAND lcov --capture --directory . --output-file build/coverage.info
                COMMAND genhtml build/coverage.info --output-directory build/coverage_html
                COMMENT "Generating code coverage report"
                VERBATIM
            )
        else()
            message(WARNING "LCOV not found, coverage reporting will not be available")
        endif()
    endif()
endif()
