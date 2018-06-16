# General CMAKE

set(CMAKE_BUILD_TYPE Debug)


cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# json sources
include_directories("${PROJECT_SOURCE_DIR}/include/rapidjson")



# Spine sources
include_directories("${PROJECT_SOURCE_DIR}/include/spine")

file(GLOB spine_files
        "spine/*.cpp"
        "spine/*.c"
)



# General Project

project(RareAttack)

set(RareAttack_VERSION_MAJOR 1)
set(RareAttack_VERSION_MINOR 0)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(EXECUTABLE_NAME "game")

file(GLOB cpp_files
    "*.cpp"
)


add_executable(${EXECUTABLE_NAME} ${cpp_files} ${spine_files})


# Detect and add SFML

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

