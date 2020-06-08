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
    SURVIVAL,
    NONE
  };

  const static std::map<skill, std::string> skillNames {

    {skill::ACROBATICS, "Acrobatics"},
    {skill::ANIMAL, "Animal Handling"},
    {skill::ARCANA, "Arcana"},
    {skill::ATHLETICS, "Athletics"},
    {skill::DECEPTION, "Deception"},
    {skill::HISTORY, "History"},
    {skill::INSIGHT, "Insight"},
    {skill::INTIMIDATION, "Intimidation"},
    {skill::INVESTIGATION, "Investigation"},
    {skill::MEDICINE, "Medicine"},
    {skill::NATURE, "Nature"},
    {skill::PERCEPTION, "Perception"},
    {skill::PERFORMANCE, "Performance"},
    {skill::PERSUASION, "Persuasion"},
    {skill::RELIGION, "Relgion"},
    {skill::SLEIGHT, "Sleight of Hand"},
    {skill::STEALTH, "Stealth"},
    {skill::SURVIVAL, "Survival"},
    {skill::NONE, "None"}

  };

  enum ability {
    STRENGTH,
    DEXTERITY,
    CONSTITUTION,
    INTELLIGENCE,
    WISDOM,
    CHARISMA,
    NOT
  };

  const static std::map<ability, std::string> abilityNames {
    {ability::STRENGTH, "Strength"},
      {ability::DEXTERITY, "Dexterity"},
      {ability::CONSTITUTION, "Constitution"},
      {ability::INTELLIGENCE, "Intelligence"},
      {ability::WISDOM, "Wisdom"},
      {ability::CHARISMA, "Charisma"},
      {ability::NOT, "None"}
  };


  // A general map to find the ability score for a given skill
  // (Athletics to Strength, ect)
  const static std::map<skill, ability> skillAbilities = {
    {ACROBATICS, DEXTERITY},
    {ANIMAL, WISDOM},
    {ARCANA, INTELLIGENCE},
    {ATHLETICS, STRENGTH},
    {DECEPTION, CHARISMA},
    {HISTORY, INTELLIGENCE},
    {INSIGHT, WISDOM},
    {INTIMIDATION, CHARISMA},
    {INVESTIGATION, INTELLIGENCE},
    {MEDICINE, WISDOM},
    {NATURE, INTELLIGENCE},
    {PERCEPTION, WISDOM},
    {PERFORMANCE, CHARISMA},
    {PERSUASION, CHARISMA},
    {RELIGION, INTELLIGENCE},
    {SLEIGHT, DEXTERITY},
    {STEALTH, DEXTERITY},
    {SURVIVAL, WISDOM},
    {NONE, NOT}
  };


  enum critical {
    SUCCESS,
    FAILURE,
    NOCRIT
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
      check rollCheck(skill t_skill);

      check rollCheck(ability t_ability);

      // Rolls a check for a given skill, with a given advantage
      check rollCheck(skill t_skill, advantage t_advantage);

      check rollCheck(ability t_ability, advantage t_advantage);

      // Returns the character's proficiency for a skill
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
