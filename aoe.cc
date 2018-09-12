#include <string>
#include "aoe.h"
#include "owner.h"

using namespace std;

Aoe::Aoe(int attackChange, int defenseChange, int targets) :
attackChange{attackChange}, defenseChange{defenseChange}, targets{targets} {}

Aoe::~Aoe(){}

Aoe* Aoe::copyCtor() const{
  return new Aoe(*this);
}

int Aoe::getAttackChange() const{
  return this->attackChange;
}

int Aoe::getDefenseChange() const{
  return this->defenseChange;
}

int Aoe::getTargets() const{
  return this->targets;
}

void Aoe::activate(Owner *me, Owner *opponent) {
  if (this->targets == 1) {
    me->activate(this);
  } else if (this->targets == 2) {
    opponent->activate(this);
  } else if (this->targets == 3) {
    me->activate(this);
    opponent->activate(this);
  }
}

void Aoe::activate(int fieldIndex, Owner *player) {
  throw string("NoNeedIndex");
}

