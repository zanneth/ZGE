/*
 * audio_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#include <zge/audio_manager.h>
#include <zge/audio_asset.h>
#include <zge/logger.h>
#include <zge/sound_private.h>
#include <SDL2/SDL.h>

#ifndef MIN
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#endif

BEGIN_ZGE_NAMESPACE

static void _audio_callback(void *userdata, uint8_t *stream, int len);

struct _ZAudioManagerImpl {
    SDL_AudioDeviceID device_id;
    std::vector<ZSoundRef> active_sounds;
};

ZAudioManager::ZAudioManager() :
    _impl(new _ZAudioManagerImpl)
{
    SDL_AudioSpec spec = {0};
    spec.callback = _audio_callback;
    spec.userdata = this;
    
    SDL_AudioSpec actual_spec;
    SDL_AudioDeviceID device_id = SDL_OpenAudioDevice(NULL, 0, &spec, &actual_spec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    if (device_id != 0) {
        zlog("Successfully opened audio device with ID %u", device_id);
        _impl->device_id = device_id;
        
        SDL_PauseAudioDevice(device_id, 0);
    } else {
        const char *sdl_error = SDL_GetError();
        zlog("Failed to open audio device: %s", sdl_error);
    }
}

ZAudioManager::~ZAudioManager()
{
    if (_impl->device_id) {
        SDL_CloseAudioDevice(_impl->device_id);
        _impl->device_id = 0;
    }
}

#pragma mark - API

void ZAudioManager::add_sound(ZSoundRef sound)
{
    zlog("Adding sound %p as active", sound.get());
    _impl->active_sounds.push_back(sound);
}

std::vector<ZSoundRef> ZAudioManager::get_active_sounds() const
{
    return _impl->active_sounds;
}

#pragma mark - Schedulable

void ZAudioManager::run(uint32_t dtime)
{
    std::vector<ZSoundRef> &active_sounds = _impl->active_sounds;
    
    // for sounds that repeat, reset their current offsets
    for (ZSoundRef sound : active_sounds) {
        ZAudioAssetRef asset = sound->get_asset();
        _ZSoundPlaybackState *playback_state = sound->_get_playback_state();
        int repeat_count = sound->get_repeat_count();
        uint32_t current_repeated = playback_state->current_repeated;
        uint32_t current_offset = playback_state->current_offset;
        
        if (current_offset == asset->get_buffer_length()) {
            if (repeat_count == -1 || current_repeated < repeat_count) {
                playback_state->current_offset = 0;
                playback_state->current_repeated++;
            } else {
                zlog("Finished playing sound %p", sound.get());
                playback_state->stopped = true;
            }
        }
    }
    
    // remove sounds that have stopped
    auto new_end_iter = std::remove_if(active_sounds.begin(), active_sounds.end(), [](ZSoundRef sound) {
        return sound->is_stopped();
    });
    active_sounds.erase(new_end_iter, active_sounds.end());
}

#pragma mark - Callbacks

void _audio_callback(void *userdata, uint8_t *stream, int len)
{
    // ensure silence if no data
    memset(stream, 0, len);
    
    ZAudioManager *audio_manager = static_cast<ZAudioManager *>(userdata);
    std::vector<ZSoundRef> active_sounds = audio_manager->get_active_sounds();
    for (ZSoundRef sound : active_sounds) {
        ZAudioAssetRef asset = sound->get_asset();
        float volume = sound->get_volume();
        
        _ZSoundPlaybackState *playback_state = sound->_get_playback_state();
        uint8_t *src_buffer = asset->get_buffer_data() + playback_state->current_offset;
        size_t remaining_length = asset->get_buffer_length() - playback_state->current_offset;
        SDL_AudioFormat format = static_cast<SDL_AudioFormat>(asset->get_audio_format());
        
        size_t len_to_mix = (len > remaining_length ? remaining_length : len);
        SDL_MixAudioFormat(stream, src_buffer, format, len_to_mix, volume * (float)SDL_MIX_MAXVOLUME);
        playback_state->current_offset += len_to_mix;
    }
}

END_ZGE_NAMESPACE
