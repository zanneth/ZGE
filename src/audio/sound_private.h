//
//  sound_private.h
//  ZGE
//
//  Created by Charles Magahern on 5/5/14.
//  Copyright (c) 2014 omegaHern. All rights reserved.
//

#pragma once

#include <zge/defines.h>
#include <zge/sound.h>

BEGIN_ZGE_NAMESPACE

struct _ZSoundPlaybackState {
    ZAudioAssetRef asset;
    bool           playing;
    bool           stopped;
    float          volume;
    int            repeat_count;
    uint32_t       current_offset;
    uint32_t       current_repeated;
};

END_ZGE_NAMESPACE
