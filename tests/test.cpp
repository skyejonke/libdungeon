#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
#include "character.hpp"

using namespace std;

TEST_CASE("characters work as intended", "[character]"){

  libdungeon::Character test = libdungeon::Character("Test", "Swordsman", 1);

  REQUIRE("Test" == test.getName());

  test.setProficient(libdungeon::skill::ATHLETICS, true);

  REQUIRE(test.getProficiency(libdungeon::skill::ATHLETICS).proficient);


}
