cmake_minimum_required(VERSION 3.13.0)

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

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

add_executable(lsd)

target_sources(lsd PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/src/glad.c"
                          "src/BlockComponent.cpp"
                          "src/BoundingBoxComponent.cpp"
                          "src/Window.cpp"
                          "src/Model.cpp"
                          "src/GameObject.cpp"
                          "src/MoveToComponent.cpp"
                          "src/Shader.cpp"
                          "src/ControlComponent.cpp"
                          "src/main.cpp"
                          "src/SpinComponent.cpp"
                          "src/ModelComponent.cpp"
                          "src/Camera.cpp"
                          "src/RenderObject.cpp"
                          "src/Texture.cpp")

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${PROJECT_BINARY_DIR}/Debug/resources
    COMMENT "Copying resources!")
add_dependencies(lsd copy_resources)

target_include_directories(lsd PUBLIC "${CMAKE_SOURCE_DIR}/header/") 
target_include_directories(lsd PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/include/")

if(UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(deps REQUIRED IMPORTED_TARGET sdl2 opencv4)
    target_link_libraries(lsd PUBLIC PkgConfig::deps)
else()
    target_include_directories(lsd PUBLIC "${CMAKE_SOURCE_DIR}/SDL/include/")
    add_subdirectory(SDL EXCLUDE_FROM_ALL)
    find_package(OpenCV REQUIRED)
    target_link_libraries(lsd PRIVATE SDL2::SDL2 ${OpenCV_LIBS})
endif()

