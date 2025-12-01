#pragma once

#include "objects.h"
#include "player.h"
#include "box_factories.h"

#include <vector>
#include <memory>
#include <windows.h>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cstdlib>



class Clock {
private:
    using clock = std::chrono::steady_clock;
    using time_point = std::chrono::time_point<clock>;
    const std::chrono::milliseconds frameTime;
    time_point lastFrame;

public:
    static constexpr int MILLISECONDS_IN_SECOND = 1000;
    Clock(int FPS) : frameTime(MILLISECONDS_IN_SECOND / FPS), lastFrame(clock::now()) {}

    void limitFrameRate() {
        auto now = clock::now();
        auto elapsed = now - lastFrame;
        if (elapsed < frameTime)
            std::this_thread::sleep_for(frameTime - elapsed);
        lastFrame = clock::now();
    }
};



class World {
private:
    static constexpr int CONTAINER_Y = 17;
    static constexpr int FRAMES_BETWEEN_SPAWNS = 20;

    int framesSinceLastSpawn = 0;
    Conveyor conveyor;
    std::vector<Container> containers;
    std::vector<std::unique_ptr<Box>> boxes;
    std::unique_ptr<BoxFactory> factory;
    Player player;
    void moveBox(Box& box);
    void dropBox(Box& box);
    void deleteBoxes();
    void checkBoxCollision(Box& box);
    void moveBoxes();
    void checkPlayerInput();
    void spawnBox();
    bool moveWithConveyor(Box& box);
    bool dropThroughValve(Box& box);

public:
    bool isGameOver() const;
    World();
    void update();
    KeyPress getPlayerInput() const;
    std::vector<Container> getContainers() const;
    const std::vector<std::unique_ptr<Box>>& getBoxes() const;
    Lives getPlayerLives() const;
    Score getPlayerScore() const;
    Conveyor getConveyor() const;
    std::vector<Valve> getConveyorValves() const;
    Player& getPlayer();
    const Player& getPlayer() const;
    const int getFramesBetweenSpawns() const { return FRAMES_BETWEEN_SPAWNS; }
};