cmake_minimum_required(VERSION 3.1)

include(CheckCXXCompilerFlag)
include(FindPkgConfig)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(ZGE CXX)

file(GLOB_RECURSE SOURCES "src/zge/*.cpp")
file(GLOB_RECURSE HEADERS "src/zge/*.h")

add_library(zge SHARED ${SOURCES} ${HEADERS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/zge/audio)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/zge/contrib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/zge/core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/zge/graph)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/zge/input)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/zge/math)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/zge/renderer)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/zge/shaders)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/zge/text)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/zge/util)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/lib3ds)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/freetype2)

target_include_directories(zge
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# OpenGL
find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(zge ${OPENGL_LIBRARIES})

# SDL
set(SDL2_LIBRARY "/usr/local/lib/libSDL2.dylib")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(zge ${SDL2_LIBRARY})

# SDL_Image
find_package(SDL_image REQUIRED)
include_directories(${SDL_IMAGE_INCLUDE_DIRS})
target_link_libraries(zge ${SDL_IMAGE_LIBRARIES})

# lib3ds
find_package(Lib3ds REQUIRED)
include_directories(${LIB3DS_INCLUDE_DIR})
target_link_libraries(zge ${LIB3DS_LIBRARY})

# Freetype
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIR_freetype2})
target_link_libraries(zge ${FREETYPE_LIBRARIES})

install (FILES ${HEADERS}
   DESTINATION include/zge
   COMPONENT devel
)
