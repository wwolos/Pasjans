#include <catch2/catch_all.hpp>
#include <Pasjans/command.h>

TEST_CASE("Command constructor with \"k1:k2\""){
    Command command = Command(std::string("k1:k2"));
    REQUIRE(command.isCorrect);
    REQUIRE(command.sourceType == 1);
    REQUIRE(command.destinationType == 1);
    REQUIRE(command.sourceIndex == 0);
    REQUIRE(command.destinationIndex == 1);
    REQUIRE(command.amountOfCards == 1);
    REQUIRE(command.isWasteScroll == false);
}

TEST_CASE("Command constructor with \"k1x5:k2\""){
    Command command = Command("k1x5:k2");
    REQUIRE(command.isCorrect);
    REQUIRE(command.sourceType == 1);
    REQUIRE(command.destinationType == 1);
    REQUIRE(command.sourceIndex == 0);
    REQUIRE(command.destinationIndex == 1);
    REQUIRE(command.amountOfCards == 5);
    REQUIRE(command.isWasteScroll == false);
}

TEST_CASE("Command constructor with \"k1:sk\""){
    Command command = Command("k1:sk");
    REQUIRE(command.isCorrect);
    REQUIRE(command.sourceType == 1);
    REQUIRE(command.destinationType == 2);
    REQUIRE(command.sourceIndex == 0);
    REQUIRE(command.amountOfCards == 1);
    REQUIRE(command.isWasteScroll == false);
}

TEST_CASE("Command constructor with \"sr:k2\""){
    Command command = Command("sr:k2");
    REQUIRE(command.isCorrect);
    REQUIRE(command.sourceType == 2);
    REQUIRE(command.destinationType == 1);
    REQUIRE(command.destinationIndex == 1);
    REQUIRE(command.amountOfCards == 1);
    REQUIRE(command.isWasteScroll == false);
}

TEST_CASE("Command constructor with \"sr:sr\""){
    Command command = Command("sr:sr");
    REQUIRE(command.isCorrect);
    REQUIRE(command.isWasteScroll == true);
}

TEST_CASE("Command constructor with \"k1:k2x5\" (invalid)"){
    Command command = Command("k1:k2x5");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"k15:k2\" (invalid)"){
    Command command = Command("k1:k2x5");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"sk:k2\"  (invalid)"){
    Command command = Command("k1:k2x5");
    REQUIRE(!command.isCorrect);
}