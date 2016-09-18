/*
 * sound.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#include <zge/audio/sound.h>
#include <zge/audio/sound_private.h>
#include <zge/audio/audio_manager.h>
#include <zge/core/engine.h>

ZGE_BEGIN_NAMESPACE

ZSound::ZSound(ZAudioAssetRef asset) :
    _playback_state(new _ZSoundPlaybackState)
{
    _playback_state->asset = asset;
    _playback_state->playing = false;
    _playback_state->stopped = false;
    _playback_state->volume = 1.0;
    _playback_state->repeat_count = 0;
    _playback_state->current_offset = 0;
    _playback_state->current_repeated = 0;
}

#pragma mark - API

void ZSound::pause()
{
    _playback_state->playing = false;
}

void ZSound::stop()
{
    _playback_state->stopped = true;
}

#pragma mark - Accessors

bool ZSound::is_playing() const { return _playback_state->playing; }
bool ZSound::is_stopped() const { return _playback_state->stopped; }
float ZSound::get_volume() const { return _playback_state->volume; }
void ZSound::set_volume(float volume) { _playback_state->volume = volume; }
int ZSound::get_repeat_count() const { return _playback_state->repeat_count; }
void ZSound::set_repeat_count(int repeat_count) { _playback_state->repeat_count = repeat_count; }
ZAudioAssetRef ZSound::get_asset() const { return _playback_state->asset; }
_ZSoundPlaybackState* ZSound::_get_playback_state() { return _playback_state.get(); }

ZGE_END_NAMESPACE
