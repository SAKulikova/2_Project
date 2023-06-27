cmake_minimum_required(VERSION 3.23)
project(opencv)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(/opt/homebrew/Cellar/opencv/4.7.0_4/include)
link_directories(/opt/homebrew/Cellar/opencv/4.7.0_4/lib)

link_directories(/Users/polina/Desktop/С++/2_Project/cmake-build-debug/pics/)

add_executable(opencv main.cpp Trackbar.hpp Trackbar.cpp)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)


target_link_libraries(opencv ${OpenCV_LIBS})
