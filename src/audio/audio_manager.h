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

ZGE_BEGIN_NAMESPACE

class ZAudioManager : public ZSchedulable, ZNoncopyable {
public:
    ZAudioManager();
    ~ZAudioManager();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZAudioManager);
    
    /// Add a sound object to the active queue and play immediately.
    void add_sound(ZSoundRef sound);
    
    /// Returns an array of sounds in the active queue.
    std::vector<ZSoundRef> get_active_sounds() const;
    
    /// Schedulable override.
    void run(uint32_t dtime) override;
    
private:
    static void _callback(void *userdata, uint8_t *stream, int len);
    
private:
    std::auto_ptr<struct _ZAudioManagerImpl> _impl;
};

ZGE_DEFINE_SREF_TYPE(ZAudioManager);

ZGE_END_NAMESPACE
