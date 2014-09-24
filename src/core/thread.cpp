/*
 * thread.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/23/2014
 */

#include "thread.h"

BEGIN_ZGE_NAMESPACE

ZThread::ZThread() :
    _runloop(std::make_shared<ZRunloop>()),
    _thread([this] { _runloop->run(); })
{}

#pragma mark - Accessors

ZRunloopRef ZThread::get_runloop() const { return _runloop; }
std::thread::id ZThread::get_id() const { return _thread.get_id(); }

#pragma mark - API

void ZThread::join()
{
    _runloop->stop();
    _thread.join();
}

void ZThread::detach()
{
    _thread.detach();
}

END_ZGE_NAMESPACE
