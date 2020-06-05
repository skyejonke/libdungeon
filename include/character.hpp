#pragma once
#include "libdungeon.hpp"
#include "dice.hpp"
#include <string>
#include <map>
#include <fstream>
#include <cereal/access.hpp>

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

      // Sets wether or not the character is proficient in a specific
      // skill
      void setProficient(skill t_skill, bool t_proficient);

      // Sets the bonus for a specifcied skill
      void setBonus(skill t_skill, int t_bonus);

      // Rolls a check for a given skill
      [[nodiscard]] check rollCheck(skill t_skill);

      // Rolls a check for a given skill, with a given advantage
      [[nodiscard]] check rollCheck(skill t_skill, advantage t_advantage);

      // Returns the character's proficiency for a skill
      [[nodiscard]] proficiency getProficiency(skill t_skill);

      [[nodiscard]] std::string getName();

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

      // A general map to find the ability score for a given skill
      // (Athletics to Strength, ect)
      const static std::map<skill, ability> skillAbilities;

      // This is just a map of each skill to a character's specific
      // proficiency struct
      std::map<skill, proficiency> m_proficiencies = buildProficiencies();

      // These are ability scores (strength, intelligence, ect)
      std::map<ability, int> m_abilities;

      static std::map<skill, proficiency> buildProficiencies();

      int m_attack;

      Dice checkDie  = Dice (1,20);

  };
}
