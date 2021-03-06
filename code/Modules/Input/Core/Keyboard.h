#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::Keyboard
    @ingroup Input
    @brief access to keyboard state
*/
#include "Input/Core/Key.h"
#include "Core/Assertion.h"
#include <bitset>

namespace Oryol {

class Keyboard {
public:
    /// constructor
    Keyboard();
    
    /// keyboard attached?
    bool Attached;
    /// test if key is currently pressed
    bool KeyPressed(Key::Code key) const;
    /// test if key was pressed down last frame
    bool KeyDown(Key::Code key) const;
    /// test if key was released last frame
    bool KeyUp(Key::Code key) const;
    /// test if key-repeat happened
    bool KeyRepeat(Key::Code key) const;
    
    /// return true if text capturing is active
    bool IsCapturingText() const;
    /// get current captured text
    const wchar_t* CapturedText() const;

    /// call when key down event happens
    void onKeyDown(Key::Code key);
    /// call when key up event happens
    void onKeyUp(Key::Code key);
    /// call when key repeat event happens
    void onKeyRepeat(Key::Code key);
    /// call when character is appended
    void onChar(wchar_t c);
    /// reset the keyboard state
    void reset();
    /// begin text capturing
    void beginCaptureText();
    /// end text capturing
    void endCaptureText();
    /// clear captured text (called in beginCaptureText() and reset())
    void clearCapturedText();

private:
    std::bitset<Key::NumKeys> down;
    std::bitset<Key::NumKeys> up;
    std::bitset<Key::NumKeys> pressed;
    std::bitset<Key::NumKeys> repeat;
    static const int32 MaxNumChars = 128;
    int32 charIndex;
    wchar_t chars[MaxNumChars + 1];
    bool textCapturing;
};

//------------------------------------------------------------------------------
inline bool
Keyboard::KeyPressed(Key::Code key) const {
    o_assert_range_dbg(key, Key::NumKeys);
    return this->pressed[key];
}

//------------------------------------------------------------------------------
inline bool
Keyboard::KeyDown(Key::Code key) const {
    o_assert_range_dbg(key, Key::NumKeys);
    return this->down[key];
}

//------------------------------------------------------------------------------
inline bool
Keyboard::KeyUp(Key::Code key) const {
    o_assert_range_dbg(key, Key::NumKeys);
    return this->up[key];
}

//------------------------------------------------------------------------------
inline bool
Keyboard::KeyRepeat(Key::Code key) const {
    o_assert_range_dbg(key, Key::NumKeys);
    return this->repeat[key];
}

//------------------------------------------------------------------------------
inline bool
Keyboard::IsCapturingText() const {
    return this->textCapturing;
}

//------------------------------------------------------------------------------
inline const wchar_t*
Keyboard::CapturedText() const {
    return this->chars;
}
    
} // namespace Oryol

