/*
 * input_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <zge/core/defines.h>
#include <zge/input/event.h>
#include <zge/core/schedulable.h>
#include <zge/core/noncopyable.h>
#include <zge/input/responder.h>
#include <functional>
#include <list>
#include <memory>
#include <queue>

ZGE_BEGIN_NAMESPACE

class ZInputManager : public ZSchedulable, ZNoncopyable {
public:
    ZInputManager()  = default;
    ~ZInputManager() = default;
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZInputManager);
    
    /* Adding/Removing Responders */
    void add_responder(ZResponderRef responder);
    ZResponderRef add_responder(ZResponderFunction func, bool swallow_events = false); // shorthand
    void remove_responder(ZResponderRef responder);
    void promote_first_responder(ZResponderRef responder);
    void demote_responder(ZResponderRef responder);
    
    /* Schedulable Overrides */
    void run(uint32_t dtime) override;
    
    /* Sending Events through the System */
    void push_event(const ZEvent &event);
    
private:
    void _remove_responder_internal(ZResponderRef responder);
    
private:
    std::list<ZResponderRef> _responder_chain;
    std::queue<ZResponderRef> _removal_queue;
};

ZGE_DEFINE_SREF_TYPE(ZInputManager);

ZGE_END_NAMESPACE
