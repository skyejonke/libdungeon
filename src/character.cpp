#include "character.hpp"

using namespace std;

namespace libdungeon {

  //Generic constructor
  Character::Character(string t_name, string t_class, int t_level){
    m_name = t_name;
    m_class = t_class;
    m_level = t_level;


    // Go through each ability, and set the score to 10
    for (int it = STRENGTH; it != CHARISMA + 1 ; it++ ){
      ability abil = static_cast<ability>(it);
      scores[abil] = 10;
    }
  }

  // A map of which skills use which ability scores
  const map<skill, ability> Character::skillAbilities = {
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
    {SURVIVAL, WISDOM}
  };

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
  void Character::makeProficient(skill t_skill){
    proficiencies[t_skill].proficient = true;
  }

  void Character::setBonus(skill t_skill, int t_bonus){
    proficiencies[t_skill].bonus = t_bonus;
  }

  Character::proficiency Character::getProficiency(skill t_skill){
    return proficiencies[t_skill];
  }

  string Character::getName() {
    return m_name;
  }

}
