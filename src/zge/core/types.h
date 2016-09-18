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
#include <zge/core/defines.h>
#include <zge/util/describable.h>

ZGE_BEGIN_NAMESPACE

typedef std::chrono::time_point<std::chrono::system_clock> ZTime;
typedef std::chrono::duration<double> ZTimeInterval;

struct ZPoint2D {
    float x;
    float y;
    
    bool operator==(const ZPoint2D &rhs) const
    {
        return (x == rhs.x && y == rhs.y);
    }
    
    bool operator!=(const ZPoint2D &rhs) const
    {
        return !operator==(rhs);
    }
};

struct ZSize2D {
    float width;
    float height;
    
    bool operator==(const ZSize2D &rhs) const
    {
        return (width == rhs.width && height == rhs.height);
    }
    
    bool operator!=(const ZSize2D &rhs) const
    {
        return !operator==(rhs);
    }
};

struct ZEdgeInsets {
    float top;
    float left;
    float bottom;
    float right;
};

struct ZRect {
    ZPoint2D origin;
    ZSize2D size;
    
    ZRect(const ZPoint2D &origin, const ZSize2D &size);
    ZRect(float x = 0.f, float y = 0.f, float width = 0.f, float height = 0.f);
    
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
    
    inline bool contains_point(const ZPoint2D &pt) const
    {
        return (
            pt.x >= origin.x && pt.x <= origin.x + size.width &&
            pt.y >= origin.y && pt.y <= origin.y + size.height
        );
    }
};

struct ZPolar2D {
    float r;
    float theta;
    
    ZPolar2D(float radius = 0.0, float angle = 0.0);
    ZPolar2D(const ZPoint2D &cartesian);
    ZPoint2D cartesian() const;
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
#if !OPENGL_ES
    ZCOMPONENT_TYPE_DOUBLE
#endif
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
#if !OPENGL_ES
    ZBUFFER_TARGET_TEXTURE,
#endif
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
    ZPIXEL_FORMAT_R,
    ZPIXEL_FORMAT_RG,
    ZPIXEL_FORMAT_RGB,
    ZPIXEL_FORMAT_RGBA,
    ZPIXEL_FORMAT_BGR,
    ZPIXEL_FORMAT_BGRA,
};

struct ZImageFormat {
    uint8_t bytes_per_pixel;
    ZPixelFormat pixel_format;
};

enum ZShaderType {
    ZVERTEX_SHADER,
    ZFRAGMENT_SHADER
};

enum ZLightType {
    ZLIGHT_TYPE_POINT,
    ZLIGHT_TYPE_AMBIENT
};

enum ZLineBreakMode {
    ZLINE_BREAK_NONE = 0,
    ZLINE_BREAK_WORD,
    ZLINE_BREAK_CHAR
};

ZGE_END_NAMESPACE
