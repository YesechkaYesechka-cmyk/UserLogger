CMAKE_MINIMUM_REQUIRED(VERSION 3.23)
project(UserLogger)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

list(APPEND UserLogger_SOURCES
        sources/user.cpp
        sources/log_session.cpp
        )

list(APPEND UserLogger_HEADERS
        "${CMAKE_SOURCE_DIR}/include"
        )

add_executable(UserLogger ${UserLogger_SOURCES} main.cpp)
target_include_directories(UserLogger PUBLIC ${UserLogger_HEADERS})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)


FetchContent_MakeAvailable(googletest)

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_executable(tests_google tests/google_tests.cpp ${UserLogger_SOURCES})
target_include_directories(tests_google PUBLIC ${UserLogger_HEADERS})
target_link_libraries(tests_google gtest gtest_main)
target_compile_definitions(tests_google PUBLIC BUILD_GOOGLE_TEST)
enable_testing()

add_test(NAME UserLoggerTests COMMAND tests_google)
