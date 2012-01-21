//
//  types.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_TYPES_H_
#define _ZGE_TYPES_H_

namespace zge {

template <class T>
struct ZNullDeleter {
    void operator()(void const *) const {}
};

}

#endif // _ZGE_TYPES_H_
