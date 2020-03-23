#include "character.hpp"

using namespace std;

character::character(string nameIn){
    name = nameIn;

    stats = scores {
        str: 10,
        dex: 10,
        con: 10,
        intel: 10,
        wis: 10,
        cha: 10
    };


}