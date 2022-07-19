cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(adhan-system-cpp VERSION 0.0.1 LANGUAGES CXX)

add_executable(adhan-daemon
  main.cpp
)

include(FetchContent)
FetchContent_Declare(
    tomleleven
    GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
    GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(tomleleven)

