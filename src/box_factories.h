#pragma once

#include "boxes.h"

#include <memory>

class BoxFactory {
public:
    virtual ~BoxFactory() = default;

    virtual std::unique_ptr<Box> createBox(int x, int y) const = 0;
};

class ScoreBoxFactory : public BoxFactory {
public:
    std::unique_ptr<Box> createBox(int x, int y) const override;
};

class NegativeScoreBoxFactory : public BoxFactory {
public:
    std::unique_ptr<Box> createBox(int x, int y) const override;
};

class LifeBoxFactory : public BoxFactory {
public:
    std::unique_ptr<Box> createBox(int x, int y) const override;
};
