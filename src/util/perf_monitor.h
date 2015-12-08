//
//  perf_monitor.h
//  ZGE
//
//  Created by Charles Magahern on 12/7/15.
//  Copyright © 2015 omegaHern. All rights reserved.
//

#pragma once

#include <zge/defines.h>
#include <zge/foundation.h>
#include <zge/types.h>
#include <deque>

ZGE_BEGIN_NAMESPACE

enum ZPerformanceEventType {
    ZPERF_EVENT_FRAME_BEGAN,
    ZPERF_EVENT_FRAME_ENDED
};

struct ZPerformanceEvent {
    ZTime timestamp;
    ZPerformanceEventType type;
};

class ZPerformanceMonitor {
public:
    ZPerformanceMonitor();
    ~ZPerformanceMonitor() = default;
    
    ZTime get_start_time() const;
    size_t get_sample_size() const;
    void set_sample_size(size_t size);
    
    void start_monitoring();
    void stop_monitoring();
    
    void log_event(ZPerformanceEventType event);
    
    double compute_frames_per_second() const;
    
public:
    static size_t default_sample_size;
    
private:
    size_t _sample_size;
    ZTime _start_time;
    ZTime _stop_time;
    std::deque<ZPerformanceEvent> _events;
};

ZGE_END_NAMESPACE
