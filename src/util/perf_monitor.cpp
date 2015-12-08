//
//  perf_monitor.cpp
//  ZGE
//
//  Created by Charles Magahern on 12/7/15.
//  Copyright © 2015 omegaHern. All rights reserved.
//

#include "perf_monitor.h"
#include "util.h"

ZGE_BEGIN_NAMESPACE

size_t ZPerformanceMonitor::default_sample_size = 50;

ZPerformanceMonitor::ZPerformanceMonitor() :
    _sample_size(default_sample_size)
{}

ZTime ZPerformanceMonitor::get_start_time() const
{
    return _start_time;
}

void ZPerformanceMonitor::start_monitoring()
{
    _start_time = ZUtil::get_current_time();
    _stop_time = ZUtil::get_current_time();
}

void ZPerformanceMonitor::stop_monitoring()
{
    _stop_time = ZUtil::get_current_time();
}

void ZPerformanceMonitor::log_event(ZPerformanceEventType event)
{
    _events.push_front({ZUtil::get_current_time(), event});
    if (_events.size() > _sample_size) {
        _events.pop_back();
    }
}

double ZPerformanceMonitor::compute_frames_per_second() const
{
    ZTime earliest_frame;
    ZTime latest_frame;
    size_t total_frames = 0;
    
    for (const ZPerformanceEvent &event : _events) {
        if (event.type == ZPERF_EVENT_FRAME_ENDED) {
            if (earliest_frame.time_since_epoch().count() == 0 || event.timestamp < earliest_frame) {
                earliest_frame = event.timestamp;
            }
            
            if (latest_frame.time_since_epoch().count() == 0 || event.timestamp > latest_frame) {
                latest_frame = event.timestamp;
            }
            
            ++total_frames;
        }
    }
    
    ZTimeInterval duration = latest_frame - earliest_frame;
    return (double(total_frames) / double(duration.count()));
}

ZGE_END_NAMESPACE
