# Install script for directory: /home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/lab_radar" TYPE FILE FILES "/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/cmake/Modules/lab_radarConfig.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/build/include/lab_radar/cmake_install.cmake")
  include("/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/build/lib/cmake_install.cmake")
  include("/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/build/apps/cmake_install.cmake")
  include("/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/build/docs/cmake_install.cmake")
  include("/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/build/swig/cmake_install.cmake")
  include("/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/build/python/cmake_install.cmake")
  include("/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/build/grc/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/jonas/Documents/university/SDR-Positioning-System/gnuradio/CodeRadar/gr-lab_radar/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
