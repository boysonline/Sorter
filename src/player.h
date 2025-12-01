#pragma once

#include "objects.h"

#include <windows.h>

enum class KeyPress {
    NONE,
    ONE,
	TWO,
	THREE,
	Q,
	ANY
};

class Player {
private:
    Lives lives;
    Score score;

public:
    void gainScore() { score.gain(); }
    void loseScore() { score.lose(); }
    void restoreLife() { lives.restore(); }
    void loseLife() { lives.lose(); }
    const int getStartingLives() const { return lives.getStarting(); }
    const int getStartingScore() const { return score.getStarting(); }
    KeyPress getInput() const;
    Score getScore() const { return score; };
    Lives getLives() const { return lives; };
    bool isDead() const;
};