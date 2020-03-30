#ifndef CHAR_H
#define CHAR_H
/* #include <boost/random.hpp> */
#include "skyelib.hpp"
#include <string>
#include <map>
#include <memory>

namespace libdungeon {

  extern skyelib::toolkit tools;

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
    RELIGION,
    SLEIGHT,
    STEALTH,
    SURVIVAL
  };

  enum ability {
    STRENGTH,
    DEXTERITY,
    CONSTITUTION,
    INTELLIGENCE,
    WISDOM,
    CHARISMA
  };

  class Character {

    public:

      struct proficiency {
        bool proficient = false;
        int bonus = 0;
        ability score;
      };

      Character(std::string t_name,
          std::string t_class,
          int t_level);
      /* Character(std::string nameIn, scores statsIn); */

      void makeProficient(skill t_skill);

      void setBonus(skill t_skill, int t_bonus);

      int rollCheck(skill t_skill);

      int rollCheck(skill t_skill, bool advantage);

      proficiency getProficiency(skill t_skill);

      std::string getName();

      /* scores getScores(); */

    private:
      std::string m_name;

      std::string m_class;

      int m_level;

      const static std::map<skill, ability> skillAbilities;

      std::map<skill, proficiency> proficiencies = buildProficiencies();

      std::map<ability, int> scores;

      static std::map<skill, proficiency> buildProficiencies();

      int m_attack;


  };
}

#endif
