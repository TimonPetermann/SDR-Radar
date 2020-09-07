#----------------------------------------------------------------
# Generated CMake target import file for configuration "DebugRelease".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "gnuradio::gnuradio-lab_radar" for configuration "DebugRelease"
set_property(TARGET gnuradio::gnuradio-lab_radar APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUGRELEASE)
set_target_properties(gnuradio::gnuradio-lab_radar PROPERTIES
  IMPORTED_LOCATION_DEBUGRELEASE "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libgnuradio-lab_radar.so.v1.0-compat-xxx-xunknown"
  IMPORTED_SONAME_DEBUGRELEASE "libgnuradio-lab_radar.so.1.0.0git"
  )

list(APPEND _IMPORT_CHECK_TARGETS gnuradio::gnuradio-lab_radar )
list(APPEND _IMPORT_CHECK_FILES_FOR_gnuradio::gnuradio-lab_radar "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libgnuradio-lab_radar.so.v1.0-compat-xxx-xunknown" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
