/*
 * audio_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#pragma once

#include <zge/defines.h>
#include <zge/noncopyable.h>
#include <zge/schedulable.h>
#include <zge/sound.h>
#include <memory>
#include <vector>

BEGIN_ZGE_NAMESPACE

class ZAudioManager : public ZSchedulable, ZNoncopyable {
public:
    ZAudioManager();
    ~ZAudioManager();
    
    void add_sound(ZSoundRef sound);
    std::vector<ZSoundRef> get_active_sounds() const;
    void run(uint32_t dtime) override;
    
private:
    std::auto_ptr<struct _ZAudioManagerImpl> _impl;
};

typedef std::shared_ptr<ZAudioManager> ZAudioManagerRef;

END_ZGE_NAMESPACE
