# Example

# simple_mmd_viewer_glfw
add_executable(mmd_viewer_glfw
    mmd_viewer_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/gl3w/src/gl3w.c
)

set(mmd_viewer_glfw_LIBRARIES
    ${OPENGL_LIBRARY}
    MMD
)
if(MMD_FORCE_GLFW_BUILD)
    list(APPEND mmd_viewer_glfw_LIBRARIES glfw)
else()
    list(APPEND mmd_viewer_glfw_LIBRARIES ${GLFW_LIBRARIES})
endif()
if(UNIX)
    list(APPEND mmd_viewer_glfw_LIBRARIES ${CMAKE_DL_LIBS})
endif()
target_link_libraries(mmd_viewer_glfw ${mmd_viewer_glfw_LIBRARIES})

add_custom_command(TARGET mmd_viewer_glfw POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/../resource
    $<TARGET_FILE_DIR:mmd_viewer_glfw>/resource
)

