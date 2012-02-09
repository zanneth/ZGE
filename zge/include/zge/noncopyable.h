//
//  noncopyable.h
//  ZGE
//
//  Created by Charles Magahern on 2/9/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

namespace zge {

class ZNonCopyable {
protected:
    ZNonCopyable()  = default;
    ~ZNonCopyable() = default;

private:
    ZNonCopyable(const ZNonCopyable&)                   = delete;
    const ZNonCopyable& operator=(const ZNonCopyable&)  = delete;
};

} // namespace zge