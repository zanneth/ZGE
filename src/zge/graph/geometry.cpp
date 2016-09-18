/*
 * geometry.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/30/2013
 */

#include "geometry.h"
#include <zge/renderer/shader_program.h>
#include <zge/renderer/uniform.h>

ZGE_BEGIN_NAMESPACE
    
static void _update_material_data(ZRenderContextRef context, std::vector<ZMaterialRef> materials);

ZGeometryRef ZGeometry::copy() const
{
    return ZGeometryRef(new ZGeometry(*this));
}

#pragma mark -

std::vector<ZMaterialRef> ZGeometry::get_materials() const
{
    return _materials;
}

void ZGeometry::add_material(ZMaterialRef material)
{
    _materials.push_back(material);
}

void ZGeometry::remove_material(ZMaterialRef material_to_remove)
{
    std::remove_if(_materials.begin(), _materials.end(), [material_to_remove](ZMaterialRef m) {
        return m.get() == material_to_remove.get();
    });
}

void ZGeometry::clear_materials()
{
    _materials.clear();
}

#pragma mark - Rendering

void ZGeometry::prepare_render(ZRenderContextRef context)
{
    _update_material_data(context, _materials);
    for (ZMaterialRef material : _materials) {
        material->prepare_for_draw(context);
    }
}

void ZGeometry::render(ZRenderContextRef context)
{
    // subclasses will render geometry
}

void ZGeometry::finalize_render(ZRenderContextRef context)
{
    for (ZMaterialRef material : _materials) {
        material->finalize_draw(context);
    }
}

#pragma mark - Internal

void _update_material_data(ZRenderContextRef context, std::vector<ZMaterialRef> materials)
{
    ZShaderProgramRef program = context->get_shader_program();
    
    for (ZMaterialRef material : materials) {
        std::string uniform_name = material->get_shader_name();
        ZUniformRef uniform = program->get_uniform(uniform_name);
        if (uniform) {
            const void *material_data = material->get_contents_data();
            uniform->set_data(material_data);
        }
    }
}

ZGE_END_NAMESPACE
