cmake_minimum_required(VERSION 3.0)

include(CheckCXXCompilerFlag)
include(FindPkgConfig)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(ZGE C CXX)

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

target_include_directories(zge
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# OpenGL/ES
find_package(OpenGL)

if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(zge ${OPENGL_LIBRARIES})
else()
    find_package(OpenGLES2)
    include_directories(${OPENGLES2_INCLUDE_DIR})
    target_link_libraries(zge ${OPENGLES2_LIBRARIES})
    add_definitions(-DOPENGL_ES -DOPENGL_ES2)
endif()

# SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(zge ${SDL2_LIBRARY})

# SDL_Image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(zge ${SDL2_IMAGE_LIBRARIES})

# lib3ds
find_package(Lib3ds REQUIRED)
include_directories(${LIB3DS_INCLUDE_DIR})
target_link_libraries(zge ${LIB3DS_LIBRARY})

# Freetype
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIR_freetype2})
target_link_libraries(zge ${FREETYPE_LIBRARIES})

# Eigen
find_package(Eigen REQUIRED)
include_directories(${EIGEN_INCLUDE_DIRS})

install (FILES ${HEADERS}
   DESTINATION include/zge
   COMPONENT devel
)
