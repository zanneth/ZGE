/*
 * audio_asset.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/04/2014
 */

#pragma once

#include <zge/defines.h>
#include <zge/noncopyable.h>
#include <memory>

BEGIN_ZGE_NAMESPACE

typedef uint16_t ZAudioFormat;

class ZAudioAsset {
public:
    virtual ~ZAudioAsset();
    
    virtual uint8_t*     get_buffer_data() const = 0;
    virtual size_t       get_buffer_length() const = 0;
    virtual ZAudioFormat get_audio_format() const = 0;
};

typedef std::shared_ptr<ZAudioAsset> ZAudioAssetRef;

END_ZGE_NAMESPACE
