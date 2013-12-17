/*
 * geometry.tpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#pragma once

#include <ostream>
#include <string>

namespace zge {

template <typename Derived>
std::string ZGeometry::description(const MatrixBase<Derived> &matrix)
{
    IOFormat format(StreamPrecision, DontAlignCols, ", ", ",", "", "", "{", "}");
    std::ostringstream stream;
    stream << matrix.format(format);
    return stream.str();
}

} // namespace zge
