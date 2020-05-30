INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_GUYU guyu)

FIND_PATH(
    GUYU_INCLUDE_DIRS
    NAMES guyu/api.h
    HINTS $ENV{GUYU_DIR}/include
        ${PC_GUYU_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GUYU_LIBRARIES
    NAMES gnuradio-guyu
    HINTS $ENV{GUYU_DIR}/lib
        ${PC_GUYU_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GUYU DEFAULT_MSG GUYU_LIBRARIES GUYU_INCLUDE_DIRS)
MARK_AS_ADVANCED(GUYU_LIBRARIES GUYU_INCLUDE_DIRS)

