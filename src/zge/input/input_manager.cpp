/*
 * input_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 04/20/2012
 */
 
#include <zge/input/input_manager.h>
#include <zge/core/application.h>
#include <zge/util/logger.h>
#include <zge/core/run_loop.h>

#include <algorithm>
#include <SDL2/SDL.h>

ZGE_BEGIN_NAMESPACE

ZEvent _convert_sdl_event(const SDL_Event &sdl_event);
ZKey _convert_sdl_key(SDL_Keycode sdl_keycode);

#pragma mark - Adding/Removing Responders

void ZInputManager::add_responder(ZResponderRef responder)
{
    _responder_chain.push_back(responder);
}

ZResponderRef ZInputManager::add_responder(ZResponderFunction func, bool swallows_events)
{
    ZResponderRef new_responder(new ZResponder(func, swallows_events));
    add_responder(new_responder);
    return new_responder;
}

void ZInputManager::remove_responder(ZResponderRef responder)
{
    if (responder) {
        _removal_queue.push(responder);
    }
}

void ZInputManager::promote_first_responder(ZResponderRef responder)
{
    if (responder != _responder_chain.front()) {
        auto itr = std::find(_responder_chain.begin(), _responder_chain.end(), responder);
        if (itr != _responder_chain.end()) {
            ZResponderRef responder = *itr;
            _responder_chain.erase(itr);
            _responder_chain.push_front(responder);
        }
    }
}

void ZInputManager::demote_responder(ZResponderRef responder)
{
    if (responder != _responder_chain.back()) {
        auto itr = std::find(_responder_chain.begin(), _responder_chain.end(), responder);
        if (itr != _responder_chain.end()) {
            ZResponderRef responder = *itr;
            _responder_chain.erase(itr);
            _responder_chain.push_back(responder);
        }
    }
}

#pragma mark - Schedulable Overrides

void ZInputManager::run(uint32_t dtime)
{
    // remove responders
    while (!_removal_queue.empty()) {
        _remove_responder_internal(_removal_queue.front());
        _removal_queue.pop();
    }
    
    SDL_Event sdl_event;
    while (SDL_PollEvent(&sdl_event)) {
        ZEvent event = _convert_sdl_event(sdl_event);
        event.timestamp = ZUtil::get_current_time();
        push_event(event);
    }
}

#pragma mark - Sending Events through the System

void ZInputManager::push_event(const ZEvent &event)
{
    for (const auto &responder : _responder_chain) {
        responder->send_event(event);
        if (responder->swallows_events()) {
            break;
        }
    }
}

#pragma mark - Internal

void ZInputManager::_remove_responder_internal(ZResponderRef responder)
{
    auto itr = std::find(_responder_chain.begin(), _responder_chain.end(), responder);
    if (itr != _responder_chain.end()) {
        _responder_chain.erase(itr);
    } else {
        ZLogger::log_error("Could not remove responder. Not found in responder chain.");
    }
}

