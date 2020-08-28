INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_CHIRP_RADAR chirp_radar)

FIND_PATH(
    CHIRP_RADAR_INCLUDE_DIRS
    NAMES chirp_radar/api.h
    HINTS $ENV{CHIRP_RADAR_DIR}/include
        ${PC_CHIRP_RADAR_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    CHIRP_RADAR_LIBRARIES
    NAMES gnuradio-chirp_radar
    HINTS $ENV{CHIRP_RADAR_DIR}/lib
        ${PC_CHIRP_RADAR_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/chirp_radarTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CHIRP_RADAR DEFAULT_MSG CHIRP_RADAR_LIBRARIES CHIRP_RADAR_INCLUDE_DIRS)
MARK_AS_ADVANCED(CHIRP_RADAR_LIBRARIES CHIRP_RADAR_INCLUDE_DIRS)
