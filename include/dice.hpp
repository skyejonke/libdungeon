#pragma once
#include "libdungeon.hpp"
#include "skyelib.hpp"

namespace libdungeon {

  class Dice {

    public:

      Dice();

      Dice(int t_num, int t_sides);

      [[nodiscard]] int roll();

      template<class Archive>
      void serialize(Archive & ar){
        ar (m_num, m_sides);
      }

    private:

      int m_num;

      int m_sides;

  };

}
