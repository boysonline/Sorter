#pragma once

#include "objects.h"
#include "player.h"


class Box : public TypedGameObject, public ISpriteMaker {
protected:
    bool falling = false;
    bool del = false;

public:
    Box(char type, int x, int y);
    virtual ~Box() = default;

    std::string makeSprite(char type) const override;

    virtual void onCollision(Player& player, bool matched) = 0;

    void setToDelete();
    bool toDelete() const;
    bool isFalling() const;

    void move(const int& units);
    void fall();

    bool isOn(const Valve& valve) const;
    bool isOn(const Conveyor& conveyor) const;
};

// all subclasses now share the same sprite logic
class ScoreBox : public Box {
public:
    ScoreBox(int x, int y);
    void onCollision(Player& player, bool matched) override;
};

class NegativeScoreBox : public Box {
public:
    NegativeScoreBox(int x, int y);
    void onCollision(Player& player, bool matched) override;
};

class LifeBox : public Box {
public:
    LifeBox(int x, int y);
    void onCollision(Player& player, bool matched) override;
};
