//
//  responder.cpp
//  ZGE
//
//  Created by Charles Magahern on 9/23/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#include "responder.h"

ZGE_BEGIN_NAMESPACE

static unsigned __responder_global_uid_count = 1;

ZResponder::ZResponder(ZResponderFunction function, bool swallows_events) :
    _function(function),
    _swallows_events(swallows_events),
    _uid(__responder_global_uid_count++)
{}

bool ZResponder::operator==(const ZResponder &other)
{
    return _uid == other._uid;
}

bool ZResponder::operator!=(const ZResponder &other)
{
    return !operator==(other);
}

void ZResponder::send_event(const ZEvent &event)
{
    _function(event);
}

ZGE_END_NAMESPACE
