/*
 * texture.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/08/2014
 */

#include <zge/texture.h>
#include <zge/opengl.h>
#include <zge/glutil.h>

BEGIN_ZGE_NAMESPACE

struct _ZTextureImpl {
    GLuint name;
    ZSize2D size;
    ZRect coordinate_rect;
};

ZTexture::ZTexture(ZImageRef image) :
    _impl(new _ZTextureImpl)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    ZSize2D img_size = image->get_size();
    ZDataRef img_data = image->get_pixel_data();
    ZImageFormat img_format = image->get_format();
    GLenum gl_format = ZGLUtil::gl_format_from_pixel_format(img_format.pixel_format);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_size.width, img_size.height, 0, gl_format, GL_UNSIGNED_BYTE, img_data->get_data());
    glBindTexture(GL_TEXTURE_2D, 0);
    
    _impl->name = texture;
    _impl->size = img_size;
    _impl->coordinate_rect = {{0.0, 0.0}, {1.0, 1.0}};
}

ZTexture::~ZTexture()
{
#if (ZDEBUG)
    zlog("Texture %p destroyed.", this);
#endif
    
    glDeleteTextures(1, &(_impl->name));
}

#pragma mark -

ZSize2D ZTexture::get_size() const
{
    return _impl->size;
}

ZRect ZTexture::get_texture_rect() const
{
    return _impl->coordinate_rect;
}

#pragma mark - Private

uint32_t ZTexture::_get_texture_name() const
{
    return _impl->name;
}

END_ZGE_NAMESPACE
