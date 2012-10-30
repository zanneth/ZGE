/*
 * event.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/20/2012
 */
 
#pragma once

#include "zge/geometry.h"
#include "zge/types.h"

#include <memory>
#include <string>
#include <vector>

namespace zge {

enum ZEventType {
    UNKNOWN_EVENT = 0,
    
    // mouse events
    MOUSE_DOWN_EVENT,
    MOUSE_UP_EVENT,
    MOUSE_MOVED_EVENT,
    MOUSE_DRAGGED_EVENT,
    SCROLL_WHEEL_EVENT,
    
    // touch events
    TOUCH_DOWN_EVENT,
    TOUCH_UP_EVENT,
    
    // key events
    KEY_DOWN_EVENT,
    KEY_UP_EVENT,
    
    // other events
    USER_EVENT,
    APPLICATION_EVENT,
    SYSTEM_EVENT,
    PERIODIC_EVENT,
    OTHER_EVENT
};

enum ZKeyModifierFlags : unsigned {
    NO_MODIFIERS      = 0,
    LEFT_SHIFT_KEY    = 1 << 0,
    RIGHT_SHIFT_KEY   = 1 << 1,
    LEFT_CONTROL_KEY  = 1 << 2,
    RIGHT_CONTROL_KEY = 1 << 3,
    LEFT_ALT_KEY      = 1 << 4,
    RIGHT_ALT_KEY     = 1 << 5,
    LEFT_META_KEY     = 1 << 6,
    RIGHT_META_KEY    = 1 << 7,
    NUM_LOCK_KEY      = 1 << 8,
    CAPS_LOCK_KEY     = 1 << 9
};
// for all my Mac homeboys
#define LEFT_COMMAND_KEY  LEFT_META_KEY
#define RIGHT_COMMAND_KEY RIGHT_META_KEY
#define LEFT_OPTION_KEY   LEFT_ALT_KEY
#define RIGHT_OPTION_KEY  RIGHT_ALT_KEY

enum ZMouseButtonFlags : unsigned {
    NO_BUTTONS              = 0,
    LEFT_MOUSE_BUTTON       = 1 << 0,
    MIDDLE_MOUSE_BUTTON     = 1 << 1,
    RIGHT_MOUSE_BUTTON      = 1 << 2,
    WHEEL_DOWN              = 1 << 3,
    WHEEL_UP                = 1 << 4,
    MOUSE_BUTTON_1          = 1 << 5,
    MOUSE_BUTTON_2          = 1 << 6,
    MOUSE_BUTTON_3          = 1 << 7,
    MOUSE_BUTTON_4          = 1 << 8,
    MOUSE_BUTTON_5          = 1 << 9,
    MOUSE_BUTTON_6          = 1 << 10,
    MOUSE_BUTTON_7          = 1 << 11,
    MOUSE_BUTTON_8          = 1 << 12
};

enum ZKey {
    ZKEY_UNKNOWN = 0,
    ZKEY_BACKSPACE,
    ZKEY_TAB,
    ZKEY_CLEAR,
    ZKEY_RETURN,
    ZKEY_PAUSE,
    ZKEY_ESCAPE,
    ZKEY_SPACE,
    ZKEY_EXCLAMATION,
    ZKEY_QUOTEDBL,
    ZKEY_HASH,
    ZKEY_DOLLAR,
    ZKEY_AMPERSAND,
    ZKEY_QUOTE,
    ZKEY_LEFTPAREN,
    ZKEY_RIGHTPAREN,
    ZKEY_ASTERISK,
    ZKEY_PLUS,
    ZKEY_COMMA,
    ZKEY_MINUS,
    ZKEY_PERIOD,
    ZKEY_SLASH,
    ZKEY_0,
    ZKEY_1,
    ZKEY_2,
    ZKEY_3,
    ZKEY_4,
    ZKEY_5,
    ZKEY_6,
    ZKEY_7,
    ZKEY_8,
    ZKEY_9,
    ZKEY_COLON,
    ZKEY_SEMICOLON,
    ZKEY_LESS,
    ZKEY_EQUALS,
    ZKEY_GREATER,
    ZKEY_QUESTION,
    ZKEY_AT,
    ZKEY_LEFTBRACKET,
    ZKEY_BACKSLASH,
    ZKEY_RIGHTBRACKET,
    ZKEY_CARET,
    ZKEY_UNDERSCORE,
    ZKEY_BACKQUOTE,
    ZKEY_A,
    ZKEY_B,
    ZKEY_C,
    ZKEY_D,
    ZKEY_E,
    ZKEY_F,
    ZKEY_G,
    ZKEY_H,
    ZKEY_I,
    ZKEY_J,
    ZKEY_K,
    ZKEY_L,
    ZKEY_M,
    ZKEY_N,
    ZKEY_O,
    ZKEY_P,
    ZKEY_Q,
    ZKEY_R,
    ZKEY_S,
    ZKEY_T,
    ZKEY_U,
    ZKEY_V,
    ZKEY_W,
    ZKEY_X,
    ZKEY_Y,
    ZKEY_Z,
    ZKEY_DELETE,
    ZKEY_KP0,
    ZKEY_KP1,
    ZKEY_KP2,
    ZKEY_KP3,
    ZKEY_KP4,
    ZKEY_KP5,
    ZKEY_KP6,
    ZKEY_KP7,
    ZKEY_KP8,
    ZKEY_KP9,
    ZKEY_KP_PERIOD,
    ZKEY_KP_DIVIDE,
    ZKEY_KP_MULTIPLY,
    ZKEY_KP_MINUS,
    ZKEY_KP_PLUS,
    ZKEY_KP_ENTER,
    ZKEY_KP_EQUALS,
    ZKEY_UP,
    ZKEY_DOWN,
    ZKEY_RIGHT,
    ZKEY_LEFT,
    ZKEY_INSERT,
    ZKEY_HOME,
    ZKEY_END,
    ZKEY_PAGEUP,
    ZKEY_PAGEDOWN,
    ZKEY_F1,
    ZKEY_F2,
    ZKEY_F3,
    ZKEY_F4,
    ZKEY_F5,
    ZKEY_F6,
    ZKEY_F7,
    ZKEY_F8,
    ZKEY_F9,
    ZKEY_F10,
    ZKEY_F11,
    ZKEY_F12,
    ZKEY_F13,
    ZKEY_F14,
    ZKEY_F15,
    ZKEY_NUMLOCK,
    ZKEY_CAPSLOCK,
    ZKEY_SCROLLOCK,
    ZKEY_RSHIFT,
    ZKEY_LSHIFT,
    ZKEY_RCTRL,
    ZKEY_LCTRL,
    ZKEY_RALT,
    ZKEY_LALT,
    ZKEY_RMETA,
    ZKEY_LMETA,
    ZKEY_LSUPER,
    ZKEY_RSUPER,
    ZKEY_MODE,
    ZKEY_COMPOSE,
    ZKEY_HELP,
    ZKEY_PRINT,
    ZKEY_SYSREQ,
    ZKEY_BREAK,
    ZKEY_MENU,
    ZKEY_POWER,
    ZKEY_EURO,
    ZKEY_UNDO
};

enum ZButtonState {
    UNKNOWN_BUTTON_STATE = 0,
    PRESSED,
    RELEASED
};

struct ZKeyEvent {
    ZKey                    key;            // hardware-independent virtual key code
    ZKeyModifierFlags       modifier_flags; // flags for modifier keys
    ZButtonState            state;          // whether the button is pressed or released
};

struct ZMouseEvent {
    ZVec2                   location;         // mouse location at the time of the event
    ZVec2                   velocity;         // velocity vector for mouse movement
    ZMouseButtonFlags       pressed_buttons;  // mouse buttons that are pressed for this event
    ZMouseButtonFlags       released_buttons; // mouse buttons that were released for this event
    unsigned                click_count;      // single-, double-, triple-click, etc.
};

struct ZTouchEvent {
    ZVec2                   location;       // location of the touch
    unsigned                tap_count;      // number of taps registered for this event
};

enum ZApplicationEvent {
    UNKNOWN_APPLICATION_EVENT = 0,
    APPLICATION_QUIT_EVENT,
    APPLICATION_SUSPENDED_EVENT,
    APPLICATION_ACTIVE_EVENT,
    APPLICATION_INACTIVE_EVENT
};

struct ZEvent {
    uint32_t                timestamp;      // the time when the event was created
    ZEventType              type;           // the type of event
    std::shared_ptr<void>   context;        // an arbitrary context. if the event was spawned by the input manager, this would be a pointer to the responder
    bool                    is_repeat;      // a repeat of a previous event (e.g. key held down)
    
    union _ZConcreteEvent {
        ZKeyEvent                   key_event;
        ZMouseEvent                 mouse_event;
        std::vector<ZTouchEvent>    touch_events;
        ZApplicationEvent           application_event;
        
        _ZConcreteEvent()  {}
        _ZConcreteEvent(const _ZConcreteEvent&) {}
        ~_ZConcreteEvent() {}
    } event;
    
    std::string get_description() const;
    
private:
    std::string _type_description() const;
    std::string _key_event_description() const;
    std::string _mouse_event_description() const;
    std::string _touch_event_description() const;
    std::string _application_event_description() const;
};
 
} // namespace zge
