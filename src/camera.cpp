/*
 * camera.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/30/2012
 */
 
#include "zge/camera.h"

namespace zge {

ZCamera::ZCamera() :
    _fieldOfView(kDefaultFieldOfView),
    _nearClippingDistance(kDefaultNearClippingDistance),
    _farClippingDistance(kDefaultFarClippingDistance)
{}

} // namespace zge
