/*
 * display_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/noncopyable.h"
#include "zge/schedulable.h"

#include <memory>

namespace zge {

class display;
struct display_mode;

typedef std::shared_ptr<class display_manager> display_manager_ref;

class display_manager : public schedulable, noncopyable {
    display *_current_display;
    
public:
    display_manager();
    ~display_manager();
    
    /** Creating the Display **/
    display* create_display(const display_mode &mode);
    display* get_current_display() { return _current_display; }
    
    /** schedulable **/
    void run(unsigned dtime) override;
};

} // namespace zge
