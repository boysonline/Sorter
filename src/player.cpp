
#include "player.h"

KeyPress Player::getInput() const {
    static SHORT previousState[256] = {0};

    auto wasPressed = [&](int vk) {
        SHORT currentState = GetAsyncKeyState(vk);
        bool pressed = (currentState & 0x8000) && !(previousState[vk] & 0x8000);
        previousState[vk] = currentState;
        return pressed;
    };

    if (wasPressed('1')) return KeyPress::ONE;
    if (wasPressed('2')) return KeyPress::TWO;
    if (wasPressed('3')) return KeyPress::THREE;
    if (wasPressed('Q')) return KeyPress::Q;

    for (int vk = 1; vk <= 223; vk++) {
        if (wasPressed(vk)) return KeyPress::ANY;
    }

    return KeyPress::NONE;
}

bool Player::isDead() const {
    if (lives.get() <= 0) return true;
    return false;
}
