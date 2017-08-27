cmake_minimum_required(VERSION 2.6)
list( APPEND CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -pedantic")

add_subdirectory(src/glm-0.9.8.4/)

file(GLOB SOURCES
    src/*.h
    src/*.cpp
)


project(collision_detection)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(glm REQUIRED)


include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} )

add_executable(collision_detection collision_detection.cpp ${SOURCES})
add_executable(bouncing_balls bouncing_balls.cpp ${SOURCES})
add_executable(test test.cpp ${SOURCES})

target_link_libraries(collision_detection ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} glm)
target_link_libraries(bouncing_balls ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLFW_LIBRARIES}  ${GLEW_LIBRARIES} glm)
target_link_libraries(test ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLFW_LIBRARIES}  ${GLEW_LIBRARIES} glm)

