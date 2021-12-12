
if(NOT "/workspaces/robot-test/build/_deps/replxx-subbuild/replxx-populate-prefix/src/replxx-populate-stamp/replxx-populate-gitinfo.txt" IS_NEWER_THAN "/workspaces/robot-test/build/_deps/replxx-subbuild/replxx-populate-prefix/src/replxx-populate-stamp/replxx-populate-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/workspaces/robot-test/build/_deps/replxx-subbuild/replxx-populate-prefix/src/replxx-populate-stamp/replxx-populate-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/workspaces/robot-test/build/_deps/replxx-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/workspaces/robot-test/build/_deps/replxx-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout --depth 1 --no-single-branch "https://github.com/AmokHuginnsson/replxx.git" "replxx-src"
    WORKING_DIRECTORY "/workspaces/robot-test/build/_deps"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/AmokHuginnsson/replxx.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout release-0.0.4 --
  WORKING_DIRECTORY "/workspaces/robot-test/build/_deps/replxx-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'release-0.0.4'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/workspaces/robot-test/build/_deps/replxx-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/workspaces/robot-test/build/_deps/replxx-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/workspaces/robot-test/build/_deps/replxx-subbuild/replxx-populate-prefix/src/replxx-populate-stamp/replxx-populate-gitinfo.txt"
    "/workspaces/robot-test/build/_deps/replxx-subbuild/replxx-populate-prefix/src/replxx-populate-stamp/replxx-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/workspaces/robot-test/build/_deps/replxx-subbuild/replxx-populate-prefix/src/replxx-populate-stamp/replxx-populate-gitclone-lastrun.txt'")
endif()