ZEvent _convert_sdl_event(const SDL_Event &sdl_event)
{
    ZEvent event;
    
    // get event type
    switch (sdl_event.type) {
        case SDL_MOUSEWHEEL:
            event.type = ZSCROLL_WHEEL_EVENT;
            break;
        case SDL_MOUSEBUTTONDOWN:
            event.type = ZMOUSE_DOWN_EVENT;
            break;
        case SDL_MOUSEBUTTONUP:
            event.type = ZMOUSE_UP_EVENT;
            break;
        case SDL_MOUSEMOTION:
            event.type = ZMOUSE_MOVED_EVENT;
            break;
        case SDL_KEYDOWN:
            event.type = ZKEY_DOWN_EVENT;
            break;
        case SDL_KEYUP:
            event.type = ZKEY_UP_EVENT;
            break;
        case SDL_USEREVENT:
            event.type = ZUSER_EVENT;
            break;
        case SDL_SYSWMEVENT:
        case SDL_QUIT:
        case SDL_WINDOWEVENT:
            event.type = ZAPPLICATION_EVENT;
            event.application_event = ZUNKNOWN_APPLICATION_EVENT;
            break;
        // TODO: Mouse Dragged
        // TODO: Touch Events
    }
    
    // parse mouse button event
    if (sdl_event.type == SDL_MOUSEBUTTONDOWN || sdl_event.type == SDL_MOUSEBUTTONUP) {
        ZPoint2D location = { (float)sdl_event.button.x, (float)sdl_event.button.y };
        event.mouse_event.location = location;
        
        ZMouseButtonFlags button;
        switch (sdl_event.button.button) {
            case SDL_BUTTON_LEFT:
                button = ZLEFT_MOUSE_BUTTON;
                break;
            case SDL_BUTTON_MIDDLE:
                button = ZMIDDLE_MOUSE_BUTTON;
                break;
            case SDL_BUTTON_RIGHT:
                button = ZRIGHT_MOUSE_BUTTON;
                break;
            case SDL_BUTTON_X1:
                button = ZMOUSE_BUTTON_1;
                break;
            case SDL_BUTTON_X2:
                button = ZMOUSE_BUTTON_2;
                break;
            default: // this should be impossible but what the hell
                button = ZNO_BUTTONS;
                break;
        }
        
        if (sdl_event.button.state == SDL_PRESSED) {
            event.mouse_event.pressed_buttons = button;
        } else if (sdl_event.button.state == SDL_RELEASED) {
            event.mouse_event.released_buttons = button;
        }
        event.mouse_event.click_count = 1;
    }
    
    // parse mouse wheel event
    if (sdl_event.type == SDL_MOUSEWHEEL) {
        ZMouseButtonFlags button;
        if (sdl_event.wheel.y < 0) {
            button = ZWHEEL_UP;
        } else {
            button = ZWHEEL_DOWN;
        }
        
        event.mouse_event.pressed_buttons = button;
        event.mouse_event.click_count = 1;
    }
    
    // parse mouse motion event
    if (sdl_event.type == SDL_MOUSEMOTION) {
        ZPoint2D location = { (float)sdl_event.motion.x, (float)sdl_event.motion.y };
        ZPoint2D velocity = { (float)sdl_event.motion.xrel, (float)sdl_event.motion.yrel };
        event.mouse_event.location = location;
        event.mouse_event.velocity = velocity;
        
        unsigned pressed_buttons = ZNO_BUTTONS;
        uint8_t sdl_buttons = sdl_event.motion.state;
        if (sdl_buttons != 0) {
            if (sdl_buttons & SDL_BUTTON_LMASK) {
                pressed_buttons |= ZLEFT_MOUSE_BUTTON;
            }
            if (sdl_buttons & SDL_BUTTON_RMASK) {
                pressed_buttons |= ZRIGHT_MOUSE_BUTTON;
            }
            if (sdl_buttons & SDL_BUTTON_MMASK) {
                pressed_buttons |= ZMIDDLE_MOUSE_BUTTON;
            }
            if (sdl_buttons & SDL_BUTTON_X1MASK) {
                pressed_buttons |= ZMOUSE_BUTTON_1;
            }
            if (sdl_buttons & SDL_BUTTON_X2MASK) {
                pressed_buttons |= ZMOUSE_BUTTON_2;
            }
        }
        event.mouse_event.pressed_buttons = static_cast<ZMouseButtonFlags>(pressed_buttons);
    }
    
    // parse key event
    if (sdl_event.type == SDL_KEYDOWN || sdl_event.type == SDL_KEYUP) {
        SDL_Keysym sdl_key = sdl_event.key.keysym;
        ZKey key = _convert_sdl_key(sdl_key.sym);
        event.key_event.key = key;
        
        uint16_t sdl_mods = sdl_key.mod;
        unsigned mods = ZNO_MODIFIERS;
        if (sdl_mods != KMOD_NONE) {
            if (sdl_mods & KMOD_LSHIFT) {
                mods |= ZLEFT_SHIFT_KEY;
            }
            if (sdl_mods & KMOD_RSHIFT) {
                mods |= ZRIGHT_SHIFT_KEY;
            }
            if (sdl_mods & KMOD_LCTRL) {
                mods |= ZLEFT_CONTROL_KEY;
            }
            if (sdl_mods & KMOD_RCTRL) {
                mods |= ZRIGHT_CONTROL_KEY;
            }
            if (sdl_mods & KMOD_LALT) {
                mods |= ZLEFT_ALT_KEY;
            }
            if (sdl_mods & KMOD_RALT) {
                mods |= ZRIGHT_ALT_KEY;
            }
            if (sdl_mods & KMOD_LGUI) {
                mods |= ZLEFT_META_KEY;
            }
            if (sdl_mods & KMOD_RGUI) {
                mods |= ZRIGHT_META_KEY;
            }
            if (sdl_mods & KMOD_NUM) {
                mods |= ZNUM_LOCK_KEY;
            }
            if (sdl_mods & KMOD_CAPS) {
                mods |= ZCAPS_LOCK_KEY;
            }
        }
        event.key_event.modifier_flags = static_cast<ZKeyModifierFlags>(mods);
        event.key_event.state = (sdl_event.key.state == SDL_PRESSED ? ZPRESSED : ZRELEASED);
    }
    
    // parse application event
    if (sdl_event.type == SDL_QUIT) {
        event.application_event = ZAPPLICATION_QUIT_EVENT;
    } else if (sdl_event.type == SDL_WINDOWEVENT) {
        switch (sdl_event.window.event) {
            case SDL_WINDOWEVENT_SHOWN:
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                event.application_event = ZAPPLICATION_ACTIVE_EVENT;
                break;
            case SDL_WINDOWEVENT_HIDDEN:
            case SDL_WINDOWEVENT_FOCUS_LOST:
                event.application_event = ZAPPLICATION_INACTIVE_EVENT;
                break;
        }
    }
    
    return event;
}

