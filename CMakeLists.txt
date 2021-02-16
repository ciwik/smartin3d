cmake_minimum_required(VERSION 3.17)
project(smartin3d)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

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
    if (NOT GLEW_ROOT)
        find_package(GLEW QUIET)
        if(GLEW_FOUND)
            get_filename_component(GLEW_ROOT ${GLEW_INCLUDE_DIRS} DIRECTORY)
        endif()
    endif()

    if (NOT GLEW_ROOT)
        message(FATAL_ERROR  "Could not find GLEW. Please put the path to GLEW root folder into GLEW_ROOT environment variable")
    else()
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

        message("GLEW found at path: '${GLEW_INCLUDE_PATH}', '${GLEW_LIBRARY}', '${GLEW_DLL_PATH}'")
    endif()


    # GLFW - Graphics Library Framework
    # Provides a simple API for creating windows, contexts and surfaces, receiving input and events.
    if (NOT GLFW_ROOT)
        find_package(GLFW QUIET)
        if(GLFW_FOUND)
            get_filename_component(GLFW_ROOT ${GLFW_INCLUDE_DIR} DIRECTORY)
        else()
            if (32BIT)
                set(GLFW_ROOT ${GLFW32_ROOT})
            elseif(64BIT)
                set(GLFW_ROOT ${GLFW64_ROOT})
            endif()
        endif()
    endif()

    if (NOT GLFW_ROOT)
        message(FATAL_ERROR "Could not find GLFW. Please put the path to GLFW root folder into GLFW32_ROOT or/and GLFW64_ROOT environment variable depends on your target architecture")
    else()
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

        message("GLFW found at path: '${GLFW_INCLUDE_PATH}', '${GLFW_LIBRARY}', '${GLFW_DLL_PATH}'")
    endif()


    # GLM - OpenGL Mathematics
    # Header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
    # Provides classes and functions designed and implemented with the same naming conventions and functionality than GLSL so that anyone who knows GLSL, can use GLM as well in C++.
    if (NOT GLM_ROOT)
        find_package(GLM QUIET)
        if (GLM_FOUND)
            get_filename_component(GLM_ROOT ${GLM_INCLUDE_DIRS} DIRECTORY)
        endif()
    endif()

    if (NOT GLM_ROOT)
        message(FATAL_ERROR "Could not find GLM. Please put the path to GLM root folder into GLM_ROOT environment variable")
    else()
        set(GLM_INCLUDE_PATH ${GLM_ROOT})
        message("GLM found at path: '${GLM_INCLUDE_PATH}'")
    endif()


    # assimp - Open Asset Import Library
    # A library to import and export various 3d-model-formats including scene-post-processing to generate missing render data.
    if (NOT ASSIMP_ROOT)
        find_package(assimp QUIET)
        if (assimp_FOUND)
            get_filename_component(ASSIMP_ROOT ${assimp_INCLUDE_DIRS} DIRECTORY)
        endif()
    endif()

    if (NOT ASSIMP_ROOT)
        message(FATAL_ERROR "Could not find ASSIMP. Please put the path to ASSIMP root folder into ASSIMP_ROOT environment variable")
    else()
        set(ASSIMP_INCLUDE_PATH "${ASSIMP_ROOT}/include")

        set(ASSIMP_LIB_PATH "${ASSIMP_ROOT}/lib")
        find_library(ASSIMP_LIBRARY PATH_SUFFIXES ".lib" NAMES assimp assimp-vc142 assimp-vc142-mt PATHS "${ASSIMP_LIB_PATH}")
        string(REPLACE ".lib" ".dll" ASSIMP_DLL_PATH ${ASSIMP_LIBRARY})
    endif()
endif (WINDOWS)

if (LINUX)
    # todo
endif (LINUX)

if (MACOS)
    # todo
endif (MACOS)

include_directories(${GLEW_INCLUDE_PATH} ${GLFW_INCLUDE_PATH} ${GLM_INCLUDE_PATH} ${ASSIMP_INCLUDE_PATH} include include/base/actors include/jobs include/3rdparty)

set (HEADER_FILES
        include/base/Actor.h
        include/base/Camera.h
        include/base/Job.h
        include/base/Transform.h

        include/graphics/Material.h
        include/graphics/Mesh.h
        include/graphics/Render.h
        include/graphics/Shader.h
        include/graphics/Texture.h
        include/graphics/Window.h

        include/utils/AssetUtils.h
        include/utils/External.h
        include/utils/FileUtils.h
        include/utils/Input.h
        include/utils/Log.h
        include/utils/OpenGLContext.h
        include/utils/TimeUtils.h
)

set (SOURCE_FILES
        src/base/Actor.cpp
        src/base/Camera.cpp
        src/base/Transform.cpp

        src/graphics/Material.cpp
        src/graphics/Mesh.cpp
        src/graphics/Render.cpp
        src/graphics/Shader.cpp
        src/graphics/Texture.cpp
        src/graphics/Window.cpp

        src/utils/AssetUtils.cpp
        src/utils/Input.cpp
        src/utils/Log.cpp
        src/utils/TimeUtils.cpp
)

set(PROJECT_VERSION "0.0.1")
set(LIBS ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${ASSIMP_LIBRARY})

# Build engine library
add_library(smartin3d SHARED ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(smartin3d PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(smartin3d PUBLIC ${LIBS})

# Build static engine library (for linking)
add_library(smartin3dlib STATIC ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(smartin3dlib PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(smartin3dlib PUBLIC ${LIBS})

# Enable tests
add_subdirectory(tests)

# Build a demo
add_executable(smartin3ddemo main.cpp)
target_link_libraries(smartin3ddemo smartin3dlib)

if (WINDOWS)
    add_custom_command(TARGET smartin3ddemo PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${GLFW_DLL_PATH}" $<TARGET_FILE_DIR:smartin3d>)
    add_custom_command(TARGET smartin3ddemo PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${GLEW_DLL_PATH}" $<TARGET_FILE_DIR:smartin3d>)
    add_custom_command(TARGET smartin3ddemo PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${ASSIMP_DLL_PATH}" $<TARGET_FILE_DIR:smartin3d>)
    add_custom_command(TARGET smartin3ddemo PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/shaders" $<TARGET_FILE_DIR:smartin3d>/shaders)
    add_custom_command(TARGET smartin3ddemo PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/textures" $<TARGET_FILE_DIR:smartin3d>/textures)
endif (WINDOWS)
