#include "character.hpp"
#include "iostream"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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
      m_abilities[abil] = 10;
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
      out.crit = NONE;
    }

    out.value +=
      // Is the user proficient in this skill? If so, add their bonus
      ((int) m_proficiencies[t_skill].proficient)*((7 + m_level)/4) +
      // Get the user's ability score mod
      (m_abilities[m_proficiencies[t_skill].score] - 10) / 2;

    return out;

  }

  Character::check Character::rollCheck(skill t_skill, advantage t_advantage){

    if (t_advantage != NEITHER){
      auto first = rollCheck(t_skill);
      auto second = rollCheck(t_skill);
      cout << first.value << endl;
      cout << second.value << endl;


      if (first.crit == SUCCESS){
        cout << "crit" << endl;
        return (t_advantage == ADVANTAGE) ? first : second;
      }
      else if (second.crit == SUCCESS){
        cout << "2crit" << endl;
        return (t_advantage == ADVANTAGE) ? second : first;
      }

      if (first.value > second.value) {
        cout << "1val" << endl;
        return (t_advantage == ADVANTAGE) ? first : second;
      }
      else {
        cout << "2val" << endl;
        return (t_advantage == ADVANTAGE) ? second : first;
      }

    }

    return rollCheck(t_skill);

  }

  void Character::store(string t_path) {

  }

  template<class Archive>
  void Character::serialize(Archive & ar, const unsigned int version) {
        ar & m_name;
        /* ar & m_class; */
        /* ar & m_level; */
        /* ar & skillAbilities; */
        /* ar & m_proficiencies; */
        /* ar & m_attack; */
        /* ar & checkDie; */
    }





}
