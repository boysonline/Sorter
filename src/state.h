#include <iostream>
#include <memory>
#include <renderer.h>

class GameState {
private:
    Renderer renderer;
public:
    virtual ~GameState() = default;
    virtual void advance(Game& game) const = 0;
    virtual void draw() = 0;
    void render() { renderer.render(); }
    virtual void checkForInput() = 0;
};

class StartState : public GameState {
public:
    void advance(Game& game) const override {
        game.setState(std::make_unique<PlayState>());
    }
    void draw() {

    }
    void checkForInput() {

    }
    
};

class PlayState : public GameState {
private:
    World world;
public:
    void advance(Game& game) const override {
        game.setState(std::make_unique<EndState>());
    }
    virtual void update() {};
    void draw() {

    }
    void checkForInput() {
        
    }
};

class EndState : public GameState {
public:
    void advance(Game& game) const override {
        game.setState(std::make_unique<EndState>());
    }
    void draw() {

    }
    void checkForInput() {
        
    }
};

class Game {
private:
    std::unique_ptr<GameState> state;

public:
    Game() : state(std::make_unique<StartState>()) {}

    void setState(std::unique_ptr<GameState> state) {
        this->state = std::move(state);
    }

    void advanceState() { state->advance(*this); }

    void checkForPlayerInput() {
        
    }

    void drawAndRender() {
        state->draw();
        state->render();
    }
};

