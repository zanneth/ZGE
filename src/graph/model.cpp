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

#include <cassert>
#include <lib3ds.h>
#include <sstream>

BEGIN_ZGE_NAMESPACE

ZModel::ZModel(std::string filename) :
    _num_faces(0),
    _num_vertices(0),
    _vertex_array(new ZVertexArray),
    _element_vbo(new ZElementGraphicsBuffer),
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
    _vertex_array->set_element_buffer(_element_vbo);
    
    if (filename.length()) {
        load_file(filename);
    }
}

ZGeometryRef ZModel::copy() const
{
    return ZModelRef(new ZModel(*this));
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
    
    // calculate the total number of faces (triangles) and vertices
    unsigned total_faces = 0;
    unsigned total_vertices = 0;
    for (unsigned i = 0; i < model_file->nmeshes; ++i) {
        Lib3dsMesh *mesh = model_file->meshes[i];
        total_faces += mesh->nfaces;
        total_vertices += mesh->nvertices;
    }
    _num_faces = total_faces;
    _num_vertices = total_vertices;
    
    // create our element, vertex, and normal arrays
    unsigned *elements  = new unsigned[total_faces * 3]; // 3 indices (elements) per face
    float *vertices     = new float[total_vertices * 3]; // 3 floats per vertex
    float *normals      = new float[total_faces * 3];    // 3 floats per vertex normal per face
    
    // copy data for each mesh from model file
    unsigned faces_copied = 0;
    for (unsigned i = 0; i < model_file->nmeshes; ++i) {
        Lib3dsMesh *mesh = model_file->meshes[i];
        
        // calculate normals and fill buffer
        float (*cur_normals)[3] = (float(*)[3])&normals[faces_copied * 3];
        lib3ds_mesh_calculate_face_normals(mesh, cur_normals);
        
        // copy vertex data
        float (*cur_vertices)[3] = (float(*)[3])&vertices[i * 3];
        memcpy(cur_vertices, mesh->vertices, 3 * mesh->nvertices * sizeof(float));
        
        // copy element data
        for (unsigned j = 0; j < mesh->nfaces; ++j) {
            Lib3dsFace *face = &mesh->faces[j];
            for (unsigned k = 0; k < 3; ++k) {
                elements[faces_copied * 3 + k] = face->index[k];
            }
            
            faces_copied++;
        }
    }
    
    // load data into each VBO
    ZBufferUsage static_draw = { ZBUFFER_USAGE_FREQUENCY_STATIC, ZBUFFER_USAGE_NATURE_DRAW };
    _element_vbo->load_data(elements, total_faces * 3 * sizeof(unsigned), static_draw);
    _vertex_vbo->load_data(vertices, total_vertices * 3 * sizeof(float), static_draw);
    _normal_vbo->load_data(normals, total_faces * 3 * sizeof(float), static_draw);
    
    _element_vbo->set_elements_count(_num_faces * 3);
    _element_vbo->set_indices_type(ZCOMPONENT_TYPE_UNSIGNED_INT);
    
    // cleanup
    delete[] elements;
    delete[] vertices;
    delete[] normals;
    lib3ds_file_free(model_file);
}

#pragma mark - Drawing

void ZModel::render(ZRenderContextRef context)
{
    ZGeometry::render(context);
    context->draw_elements(ZRENDER_MODE_TRIANGLES, _vertex_array);
}

END_ZGE_NAMESPACE
