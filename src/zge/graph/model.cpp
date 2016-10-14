/*
 * model.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/27/2012
 */

#include <zge/util/exception.h>
#include <zge/graph/model.h>
#include <zge/util/logger.h>
#include <zge/renderer/shader_program.h>
#include <zge/util/util.h>
#include <array>
#include <cassert>
#include <lib3ds/mesh.h>
#include <lib3ds/node.h>
#include <lib3ds/file.h>
#include <sstream>

ZGE_BEGIN_NAMESPACE

template<typename T, size_t S>
std::array<T, S> __copy_vertex_data(T vertex[S]);

ZModel::ZModel(std::string filename) :
    _faces_count(0),
    _vertices_count(0),
    _render_mode(ZRENDER_MODE_TRIANGLE_STRIP)
{
    ZRenderContext *ctx = ZRenderContext::get_current_context();
    zassert(ctx, "invalid context");
    
    _vertex_array = ctx->create_vertex_array();
    _vertex_vbo = ctx->create_graphics_buffer();
    _normal_vbo = ctx->create_graphics_buffer();
    
    ZBufferAttribute vertex_attrib = {
        .components_per_vertex = 3,
        .component_type = ZCOMPONENT_TYPE_FLOAT,
        .normalized = false,
        .stride = 0,
        .offset = 0
    };
    _vertex_vbo->add_attribute(vertex_attrib);
    
    ZBufferAttribute normal_attrib = {
        .components_per_vertex = 3,
        .component_type = ZCOMPONENT_TYPE_FLOAT,
        .normalized = false,
        .stride = 0,
        .offset = 0
    };
    _normal_vbo->add_attribute(normal_attrib);
    
    _vertex_array->add_buffer(_vertex_vbo, ZVERTEX_ATTRIB_POSITION);
    _vertex_array->add_buffer(_normal_vbo, ZVERTEX_ATTRIB_NORMAL);
    
    if (filename.length()) {
        load_file(filename);
    }
}

ZGeometryRef ZModel::copy() const
{
    return std::make_shared<ZModel>(*this);
}

#pragma mark - Loading from Files

void ZModel::load_file(std::string filename)
{
    Lib3dsFile *model_file = lib3ds_file_load(filename.c_str());
    if (!model_file) {
        ZException e(ZFILE_EXCEPTION_CODE);
        e.extra_info = "Unable to load file " + filename;
        throw e;
    }
    
    if (model_file->meshes == nullptr) {
        ZException e(ZENGINE_EXCEPTION_CODE);
        e.extra_info = "Model file " + filename + " contains no meshes.";
        throw e;
    }
    
    // load information about the model
    _name = model_file->name;
    
    size_t total_faces = 0;
    size_t total_vertices = 0;
    std::vector<std::array<float, 3>> vertices;
    std::vector<std::array<float, 3>> normals;
    
    // copy data for each mesh from model file
    Lib3dsMesh *mesh = model_file->meshes;
    do {
        size_t mesh_faces_count = mesh->faces;
        size_t mesh_vertices_count = mesh->points;
        
        float (*calculated_normals)[3] = new float[mesh_faces_count * 3][3];
        lib3ds_mesh_calculate_normals(mesh, calculated_normals);
        
        unsigned cur_normals_idx = 0;
        for (unsigned j = 0; j < mesh_faces_count; ++j) {
            Lib3dsFace *face = &mesh->faceL[j];
            for (unsigned k = 0; k < 3; ++k) {
                vertices.push_back(__copy_vertex_data<float, 3>(mesh->pointL[face->points[k]].pos));
                normals.push_back(__copy_vertex_data<float, 3>(calculated_normals[cur_normals_idx++]));
            }
        }
        
        total_faces += mesh_faces_count;
        total_vertices += mesh_vertices_count;
        delete [] calculated_normals;
    } while ((mesh = mesh->next));
    
    // load data into each VBO
    #define VEC_ARR_DATA_SZ(vec) (vec.size() * 3 * sizeof(decltype(vec)::value_type::value_type))
    ZBufferUsage static_draw = { ZBUFFER_USAGE_FREQUENCY_STATIC, ZBUFFER_USAGE_NATURE_DRAW };
    _vertex_vbo->load_data(vertices.data(), VEC_ARR_DATA_SZ(vertices), static_draw);
    _normal_vbo->load_data(normals.data(), VEC_ARR_DATA_SZ(normals), static_draw);
    
    _faces_count = total_faces;
    _vertices_count = total_vertices;
    
    lib3ds_file_free(model_file);
}

#pragma mark - Accessors

std::string ZModel::get_name() const { return _name; }
ZRenderMode ZModel::get_render_mode() const { return _render_mode; }
void ZModel::set_render_mode(ZRenderMode mode) { _render_mode = mode; }

#pragma mark - Drawing

void ZModel::render(ZRenderContextRef context)
{
    ZGeometry::render(context);
    
    context->set_depth_testing_enabled(true);
    context->draw_array(_render_mode, _vertex_array, 0, _faces_count * 3);
    context->set_depth_testing_enabled(false);
}

#pragma mark - Internal

template<typename T, size_t S>
std::array<T, S> __copy_vertex_data(T vertex[S])
{
    std::array<T, S> array;
    std::copy(vertex, vertex + 3, array.begin());
    return array;
}

ZGE_END_NAMESPACE
