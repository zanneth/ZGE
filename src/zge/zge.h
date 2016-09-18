/*
 * zge.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/02/2012
 */
 
#pragma once

#include <zge/graph/action.h>
#include <zge/core/application.h>
#include <zge/audio/audio_asset.h>
#include <zge/audio/audio_manager.h>
#include <zge/contrib/box_layout.h>
#include <zge/contrib/3dcamera.h>
#include <zge/renderer/camera.h>
#include <zge/contrib/camera_controller.h>
#include <zge/core/color.h>
#include <zge/math/constants.h>
#include <zge/contrib/cube.h>
#include <zge/util/data.h>
#include <zge/core/defines.h>
#include <zge/core/display.h>
#include <zge/renderer/display_render_context.h>
#include <zge/core/engine.h>
#include <zge/input/event.h>
#include <zge/util/exception.h>
#include <zge/text/font.h>
#include <zge/graph/geometry.h>
#include <zge/text/glyph.h>
#include <zge/renderer/graphics_buffer.h>
#include <zge/input/input_manager.h>
#include <zge/renderer/image.h>
#include <zge/graph/layout.h>
#include <zge/renderer/light.h>
#include <zge/contrib/line.h>
#include <zge/util/logger.h>
#include <zge/graph/material.h>
#include <zge/math/matrix.h>
#include <zge/graph/model.h>
#include <zge/graph/node.h>
#include <zge/core/noncopyable.h>
#include <zge/core/observable.h>
#include <zge/renderer/opengl.h>
#include <zge/contrib/orthocamera.h>
#include <zge/contrib/plane.h>
#include <zge/contrib/quad.h>
#include <zge/renderer/render_context.h>
#include <zge/renderer/render_manager.h>
#include <zge/core/resource_bundle.h>
#include <zge/input/responder.h>
#include <zge/core/run_loop.h>
#include <zge/graph/scene.h>
#include <zge/core/schedulable.h>
#include <zge/renderer/shader.h>
#include <zge/renderer/shader_program.h>
#include <zge/audio/sound.h>
#include <zge/contrib/sprite_node.h>
#include <zge/text/text_node.h>
#include <zge/renderer/texture.h>
#include <zge/core/timer.h>
#include <zge/core/types.h>
#include <zge/renderer/uniform.h>
#include <zge/util/util.h>
#include <zge/math/vector.h>
#include <zge/renderer/vertex_array.h>
#include <zge/contrib/wave_audio_asset.h>

#if TARGET_OS_IPHONE
#include <zge/renderer/eagl_render_context.h>
#endif
