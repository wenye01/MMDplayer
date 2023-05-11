cmake_minimum_required(VERSION 3.2)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(mmd)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

option (MMD_BULLET_ROOT "Bullet Root Directory" "")
option (MMD_ENABLE_TEST "Enable Google test." on)
option (MMD_ENABLE_GL_TEST "OpenGL test." off)
option (MMD_USE_GLSLANG "glsl Preprocessor : glslang lib" off)
option (MMD_INSTALL "MMD install." off)
option (MMD_GLFW_ROOT "GLFW Root Directory" "")
option (MMD_FORCE_GLFW_BUILD "Force glfw build." off)
option (MMD_ENABLE_EXAMPLE_VULKAN "Build vulakn's example." off)

set (BULLET_ROOT ${MMD_BULLET_ROOT})

find_package (OpenGL REQUIRED)
find_package (Bullet REQUIRED)

if (NOT MMD_FORCE_GLFW_BUILD)
    set (GLFW_ROOT ${MMD_GLFW_ROOT})
    find_package (GLFW)
endif ()

if (NOT GLFW_FOUND)
    set (MMD_FORCE_GLFW_BUILD on CACHE BOOL "" FORCE)
endif ()

if (MMD_FORCE_GLFW_BUILD)
    include_directories (${PROJECT_SOURCE_DIR}/external/glfw/include)
else ()
    include_directories (${GLFW_INCLUDE_DIR})
endif ()

if (MMD_ENABLE_TEST)
    enable_testing()
endif()

if (MMD_ENABLE_EXAMPLE_VULKAN)
    find_package(Vulkan REQUIRED)
endif()

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/viewer)
include_directories(${PROJECT_SOURCE_DIR}/external/gl3w/include)
include_directories(${PROJECT_SOURCE_DIR}/external/glm/include)
include_directories(${PROJECT_SOURCE_DIR}/external/stb/include)
include_directories(${PROJECT_SOURCE_DIR}/external/spdlog/include)
include_directories(${PROJECT_SOURCE_DIR}/external/tinyobjloader/include)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/external/lua)
include_directories(${BULLET_INCLUDE_DIRS})

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

ADD_DEFINITIONS(/MP)

add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(example)

# Install
if (MMD_INSTALL)
    install (DIRECTORY src/MMD DESTINATION include  FILES_MATCHING PATTERN "*.h")
endif()
