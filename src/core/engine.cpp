/*
 * engine.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/07/2012
 */
 
#include <zge/engine.h>
#include <zge/display.h>
#include <zge/exception.h>
#include <zge/run_loop.h>

ZGE_BEGIN_NAMESPACE

ZEngine::ZEngine() :
    _input_manager(new ZInputManager),
    _render_manager(new ZRenderManager),
    _audio_manager(new ZAudioManager),
    _scene(nullptr),
    _initialized(false),
    _application(nullptr),
    _root_responder(nullptr)
{}

ZEngine::~ZEngine()
{
    if (_root_responder) {
        _input_manager->remove_responder(_root_responder);
    }
}

#pragma mark - Initialization

void ZEngine::initialize(ZRunloopRef runloop)
{
    if (!_initialized) {
        if (!runloop) {
            ZException ex(ZASSERTION_EXCEPTION_CODE);
            ex.extra_info = "A runloop must be provided to the initialize routine.";
            throw ex;
        }
        
        runloop->schedule(_input_manager);
        runloop->schedule(_render_manager);
        runloop->schedule(_audio_manager);
        
        _root_responder = ZResponder::create(std::bind(&ZEngine::_handle_input_event, this, std::placeholders::_1));
        _input_manager->add_responder(_root_responder);
        
        _initialized = true;
    }
}

#pragma mark - Accessors

ZApplication* ZEngine::get_application() const { return _application; }
void ZEngine::set_application(ZApplication *application) { _application = application; }
ZInputManagerRef ZEngine::get_input_manager() { return _input_manager; }
ZRenderManagerRef ZEngine::get_render_manager() { return _render_manager; }
ZAudioManagerRef ZEngine::get_audio_manager() { return _audio_manager; }

#pragma mark - Utility

ZRect ZEngine::get_viewport_rect() const
{
    ZRect viewport_rect;
    ZDisplayRef cur_display = _render_manager->get_current_display();
    if (cur_display) {
        ZDisplayMode disp_mode = cur_display->get_display_mode();
        viewport_rect = {
            ZPoint2D(),
            { (float)disp_mode.width, (float)disp_mode.height }
        };
    }
    
    return viewport_rect;
}

ZSceneRef ZEngine::get_current_scene() const
{
    return _scene;
}

void ZEngine::set_current_scene(ZSceneRef scene)
{
    if (_scene) {
        _scene->on_exit();
    }
    
    _scene = scene;
    _render_manager->set_renderable(scene);
    
    if (_scene) {
        _scene->on_enter();
    }
}

#pragma mark - Internal

void ZEngine::_handle_input_event(const ZEvent &event)
{
    if (event.type == ZAPPLICATION_EVENT && _application != nullptr) {
        _application->handle_application_event(event);
    } else if (_scene) {
        _scene->handle_input_event(event);
    }
}

ZGE_END_NAMESPACE
