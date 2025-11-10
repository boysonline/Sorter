#pragma once

#include "world.h"
#include "renderer.h"
#include "clock.h"

class Game; // forward declaration

// ───────────────────────────────────────────────
// Base abstract state
// ───────────────────────────────────────────────
class State {
public:
    virtual ~State() = default;

    virtual void enter(Game& game) {}
    virtual void update(Game& game) = 0;
    virtual void exit(Game& game) {}
};

// ───────────────────────────────────────────────
// Concrete states
// ───────────────────────────────────────────────
class StartState : public State {
public:
    void enter(Game& game) override;
    void update(Game& game) override;
};

class PlayState : public State {
private:
    Renderer renderer;
    Clock clock{10};

public:
    void enter(Game& game) override;
    void update(Game& game) override;
};

class EndState : public State {
public:
    void enter(Game& game) override;
    void update(Game& game) override;
};
