cmake_minimum_required(VERSION 4.0)
project(C-lab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /WX)
else ()
    add_compile_options(-Wall -Wextra -Werror -pedantic)
endif ()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


set(SOURCE_FILES
    src/ExecutorImpl.cpp
)

set(TEST_FILES
    tests/ExecutorTest.cpp
)

add_executable(Experiment4Student-main
    ${SOURCE_FILES}
    ${TEST_FILES}
)

target_link_libraries(Experiment4Student-main
    GTest::gtest_main
)

target_include_directories(Experiment4Student-main
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${PROJECT_SOURCE_DIR}/src
    PRIVATE ${PROJECT_SOURCE_DIR}/tests
)

include(GoogleTest)
gtest_discover_tests(Experiment4Student-main)