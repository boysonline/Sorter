#include "box_factories.h"

std::unique_ptr<Box> ScoreBoxFactory::createBox(int x, int y) const {
    return std::make_unique<ScoreBox>(x, y);
}

std::unique_ptr<Box> NegativeScoreBoxFactory::createBox(int x, int y) const {
    return std::make_unique<NegativeScoreBox>(x, y);
}

std::unique_ptr<Box> LifeBoxFactory::createBox(int x, int y) const {
    return std::make_unique<LifeBox>(x, y);
}
