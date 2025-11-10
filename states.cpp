#include "game.h"
#include "states.h"

Game::Game() {
    currentState = std::make_unique<StartState>();
}

void Game::run() {
    while (running) {
        currentState->update(*this);
    }
}

void Game::changeState(std::unique_ptr<State> newState) {
    currentState->exit(*this);
    currentState = std::move(newState);
    currentState->enter(*this);
}

void Game::stop() {
    running = false;
}
