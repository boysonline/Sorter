#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "../src/state.h"

TEST_CASE("Player score system works") {
    Player player;

    REQUIRE(player.getScore().get() == player.getStartingScore());
    player.gainScore();
    REQUIRE(player.getScore().get() == player.getStartingScore() + 1);
    player.loseScore();
    REQUIRE(player.getScore().get() == player.getStartingScore());
}

TEST_CASE("Player lives system works") {
    Player player;

    REQUIRE(player.getLives().get() == player.getStartingLives());
    player.loseLife();
    REQUIRE(player.getLives().get() == player.getStartingLives() - 1);
    player.restoreLife();
    REQUIRE(player.getLives().get() == player.getStartingLives());
}

TEST_CASE("Player death detection works") {
    Player player;

    REQUIRE(!player.isDead());
    while (player.getLives().get() > 0) { player.loseLife(); }
    REQUIRE(player.isDead());
}

TEST_CASE("ScoreBox adds score on-hit") {
    Player player;
    ScoreBox box(5, 5);

    box.onCollision(player, true);

    REQUIRE(player.getScore().get() == 1);
    REQUIRE(box.toDelete());
}

TEST_CASE("NegativeScoreBox removes score on-hit") {
    Player player;
    player.gainScore();

    NegativeScoreBox box(5, 5);
    box.onCollision(player, true);

    REQUIRE(player.getScore().get() == 0);
    REQUIRE(box.toDelete());
}

TEST_CASE("LifeBox restores life on-hit") {
    Player player;
    REQUIRE(player.getLives().get() == player.getStartingLives());

    player.loseLife();      
    REQUIRE(player.getLives().get() == player.getStartingLives() - 1);

    LifeBox box(5, 5);
    box.onCollision(player, true);

    REQUIRE(player.getLives().get() == player.getStartingLives());
}

TEST_CASE("World spawns boxes automatically through update()") {
    World world;

    int frames = world.getFramesBetweenSpawns();

    for (int i = 0; i <= frames; i++) { world.update(); }

    REQUIRE(world.getBoxes().size() == 1);
}

TEST_CASE("Box move and get flaged for delete") {
    ScoreBox box(5, 5);

    REQUIRE(!box.isFalling());
    box.fall();
    REQUIRE(box.isFalling());

    int oldX = box.getHitboxX();
    box.move(5);
    REQUIRE(box.getHitboxX() == oldX + 5);

    box.setToDelete();
    REQUIRE(box.toDelete());
}

TEST_CASE("World deletes boxes flaged for deletion") {
    World world;

    for (int i = 0; i < 25; i++)
        world.update();

    REQUIRE(world.getBoxes().size() >= 1);

    world.getBoxes()[0]->setToDelete();
    world.update();

    REQUIRE(world.getBoxes().empty());
}
TEST_CASE("World detects game over when player lost") {
    World world;

    REQUIRE(world.isGameOver() == false);
    Player& player = world.getPlayer();

    while (player.getLives().get() > 0) { player.loseLife(); }

    REQUIRE(player.isDead() == true);
    REQUIRE(world.isGameOver() == true);
}
