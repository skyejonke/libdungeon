#include "character.hpp"
#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;
int main() {
  string temp = "hi";
  libdungeon::Character test = libdungeon::Character("Bob", "Barbarian", 5);
  //test.setProficient(libdungeon::skill::HISTORY, true);
  for (int i = 0; i < 20; i++) {
    test.rollCheck(libdungeon::skill::HISTORY, libdungeon::advantage::DISADVANTAGE).value;
  }

  std::ofstream ofs("archive");
  boost::archive::text_oarchive oa(ofs);

   oa << test;

}
