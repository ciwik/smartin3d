cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

add_executable(smartin3ddemoflyingcamera src/CameraMovementJob.h src/XwingDestroyJob.h src/main.cpp)
target_link_libraries(smartin3ddemoflyingcamera smartin3dlib)

if (WINDOWS)
    add_custom_command(TARGET smartin3ddemoflyingcamera POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${GLFW_DLL_PATH}" $<TARGET_FILE_DIR:smartin3ddemoflyingcamera>)
    add_custom_command(TARGET smartin3ddemoflyingcamera POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${GLEW_DLL_PATH}" $<TARGET_FILE_DIR:smartin3ddemoflyingcamera>)
    add_custom_command(TARGET smartin3ddemoflyingcamera POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${ASSIMP_DLL_PATH}" $<TARGET_FILE_DIR:smartin3ddemoflyingcamera>)
    add_custom_command(TARGET smartin3ddemoflyingcamera POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:smartin3d>/smartin3d.dll $<TARGET_FILE_DIR:smartin3ddemoflyingcamera>)
    add_custom_command(TARGET smartin3ddemoflyingcamera POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" $<TARGET_FILE_DIR:smartin3ddemoflyingcamera>/assets)
endif (WINDOWS)
