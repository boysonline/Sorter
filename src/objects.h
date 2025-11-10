#pragma once

#include <string>     
#include <vector> 

class GameObject {
protected:
    std::string sprite;
    int spriteX;
    int hitboxX;
    int y;

public:
    GameObject(std::string sprite, int spriteX, int y);
    GameObject(std::string sprite, int spriteX, int hitboxX, int y);
    virtual ~GameObject() = default;

    int getSpriteX() const;
    void setSpriteX(int x);

    int getHitboxX() const;
    void setHitboxX(int x);

    int getY() const;
    void setY(int y);

    std::string getSprite() const;
    void setSprite(std::string sprite);

    virtual int getHitboxLength() const;
    virtual int getSpriteLength() const;

    bool collidesWith(const GameObject& other) const;
};

struct ISpriteMaker {
    virtual ~ISpriteMaker() = default;
    virtual std::string makeSprite(char value) const = 0;
};

class Score : public GameObject, public ISpriteMaker {
private:
    static constexpr int STARTING_SCORE = 0;
    static constexpr int X = 3;
    static constexpr int Y = 3;

    virtual std::string makeSprite(char score) const override;
    int score = 0;

public:
    Score();
    int get() const { return score; }
    void gain();
    void lose();
};

class Lives : public GameObject, public ISpriteMaker {
private:
    static constexpr int STARTING_LIVES = 4;
    static constexpr int X = 65;
    static constexpr int Y = 3;

    int lives;
    virtual std::string makeSprite(char lives) const override;

public:
    Lives();
    int get() const { return lives; }
    void lose();
    void restore();
};

class Valve : public GameObject {
private:
    static constexpr const char* OPEN_SPRITE   = "*\\   /*";
    static constexpr const char* CLOSED_SPRITE = "*=====*";
    static constexpr int HITBOX_LENGTH = 3;

    bool open_;

public:
    static constexpr const char* getOpenSprite();
    static constexpr const char* getClosedSprite();

    int getSpriteX() const;
    bool isOpen() const;
    int getHitboxLength() const override;

    Valve(int spriteX, int hitboxX, int y);

    void open();
    void close();
};

class TypedGameObject : public GameObject {
protected:
    char type;

public:
    TypedGameObject(char type, std::string sprite, int x, int y);

    char getType() const;
    void setType(char type);
    bool matches(const TypedGameObject& other) const;
};

class Container : public TypedGameObject, public ISpriteMaker {
public:
    Container(char type, int x, int y);
    virtual std::string makeSprite(char type) const override;
};

class Conveyor : public GameObject {
private:
    static constexpr int STARTING_SPEED = 1;
    static constexpr const char* SPRITE = "======================================================================";
    static constexpr int X = 0;
    static constexpr int Y = 10;

    static constexpr int VALVE1_HITBOX_X = 20;
    static constexpr int VALVE1_Y = Y;
    static constexpr int VALVE1_SPRITE_X = VALVE1_HITBOX_X - 2;
    
    static constexpr int VALVE2_HITBOX_X = 40;
    static constexpr int VALVE2_Y = Y;
    static constexpr int VALVE2_SPRITE_X = VALVE2_HITBOX_X - 2;
    
    static constexpr int VALVE3_HITBOX_X = 60;
    static constexpr int VALVE3_Y = Y;
    static constexpr int VALVE3_SPRITE_X = VALVE3_HITBOX_X - 2;
    
    int speed;
    std::vector<Valve> valves;

public:
    Conveyor();

    int getSpeed() const;
    std::vector<Valve> getValves() const;

    void toggleValve(int valveNumber);
};
