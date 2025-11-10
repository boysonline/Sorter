#include "objects.h"

GameObject::GameObject(std::string sprite, int spriteX, int y)
    : sprite(std::move(sprite)), spriteX(spriteX), hitboxX(spriteX), y(y) {}

GameObject::GameObject(std::string sprite, int spriteX, int hitboxX, int y)
    : sprite(std::move(sprite)), spriteX(spriteX), hitboxX(hitboxX), y(y) {}

int GameObject::getSpriteX() const { return spriteX; }
void GameObject::setSpriteX(int x) { spriteX = x; }

int GameObject::getHitboxX() const { return hitboxX; }
void GameObject::setHitboxX(int x) { hitboxX = x; }

int GameObject::getY() const { return y; }
void GameObject::setY(int y) { this->y = y; }

std::string GameObject::getSprite() const { return sprite; }
void GameObject::setSprite(std::string sprite) { this->sprite = sprite; }

bool GameObject::collidesWith(const GameObject& other) const {
    int leftA = hitboxX;
    int rightA = hitboxX + getHitboxLength() - 1;
    int leftB = other.getHitboxX();
    int rightB = other.getHitboxX() + other.getHitboxLength() - 1;
    return (y == other.getY()) && (rightA >= leftB) && (leftA <= rightB);
}

int GameObject::getSpriteLength() const { return sprite.size(); }
int GameObject::getHitboxLength() const { return sprite.size(); }



Score::Score() : GameObject(makeSprite(STARTING_SCORE), X, Y) {
    score = STARTING_SCORE;
}

void Score::gain() {
    score++;
    sprite = makeSprite(score);
}

void Score::lose() {
    if (score > STARTING_SCORE) score--;
    sprite = makeSprite(score);
}

std::string Score::makeSprite(char score) const {
    return "Score: " + std::to_string(score);
}



std::string Lives::makeSprite(char lives) const {
    std::string s;
    for (int i = lives; i < STARTING_LIVES; i++) s += "[ ]";
    for (int i = 0; i < lives; i++) s += "[O]";
    return s;
}

Lives::Lives() : GameObject(makeSprite(STARTING_LIVES), X, Y) { lives = STARTING_LIVES; }

void Lives::lose() {
    lives--;
    sprite = makeSprite(lives);
}

void Lives::restore() {
    if (lives < STARTING_LIVES) lives++;
    sprite = makeSprite(lives);
}



constexpr const char* Valve::getOpenSprite() { return OPEN_SPRITE; }
constexpr const char* Valve::getClosedSprite() { return CLOSED_SPRITE; }

Valve::Valve(int spriteX, int hitboxX, int y)
    : GameObject("", spriteX, hitboxX, y), open_(false) {
    close();
}

bool Valve::isOpen() const { return open_; }

void Valve::open() {
    open_ = true;
    sprite = OPEN_SPRITE;
}

void Valve::close() {
    open_ = false;
    sprite = CLOSED_SPRITE;
}

int Valve::getHitboxLength() const { return HITBOX_LENGTH; }



TypedGameObject::TypedGameObject(char type, std::string sprite, int x, int y)
    : GameObject(std::move(sprite), x, y), type(type) {}

char TypedGameObject::getType() const { return type; }
void TypedGameObject::setType(char t) { type = t; }
bool TypedGameObject::matches(const TypedGameObject& other) const {
    return type == other.getType();
}



Container::Container(char type, int x, int y)
    : TypedGameObject(type, makeSprite(type), x, y) {}

std::string Container::makeSprite(char type) const {
    return std::string("##") + char(type) + "##";
}



Conveyor::Conveyor()
    : GameObject(SPRITE, X, Y), speed(STARTING_SPEED) {
    valves = { Valve(VALVE1_SPRITE_X, VALVE1_HITBOX_X, VALVE1_Y),
               Valve(VALVE2_SPRITE_X, VALVE2_HITBOX_X, VALVE2_Y),
               Valve(VALVE3_SPRITE_X, VALVE3_HITBOX_X, VALVE3_Y) };
}

int Conveyor::getSpeed() const { return speed; }

std::vector<Valve> Conveyor::getValves() const { return valves; }

void Conveyor::toggleValve(int valveNumber) {
    int valveIndex = valveNumber - 1;
    Valve& valve = valves[valveIndex];
    valve.isOpen() ? valve.close() : valve.open();
}
