#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "replxx::replxx" for configuration "Debug"
set_property(TARGET replxx::replxx APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(replxx::replxx PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libreplxx-d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS replxx::replxx )
list(APPEND _IMPORT_CHECK_FILES_FOR_replxx::replxx "${_IMPORT_PREFIX}/lib/libreplxx-d.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
