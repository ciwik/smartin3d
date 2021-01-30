cmake_minimum_required(VERSION 3.17)
project(smartin3d)

set(CMAKE_CXX_STANDARD 17)

# Detect OS
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOS TRUE)
    message("MacOS has been detected")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX TRUE)
    message("Linux has been detected")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WINDOWS TRUE)
    message("Windows has been detected")
endif()

# Detect platform word size
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(64BIT TRUE)
    message("64-bit has been detected")
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(32BIT TRUE)
    message("32-bit has been detected")
endif()

find_package(OpenGL REQUIRED)

if (WINDOWS)
    # GLEW - OpenGL Extension Wrangler Library
    # Provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target platform.
    # OpenGL core and extension functionality is exposed in a single header file.
    set(GLEW_INCLUDE_PATH "${GLEW_ROOT}/include")

    if (32BIT)
        set(GLEW_LIB_PATH "lib/Release/Win32")
    elseif (64BIT)
        set(GLEW_LIB_PATH "lib/Release/x64")
    endif()
    find_library(GLEW_LIBRARY NAMES glew glew32 glew32s PATHS "${GLEW_ROOT}/${GLEW_LIB_PATH}")

    if (32BIT)
        set(GLEW_DLL_PATH "${GLEW_ROOT}/bin/Release/Win32/glew32.dll")
    elseif(64BIT)
        set(GLEW_DLL_PATH "${GLEW_ROOT}/bin/Release/x64/glew32.dll")
    endif()


    # GLFW - Graphics Library Framework
    # Provides a simple API for creating windows, contexts and surfaces, receiving input and events.
    if (32BIT)
        set(GLFW_ROOT ${GLFW32_ROOT})
    elseif(64BIT)
        set(GLFW_ROOT ${GLFW64_ROOT})
    endif()

    set(GLFW_INCLUDE_PATH "${GLFW_ROOT}/include")

    if (MINGW)
        message("MinGW has been detected")
        if (32BIT)
            set(GLFW_LIB_PATH "lib-mingw")
        elseif(64BIT)
            set(GLFW_LIB_PATH "lib-mingw-w64")
        endif()
    elseif (MSVC)
        message("Visual Studio C++ compiler has been detected")
        if (MSVC_VERSION EQUAL 1600)
            message("Visual Studio 2010 has been found")
            set(GLFW_LIB_PATH "lib-vc2010")
        elseif (MSVC_VERSION EQUAL 1700)
            message("Visual Studio 2012 has been found")
            set(GLFW_LIB_PATH "lib-vc2012")
        elseif (MSVC_VERSION EQUAL 1800)
            message("Visual Studio 2013 has been found")
            set(GLFW_LIB_PATH "lib-vc2013")
        elseif (MSVC_VERSION EQUAL 1900)
            message("Visual Studio 2015 has been found")
            set(GLFW_LIB_PATH "lib-vc2015")
        elseif (MSVC_VERSION GREATER_EQUAL 1910 AND MSVC_VERSION LESS_EQUAL 1919)
            message("Visual Studio 2017 has been found")
            set(GLFW_LIB_PATH "lib-vc2017")
        elseif (MSVC_VERSION GREATER_EQUAL 1920 AND MSVC_VERSION LESS_EQUAL 1929)
            message("Visual Studio 2019 has been found")
            set(GLFW_LIB_PATH "lib-vc2019")
        endif()
    endif()

    find_library(GLFW_LIBRARY NAMES glfw glfw3 libglfw3 libglfw3dll PATHS "${GLFW_ROOT}/${GLFW_LIB_PATH}")
    set(GLFW_DLL_PATH "${GLFW_ROOT}/${GLFW_LIB_PATH}/glfw3.dll")


    # GLM - OpenGL Mathematics
    # Header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
    # Provides classes and functions designed and implemented with the same naming conventions and functionality than GLSL so that anyone who knows GLSL, can use GLM as well in C++.
    set(GLM_INCLUDE_PATH ${GLM_ROOT})
endif (WINDOWS)

if (LINUX)
    # todo
endif (LINUX)

if (MACOS)
    # todo
endif (MACOS)

include_directories(${GLEW_INCLUDE_PATH} ${GLFW_INCLUDE_PATH} ${GLM_INCLUDE_PATH} include)

add_subdirectory(src)

set (HEADER_FILES
        include/Log.h
        include/Window.h
        include/Time.h
        include/Log.h
        include/Mesh.h
        include/Shader.h
        include/FileUtils.h
        include/Actor.h
        include/OpenGLContext.h)

set (SOURCE_FILES
        src/Window.cpp
        src/main.cpp
        src/Log.cpp
        src/Time.cpp
        src/Mesh.cpp
        src/Shader.cpp
        src/Camera.cpp
        src/Transform.cpp
        src/Actor.cpp)

add_executable(smartin3d ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(smartin3d ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY})

if (WINDOWS)
    add_custom_command(TARGET smartin3d POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${GLFW_DLL_PATH}" $<TARGET_FILE_DIR:smartin3d>)
    add_custom_command(TARGET smartin3d POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${GLEW_DLL_PATH}" $<TARGET_FILE_DIR:smartin3d>)
    add_custom_command(TARGET smartin3d POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/shaders" $<TARGET_FILE_DIR:smartin3d>/shaders)
endif (WINDOWS)