//
//  util.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include "zge/error.h"

namespace zge {
namespace util {

/** Fatal Errors **/
void fatalError();
void fatalError(ZError error);

} // namespace util
} // namespace zge