ZKey _convert_sdl_key(SDL_Keycode sdl_keycode)
{
    ZKey key = ZKEY_UNKNOWN;
    switch (sdl_keycode) {
        case SDLK_BACKSPACE:
            key = ZKEY_BACKSPACE;
            break;
        case SDLK_TAB:
            key = ZKEY_TAB;
            break;
        case SDLK_CLEAR:
            key = ZKEY_CLEAR;
            break;
        case SDLK_RETURN:
            key = ZKEY_RETURN;
            break;
        case SDLK_PAUSE:
            key = ZKEY_PAUSE;
            break;
        case SDLK_ESCAPE:
            key = ZKEY_ESCAPE;
            break;
        case SDLK_SPACE:
            key = ZKEY_SPACE;
            break;
        case SDLK_EXCLAIM:
            key = ZKEY_EXCLAMATION;
            break;
        case SDLK_QUOTEDBL:
            key = ZKEY_QUOTEDBL;
            break;
        case SDLK_HASH:
            key = ZKEY_HASH;
            break;
        case SDLK_DOLLAR:
            key = ZKEY_DOLLAR;
            break;
        case SDLK_AMPERSAND:
            key = ZKEY_AMPERSAND;
            break;
        case SDLK_QUOTE:
            key = ZKEY_QUOTE;
            break;
        case SDLK_LEFTPAREN:
            key = ZKEY_LEFTPAREN;
            break;
        case SDLK_RIGHTPAREN:
            key = ZKEY_RIGHTPAREN;
            break;
        case SDLK_ASTERISK:
            key = ZKEY_ASTERISK;
            break;
        case SDLK_PLUS:
            key = ZKEY_PLUS;
            break;
        case SDLK_COMMA:
            key = ZKEY_COMMA;
            break;
        case SDLK_MINUS:
            key = ZKEY_MINUS;
            break;
        case SDLK_PERIOD:
            key = ZKEY_PERIOD;
            break;
        case SDLK_SLASH:
            key = ZKEY_SLASH;
            break;
        case SDLK_0:
            key = ZKEY_0;
            break;
        case SDLK_1:
            key = ZKEY_1;
            break;
        case SDLK_2:
            key = ZKEY_2;
            break;
        case SDLK_3:
            key = ZKEY_3;
            break;
        case SDLK_4:
            key = ZKEY_4;
            break;
        case SDLK_5:
            key = ZKEY_5;
            break;
        case SDLK_6:
            key = ZKEY_6;
            break;
        case SDLK_7:
            key = ZKEY_7;
            break;
        case SDLK_8:
            key = ZKEY_8;
            break;
        case SDLK_9:
            key = ZKEY_9;
            break;
        case SDLK_COLON:
            key = ZKEY_COLON;
            break;
        case SDLK_SEMICOLON:
            key = ZKEY_SEMICOLON;
            break;
        case SDLK_LESS:
            key = ZKEY_LESS;
            break;
        case SDLK_EQUALS:
            key = ZKEY_EQUALS;
            break;
        case SDLK_GREATER:
            key = ZKEY_GREATER;
            break;
        case SDLK_QUESTION:
            key = ZKEY_QUESTION;
            break;
        case SDLK_AT:
            key = ZKEY_AT;
            break;
        case SDLK_LEFTBRACKET:
            key = ZKEY_LEFTBRACKET;
            break;
        case SDLK_BACKSLASH:
            key = ZKEY_BACKSLASH;
            break;
        case SDLK_RIGHTBRACKET:
            key = ZKEY_RIGHTBRACKET;
            break;
        case SDLK_CARET:
            key = ZKEY_CARET;
            break;
        case SDLK_UNDERSCORE:
            key = ZKEY_UNDERSCORE;
            break;
        case SDLK_BACKQUOTE:
            key = ZKEY_BACKQUOTE;
            break;
        case SDLK_a:
            key = ZKEY_A;
            break;
        case SDLK_b:
            key = ZKEY_B;
            break;
        case SDLK_c:
            key = ZKEY_C;
            break;
        case SDLK_d:
            key = ZKEY_D;
            break;
        case SDLK_e:
            key = ZKEY_E;
            break;
        case SDLK_f:
            key = ZKEY_F;
            break;
        case SDLK_g:
            key = ZKEY_G;
            break;
        case SDLK_h:
            key = ZKEY_H;
            break;
        case SDLK_i:
            key = ZKEY_I;
            break;
        case SDLK_j:
            key = ZKEY_J;
            break;
        case SDLK_k:
            key = ZKEY_K;
            break;
        case SDLK_l:
            key = ZKEY_L;
            break;
        case SDLK_m:
            key = ZKEY_M;
            break;
        case SDLK_n:
            key = ZKEY_N;
            break;
        case SDLK_o:
            key = ZKEY_O;
            break;
        case SDLK_p:
            key = ZKEY_P;
            break;
        case SDLK_q:
            key = ZKEY_Q;
            break;
        case SDLK_r:
            key = ZKEY_R;
            break;
        case SDLK_s:
            key = ZKEY_S;
            break;
        case SDLK_t:
            key = ZKEY_T;
            break;
        case SDLK_u:
            key = ZKEY_U;
            break;
        case SDLK_v:
            key = ZKEY_V;
            break;
        case SDLK_w:
            key = ZKEY_W;
            break;
        case SDLK_x:
            key = ZKEY_X;
            break;
        case SDLK_y:
            key = ZKEY_Y;
            break;
        case SDLK_z:
            key = ZKEY_Z;
            break;
        case SDLK_DELETE:
            key = ZKEY_DELETE;
            break;
        case SDLK_KP_0:
            key = ZKEY_KP0;
            break;
        case SDLK_KP_1:
            key = ZKEY_KP1;
            break;
        case SDLK_KP_2:
            key = ZKEY_KP2;
            break;
        case SDLK_KP_3:
            key = ZKEY_KP3;
            break;
        case SDLK_KP_4:
            key = ZKEY_KP4;
            break;
        case SDLK_KP_5:
            key = ZKEY_KP5;
            break;
        case SDLK_KP_6:
            key = ZKEY_KP6;
            break;
        case SDLK_KP_7:
            key = ZKEY_KP7;
            break;
        case SDLK_KP_8:
            key = ZKEY_KP8;
            break;
        case SDLK_KP_9:
            key = ZKEY_KP9;
            break;
        case SDLK_KP_PERIOD:
            key = ZKEY_KP_PERIOD;
            break;
        case SDLK_KP_DIVIDE:
            key = ZKEY_KP_DIVIDE;
            break;
        case SDLK_KP_MULTIPLY:
            key = ZKEY_KP_MULTIPLY;
            break;
        case SDLK_KP_MINUS:
            key = ZKEY_KP_MINUS;
            break;
        case SDLK_KP_PLUS:
            key = ZKEY_KP_PLUS;
            break;
        case SDLK_KP_ENTER:
            key = ZKEY_KP_ENTER;
            break;
        case SDLK_KP_EQUALS:
            key = ZKEY_KP_EQUALS;
            break;
        case SDLK_UP:
            key = ZKEY_UP;
            break;
        case SDLK_DOWN:
            key = ZKEY_DOWN;
            break;
        case SDLK_RIGHT:
            key = ZKEY_RIGHT;
            break;
        case SDLK_LEFT:
            key = ZKEY_LEFT;
            break;
        case SDLK_INSERT:
            key = ZKEY_INSERT;
            break;
        case SDLK_HOME:
            key = ZKEY_HOME;
            break;
        case SDLK_END:
            key = ZKEY_END;
            break;
        case SDLK_PAGEUP:
            key = ZKEY_PAGEUP;
            break;
        case SDLK_PAGEDOWN:
            key = ZKEY_PAGEDOWN;
            break;
        case SDLK_F1:
            key = ZKEY_F1;
            break;
        case SDLK_F2:
            key = ZKEY_F2;
            break;
        case SDLK_F3:
            key = ZKEY_F3;
            break;
        case SDLK_F4:
            key = ZKEY_F4;
            break;
        case SDLK_F5:
            key = ZKEY_F5;
            break;
        case SDLK_F6:
            key = ZKEY_F6;
            break;
        case SDLK_F7:
            key = ZKEY_F7;
            break;
        case SDLK_F8:
            key = ZKEY_F8;
            break;
        case SDLK_F9:
            key = ZKEY_F9;
            break;
        case SDLK_F10:
            key = ZKEY_F10;
            break;
        case SDLK_F11:
            key = ZKEY_F11;
            break;
        case SDLK_F12:
            key = ZKEY_F12;
            break;
        case SDLK_F13:
            key = ZKEY_F13;
            break;
        case SDLK_F14:
            key = ZKEY_F14;
            break;
        case SDLK_F15:
            key = ZKEY_F15;
            break;
        case SDLK_NUMLOCKCLEAR:
            key = ZKEY_NUMLOCK;
            break;
        case SDLK_CAPSLOCK:
            key = ZKEY_CAPSLOCK;
            break;
        case SDLK_SCROLLLOCK:
            key = ZKEY_SCROLLOCK;
            break;
        case SDLK_RSHIFT:
            key = ZKEY_RSHIFT;
            break;
        case SDLK_LSHIFT:
            key = ZKEY_LSHIFT;
            break;
        case SDLK_RCTRL:
            key = ZKEY_RCTRL;
            break;
        case SDLK_LCTRL:
            key = ZKEY_LCTRL;
            break;
        case SDLK_RALT:
            key = ZKEY_RALT;
            break;
        case SDLK_LALT:
            key = ZKEY_LALT;
            break;
        case SDLK_RGUI:
            key = ZKEY_RMETA;
            break;
        case SDLK_LGUI:
            key = ZKEY_LMETA;
            break;
        case SDLK_MODE:
            key = ZKEY_MODE;
            break;
        case SDLK_HELP:
            key = ZKEY_HELP;
            break;
        case SDLK_SYSREQ:
            key = ZKEY_SYSREQ;
            break;
        case SDLK_MENU:
            key = ZKEY_MENU;
            break;
        case SDLK_POWER:
            key = ZKEY_POWER;
            break;
        case SDLK_UNDO:
            key = ZKEY_UNDO;
            break;
        default:
            key = ZKEY_UNKNOWN;
            break;
    }
    
    return key;
}

ZGE_END_NAMESPACE
