cmake_minimum_required(VERSION 3.0)

project(lsd)

#zet de dll library automatisch in de exe folder.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIGURATION>)

#Extra
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wvla")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wvla -Wno-missing-field-initializers")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
    if (ASAN)
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined")
    endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

add_executable(lsd)

file(GLOB_RECURSE sources src/*.cpp)
target_sources(lsd PUBLIC ${sources} "${CMAKE_SOURCE_DIR}/dependencies/src/glad.c" "header/move_to_component.h" "src/MoveToComponent.cpp")


find_package(OpenCV REQUIRED)

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${PROJECT_BINARY_DIR}/Debug/resources
    COMMENT "Copying resources!")
add_dependencies(lsd copy_resources)

target_include_directories(lsd PUBLIC "${CMAKE_SOURCE_DIR}/header/") 
target_include_directories(lsd PUBLIC "${CMAKE_SOURCE_DIR}/SDL/include/")
target_include_directories(lsd PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/include/")

add_subdirectory(SDL EXCLUDE_FROM_ALL)
target_link_libraries(lsd PRIVATE SDL2::SDL2 ${OpenCV_LIBS})

