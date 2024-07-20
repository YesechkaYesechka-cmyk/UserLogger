CMAKE_MINIMUM_REQUIRED(VERSION 3.23)
project(UserLogger)

add_executable(UserLogger main.cpp sources/user.cpp)
target_include_directories(UserLogger PUBLIC include)
