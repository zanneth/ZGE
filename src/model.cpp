/*
 * model.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/27/2012
 */

#include "zge/exception.h"
#include "zge/gl_includes.h"
#include "zge/model.h"
#include "zge/logger.h"
#include "zge/util.h"

#include <cassert>
#include <lib3ds.h>
#include <iostream>
#include <sstream>

#define DEBUG_LOG 0

namespace zge {

ZModel::ZModel(std::string filename) :
    _num_faces(0),
    _num_vertices(0),
    _element_vbo(new ZGLBuffer),
    _vertex_vbo(new ZGLBuffer),
    _normal_vbo(new ZGLBuffer)
{
    _element_vbo->set_target(GL_ELEMENT_ARRAY_BUFFER);
    _vertex_vbo->set_target(GL_ARRAY_BUFFER);
    _normal_vbo->set_target(GL_ARRAY_BUFFER);
    
    if (filename.length()) {
        load_file(filename);
    }
}


#pragma mark - Loading from Files

void ZModel::load_file(std::string filename)
{
    Lib3dsFile *model_file = lib3ds_file_open(filename.c_str());
    if (!model_file) {
        ZException e(FILE_EXCEPTION_CODE);
        e.extra_info = "Unable to load file " + filename;
        throw e;
    }
    
    if (model_file->nmeshes == 0) {
        ZException e(ENGINE_EXCEPTION_CODE);
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
        float (*cur_normals)[3] = (float(*)[3]) &normals[faces_copied * 3];
        lib3ds_mesh_calculate_face_normals(mesh, cur_normals);
        
        // copy vertex data
        float (*cur_vertices)[3] = (float(*)[3]) &vertices[i * 3];
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
    _element_vbo->load_data(total_faces * 3 * sizeof(unsigned), elements, GL_STATIC_DRAW);
    _vertex_vbo->load_data(total_vertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
    _normal_vbo->load_data(total_faces * 3 * sizeof(float), normals, GL_STATIC_DRAW);
    
#if (DEBUG_LOG)
    ZLogger::log("Number of meshes: %u", model_file->nmeshes);
    ZLogger::log("Number of faces (polygons): %u", total_faces);
    ZLogger::log("Number of vertices: %u", total_vertices);
    // print elements array
    ZLogger::log("Elements array:");
    ZLogger::log_array(elements, total_faces * 3);
    
    ZLogger::log("Vertex array:");
    ZLogger::log_array(vertices, total_vertices * 3);
    
    ZLogger::log("Normals array:");
    ZLogger::log_array(normals, total_faces * 3);
#endif

    // cleanup
    delete[] elements;
    delete[] vertices;
    delete[] normals;
    lib3ds_file_free(model_file);
}


#pragma mark - Drawing

void ZModel::draw()
{
    glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    _vertex_vbo->bind();
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    
    _normal_vbo->bind();
    glNormalPointer(GL_FLOAT, 0, NULL);
    
    _element_vbo->bind();
    glDrawElements(GL_TRIANGLES, _num_faces * 3, GL_UNSIGNED_INT, (void *)0);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glPopClientAttrib();
}

} // namespace zge
