//
//  responder.h
//  ZGE
//
//  Created by Charles Magahern on 9/23/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#pragma once

#include <zge/core/foundation.h>
#include <zge/input/event.h>

ZGE_BEGIN_NAMESPACE

typedef std::function<void(const ZEvent &event)> ZResponderFunction;

class ZResponder : ZNoncopyable {
public:
    ZResponder(ZResponderFunction function = [](const ZEvent&){}, bool swallows_events = false);
    ZResponder(const ZResponder&)   = default;
    ZResponder(ZResponder&&)        = default;
    virtual ~ZResponder()           = default;
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZResponder);

    /* Accessors */
    ZResponderFunction get_function() { return _function; }
    virtual void set_function(const ZResponderFunction &func) { _function = func; }
    bool swallows_events() { return _swallows_events; }
    virtual void set_swallows_events(bool swallows) { _swallows_events = swallows; }

    /* Event Sending Convenience */
    void send_event(const ZEvent &event);

    /* Operators */
    bool operator==(const ZResponder&);
    bool operator!=(const ZResponder&);
    
protected:
    ZResponderFunction  _function;
    bool                _swallows_events;
    unsigned            _uid;
};

ZGE_DEFINE_SREF_TYPE(ZResponder);

ZGE_END_NAMESPACE
