/*
 * vector_private.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 12/19/2013
 */

#pragma once

#include <zge/defines.h>
#include <Eigen/Eigen>

BEGIN_ZGE_NAMESPACE

struct ZVectorImpl {
    Eigen::Vector3f data;
};
    
END_ZGE_NAMESPACE
