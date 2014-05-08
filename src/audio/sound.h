/*
 * sound.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#pragma once

#include <zge/defines.h>
#include <zge/audio_asset.h>
#include <zge/noncopyable.h>
#include <memory>

BEGIN_ZGE_NAMESPACE

struct _ZSoundPlaybackState;

class ZSound : public std::enable_shared_from_this<ZSound>, ZNoncopyable {
public:
    ZSound(ZAudioAssetRef asset);
    
    void play();
    void pause();
    void stop();
    
    bool is_playing() const;
    bool is_stopped() const;
    
    float get_volume() const;
    void  set_volume(float volume);
    
    int  get_repeat_count() const; // default is 0
    void set_repeat_count(int repeat_count); // use -1 for infinite
    
    ZAudioAssetRef get_asset() const;
    
    // private
    _ZSoundPlaybackState* _get_playback_state();
    
private:
    std::auto_ptr<_ZSoundPlaybackState> _playback_state;
};

typedef std::shared_ptr<ZSound> ZSoundRef;

END_ZGE_NAMESPACE
