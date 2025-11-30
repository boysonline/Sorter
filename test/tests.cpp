#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "../src/state.h"

TEST_CASE("ScoreBox adds score when matched") {
    Player p;
    ScoreBox b(5, 5);

    b.onCollision(p, true);

    REQUIRE(p.getScore().get() == 1);
    REQUIRE(b.toDelete());
}

TEST_CASE("NegativeScoreBox removes score when matched") {
    Player p;
    p.gainScore();

    NegativeScoreBox b(5, 5);
    b.onCollision(p, true);

    REQUIRE(p.getScore().get() == 0);
    REQUIRE(b.toDelete());
}

TEST_CASE("LifeBox restores life when matched") {
    Player p;
    REQUIRE(p.getLives().get() == 4);

    p.loseLife();      // now at 3
    REQUIRE(p.getLives().get() == 3);

    LifeBox b(5, 5);
    b.onCollision(p, true);

    REQUIRE(p.getLives().get() == 4);
}

TEST_CASE("Box movement and deletion flags work") {
    ScoreBox b(5, 5);

    REQUIRE(!b.isFalling());
    b.fall();
    REQUIRE(b.isFalling());

    int oldX = b.getHitboxX();
    b.move(5);
    REQUIRE(b.getHitboxX() == oldX + 5);

    b.setToDelete();
    REQUIRE(b.toDelete());
}

TEST_CASE("Player score system works") {
    Player p;

    REQUIRE(p.getScore().get() == 0);
    p.gainScore();
    REQUIRE(p.getScore().get() == 1);
    p.loseScore();
    REQUIRE(p.getScore().get() == 0);
}

TEST_CASE("Player lives system works") {
    Player p;

    REQUIRE(p.getLives().get() == 4);
    p.loseLife();
    REQUIRE(p.getLives().get() == 3);
    p.restoreLife();
    REQUIRE(p.getLives().get() == 4);
}

TEST_CASE("Player death detection works") {
    Player p;

    REQUIRE(!p.isDead());
    p.loseLife(); // 3
    p.loseLife(); // 2
    p.loseLife(); // 1
    p.loseLife(); // 0
    REQUIRE(p.isDead());
}

TEST_CASE("World spawns boxes automatically through update()") {
    World w;

    for (int i = 0; i < 25; i++)
        w.update();

    REQUIRE(w.getBoxes().size() >= 1);
}

TEST_CASE("World deletes boxes marked for deletion") {
    World w;

    for (int i = 0; i < 25; i++)
        w.update();

    REQUIRE(w.getBoxes().size() >= 1);

    w.getBoxes()[0]->setToDelete();
    w.update();

    REQUIRE(w.getBoxes().empty());
}
TEST_CASE("World detects game over when player loses all lives") {
    World w;

    REQUIRE(w.isGameOver() == false);
    Player& p = w.getPlayer();

    p.loseLife();  // 3
    p.loseLife();  // 2
    p.loseLife();  // 1
    p.loseLife();  // 0

    REQUIRE(p.isDead() == true);
    REQUIRE(w.isGameOver() == true);
}
