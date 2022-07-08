cmake_minimum_required(VERSION 2.8.2)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest-download
                    GIT_REPOSITORY;https://github.com/google/googletest.git;GIT_TAG;master;UPDATE_DISCONNECTED;1
                    SOURCE_DIR          "/home/the-code-heist/my_codes/adhan-system-cpp/adhan-c/Adhan/C/adhan/googletest-src"
                    BINARY_DIR          "/home/the-code-heist/my_codes/adhan-system-cpp/adhan-c/Adhan/C/adhan/googletest-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)

