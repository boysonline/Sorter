#include "renderer.h"

constexpr int Renderer::getSceneWidth()  { return SCENE_WIDTH; }
constexpr int Renderer::getSceneHeight() { return SCENE_HEIGHT; }

Renderer::Renderer() { clearFrame(); }

void Renderer::clearScreen() { system("cls"); }

void Renderer::render() {
    clearScreen();
    for (int y = 0; y < SCENE_HEIGHT; y++) {
        for (int x = 0; x < SCENE_WIDTH; x++)
            std::cout << frame[y][x];
        std::cout << std::endl;
    }
}

void Renderer::clearFrame() {
    frame = Frame(SCENE_HEIGHT, std::vector<std::string>(SCENE_WIDTH, " "));
}

void Renderer::drawWindow() {
    for (int x = 0; x < SCENE_WIDTH; x++) {
        frame[0][x] = '=';
        frame[SCENE_HEIGHT - 1][x] = '=';
    }

    for (int y = 0; y < SCENE_HEIGHT; y++) {
        frame[y][0] = frame[y][1] = '|';
        frame[y][SCENE_WIDTH - 1] = frame[y][SCENE_WIDTH - 2] = '|';
    }

    frame[0][0] = frame[0][1] = '#';
    frame[0][SCENE_WIDTH - 2] = frame[0][SCENE_WIDTH - 1] = '#';
    frame[SCENE_HEIGHT - 1][0] = frame[SCENE_HEIGHT - 1][1] = '#';
    frame[SCENE_HEIGHT - 1][SCENE_WIDTH - 2] = frame[SCENE_HEIGHT - 1][SCENE_WIDTH - 1] = '#';

    static constexpr int TITLE_X = 30;
    static constexpr int TITLE_Y = 0;
    static constexpr const char*  TITLE_TEXT = "[Sorter.exe]";

    drawObject(GameObject(TITLE_TEXT, TITLE_X, TITLE_Y));
}

void Renderer::drawObject(const GameObject& object) {
    for (int i = 0; i < object.getSpriteLength(); i++)
        frame[object.getY()][object.getSpriteX() + i] = object.getSprite()[i];
}

void Renderer::drawStart() {
    static constexpr const char* MESSAGE_TEXT = "Press any key to play...";
    static constexpr int MESSAGE_X = 10;
    static constexpr int MESSAGE_Y = 3;
    
    clearFrame();
    drawObject(GameObject(MESSAGE_TEXT, MESSAGE_X, MESSAGE_Y));
    drawWindow();
}

void Renderer::drawEnd(const Score& score) {
    static constexpr const char* MESSAGE_TEXT = "Game Over!";
    static constexpr int MESSAGE_X = 3;
    static constexpr int MESSAGE_Y = 1;
    
    clearFrame();
    drawObject(GameObject(MESSAGE_TEXT, MESSAGE_X, MESSAGE_Y));
    drawObject(score);
    drawWindow();
}

void Renderer::drawWorld(const World& world) {
    clearFrame();
    drawObject(world.getConveyor());
    for (const Valve& valve : world.getConveyorValves())
        drawObject(valve);
    for (const auto& box : world.getBoxes())
        drawObject(*box);
    for (const Container& container : world.getContainers())
        drawObject(container);

    drawObject(world.getPlayerLives());
    drawObject(world.getPlayerScore());
    
    drawWindow();
}
