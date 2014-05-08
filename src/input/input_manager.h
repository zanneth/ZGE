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

#include <functional>
#include <list>
#include <memory>
#include <queue>

BEGIN_ZGE_NAMESPACE

typedef std::shared_ptr<class ZInputManager> ZInputManagerRef;
typedef std::shared_ptr<class ZResponder> ZResponderRef;
typedef std::function<void(const ZEvent &event)> ZResponderFunction;

class ZResponder : ZNoncopyable {
protected:
    ZResponderFunction  _function;
    bool                _swallows_events;
    unsigned            _uid;
    
public:
    ZResponder(ZResponderFunction function = [](const ZEvent&){}, bool swallows_events = false);
    ZResponder(const ZResponder&)   = default;
    ZResponder(ZResponder&&)        = default;
    virtual ~ZResponder()           = default;

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
};

class ZInputManager : public ZSchedulable, ZNoncopyable {
    std::list<ZResponderRef> _responder_chain;
    std::queue<ZResponderRef> _removal_queue;
    
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
};

END_ZGE_NAMESPACE
