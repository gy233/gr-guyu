# Copyright 2011,2012,2016 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND guyu_sources
    print_data_f_impl.cc
    myCMA22_impl.cc
    my_DQPSK_Demod_impl.cc
    my_file_sink_impl.cc )

set(guyu_sources "${guyu_sources}" PARENT_SCOPE)
if(NOT guyu_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT guyu_sources)

add_library(gnuradio-guyu SHARED ${guyu_sources})
target_link_libraries(gnuradio-guyu ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-guyu PROPERTIES DEFINE_SYMBOL "gnuradio_guyu_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-guyu PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-guyu RUNTIME_COMPONENT "guyu_runtime" DEVEL_COMPONENT "guyu_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})
list(APPEND test_guyu_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_guyu.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_guyu.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_myCMA22.cc
    )

add_executable(test-guyu ${test_guyu_sources})

target_link_libraries(
  test-guyu
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-guyu
)

GR_ADD_TEST(test_guyu test-guyu)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

