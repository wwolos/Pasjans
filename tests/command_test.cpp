#include <Pasjans/command.h>

#include <catch2/catch_all.hpp>

TEST_CASE("Command constructor with \"k1:k2\"") {
    Command command = Command(std::string("k1:k2"));
    REQUIRE(command.isCorrect);
    REQUIRE(command.sourceType == Command::sourceTypes::COLUMN);
    REQUIRE(command.destinationType == Command::destinationTypes::COLUMN);
    REQUIRE(command.sourceIndex == 0);
    REQUIRE(command.destinationIndex == 1);
    REQUIRE(command.amountOfCards == 1);
    REQUIRE(command.isWasteScroll == false);
}

TEST_CASE("Command constructor with \"k1x5:k2\"") {
    Command command = Command("k1x5:k2");
    REQUIRE(command.isCorrect);
    REQUIRE(command.sourceType == Command::sourceTypes::COLUMN);
    REQUIRE(command.destinationType == Command::destinationTypes::COLUMN);
    REQUIRE(command.sourceIndex == 0);
    REQUIRE(command.destinationIndex == 1);
    REQUIRE(command.amountOfCards == 5);
    REQUIRE(command.isWasteScroll == false);
}

TEST_CASE("Command constructor with \"k1:sk\"") {
    Command command = Command("k1:sk");
    REQUIRE(command.isCorrect);
    REQUIRE(command.sourceType == Command::sourceTypes::COLUMN);
    REQUIRE(command.destinationType == Command::destinationTypes::FOUNDATION);
    REQUIRE(command.sourceIndex == 0);
    REQUIRE(command.amountOfCards == 1);
    REQUIRE(command.isWasteScroll == false);
}

TEST_CASE("Command constructor with \"sr:k2\"") {
    Command command = Command("sr:k2");
    REQUIRE(command.isCorrect);
    REQUIRE(command.sourceType == Command::sourceTypes::WASTE);
    REQUIRE(command.destinationType == Command::destinationTypes::COLUMN);
    REQUIRE(command.destinationIndex == 1);
    REQUIRE(command.amountOfCards == 1);
    REQUIRE(command.isWasteScroll == false);
}

TEST_CASE("Command constructor with \"sr:sr\"") {
    Command command = Command("sr:sr");
    REQUIRE(command.isCorrect);
    REQUIRE(command.isWasteScroll == true);
}

TEST_CASE("Command constructor with \"k1:k2x5\" (invalid)") {
    Command command = Command("k1:k2x5");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"k15:k2\" (invalid)") {
    Command command = Command("k15:k2");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"sk:k2\"  (invalid)") {
    Command command = Command("sk:k2");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"k3x-1:k2\"  (invalid)") {
    Command command = Command("k3x-1:k2");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"k1x50:k2\"  (invalid)") {
    Command command = Command("k1x50:k2");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"\"  (invalid)") {
    Command command = Command("");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"abc:xyz\"  (invalid)") {
    Command command = Command("abc:xyz");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"k1k2\"  (invalid)") {
    Command command = Command("k1k2");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"k1::k2\"  (invalid)") {
    Command command = Command("k1::k2");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"k1:sr\"  (invalid)") {
    Command command = Command("k1:sr");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"sk:k1\"  (invalid)") {
    Command command = Command("sk:k1");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"k1x5:xyz\"  (invalid)") {
    Command command = Command("k1x5:xyz");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"k-1:k2\"  (invalid)") {
    Command command = Command("k-1:k2");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"k1x0:k2\"  (invalid)") {
    Command command = Command("k1x0:k2");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"sr:srx1\"  (invalid)") {
    Command command = Command("sr:srx1");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"k1x5:k2#\"  (invalid)") {
    Command command = Command("k1x5:k2#");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Command constructor with \"k1x1000:k2x1000\"  (invalid)") {
    Command command = Command("k1x1000:k2x1000");
    REQUIRE(!command.isCorrect);
}

TEST_CASE("Test efficiency of command") {
    BENCHMARK("Command constructor with \"k1x2:k3\" 1000 times") {
        for (int i = 0; i < 1000; i++) {
            Command command = Command("k1x2:k3");
        }
    };
}
