#pragma once
#include <boost/random.hpp>
#include <string>

class character {

  public:

    character(std::string nameIn);

    enum skill {
      ACROBATICS,
      ANIMAL,
      ARCANA,
      ATHLETICS,
      DECEPTION,
      HISTORY,
      INSIGHT,
      INTIMIDATION,
      INVESTIGATION,
      MEDICINE,
      NATURE,
      PERCEPTION,
      PERFORMANCE,
      PERSUASION,
      SLEIGHT,
      STEALTH,
      SURVIVAL
    };

    struct proficiences {
      bool proficient;
      int bonus;
    };

    struct scores{
        int str;
        int dex;
        int con;
        int intel;
        int wis;
        int cha;
    };


    character(std::string nameIn, scores statsIn);


  private:

    scores stats;

    std::string name;

};
