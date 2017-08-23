cmake_minimum_required(VERSION 2.6)
project(QuarticFlow_display)

SET(EXECUTABLE_OUTPUT_PATH ./Compile/)
file(GLOB SOURCES src/*.cpp src/*.hpp)

find_package(OpenCV REQUIRED )
INCLUDE_DIRECTORIES(/usr/local/include)
LINK_DIRECTORIES(/usr/local/lib)

add_executable(QuarticFlow_display ${SOURCES})
TARGET_LINK_LIBRARIES(QuarticFlow_display libboost_system.a libboost_thread-mt.a ${OpenCV_LIBS})
