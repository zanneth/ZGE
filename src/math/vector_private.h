/*
 * vector_private.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/19/2013
 */

#pragma once

#include <Eigen/Eigen>

namespace zge {

struct ZVectorImpl {
    Eigen::Vector3f data;
};
    
} // namespace zge
