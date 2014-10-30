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
#include <zge/describable.h>

BEGIN_ZGE_NAMESPACE

typedef std::chrono::time_point<std::chrono::system_clock> ZTime;
typedef std::chrono::duration<double> ZTimeInterval;

struct ZPoint2D : public ZDescribable {
    float x;
    float y;
    
    ZPoint2D(float x = 0.f, float y = 0.f);
    
    std::vector<std::string> get_description_attributes() const override;
};

struct ZSize2D : public ZDescribable {
    float width;
    float height;
    
    ZSize2D(float width = 0.f, float height = 0.f);
    
    std::vector<std::string> get_description_attributes() const override;
};

struct ZEdgeInsets : public ZDescribable {
    float top;
    float left;
    float bottom;
    float right;
    
    ZEdgeInsets(float top = 0.f, float left = 0.f, float bottom = 0.f, float right = 0.f);
    
    std::vector<std::string> get_description_attributes() const override;
};

struct ZRect : public ZDescribable {
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
    
    std::array<float, 4 * 2> vertex_data() const;
    std::vector<std::string> get_description_attributes() const override;
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
    ZPIXEL_FORMAT_R,
    ZPIXEL_FORMAT_RG,
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
