#pragma once

#include "world.h"

#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>

#define Frame std::vector<std::vector<std::string>>

class Renderer {
private:
    static constexpr int SCENE_WIDTH  = 80;
    static constexpr int SCENE_HEIGHT = 20;
    Frame frame;

public:
    Renderer();

    static constexpr int getSceneWidth();
    static constexpr int getSceneHeight();

    static void clearScreen();
    void render();

    void clearFrame();
    void drawWindow();
    void drawObject(const GameObject& object);

    void drawStart();
    void drawWorld(const World& world);
    void drawEnd(const Score& score);
};
