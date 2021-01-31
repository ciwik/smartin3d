cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

project(tests)

# Catch2 test framework
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

add_executable(tests transform_tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2)

if (WINDOWS)
    add_custom_command(TARGET tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${GLFW_DLL_PATH}" $<TARGET_FILE_DIR:tests>)
    add_custom_command(TARGET tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${GLEW_DLL_PATH}" $<TARGET_FILE_DIR:tests>)
endif (WINDOWS)