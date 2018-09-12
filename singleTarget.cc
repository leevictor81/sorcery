#include <string>
#include "singleTarget.h"
#include "owner.h"

using namespace std;

SingleTarget::SingleTarget(int attackChange, int defenseChange): attackChange{attackChange}, defenseChange{defenseChange} {}

SingleTarget::~SingleTarget() {}

SingleTarget* SingleTarget::copyCtor() const{
  return new SingleTarget(*this);
}

int SingleTarget::getAttackChange() const{
  return this->attackChange;
}

int SingleTarget::getDefenseChange() const{
  return this->defenseChange;
}

void SingleTarget::activate(Owner *me, Owner *opponent) {
  throw string("NeedIndex");
}

void SingleTarget::activate(int fieldIndex, Owner *player) {
  player->activate(this, fieldIndex);
}

