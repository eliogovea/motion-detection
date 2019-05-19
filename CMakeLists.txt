cmake_minimum_required(VERSION 2.8)

project( motion_detection )

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Threads)

# build library
add_library(motion_detection_lib
    include/motion_detection/motion_detection.h
    include/motion_detection/shared_data.h
    include/motion_detection/reader.h
    include/motion_detection/detector.h
    include/motion_detection/controller.h
    include/motion_detection/recorder.h
    src/reader.cpp
    src/detector.cpp
    src/controller
    src/shared_data.cpp
    src/recorder.cpp
)

# setup include directories
target_include_directories(motion_detection_lib PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
 	$<INSTALL_INTERFACE:include>
)

# compile
add_executable(app src/app/main.cpp)

# link
target_link_libraries(app ${OpenCV_LIBS} motion_detection_lib ${CMAKE_THREAD_LIBS_INIT})
