#include <string>
#include "unsummon.h"
#include "owner.h"

using namespace std;

Unsummon::Unsummon() {}

Unsummon::~Unsummon() {}

Unsummon* Unsummon::copyCtor() const{
  return new Unsummon(*this);
}

void Unsummon::activate(Owner *me,Owner *opponent) {
  throw string("NeedIndex");
}

void Unsummon::activate(int fieldIndex,Owner *player) {
  player->activate(this, fieldIndex);
}

