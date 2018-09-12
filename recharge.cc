#include <string>
#include "recharge.h"
#include "owner.h"

using namespace std;


Recharge::Recharge(int charges) : charges{charges} {}

Recharge::~Recharge() {}

Recharge* Recharge::copyCtor() const{
  return new Recharge(*this);
}

int Recharge::getCharges() const{
  return this->charges;
}

void Recharge::activate(Owner *me, Owner *opponent) {
  me->activate(this);
}

void Recharge::activate(int fieldIndex, Owner *player) {
  throw string("NoNeedIndex");
}

