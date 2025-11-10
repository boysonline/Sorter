#include "boxes.h"

Box::Box(char type, int x, int y)
    : TypedGameObject(type, makeSprite(type), x, y) {}

std::string Box::makeSprite(char type) const {
    return "[" + std::string(1, type) + "]";
}

void Box::setToDelete() { del = true; }
bool Box::toDelete() const { return del; }
bool Box::isFalling() const { return falling; }

void Box::move(const int& units) { spriteX += units; hitboxX += units; }
void Box::fall() { falling = true; y += 1; }

bool Box::isOn(const Valve& valve) const {
    bool onTop = (valve.getY() - y == 1);
    int boxLeft = hitboxX;
    int boxRight = hitboxX + getHitboxLength() - 1;
    int valveLeft = valve.getHitboxX();
    int valveRight = valve.getHitboxX() + valve.getHitboxLength() - 1;
    return onTop && (boxLeft >= valveLeft) && (boxRight <= valveRight);
}

bool Box::isOn(const Conveyor& conveyor) const {
    bool onTop = (conveyor.getY() - y == 1);
    int boxLeft = hitboxX;
    int conveyorRight = conveyor.getHitboxX() + conveyor.getHitboxLength() - 1;
    return onTop && (boxLeft <= conveyorRight);
}


ScoreBox::ScoreBox(int x, int y) : Box('+', x, y) {}

void ScoreBox::onCollision(Player& player, bool matched) {
    if (matched) player.gainScore();
    else player.loseLife();
    setToDelete();
}

NegativeScoreBox::NegativeScoreBox(int x, int y) : Box('-', x, y) {}

void NegativeScoreBox::onCollision(Player& player, bool matched) {
    if (matched) player.loseScore();
    else player.loseLife(); 
    setToDelete();
}

LifeBox::LifeBox(int x, int y) : Box('H', x, y) {}

void LifeBox::onCollision(Player& player, bool matched) {
    if (matched) player.restoreLife();
    else player.loseLife(); 
    setToDelete();
}
