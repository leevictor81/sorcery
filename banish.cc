#include <string>
#include "banish.h"
#include "owner.h"

using namespace std;

Banish::Banish() {}

Banish::~Banish() {}

Banish* Banish::copyCtor() const{
  return new Banish(*this);
}

void Banish::activate(Owner *me, Owner *opponent) {
  throw string("NeedIndex");
}

void Banish::activate(int fieldIndex, Owner *player) {
  player->activate(this, fieldIndex);
}

