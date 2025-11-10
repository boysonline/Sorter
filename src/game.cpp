#include "Game.h"

Game::Game() {
    running = true;
    currentScene = Scene::START;
}

void Game::run() {
    while (running) {
        switch (currentScene) {
            case Scene::START:
                runStart();
                break;
            case Scene::PLAY:
                runGameLoop();
                break;
            case Scene::END:
                runEnd();
                break;
            default:
                running = false;
        }
    }
}

void Game::runStart() {
    Renderer renderer;
    Player player;
    renderer.drawStart();
    renderer.render();
    while (player.getInput() == KeyPress::NONE);
    currentScene = Scene::PLAY;
}

void Game::runGameLoop() {
    World world;
    Renderer renderer;
    Clock clock(10);

    while (currentScene == Scene::PLAY) {
        if(world.isGameOver()) { 
            finalScore = world.getPlayerScore();
            currentScene = Scene::END; 
            break; 
        }
        world.update();
        renderer.drawWorld(world);
        renderer.render();
        clock.limitFrameRate();
    }
}

void Game::runEnd() {
    Renderer renderer;
    renderer.drawEnd(finalScore);
    renderer.render();

    Player player;
    KeyPress input = KeyPress::NONE;
    while (input == KeyPress::NONE) input = player.getInput();
    if (input == KeyPress::Q) running = false;
    else currentScene = Scene::START;
}