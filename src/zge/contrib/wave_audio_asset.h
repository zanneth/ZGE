//
//  wave_audio_asset.h
//  ZGE
//
//  Created by Charles Magahern on 5/5/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#pragma once

#include <zge/core/defines.h>
#include <zge/audio/audio_asset.h>
#include <memory>

ZGE_BEGIN_NAMESPACE

class ZWaveAudioAsset : public ZAudioAsset {
public:
    ZWaveAudioAsset(std::string path);
    ZWaveAudioAsset(const ZWaveAudioAsset &cp);
    ZWaveAudioAsset(ZWaveAudioAsset &&mv);
    ~ZWaveAudioAsset();
    
    // asset overrides
    uint8_t*     get_buffer_data() const override;
    size_t       get_buffer_length() const override;
    ZAudioFormat get_audio_format() const override;
    
private:
    std::auto_ptr<struct _ZWaveAudioAssetImpl> _impl;
};

ZGE_END_NAMESPACE
