//
//  wave_audio_asset.cpp
//  ZGE
//
//  Created by Charles Magahern on 5/5/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#include <zge/wave_audio_asset.h>
#include <zge/exception.h>
#include <zge/util.h>
#include <SDL2/SDL.h>
#include <cstring>

BEGIN_ZGE_NAMESPACE

struct _ZWaveAudioAssetImpl {
    uint8_t *buffer;
    uint32_t length;
    SDL_AudioSpec spec;
};

ZWaveAudioAsset::ZWaveAudioAsset(std::string path) :
    _impl(new _ZWaveAudioAssetImpl)
{
    uint8_t *buffer;
    uint32_t length;
    SDL_AudioSpec spec;
    
    SDL_AudioSpec *result_spec = SDL_LoadWAV(path.c_str(), &spec, &buffer, &length);
    if (result_spec) {
        _impl->buffer = buffer;
        _impl->length = length;
        _impl->spec = spec;
    } else {
        ZException exception(ZFILE_EXCEPTION_CODE);
        exception.extra_info = ZUtil::format("Could not find file %s (%s)", path.c_str(), SDL_GetError());
        throw exception;
    }
}

ZWaveAudioAsset::ZWaveAudioAsset(const ZWaveAudioAsset &cp) :
    _impl(new _ZWaveAudioAssetImpl)
{
    uint8_t *src_buffer = cp._impl->buffer;
    uint32_t src_length = cp._impl->length;
    uint8_t *dst_buffer = _impl->buffer;
    
    dst_buffer = (uint8_t *)malloc(src_length);
    memcpy(dst_buffer, src_buffer, src_length);
    
    _impl->length = src_length;
    _impl->spec = cp._impl->spec;
}

ZWaveAudioAsset::ZWaveAudioAsset(ZWaveAudioAsset &&mv) :
    _impl(new _ZWaveAudioAssetImpl)
{
    _impl->buffer = mv._impl->buffer;
    _impl->length = mv._impl->length;
    _impl->spec = mv._impl->spec;
    
    mv._impl->buffer = nullptr;
    mv._impl->length = 0;
    mv._impl->spec = {0};
}

ZWaveAudioAsset::~ZWaveAudioAsset()
{
    SDL_FreeWAV(_impl->buffer);
    _impl->buffer = nullptr;
    _impl->length = 0;
}

#pragma mark - Asset Overrides

uint8_t* ZWaveAudioAsset::get_buffer_data() const
{
    return _impl->buffer;
}

size_t ZWaveAudioAsset::get_buffer_length() const
{
    return (size_t)_impl->length;
}

ZAudioFormat ZWaveAudioAsset::get_audio_format() const
{
    return static_cast<ZAudioFormat>(_impl->spec.format);
}

END_ZGE_NAMESPACE
