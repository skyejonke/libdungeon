#include "character.hpp"
#include "iostream"
#include <cereal/archives/binary.hpp>

using namespace std;

namespace libdungeon {

  //Generic constructor
  Character::Character() {
    m_name = "Venfae";
    m_class = "Barbarian";
    m_level = 1;
    for (int it = STRENGTH; it != CHARISMA + 1 ; it++ ){
      ability abil = static_cast<ability>(it);
      m_abilities[abil] = 10;
    }
  }
  //
  Character::Character(string t_name, string t_class, int t_level){
    m_name = t_name;
    m_class = t_class;
    m_level = t_level;

    // Go through each ability, and set the score to 10
    for (int it = STRENGTH; it != CHARISMA + 1 ; it++ ){
      ability abil = static_cast<ability>(it);
      m_abilities[abil] = 10;
    }
  }

  // This builds the character's proficiency list.
  std::map<skill, Character::proficiency> Character::buildProficiencies(){
    map<skill, Character::proficiency> out;
    for (auto it = skillAbilities.begin();
        it != skillAbilities.end();
        ++it){
      Character::proficiency prof {};
      prof.score = it->second;
      out[it->first] = prof;
    }
    return out;
  }

  // Sets a character's proficiency
  void Character::setProficient(skill t_skill, bool t_proficient){
    m_proficiencies[t_skill].proficient = t_proficient;
  }

  void Character::setBonus(skill t_skill, int t_bonus){
    m_proficiencies[t_skill].bonus = t_bonus;
  }

  Character::proficiency Character::getProficiency(skill t_skill){
    return m_proficiencies[t_skill];
  }

  string Character::getName() {
    return m_name;
  }

  Character::check Character::rollCheck(skill t_skill) {
    Character::check out {};
    out.value = checkDie.roll();

    if (out.value == 20){
      out.crit = SUCCESS;
    }
    else if (out.value == 1){
      out.crit = FAILURE;
    }

    else {
      out.crit = NOCRIT;
    }

    if (t_skill != skill::NONE) {
      out.value +=
        // Is the user proficient in this skill? If so, add their bonus
        ((int) m_proficiencies[t_skill].proficient)*((7 + m_level)/4) +
        // Get the user's ability score mod
        (m_abilities[m_proficiencies[t_skill].score] - 10) / 2;
    }

    return out;

  }

  Character::check Character::rollCheck(ability t_ability) {
    Character::check out {};
    out.value = checkDie.roll();

    if (out.value == 20){
      out.crit = SUCCESS;
    }
    else if (out.value == 1){
      out.crit = FAILURE;
    }

    else {
      out.crit = NOCRIT;
    }

    out.value +=
      // Get the user's ability score mod
      (m_abilities[t_ability] - 10) / 2;

    return out;
  }




    Character::check Character::rollCheck(skill t_skill, advantage t_advantage){

      if (t_advantage != NEITHER){
        auto first = rollCheck(t_skill);
        auto second = rollCheck(t_skill);

        if (first.crit == SUCCESS){
          return (t_advantage == ADVANTAGE) ? first : second;
        }
        else if (second.crit == SUCCESS){
          return (t_advantage == ADVANTAGE) ? second : first;
        }

        if (first.value > second.value) {
          return (t_advantage == ADVANTAGE) ? first : second;
        }
        else {
          return (t_advantage == ADVANTAGE) ? second : first;
        }

      }

      return rollCheck(t_skill);

    }

    Character::check Character::rollCheck(ability t_ability, advantage t_advantage){

      if (t_advantage != NEITHER){
        auto first = rollCheck(t_ability);
        auto second = rollCheck(t_ability);

        if (first.crit == SUCCESS){
          return (t_advantage == ADVANTAGE) ? first : second;
        }
        else if (second.crit == SUCCESS){
          return (t_advantage == ADVANTAGE) ? second : first;
        }

        if (first.value > second.value) {
          return (t_advantage == ADVANTAGE) ? first : second;
        }
        else {
          return (t_advantage == ADVANTAGE) ? second : first;
        }

      }

      return rollCheck(t_ability);

    }

  }
