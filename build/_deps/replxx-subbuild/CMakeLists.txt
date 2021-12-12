# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.18.4)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(replxx-populate NONE)

include(ExternalProject)
ExternalProject_Add(replxx-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/AmokHuginnsson/replxx.git" "GIT_TAG" "release-0.0.4" "GIT_SHALLOW" "1"
                    SOURCE_DIR          "/workspaces/robot-test/build/_deps/replxx-src"
                    BINARY_DIR          "/workspaces/robot-test/build/_deps/replxx-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


