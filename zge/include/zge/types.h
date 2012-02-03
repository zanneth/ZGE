//
//  types.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

namespace zge {

template <class T>
struct ZNullDeleter {
    void operator()(void const *) const {}
};

} // namespace zge