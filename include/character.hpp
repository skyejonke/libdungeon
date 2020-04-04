#pragma once
#include "libdungeon.hpp"
#include "dice.hpp"
#include <string>
#include <map>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/assume_abstract.hpp>


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
      friend class boost::serialization::access;

      struct proficiency {
        bool proficient = false;
        int bonus = 0;
        ability score;
      };

      struct check {
        int value;
        critical crit;
      };

      Character(std::string t_name,
          std::string t_class,
          int t_level);

      template<class Archive>
        void serialize(Archive & ar, const unsigned int version);

      void setProficient(skill t_skill, bool t_proficient);

      void setBonus(skill t_skill, int t_bonus);

      check rollCheck(skill t_skill);

      check rollCheck(skill t_skill, advantage t_advantage);

      proficiency getProficiency(skill t_skill);

      std::string getName();

      void store(std::string t_path);

    private:

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
