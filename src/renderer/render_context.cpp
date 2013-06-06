/*
 * render_context.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#include <zge/render_context.h>

namespace zge {

ZRenderContext::ZRenderContext() :
    _shader_program(new ZShaderProgram)
{
    for (unsigned i = 0; i < _ZRENDER_MATRIX_COUNT; ++i) {
        _matrix_stacks[i].push(Matrix4f::Identity());
    }
}

ZRenderContext::~ZRenderContext()
{}

void ZRenderContext::make_current()
{
    _shader_program->use_program();
}

void ZRenderContext::push_matrix(ZRenderMatrixType type)
{
    Matrix4f cur_matrix = _matrix_stacks[type].top();
    _matrix_stacks[type].push(cur_matrix);
}

void ZRenderContext::multiply_matrix(ZRenderMatrixType type, const Matrix4f &matrix)
{
    _matrix_stacks[type].top() *= matrix;
}

void ZRenderContext::load_identity(ZRenderMatrixType type)
{
    _matrix_stacks[type].top() = Matrix4f::Identity();
}

void ZRenderContext::pop_matrix(ZRenderMatrixType type)
{
    _matrix_stacks[type].pop();
}

} // namespace zge
