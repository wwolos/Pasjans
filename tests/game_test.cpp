#include <catch2/catch_all.hpp>
#include <Pasjans/game.h>
#include <Pasjans/card.h>

TEST_CASE("Moving more cards than possible from colum to column(invalid)"){
    Game game(true);
    game.tableau = {{Card(4, 0),Card(3, 1), Card(2, 0), Card(1,1)}, {Card(5,1)}, {}, {}, {}, {}, {}};
    game.tableau[0][0].hide();
    REQUIRE(game.processInput("k1x4:k2") != ""); //If command is executed properly, it will return an empty string. In this case the command shouldn't be executed, so it should return a non-empty string
}

TEST_CASE("Moving multiple cards to the foundation(invalid)"){
    Game game(true);
    game.tableau = {{Card(4, 0),Card(3, 1), Card(2, 0), Card(1,1)}, {Card(5,1)}, {}, {}, {}, {}, {}};
    game.tableau[0][0].hide();
    REQUIRE(game.processInput("k1x3:sk") != ""); //If command is executed properly, it will return an empty string. In this case the command shouldn't be executed, so it should return a non-empty string
}

TEST_CASE("Moving 0 cards to the foundation(invalid)"){
    Game game(true);
    game.tableau = {{Card(4, 0),Card(3, 1), Card(2, 0), Card(1,1)}, {Card(5,1)}, {}, {}, {}, {}, {}};
    game.tableau[0][0].hide();
    REQUIRE(game.processInput("k4:sk") != ""); //If command is executed properly, it will return an empty string. In this case the command shouldn't be executed, so it should return a non-empty string
}

TEST_CASE("Moving black cards onto black cards(invalid)"){
    Game game(true);
    game.tableau = {{Card(2,0),Card(1, 1)}, {Card(3,0)}, {}, {}, {}, {}, {}};
    REQUIRE(game.processInput("k1:k2") != ""); //If command is executed properly, it will return an empty string. In this case the command shouldn't be executed, so it should return a non-empty string
}

TEST_CASE("Moving red cards onto red cards(invalid)"){
    Game game(true);
    game.tableau = {{Card(2,1),Card(1, 0)}, {Card(3,1)}, {}, {}, {}, {}, {}};
    game.tableau[0][0].hide();
    REQUIRE(game.processInput("k1:k2") != ""); //If command is executed properly, it will return an empty string. In this case the command shouldn't be executed, so it should return a non-empty string
}

TEST_CASE("Moving card other than Ace to the foundation(invalid)"){
    Game game(true);
    game.tableau = {{Card(10,1)}, {}, {}, {}, {}, {}, {}};
    game.tableau[0][0].hide();
    REQUIRE(game.processInput("k1:sk") != ""); //If command is executed properly, it will return an empty string. In this case the command shouldn't be executed, so it should return a non-empty string
}