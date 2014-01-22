/*
 * uniform.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/10/2014
 */

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <zge/observable.h>
#include <zge/opengl.h>

namespace zge {

typedef std::shared_ptr<class ZUniformBase> ZUniformRef;

class ZUniformBase : public ZObservable<ZUniformRef>, public std::enable_shared_from_this<ZUniformBase> {
    std::string _name;
    GLint _location;
    GLenum _type;
    
public:
    ZUniformBase(std::string name = "", GLint location = -1, GLenum type = GL_ZERO);
    virtual ~ZUniformBase();
    
    std::string get_name() const;
    GLenum get_type() const;
    virtual const void* get_data(size_t *out_length) const = 0;
    virtual void set_data(const void *data) = 0;
    
protected:
    GLint _get_location() const;
    friend class ZShaderProgram;
};

template <typename T, unsigned count>
class ZUniform : public ZUniformBase {
    T _values[count];
    
public:
    ZUniform(std::string name = "", GLint location = -1, GLenum type = GL_ZERO);
    ZUniform(const ZUniform &cp);
    ZUniform(ZUniform&&);
    ~ZUniform();
    
    const void* get_data(size_t *out_length) const override;
    void set_data(const void *data) override;
};

} // namespace zge

#include <zge/uniform.hpp>
