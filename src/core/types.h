/*
 * types.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/20/2012
 */
 
#pragma once

#include <array>
#include <chrono>
#include <cstdint>
#include <zge/defines.h>

BEGIN_ZGE_NAMESPACE

typedef std::chrono::time_point<std::chrono::system_clock> ZTime;
typedef std::chrono::duration<double> ZTimeInterval;

struct ZPoint2D {
    float x;
    float y;
};

struct ZSize2D {
    float width;
    float height;
};

struct ZRect {
    ZPoint2D origin;
    ZSize2D size;
    
    inline bool contains_rect(const ZRect &other) const
    {
        return (
            (
                other.origin.x >= origin.x &&
                other.origin.x + other.size.width < origin.x + size.width
            ) && (
                other.origin.y >= origin.y &&
                other.origin.y + other.size.height < origin.y + size.height
            )
        );
    }
    
    std::array<float, 4 * 2> vertex_data() const
    {
        std::array<float, 4 * 2> vertex_data{{
            origin.x, origin.y,
            origin.x + size.width, origin.y,
            origin.x, origin.y + size.height,
            origin.x + size.width, origin.y + size.height
        }};
        return vertex_data;
    }
};

enum ZVertexAttributeIndex {
    ZVERTEX_ATTRIB_UNDEFINED = -1,
    ZVERTEX_ATTRIB_POSITION = 0,
    ZVERTEX_ATTRIB_COLOR,
    ZVERTEX_ATTRIB_NORMAL,
    ZVERTEX_ATTRIB_TEXCOORD0,
    ZVERTEX_ATTRIB_TEXCOORD1,
    ZVERTEX_ATTRIB_COUNT
};

enum ZComponentType {
    ZCOMPONENT_TYPE_UNKNOWN = 0,
    ZCOMPONENT_TYPE_BYTE,
    ZCOMPONENT_TYPE_UNSIGNED_BYTE,
    ZCOMPONENT_TYPE_SHORT,
    ZCOMPONENT_TYPE_UNSIGNED_SHORT,
    ZCOMPONENT_TYPE_INT,
    ZCOMPONENT_TYPE_UNSIGNED_INT,
    ZCOMPONENT_TYPE_FLOAT,
    ZCOMPONENT_TYPE_DOUBLE
};

enum ZRenderMode {
    ZRENDER_MODE_POINTS,
    ZRENDER_MODE_LINES,
    ZRENDER_MODE_LINE_LOOP,
    ZRENDER_MODE_LINE_STRIP,
    ZRENDER_MODE_TRIANGLES,
    ZRENDER_MODE_TRIANGLE_STRIP,
    ZRENDER_MODE_TRIANGLE_FAN
};

enum ZBufferTarget {
    ZBUFFER_TARGET_ARRAY,
    ZBUFFER_TARGET_COPY_READ,
    ZBUFFER_TARGET_COPY_WRITE,
    ZBUFFER_TARGET_ELEMENT_ARRAY,
    ZBUFFER_TARGET_PIXEL_PACK,
    ZBUFFER_TARGET_PIXEL_UNPACK,
    ZBUFFER_TARGET_TEXTURE,
    ZBUFFER_TARGET_TRANSFORM_FEEDBACK,
    ZBUFFER_TARGET_UNIFORM
};

enum ZBufferUsageFrequencyType {
    ZBUFFER_USAGE_FREQUENCY_STREAM, // data will be modified once and used a few times
    ZBUFFER_USAGE_FREQUENCY_STATIC, // data will be modified once and used many times
    ZBUFFER_USAGE_FREQUENCY_DYNAMIC // data will be modified and used repeatedly
};

enum ZBufferUsageNature {
    ZBUFFER_USAGE_NATURE_DRAW, // data will be used for drawing
    ZBUFFER_USAGE_NATURE_READ, // data will be used to read from the graphics library
    ZBUFFER_USAGE_NATURE_COPY, // data will be used to read and used for drawing
};

struct ZBufferUsage {
    ZBufferUsageFrequencyType frequency;
    ZBufferUsageNature nature;
};

enum ZPixelFormat {
    ZPIXEL_FORMAT_RGB,
    ZPIXEL_FORMAT_BGR,
    ZPIXEL_FORMAT_RGBA,
    ZPIXEL_FORMAT_BGRA,
};

struct ZImageFormat {
    uint8_t bytes_per_pixel;
    ZPixelFormat pixel_format;
};

END_ZGE_NAMESPACE
