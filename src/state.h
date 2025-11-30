#pragma once

#include "objects.h"
#include "boxes.h"
#include "renderer.h"

class Game;

class GameState {
protected:
    Renderer renderer;
    Game& game;

public:
    GameState(Game& game) : game(game) {}
    virtual ~GameState() = default;

    virtual void advanceState() const = 0;
    virtual void update() = 0;
};

class StartState : public GameState {
private:
    Player player;

public:
    StartState(Game& game) : GameState(game) {}

    void advanceState() const override;
    void update() override;
};

class PlayState : public GameState {
private:
    World world;
    Clock clock;

public:
    PlayState(Game& game) : GameState(game), clock(10) {}

    void advanceState() const override;
    void update() override;
};

class EndState : public GameState {
private:
    Player player;

public:
    EndState(Game& game) : GameState(game) {}

    void advanceState() const override;
    void update() override;
};

class Game {
private:
    GameState* state;

    StartState* startState;
    PlayState*  playState;
    EndState*   endState;

    Score finalScore;
    bool running = true;

public:
    Game();
    ~Game();

    void setState(GameState& newState) { state = &newState; }

    StartState& getStartState() { return *startState; }
    PlayState&  getPlayState()  { return *playState; }
    EndState&   getEndState()   { return *endState; }

    Score& getFinalScore() { return finalScore; }
    void setFinalScore(Score score) { finalScore = score; }

    void stop() { running = false; }
    void run() { while (running) state->update(); }
};

inline void StartState::advanceState() const { game.setState(game.getPlayState()); }
inline void StartState::update() {
    renderer.drawStart();
    renderer.render();
    while (player.getInput() == KeyPress::NONE);
    advanceState();   
}

inline void PlayState::advanceState() const { game.setState(game.getEndState()); }
inline void PlayState::update() {
    while (true) {
        if (world.isGameOver()) {
            game.setFinalScore(world.getPlayerScore());
            advanceState();
            break;
        }
        world.update();
        renderer.drawWorld(world);
        renderer.render();
        clock.limitFrameRate();
    }
}

inline void EndState::advanceState() const { game.setState(game.getStartState()); }
inline void EndState::update() {
    renderer.drawEnd(game.getFinalScore());
    renderer.render();

    KeyPress input = KeyPress::NONE;
    while (input == KeyPress::NONE) input = player.getInput();

    if (input == KeyPress::Q) game.stop();
    else advanceState();
}

inline Game::Game() {
    startState = new StartState(*this);
    playState  = new PlayState(*this);
    endState   = new EndState(*this);
    state = startState;
}

inline Game::~Game() {
    delete startState;
    delete playState;
    delete endState;
}