#include <string>
#include "baseMonster.h"
#include "owner.h"
#include "ascii_graphics.h"

using namespace std;

BaseMonster::BaseMonster(string name, int cost, string description, int att, int def, TriggerType t,Effect *e, int effectCost): Monster(name, cost, description), attack{att}, defense{def}, Trigger{t}, effect{e}, effectCost{effectCost}, hasAttacked{false}{}

BaseMonster::~BaseMonster() {
  delete effect;
}

//Copy Constructor
BaseMonster::BaseMonster(const BaseMonster &other) : Monster(other), attack{other.attack}, defense{other.defense}, Trigger{other.Trigger}, effectCost{other.effectCost}, hasAttacked{other.hasAttacked}{
  if (other.effect) {
    Effect* temp = other.effect->copyCtor();
    effect = temp;
  } else {
    effect = nullptr;
  }
}

//Move Constructor
BaseMonster::BaseMonster(BaseMonster &&other) : Monster(other), attack{other.attack}, defense{other.defense}, Trigger{other.Trigger}, effect{other.effect}, effectCost{other.effectCost}, hasAttacked{other.hasAttacked}{
  other.effect = nullptr;
}

//Copy Assignment Operator
BaseMonster &BaseMonster::operator=(const BaseMonster &other) {
  if(this == &other) return *this;

  BaseMonster temp = other; //calls deep copy constructor
  swap(attack, temp.attack);
  swap(defense, temp.defense);
  swap(Trigger, temp.Trigger);
  swap(effect, temp.effect);
  swap(effectCost, temp.effectCost);
  swap(hasAttacked, temp.hasAttacked);
  return *this;
}

//Move Assignment Operator
BaseMonster &BaseMonster::operator=(BaseMonster &&other) {
  swap(attack, other.attack);
  swap(defense, other.defense);
  swap(Trigger, other.Trigger);
  swap(effect, other.effect);
  swap(effectCost, other.effectCost);
  swap(hasAttacked, other.hasAttacked);
  return *this;
}

string BaseMonster::getCompName() const {
  return Card::getName();
}

int BaseMonster::getCompCost() const {
  return Card::getCost();
}

string BaseMonster::getCompDescription() const {
  return Card::getDescription();
}


void BaseMonster::notify(Owner* me, Owner* opponent, string &event) {
  if(this->effect) this->effect->activate(me, opponent);
}

void BaseMonster::notify(Owner* me, Owner* opponent, int fieldIndex, int whoSummon) {
  if(this->effect){
    if (whoSummon == 1) {
      this->effect->activate(fieldIndex, me);
    } else {
      this->effect->activate(fieldIndex, opponent);
    }
  }
}

void BaseMonster::disenchant() {
  throw string("NoEnchantment");
}

void BaseMonster::play(Owner* me, Owner* opponent) {
  BaseMonster* temp = new BaseMonster(*this);
  me->summon(temp);
}

void BaseMonster::play(int fieldIndex, Owner* player){
  throw string("NoNeedIndex");
}

void BaseMonster::changeHasAttacked(bool hasAttacked){
  this->hasAttacked = hasAttacked;
}

bool BaseMonster::getHasAttacked() const{
  return this->hasAttacked;
}

int BaseMonster::getAttack() const{
  return this->attack;
}

int BaseMonster::getDefense() const{
  return this->defense;
}

TriggerType BaseMonster::getTriggerType() const{
  return this->Trigger;
}

void BaseMonster::changeStats(int attChange, int defChange) {
  attack += attChange;
  defense += defChange;
}

void BaseMonster::activate(Owner* me, Owner* opponent) {
  if(this->effect){
    this->effect->activate(me, opponent);
  }else{
    throw string("NoEffect");
  }
}

void BaseMonster::activate(int fieldIndex, Owner* player) {
  if(this->effect){
    this->effect->activate(fieldIndex, player);
  }else{
    throw string("NoEffect");
  }
}

int BaseMonster::getEffectCost() const{
  return this->effectCost;
}

Monster* BaseMonster::getComponent() {
  throw string("NoEnchantments");
}

Effect* BaseMonster::getEffect() const{
  return this->effect;
}

card_template_t BaseMonster::makeTemplate() const{
  if(effect == nullptr){
    return display_minion_no_ability(Card::getName(), Card::getCost(), this->attack, this->defense);
  }else if(Trigger == TriggerType::None){
    return display_minion_activated_ability(Card::getName(), Card::getCost(), this->attack, this->defense, this->effectCost, Card::getDescription());
  }else{
    return display_minion_triggered_ability(Card::getName(), Card::getCost(), this->attack, this->defense, Card::getDescription());
  }
}

card_template_t BaseMonster::getMonsterTemplate() const{
  return makeTemplate();
}

vector<vector<card_template_t>> BaseMonster::makeCompleteTemplate() const {
  card_template_t monsterTemplate = this->makeTemplate();
  vector<card_template_t> line1 { monsterTemplate };
  vector<vector<card_template_t>> completeTemplate { line1 };
  return completeTemplate;
}

