cmake_minimum_required(VERSION 2.6)
list( APPEND CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -pedantic")

file(GLOB SOURCES
    src/*.h
    src/*.cpp
)

project(collision_detection)
add_executable(collision_detection collision_detection.cpp ${SOURCES})
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(collision_detection ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
