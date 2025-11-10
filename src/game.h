#pragma once

#include "objects.h"
#include "boxes.h"
#include "renderer.h"

enum class Scene {
	NONE,
	START,
	PLAY,
	END
};

class Game {
private:
    bool running;
    Scene currentScene;
    Score finalScore;
    
public:
    Game();

    void run();
    void runStart();
    void runGameLoop();
    void runEnd();
};
