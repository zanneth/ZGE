/*
 * geometry.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#include "geometry.h"
#include <zge/shader_program.h>
#include <zge/uniform.h>

namespace zge {
    
static void _update_material_data(ZRenderContextRef context, ZMaterialRef material);

ZGeometry::ZGeometry() :
    _material(new ZMaterial)
{}

ZGeometry::ZGeometry(const ZGeometry &cp) :
    _material(new ZMaterial(*cp._material))
{}

ZGeometry::ZGeometry(ZGeometry &&mv)
{
    _material = mv._material;
    mv._material = nullptr;
}

ZGeometry::~ZGeometry()
{}

ZGeometryRef ZGeometry::copy() const
{
    return ZGeometryRef(new ZGeometry(*this));
}

#pragma mark - Accessors

ZMaterialRef ZGeometry::get_material() const { return _material; }
void ZGeometry::set_material(ZMaterialRef material) { _material = material; }

#pragma mark - Rendering

void ZGeometry::render(ZRenderContextRef context)
{
    _update_material_data(context, _material);
    // subclasses will render geometry
}

#pragma mark - Internal

void _update_material_data(ZRenderContextRef context, ZMaterialRef material)
{
    ZShaderProgramRef program = context->get_shader_program();
    
    // update ambient property
    ZMaterialProperty<ZColor> *ambient = material->get_ambient();
    ZUniformRef ambient_uniform = program->get_uniform(ambient->get_name());
    ambient_uniform->set_data(ambient->get_contents().data);
}

} // namespace zge
