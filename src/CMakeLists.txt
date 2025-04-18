include_directories(${project3_SOURCE_DIR}/include)
# I assume you want to use LibProject as a library in MainProject.
# include_directories(${MyProject_SOURCE_DIR}/LibProject/inc)
# link_directories(${MyProject_SOURCE_DIR}/LibProject/src)

include_directories(${project3_SOURCE_DIR}/lib/glfw/include)
link_directories(${project3_SOURCE_DIR}/lib/glfw/src)

include_directories(${project3_SOURCE_DIR}/lib/glad/include)
link_directories(${project3_SOURCE_DIR}/lib/glad/src)

include_directories(${project3_SOURCE_DIR}/lib/glm)

include_directories(${project3_SOURCE_DIR}/lib/imgui)
include_directories(${project3_SOURCE_DIR}/lib/imgui/backends)


file(GLOB SRC_FILES
     "**.cpp"
)

set(IMGUI_SOURCES
    ${project3_SOURCE_DIR}/lib/imgui/imgui.cpp
    ${project3_SOURCE_DIR}/lib/imgui/imgui_demo.cpp
    ${project3_SOURCE_DIR}/lib/imgui/imgui_draw.cpp
    ${project3_SOURCE_DIR}/lib/imgui/imgui_widgets.cpp
    ${project3_SOURCE_DIR}/lib/imgui/imgui_tables.cpp
    ${project3_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.cpp
    ${project3_SOURCE_DIR}/lib/imgui/backends/imgui_impl_glfw.cpp
)

add_executable(project3 ${SRC_FILES} ${IMGUI_SOURCES})

add_custom_command(TARGET project3 PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:project3>/res/)
#target_link_libraries(MainProject LibProject)

target_link_libraries(project3 glfw)
target_link_libraries(project3 glad)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET project3 PROPERTY CXX_STANDARD 20)
endif()