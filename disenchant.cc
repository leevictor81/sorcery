#include <string>
#include "disenchant.h"
#include "owner.h"

using namespace std;

Disenchant::Disenchant(int numOfDisenchant) :
numOfDisenchant{numOfDisenchant} {}

Disenchant::~Disenchant() {}

Disenchant* Disenchant::copyCtor() const{
  return new Disenchant(*this);
}

int Disenchant::getNumOfDisenchant() const{
  return this->numOfDisenchant;
}

void Disenchant::activate(Owner *me, Owner *opponent) {
  throw string("NeedIndex");
}

void Disenchant::activate(int fieldIndex, Owner *player) {
  player->activate(this, fieldIndex);
}

