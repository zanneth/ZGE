/*
 * event.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/20/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/types.h>

#include <memory>
#include <string>
#include <vector>

BEGIN_ZGE_NAMESPACE

enum ZEventType {
    ZUNKNOWN_EVENT = 0,
    
    // mouse events
    ZMOUSE_DOWN_EVENT,
    ZMOUSE_UP_EVENT,
    ZMOUSE_MOVED_EVENT,
    ZMOUSE_DRAGGED_EVENT,
    ZSCROLL_WHEEL_EVENT,
    
    // touch events
    ZTOUCH_DOWN_EVENT,
    ZTOUCH_UP_EVENT,
    
    // key events
    ZKEY_DOWN_EVENT,
    ZKEY_UP_EVENT,
    
    // other events
    ZUSER_EVENT,
    ZAPPLICATION_EVENT,
    ZSYSTEM_EVENT,
    ZPERIODIC_EVENT,
    ZOTHER_EVENT
};

enum ZKeyModifierFlags : unsigned {
    ZNO_MODIFIERS      = 0,
    ZLEFT_SHIFT_KEY    = 1 << 0,
    ZRIGHT_SHIFT_KEY   = 1 << 1,
    ZLEFT_CONTROL_KEY  = 1 << 2,
    ZRIGHT_CONTROL_KEY = 1 << 3,
    ZLEFT_ALT_KEY      = 1 << 4,
    ZRIGHT_ALT_KEY     = 1 << 5,
    ZLEFT_META_KEY     = 1 << 6,
    ZRIGHT_META_KEY    = 1 << 7,
    ZNUM_LOCK_KEY      = 1 << 8,
    ZCAPS_LOCK_KEY     = 1 << 9
};
#define ZLEFT_COMMAND_KEY  ZLEFT_META_KEY
#define ZRIGHT_COMMAND_KEY ZRIGHT_META_KEY
#define ZLEFT_OPTION_KEY   ZLEFT_ALT_KEY
#define ZRIGHT_OPTION_KEY  ZRIGHT_ALT_KEY

enum ZMouseButtonFlags : unsigned {
    ZNO_BUTTONS              = 0,
    ZLEFT_MOUSE_BUTTON       = 1 << 0,
    ZMIDDLE_MOUSE_BUTTON     = 1 << 1,
    ZRIGHT_MOUSE_BUTTON      = 1 << 2,
    ZWHEEL_DOWN              = 1 << 3,
    ZWHEEL_UP                = 1 << 4,
    ZMOUSE_BUTTON_1          = 1 << 5,
    ZMOUSE_BUTTON_2          = 1 << 6,
    ZMOUSE_BUTTON_3          = 1 << 7,
    ZMOUSE_BUTTON_4          = 1 << 8,
    ZMOUSE_BUTTON_5          = 1 << 9,
    ZMOUSE_BUTTON_6          = 1 << 10,
    ZMOUSE_BUTTON_7          = 1 << 11,
    ZMOUSE_BUTTON_8          = 1 << 12
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
    ZKEY_MODE,
    ZKEY_HELP,
    ZKEY_SYSREQ,
    ZKEY_MENU,
    ZKEY_POWER,
    ZKEY_UNDO
};

enum ZButtonState {
    ZUNKNOWN_BUTTON_STATE = 0,
    ZPRESSED,
    ZRELEASED
};

struct ZKeyEvent {
    ZKey                    key;            // hardware-independent virtual key code
    ZKeyModifierFlags       modifier_flags; // flags for modifier keys
    ZButtonState            state;          // whether the button is pressed or released
};

struct ZMouseEvent {
    ZPoint2D                location;         // mouse location at the time of the event
    ZPoint2D                velocity;         // velocity vector for mouse movement
    ZMouseButtonFlags       pressed_buttons;  // mouse buttons that are pressed for this event
    ZMouseButtonFlags       released_buttons; // mouse buttons that were released for this event
    unsigned                click_count;      // single-, double-, triple-click, etc.
};

struct ZTouchEvent {
    ZPoint2D                location;       // location of the touch
    unsigned                tap_count;      // number of taps registered for this event
};

enum ZApplicationEvent {
    ZUNKNOWN_APPLICATION_EVENT = 0,
    ZAPPLICATION_QUIT_EVENT,
    ZAPPLICATION_SUSPENDED_EVENT,
    ZAPPLICATION_ACTIVE_EVENT,
    ZAPPLICATION_INACTIVE_EVENT
};

struct ZEvent {
    uint32_t                timestamp;      // the time when the event was created
    ZEventType              type;           // the type of event
    std::shared_ptr<void>   context;        // an arbitrary context. if the event was spawned by the input manager, this would be a pointer to the responder
    bool                    is_repeat;      // a repeat of a previous event (e.g. key held down)
    
    union {
        ZKeyEvent           key_event;
        ZMouseEvent         mouse_event;
        ZTouchEvent         touch_event;
        ZApplicationEvent   application_event;
    };
    
    ZEvent();
    ZEvent(const ZEvent&);
    std::string get_description() const;
    
private:
    std::string _type_description() const;
    std::string _key_event_description() const;
    std::string _mouse_event_description() const;
    std::string _touch_event_description() const;
    std::string _application_event_description() const;
    std::string _mouse_buttons_description(ZMouseButtonFlags button_flags) const;
};
 
END_ZGE_NAMESPACE
