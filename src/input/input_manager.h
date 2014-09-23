/*
 * input_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/event.h>
#include <zge/schedulable.h>
#include <zge/noncopyable.h>
#include <zge/responder.h>
#include <functional>
#include <list>
#include <memory>
#include <queue>

BEGIN_ZGE_NAMESPACE

typedef std::shared_ptr<class ZInputManager> ZInputManagerRef;

class ZInputManager : public ZSchedulable, ZNoncopyable {
public:
    ZInputManager()     = default;
    ~ZInputManager()    = default;
    
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

END_ZGE_NAMESPACE
