# CMakeList.txt : CMake project for project3, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("project3")

# Add source to this project's executable.
add_subdirectory(lib/glm)
add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)

add_subdirectory(src)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET "project3" PROPERTY CXX_STANDARD 20)
endif()


set_property(TARGET project3 PROPERTY CXX_STANDARD 20)

# TODO: Add tests and install targets if needed.
