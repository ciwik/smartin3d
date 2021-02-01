cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

# Catch2 test framework
find_package(Catch2 QUIET)
if (NOT Catch2_FOUND)
    message("Couldn't find Catch2 in local directories. Trying to get it from the Git repository. If you like to use a custom version, put the path to the Catch2 root folder into Catch2_DIR environment variable")

    Include(FetchContent)

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v2.13.1)

    FetchContent_MakeAvailable(Catch2)
endif()

set (TEST_FILES
        transform_tests.cpp)

add_executable(tests test_hints.h ${TEST_FILES})
target_link_libraries(tests smartin3dlib Catch2::Catch2)

if (WINDOWS)
    add_custom_command(TARGET tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${GLFW_DLL_PATH}" $<TARGET_FILE_DIR:tests>)
    add_custom_command(TARGET tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${GLEW_DLL_PATH}" $<TARGET_FILE_DIR:tests>)
endif (WINDOWS)