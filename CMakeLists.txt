cmake_minimum_required(VERSION 3.24)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR C:/LibSDL/MinGw/SDL2-2.26.5/x86_64-w64-mingw32/include/SDL2)
set(SDL2_LIB_DIR C:/LibSDL/MinGw/SDL2-2.26.5/x86_64-w64-mingw32/lib)

set(SDL2_INCLUDE_DIR_IMAGE C:/LibSDL/MinGw/SDL2_image-2.6.3/x86_64-w64-mingw32/include/SDL2)
set(SDL2_LIB_DIR_IMAGE C:/LibSDL/MinGw/SDL2_image-2.6.3/x86_64-w64-mingw32/lib)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_INCLUDE_DIR_IMAGE})
add_executable(${PROJECT_NAME} main.cpp entity.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/libSDL2.dll.a ${SDL2_LIB_DIR}/libSDL2main.a
        ${SDL2_LIB_DIR_IMAGE}/libSDL2_image.dll.a)