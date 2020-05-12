#include "character.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>

#include <cereal/archives/binary.hpp>

using namespace std;
int main() {
  string temp = "hi";
  {
    libdungeon::Character test = libdungeon::Character("Bob", "Barbarian", 5);
    //test.setProficient(libdungeon::skill::HISTORY, true);
    for (int i = 0; i < 20; i++) {
      test.rollCheck(libdungeon::skill::HISTORY, libdungeon::advantage::DISADVANTAGE);
    }

    std::ofstream os("out.cereal");
    cereal::BinaryOutputArchive archive( os );

    archive( test );
  }

  {
  std::ifstream is("out.cereal");

   cereal::BinaryInputArchive iarchive(is);

   libdungeon::Character test2;
   iarchive(test2);

  cout << test2.getName() << endl;

  }

}
