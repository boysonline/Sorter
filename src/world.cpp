#include "world.h"

// WORLD

Player World::getPlayer() const { return player; }

KeyPress World::getPlayerInput() const { return getPlayer().getInput(); }

Lives World::getPlayerLives() const { return getPlayer().getLives(); }

Score World::getPlayerScore() const { return getPlayer().getScore(); }

std::vector<Container> World::getContainers() const { return containers; }

const std::vector<std::unique_ptr<Box>>& World::getBoxes() const { return boxes; }

Conveyor World::getConveyor() const { return conveyor; }

std::vector<Valve> World::getConveyorValves() const { return conveyor.getValves(); }

World::World() {
    containers = {
        Container('H', conveyor.getValves()[0].getHitboxX() - 1, CONTAINER_Y),
        Container('+', conveyor.getValves()[1].getHitboxX() - 1, CONTAINER_Y),
        Container('-', conveyor.getValves()[2].getHitboxX() - 1, CONTAINER_Y),
        Container('X', conveyor.getSpriteLength() + 1, CONTAINER_Y)
    };
}

void World::spawnBox() {
    static constexpr int BOX_SPAWN_X = 0;
    static constexpr int BOX_SPAWN_Y = 9;

    if (framesSinceLastSpawn < FRAMES_BETWEEN_SPAWNS) framesSinceLastSpawn++;
    else {
        int r = rand() % 3;
        switch (r) {
            case 0: factory = std::make_unique<ScoreBoxFactory>(); break;
            case 1: factory = std::make_unique<NegativeScoreBoxFactory>(); break;
            case 2: factory = std::make_unique<LifeBoxFactory>(); break;
        }
        boxes.push_back(factory->createBox(BOX_SPAWN_X, BOX_SPAWN_Y));
        framesSinceLastSpawn = 0;
    }
}

void World::moveBox(Box& box) {
    box.move(conveyor.getSpeed());
}

void World::dropBox(Box& box) {
    box.fall();
}

void World::deleteBoxes() {
    boxes.erase(
        std::remove_if(
            boxes.begin(),
            boxes.end(),
            [](const std::unique_ptr<Box>& b) { return b->toDelete(); }
        ),
        boxes.end()
    );
}

void World::checkBoxCollision(Box& box) {
    for (Container& container : containers) {
        if (box.collidesWith(container)) {
            box.onCollision(player, box.matches(container)); break;
        }
    }
}

bool World::dropThroughValve(Box& box) {
    if (!box.isOn(conveyor)) return false;

    for (Valve& valve : conveyor.getValves()) {
        if (box.isOn(valve) && valve.isOpen()) {
            dropBox(box);
            return true; // handled
        }
    }
    return false;
}

bool World::moveWithConveyor(Box& box) {
    if (box.isOn(conveyor)) {
        box.move(conveyor.getSpeed());
        return true;
    }
    return false;
}

void World::moveBoxes() {
    for (auto& boxPtr : boxes) {
        Box& box = *boxPtr;

        if (dropThroughValve(box)) continue; 
        if (moveWithConveyor(box)) continue; 
        dropBox(box);                              
        
        checkBoxCollision(box);
    }
    deleteBoxes();
}

void World::checkPlayerInput() {
    KeyPress input = player.getInput();
    switch (input) {
        case KeyPress::ONE:   conveyor.toggleValve(1); break;
        case KeyPress::TWO:   conveyor.toggleValve(2); break;
        case KeyPress::THREE: conveyor.toggleValve(3); break;
        default: break;
    }
}

bool World::isGameOver() const { return player.isDead(); }

void World::update() {
    checkPlayerInput();
    moveBoxes();
    spawnBox();
}