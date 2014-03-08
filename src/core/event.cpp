/*
 * event.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/29/2012
 */

#include "event.h"
#include "util.h"
#include <regex>

BEGIN_ZGE_NAMESPACE

ZEvent::ZEvent() :
    timestamp(0),
    type(ZUNKNOWN_EVENT),
    context(nullptr),
    is_repeat(false)
{}

ZEvent::ZEvent(const ZEvent &copy)
{
    timestamp = copy.timestamp;
    type = copy.type;
    context = copy.context;
    is_repeat = copy.is_repeat;
    
    switch (type) {
        case ZMOUSE_DOWN_EVENT:
        case ZMOUSE_UP_EVENT:
        case ZMOUSE_MOVED_EVENT:
        case ZMOUSE_DRAGGED_EVENT:
        case ZSCROLL_WHEEL_EVENT:
            mouse_event = copy.mouse_event;
            break;
        case ZTOUCH_DOWN_EVENT:
        case ZTOUCH_UP_EVENT:
            touch_event = copy.touch_event;
            break;
        case ZKEY_DOWN_EVENT:
        case ZKEY_UP_EVENT:
            key_event = copy.key_event;
            break;
        case ZAPPLICATION_EVENT:
            application_event = copy.application_event;
            break;
        default:
            break;
    }
}

std::string ZEvent::get_description() const
{
    const char *format = "<ZEvent %p \n"
        "\ttimestamp: %d\n"
        "\ttype: %s\n"
        "\tcontext: 0x%x\n"
        "\tis_repeat: %s\n"
        "\tdetails:\n\t\t%s\n"
        ">"
    ;
    std::string type_str = _type_description();
    const char *is_repeat_str = is_repeat ? "true" : "false";
    
    std::string details_str;
    switch (type) {
        case ZMOUSE_DOWN_EVENT:
        case ZMOUSE_UP_EVENT:
        case ZMOUSE_MOVED_EVENT:
        case ZMOUSE_DRAGGED_EVENT:
        case ZSCROLL_WHEEL_EVENT:
            details_str = _mouse_event_description();
            break;
        case ZTOUCH_DOWN_EVENT:
        case ZTOUCH_UP_EVENT:
            details_str = _touch_event_description();
            break;
        case ZKEY_DOWN_EVENT:
        case ZKEY_UP_EVENT:
            details_str = _key_event_description();
            break;
        case ZAPPLICATION_EVENT:
            details_str = _application_event_description();
            break;
        default:
            details_str = "N/A";
            break;
    }
    
    std::regex details_re("\n");
    details_str = std::regex_replace(details_str, details_re, "\n\t\t");
    
    std::string description = ZUtil::format(format, this, timestamp, type_str.c_str(), context.get(), is_repeat_str, details_str.c_str());
    return description;
}

#pragma mark - Internal

std::string ZEvent::_type_description() const
{
    std::string descr;
    switch (type) {
        case ZMOUSE_DOWN_EVENT:
            descr = "Mouse Down Event";
            break;
        case ZMOUSE_UP_EVENT:
            descr = "Mouse Up Event";
            break;
        case ZMOUSE_MOVED_EVENT:
            descr = "Mouse Moved Event";
            break;
        case ZMOUSE_DRAGGED_EVENT:
            descr = "Mouse Dragged Event";
            break;
        case ZSCROLL_WHEEL_EVENT:
            descr = "Scroll Wheel Event";
            break;
        case ZTOUCH_DOWN_EVENT:
            descr = "Touch Down Event";
            break;
        case ZTOUCH_UP_EVENT:
            descr = "Touch Up Event";
            break;
        case ZKEY_DOWN_EVENT:
            descr = "Key Down Event";
            break;
        case ZKEY_UP_EVENT:
            descr = "Key Up Event";
            break;
        case ZUSER_EVENT:
            descr = "User Event";
            break;
        case ZAPPLICATION_EVENT:
            descr = "Application Event";
            break;
        case ZSYSTEM_EVENT:
            descr = "System Event";
            break;
        case ZPERIODIC_EVENT:
            descr = "Periodic/Timer Event";
            break;
        case ZOTHER_EVENT:
        case ZUNKNOWN_EVENT:
        default:
            descr = "Unknown Event";
            break;
    }
    
    return descr;
}

