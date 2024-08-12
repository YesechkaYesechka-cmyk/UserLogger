CMAKE_MINIMUM_REQUIRED(VERSION 3.23)
project(UserLogger)

add_executable(UserLogger main.cpp sources/user.cpp)
target_include_directories(UserLogger PUBLIC include)


find_package(GTest REQUIRED PATHS "D:\\UserLogger\\deps\\google_test\\")
add_executable(tests_google tests/google_tests.cpp)
target_link_libraries(tests_google GTest::gtest_main)
target_include_directories(tests_google PUBLIC "D:\\UserLogger\\deps\\google_test\\include" "D:\\UserLogger\\include")