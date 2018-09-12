#include <iostream>
#include <string>
#include "enchantments.h"
#include "ascii_graphics.h"

using namespace std;

Enchantments::Enchantments(string name, int cost, std::string description, Monster *component): Monster(name, cost, description), component{component}{}

Enchantments::~Enchantments(){
  delete this->component;
}

void Enchantments::addComponent(Monster* m){
  component = m;
}

void Enchantments::disenchant() {
  component = nullptr;
}

Monster* Enchantments::getComponent() {
  return component;
}

card_template_t Enchantments::getMonsterTemplate() const{
  if (!this->component->getEffect() && this->getCompDescription() != "SILENCED") {
    return display_minion_no_ability(this->getCompName(), this->getCompCost(), this->getAttack(), this->getDefense());
  } else if (this->component->getTriggerType() == TriggerType::None) {
    return display_minion_activated_ability(this->getCompName(), this->getCompCost(), this->getAttack(), this->getDefense(), this->getEffectCost(), this->getCompDescription());
  } else {
    return display_minion_triggered_ability(this->getCompName(), this->getCompCost(), this->getAttack(), this->getDefense(), this->getCompDescription());
  }
}

