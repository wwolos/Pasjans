#include <catch2/catch_all.hpp>
#include <Pasjans/card.h>

TEST_CASE("Card constructor") {
    Card card(0, 0);
    REQUIRE(card.rank == 0);
    REQUIRE(card.suit == 0);
    REQUIRE(card.text == "A");
}

TEST_CASE("Card constructor with rank and suit") {
    Card card(5, 2);
    REQUIRE(card.rank == 5);
    REQUIRE(card.suit == 2);
    REQUIRE(card.text == "6");
}

TEST_CASE("Card show method") {
    Card card(0, 0);
    card.show();
    REQUIRE(card.text == "A");
    REQUIRE(card.isHidden == false);
}

TEST_CASE("Card hide method") {
    Card card(0, 0);
    card.hide();
    REQUIRE(card.text == "XX ");
    REQUIRE(card.isHidden == true);
}
