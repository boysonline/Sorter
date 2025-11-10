#include <iostream>
#include <memory>
using namespace std;

class GameState {
public:
    virtual ~GameState() = default;
    virtual void handleRequest() = 0;
    virtual string name() const = 0;
};

class StartState : public GameState {
public:
    void handleRequest() override {}
};

class PlayState : public GameState {
public:
    void handleRequest() override {}
};

class EndState : public GameState {
public:
    void handleRequest() override {}
};

class Game {
private:
    unique_ptr<GameState> state;

public:
    Game() : state(make_unique<StartState>()) {}

    void setState(unique_ptr<GameState> newState) {
        state = move(newState);
    }

    void request() { state->handleRequest(); }
};

