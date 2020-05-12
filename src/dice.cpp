#include "dice.hpp"

using namespace std;

namespace libdungeon {

  // Creates a basic d20
  Dice::Dice() {
    m_num = 1;
    m_sides = 20;
  }

  Dice::Dice(int t_num, int t_sides){
    m_num = t_num;
    m_sides = t_sides;
  }

  int Dice::roll(){

    int out = 0;

    for (int i = 0; i < m_num; i++){
      out += tools.getRand(0,m_sides);
    }

    return out;

  }
}
