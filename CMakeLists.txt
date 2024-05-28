cmake_minimum_required(VERSION 3.10)
project(mars_utils VERSION 1.0.0 DESCRIPTION "This Library contains several useful utilities like a Mutex and Thread class.")
include(${CMAKE_SOURCE_DIR}/cmake/mars_utils-dependencies.cmake)

# Export the library interface
install(EXPORT mars_utils-targets
	NAMESPACE mars_utils::
	DESTINATION lib/cmake/mars_utils
)
# Create and install the version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file("mars_utils-config-version.cmake"
	VERSION ${mars_utils_VERSION}
	COMPATIBILITY SameMajorVersion)

  install(
    FILES
    cmake/mars_utils-config.cmake
    cmake/mars_utils-dependencies.cmake
    ${PROJECT_BINARY_DIR}/mars_utils-config-version.cmake
    DESTINATION
      lib/cmake/mars_utils
  )  
set(SOURCES 
    src/Color.cpp
    src/Mutex.cpp
    src/MutexLocker.cpp
    src/ReadWriteLock.cpp
    src/ReadWriteLocker.cpp
    src/Thread.cpp
    src/WaitCondition.cpp
    src/mathUtils.cpp
    src/Geometry.cpp
    src/misc.cpp
#    src/Socket.cpp
)
set(HEADERS
    src/Color.h
    src/Mutex.h
    src/MutexLocker.h
    src/Quaternion.h
    src/ReadWriteLock.h
    src/ReadWriteLocker.h
    src/Thread.h
    src/Vector.h
    src/WaitCondition.h
    src/mathUtils.h
    src/Geometry.hpp
    src/misc.h
#    src/Socket.h
)


add_library(mars_utils SHARED ${SOURCES})
target_compile_features(mars_utils PUBLIC cxx_std_17)
target_link_libraries(mars_utils PUBLIC
  pthread
	Eigen3::Eigen
  configmaps::configmaps
)

target_include_directories(mars_utils
	PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
		$<INSTALL_INTERFACE:include>
)


if(WIN32)
  set(LIB_INSTALL_DIR bin) # .dll are in PATH, like executables
else(WIN32)
  set(LIB_INSTALL_DIR lib)
endif(WIN32)

# Install the binaries
install(TARGETS mars_utils EXPORT mars_utils-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION ${LIB_INSTALL_DIR}
  ARCHIVE DESTINATION lib
)

# Install headers into mars include directory
install(FILES ${HEADERS} DESTINATION include/mars_utils)

# Prepare and install necessary files to support finding of the library 
install(
	FILES cmake/mars_utils-config.cmake
	DESTINATION lib/cmake/mars_utils
)


# using pkg-config
configure_file(mars_utils.pc.in ${CMAKE_BINARY_DIR}/mars_utils.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/mars_utils.pc DESTINATION lib/pkgconfig)

