#pragma once
#include "character.hpp"
#include "skyelib.hpp"

namespace libdungeon {

  class dice {

    public:

      dice(int t_num, int t_sides);

      int roll();

    private :

      int m_num;

      int m_sides;
  };
}
