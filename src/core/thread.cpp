/*
 * thread.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/23/2014
 */

#include "thread.h"
#include "semaphore.h"

ZGE_BEGIN_NAMESPACE

ZThread::ZThread() :
    _runloop(std::make_shared<ZRunloop>()),
    _thread([this] { _runloop->run(); })
{}

#pragma mark - Accessors

ZRunloopRef ZThread::get_runloop() const { return _runloop; }
std::thread::id ZThread::get_id() const { return _thread.get_id(); }

#pragma mark - API

void ZThread::dispatch_task(const ZThreadTask &task)
{
    ZSchedulableRef sch_task = ZWorkSchedulable::create([task](uint32_t dt){ task(); });
    sch_task->set_unschedule_after_run(true);
    _runloop->schedule(sch_task);
}

void ZThread::dispatch_task_sync(const ZThreadTask &task)
{
    ZSemaphore sema4(0);
    dispatch_task([&]{
        task();
        sema4.signal();
    });
    sema4.wait();
}

void ZThread::join()
{
    _runloop->stop();
    _thread.join();
}

void ZThread::detach()
{
    _thread.detach();
}

ZGE_END_NAMESPACE