std::string ZEvent::_key_event_description() const
{
    std::string descr;
    ZKeyEvent key_event = this->key_event;
    
    descr = ZUtil::format("Keycode: %d\n", key_event.key);
    
    unsigned modifier_flags = static_cast<unsigned>(key_event.modifier_flags);
    std::vector<std::string> modifier_strings;
    if (modifier_flags & ZLEFT_SHIFT_KEY) {
        modifier_strings.push_back("LSHIFT");
    }
    if (modifier_flags & ZRIGHT_SHIFT_KEY) {
        modifier_strings.push_back("RSHIFT");
    }
    if (modifier_flags & ZLEFT_CONTROL_KEY) {
        modifier_strings.push_back("LCONTROL");
    }
    if (modifier_flags & ZRIGHT_CONTROL_KEY) {
        modifier_strings.push_back("RCONTROL");
    }
    if (modifier_flags & ZLEFT_ALT_KEY) {
        modifier_strings.push_back("LALT");
    }
    if (modifier_flags & ZRIGHT_ALT_KEY) {
        modifier_strings.push_back("RALT");
    }
    if (modifier_flags & ZLEFT_META_KEY) {
        modifier_strings.push_back("LMETA");
    }
    if (modifier_flags & ZRIGHT_META_KEY) {
        modifier_strings.push_back("RMETA");
    }
    if (modifier_flags & ZNUM_LOCK_KEY) {
        modifier_strings.push_back("NUMLOCK");
    }
    if (modifier_flags & ZCAPS_LOCK_KEY) {
        modifier_strings.push_back("CAPSLOCK");
    }
    
    std::string modifiers_string;
    if (modifier_strings.size() > 0) {
        modifiers_string = ZUtil::separate_components(modifier_strings, ", ");
    } else {
        modifiers_string = "(no modifiers)";
    }
    descr += ZUtil::format("Modifier Keys: %s\n", modifiers_string.c_str());
    
    descr += ZUtil::format("Button State: %s", key_event.state == ZPRESSED ? "Pressed" : "Not Pressed");
    
    return descr;
}

std::string ZEvent::_mouse_event_description() const
{
    std::string descr;
    ZMouseEvent mouse_event = this->mouse_event;
    descr = ZUtil::format("Location: (%f, %f)\n", mouse_event.location.x, mouse_event.location.y);
    descr += ZUtil::format("Velocity: (%f, %f)\n", mouse_event.velocity.x, mouse_event.velocity.y);
    
    std::string pressed_str = _mouse_buttons_description(mouse_event.pressed_buttons);
    std::string released_str = _mouse_buttons_description(mouse_event.released_buttons);
    descr += ZUtil::format("Pressed: %s\n", pressed_str.c_str());
    descr += ZUtil::format("Released: %s\n", released_str.c_str());
    
    descr += ZUtil::format("Click Count: %d", mouse_event.click_count);
    
    return descr;
}

std::string ZEvent::_touch_event_description() const
{
    std::string descr;
    ZTouchEvent touch = this->touch_event;
    
    descr += ZUtil::format("\tLocation: (%f, %f)\n", touch.location.x, touch.location.y);
    descr += ZUtil::format("\tTaps: %d\n", touch.tap_count);
    
    return descr;
}

std::string ZEvent::_application_event_description() const
{
    std::string descr;
    ZApplicationEvent app_event = this->application_event;
    switch (app_event) {
        case ZAPPLICATION_QUIT_EVENT:
            descr = "Application Quit Event";
            break;
        case ZAPPLICATION_SUSPENDED_EVENT:
            descr = "Application Suspended Event";
            break;
        case ZAPPLICATION_ACTIVE_EVENT:
            descr = "Application Active Event";
            break;
        case ZAPPLICATION_INACTIVE_EVENT:
            descr = "Application Inactive Event";
            break;
        case ZUNKNOWN_APPLICATION_EVENT:
        default:
            descr = "Unknown Application Event";
            break;
    }
    
    return descr;
}

std::string ZEvent::_mouse_buttons_description(ZMouseButtonFlags button_flags) const
{
    unsigned buttons = static_cast<unsigned>(button_flags);
    std::vector<std::string> button_strings;
    if (buttons & ZLEFT_MOUSE_BUTTON) {
        button_strings.push_back("LEFTBUTTON");
    }
    if (buttons & ZMIDDLE_MOUSE_BUTTON) {
        button_strings.push_back("MIDDLEBUTTON");
    }
    if (buttons & ZRIGHT_MOUSE_BUTTON) {
        button_strings.push_back("RIGHTBUTTON");
    }
    if (buttons & ZWHEEL_DOWN) {
        button_strings.push_back("WHEELDOWN");
    }
    if (buttons & ZWHEEL_UP) {
        button_strings.push_back("WHEELUP");
    }
    if (buttons & ZMOUSE_BUTTON_1) {
		button_strings.push_back("MOUSEBUTTON1");
	}
	if (buttons & ZMOUSE_BUTTON_2) {
		button_strings.push_back("MOUSEBUTTON2");
	}
	if (buttons & ZMOUSE_BUTTON_3) {
		button_strings.push_back("MOUSEBUTTON3");
	}
	if (buttons & ZMOUSE_BUTTON_4) {
		button_strings.push_back("MOUSEBUTTON4");
	}
	if (buttons & ZMOUSE_BUTTON_5) {
		button_strings.push_back("MOUSEBUTTON5");
	}
	if (buttons & ZMOUSE_BUTTON_6) {
		button_strings.push_back("MOUSEBUTTON6");
	}
	if (buttons & ZMOUSE_BUTTON_7) {
		button_strings.push_back("MOUSEBUTTON7");
	}
	if (buttons & ZMOUSE_BUTTON_8) {
		button_strings.push_back("MOUSEBUTTON8");
	}
    
    std::string buttons_string;
    if (button_strings.size() > 0) {
        buttons_string = ZUtil::separate_components(button_strings, ", ");
    } else {
        buttons_string = "(no buttons)";
    }
    
    return buttons_string;
}
    
END_ZGE_NAMESPACE
