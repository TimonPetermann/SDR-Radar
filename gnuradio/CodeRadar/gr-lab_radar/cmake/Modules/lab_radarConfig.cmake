INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_LAB_RADAR lab_radar)

FIND_PATH(
    LAB_RADAR_INCLUDE_DIRS
    NAMES lab_radar/api.h
    HINTS $ENV{LAB_RADAR_DIR}/include
        ${PC_LAB_RADAR_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    LAB_RADAR_LIBRARIES
    NAMES gnuradio-lab_radar
    HINTS $ENV{LAB_RADAR_DIR}/lib
        ${PC_LAB_RADAR_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/lab_radarTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LAB_RADAR DEFAULT_MSG LAB_RADAR_LIBRARIES LAB_RADAR_INCLUDE_DIRS)
MARK_AS_ADVANCED(LAB_RADAR_LIBRARIES LAB_RADAR_INCLUDE_DIRS)
