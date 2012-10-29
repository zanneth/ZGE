/*
 * zge.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/02/2012
 */
 
#pragma once

#include <Eigen/Eigen>

#include "zge/application.h"
#include "zge/camera.h"
#include "zge/display.h"
#include "zge/display_manager.h"
#include "zge/engine.h"
#include "zge/event.h"
#include "zge/exception.h"
#include "zge/fp_responder.h"
#include "zge/game_manager.h"
#include "zge/geometry.h"
#include "zge/gl_buffer.h"
#include "zge/gl_display.h"
#include "zge/gl_includes.h"
#include "zge/input_manager.h"
#include "zge/logger.h"
#include "zge/model.h"
#include "zge/node.h"
#include "zge/noncopyable.h"
#include "zge/notification_center.h"
#include "zge/platform.h"
#include "zge/run_loop.h"
#include "zge/scene.h"
#include "zge/schedulable.h"
#include "zge/types.h"
#include "zge/util.h"
#include "zge/viewport.h"

// SDL does this for some reason
#ifdef main
#undef main
#endif
