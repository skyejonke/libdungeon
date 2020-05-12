#pragma once
#include "libdungeon.hpp"
#include "dice.hpp"
#include <string>
#include <map>
#include <fstream>
#include <cereal/types/string.hpp>


namespace libdungeon {

  enum skill {
    ACROBATICS,
    ANIMAL, ARCANA, ATHLETICS, DECEPTION,
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

  enum critical {
    SUCCESS,
    FAILURE,
    NONE
  };

  enum advantage {
    ADVANTAGE,
    DISADVANTAGE,
    NEITHER
  };

  class Character {

    public:

      struct proficiency {
        bool proficient = false;
        int bonus = 0;
        ability score;

        template<class Archive>
        void serialize(Archive & ar) {
          ar (proficient, bonus, score);
        }

      };

      struct check {
        int value;
        critical crit;
      };

      Character();

      Character(std::string t_name,
          std::string t_class,
          int t_level);

      void setProficient(skill t_skill, bool t_proficient);

      void setBonus(skill t_skill, int t_bonus);

      check rollCheck(skill t_skill);

      check rollCheck(skill t_skill, advantage t_advantage);

      proficiency getProficiency(skill t_skill);

      std::string getName();

      void store(std::string t_path);

    private:

      friend class cereal::access;

      template<class Archive>
        void serialize(Archive & ar) {
          ar (m_class, m_level, m_name, m_proficiencies , m_attack, m_abilities, checkDie);
        }


      std::string m_name;

      std::string m_class;

      int m_level;

      const static std::map<skill, ability> skillAbilities;

      std::map<skill, proficiency> m_proficiencies = buildProficiencies();

      std::map<ability, int> m_abilities;

      static std::map<skill, proficiency> buildProficiencies();

      int m_attack;

      Dice checkDie  = Dice (1,20);

  };
}
