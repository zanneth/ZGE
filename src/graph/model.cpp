/*
 * model.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/27/2012
 */

#include <zge/exception.h>
#include <zge/model.h>
#include <zge/logger.h>
#include <zge/shader_program.h>
#include <zge/util.h>
#include <array>
#include <cassert>
#include <lib3ds.h>
#include <sstream>

ZGE_BEGIN_NAMESPACE

template<typename T, size_t S>
std::array<T, S> __copy_vertex_data(T vertex[S]);

ZModel::ZModel(std::string filename) :
    _faces_count(0),
    _vertices_count(0),
    _vertex_array(new ZVertexArray),
    _vertex_vbo(new ZGraphicsBuffer),
    _normal_vbo(new ZGraphicsBuffer)
{
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
    Lib3dsFile *model_file = lib3ds_file_open(filename.c_str());
    if (!model_file) {
        ZException e(ZFILE_EXCEPTION_CODE);
        e.extra_info = "Unable to load file " + filename;
        throw e;
    }
    
    if (model_file->nmeshes == 0) {
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
    for (unsigned i = 0; i < model_file->nmeshes; ++i) {
        Lib3dsMesh *mesh = model_file->meshes[i];
        size_t mesh_faces_count = mesh->nfaces;
        size_t mesh_vertices_count = mesh->nvertices;
        
        float (*calculated_normals)[3] = new float[mesh_faces_count * 3][3];
        lib3ds_mesh_calculate_vertex_normals(mesh, calculated_normals);
        
        unsigned cur_normals_idx = 0;
        for (unsigned j = 0; j < mesh_faces_count; ++j) {
            Lib3dsFace *face = &mesh->faces[j];
            for (unsigned k = 0; k < 3; ++k) {
                vertices.push_back(__copy_vertex_data<float, 3>(mesh->vertices[face->index[k]]));
                normals.push_back(__copy_vertex_data<float, 3>(calculated_normals[cur_normals_idx++]));
            }
        }
        
        total_faces += mesh_faces_count;
        total_vertices += mesh_vertices_count;
        delete [] calculated_normals;
    }
    
    // load data into each VBO
    #define VEC_ARR_DATA_SZ(vec) (vec.size() * 3 * sizeof(decltype(vec)::value_type::value_type))
    ZBufferUsage static_draw = { ZBUFFER_USAGE_FREQUENCY_STATIC, ZBUFFER_USAGE_NATURE_DRAW };
    _vertex_vbo->load_data(vertices.data(), VEC_ARR_DATA_SZ(vertices), static_draw);
    _normal_vbo->load_data(normals.data(), VEC_ARR_DATA_SZ(normals), static_draw);
    
    _faces_count = total_faces;
    _vertices_count = total_vertices;
    
    lib3ds_file_free(model_file);
}

#pragma mark - Drawing

void ZModel::render(ZRenderContextRef context)
{
    ZGeometry::render(context);
    
    context->set_depth_testing_enabled(true);
    context->draw_array(ZRENDER_MODE_TRIANGLES, _vertex_array, 0, _faces_count * 3);
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
