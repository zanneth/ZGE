/*
 * input_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/schedulable.h"
#include "zge/noncopyable.h"
#include <memory>

namespace zge {

typedef std::shared_ptr<class input_manager> input_manager_ref;

class input_manager : public schedulable, noncopyable {
public:    
    void run(unsigned dtime) override;
};

} // namespace zge
