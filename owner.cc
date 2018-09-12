#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "owner.h"
#include "triggerType.h"
#include "subject.h"

using namespace std;

Owner::Owner(bool isActive)
  : Subject(), opponent{nullptr}, deck{Deck()}, hand{Hand()}, field{Field()}, life{20}, magicCurr{3}, name{"NoName"}, isActive{isActive}{
  this->initializeCards();
  cout << "Player initialized" << endl;
}

void Owner::addOpponent(Owner* opp) {
  this->opponent = opp;
  cout << "Opponent initialized" << endl;
}

void Owner::rename(string name) {
  this->name = name;
  cout << "Player name is : " << name << endl;
}

Owner::~Owner() {
  this->opponent = nullptr;
  for (auto& x: this->cardList) {
    delete x.second;
  }
}

void Owner::initializeCards() {
  this->cardList.insert(pair<string, Card*>("Air Elemental", new BaseMonster("Air Elemental", 0, "", 1, 1, TriggerType::None, nullptr, 0)));
  this->cardList.insert(pair<string, Card*>("Earth Elemental", new BaseMonster("Earth Elemental", 3, "", 4, 4, TriggerType::None, nullptr, 0)));
  this->cardList.insert(pair<string, Card*>("Fire Elemental", new BaseMonster("Fire Elemental", 2, "Whenever an opponent's minion enters play, deal 1 damage to it.", 2, 2, TriggerType::OpponentSummon, new SingleTarget(0, -1), 0)));
  this->cardList.insert(pair<string, Card*>("Potion Seller", new BaseMonster("Potion Seller", 2, "At the end of your turn, all your minions gain +0/+1.", 1, 3, TriggerType::EndOfTurn, new Aoe(0, 1, 1), 0)));
  this->cardList.insert(pair<string, Card*>("Novice Pyromancer", new BaseMonster("Novice Pyromancer", 1, "Deal 1 damage to target minion", 0, 1, TriggerType::None, new SingleTarget(0, -1), 1)));
  this->cardList.insert(pair<string, Card*>("Apprentice Summoner", new BaseMonster("Apprentice Summoner", 1, "Summon a 1/1 air elemental", 1, 1, TriggerType::None, new Summon("Air Elemental", 1), 1)));
  this->cardList.insert(pair<string, Card*>("Master Summoner", new BaseMonster("Master Summoner", 3, "Summon up to three 1/1 air elemental", 2, 2, TriggerType::None, new Summon("Air Elemental", 3), 2)));
  this->cardList.insert(pair<string, Card*>("Cloud Drake", new BaseMonster("Cloud Drake", 3, "Whenever one of your minions is destroyed, summon a 1/1 air elemental", 2, 2, TriggerType::YouDestroy, new Summon("Air Elemental", 1), 0)));
  this->cardList.insert(pair<string, Card*>("Lady Luck", new BaseMonster("Lady Luck", 1, "Flip: Give a target minion +1/+1", 1, 1, TriggerType::None, new Flip(new SingleTarget(1, 1)), 1)));
  this->cardList.insert(pair<string, Card*>("King of Spades", new BaseMonster("King of Spades", 3, "Whenever you draw a card, Flip: Draw an extra card", 1, 4, TriggerType::YouDraw, new Flip(new Draw(1)), 0)));
  this->cardList.insert(pair<string, Card*>("Banish", new Spell("Banish", 2, "Destroy target minion or ritual", new Banish())));
  this->cardList.insert(pair<string, Card*>("Unsummon", new Spell("Unsummon", 1, "Put target minion on the bottom of its owner's deck", new Unsummon())));
  this->cardList.insert(pair<string, Card*>("Recharge", new Spell("Recharge", 1,  "Your ritual gains 3 charges", new Recharge(3))));
  this->cardList.insert(pair<string, Card*>("Disenchant", new Spell("Disenchant", 1, "Destroy the top enchantment on target minion", new Disenchant(1))));
  this->cardList.insert(pair<string, Card*>("Raise Dead", new Spell("RaiseDead", 1, "Resurrect the top minion in your graveyard", new RaiseDead(1))));
  this->cardList.insert(pair<string, Card*>("Blizzard", new Spell("Blizzard", 3,"Deal 2 damage to all minions", new Aoe(0, -2, 3))));
  this->cardList.insert(pair<string, Card*>("Fireball", new Spell("Fireball", 1, "Deal 2 damage to a minion", new SingleTarget(0, -2))));
  this->cardList.insert(pair<string, Card*>("Pot of Greed", new Spell("Pot of Greed", 1, "Draw 2 cards", new Draw(2))));
  this->cardList.insert(pair<string, Card*>("Giant Strength", new Buff("Giant Strength", 1, "", nullptr, 2, 2)));
  this->cardList.insert(pair<string, Card*>("Magic Fatigue", new MagicFatigue("Magic Fatigue", 0, "Enchanted minion's activated ability costs 2 more", nullptr, 2)));
  this->cardList.insert(pair<string, Card*>("Silence", new Silence("Silence", 1,"Enchanted minion cannot use abilities", nullptr)));
  this->cardList.insert(pair<string, Card*>("Goose Jacket", new Armour("Goose Jacket", 1, "Enchanted minion takes 1 less damage when targeted", nullptr, 1)));
  this->cardList.insert(pair<string, Card*>("Dark Ritual", new Ritual("Dark Ritual", 0, "At the start of your turn, gain 1 magic", 5, TriggerType::StartOfTurn, new ChangeMagic(1), 1)));
  this->cardList.insert(pair<string, Card*>("Aura of Power", new Ritual("Aura of Power", 1, "Whenever a minion enters play under your control, it gains +1/+1", 4, TriggerType::YouSummon, new SingleTarget(1, 1), 1)));
  this->cardList.insert(pair<string, Card*>("Standstill", new Ritual("Standstill", 3, "Whenever a minion enters play, destroy it", 4, TriggerType::AnySummon, new Standstill(), 2)));
  this->cardList.insert(pair<string, Card*>("Random Forest", new Ritual("Random Forest", 1, "Whenever a minion is destroyed, Flip: Return it to the field", 4, TriggerType::AnyDestroy, new Flip(new RaiseDead(1)), 1)));
  cout << "Card List Initialized" << endl;
}

void Owner::initializeDeck(istream &deck) {
  string cardName;
  while (getline(deck, cardName)) {
    this->deck.putToBottom(cardName);
  }
  cout << "Deck Initialized" << endl;
}

bool Owner::lose() const{
  if(this->life < 0){
    return true;
  }else{
    return false;
  }
}

string Owner::getName() const{
  return this->name;
}

void Owner::setTesting(bool testing){
  this->testing = testing;
}

void Owner::play(int handIndex) {
  string cardName;
  try {
    cardName = this->hand.getCardName(handIndex);
    hand.destroyCard(handIndex);
    int cost = this->cardList[cardName]->getCost();

    if(!testing && (this->magicCurr-cost < 0)) throw string("NoMagic");

    this->cardList[cardName]->play(this, this->opponent);
    this->magicCurr -= cost;
    this->notifyObservers(TriggerType::Xwindow, this, this->opponent, cardName);
    if(testing && this->magicCurr < 0) this->magicCurr = 0;
    cout << cardName << " played" << endl;
  } catch(const string &s) {
    if (s == "HandOutOfScope") {
      cerr << "Hand Index is out of Scope" << endl;
    }else if (s == "NoNeedIndex"){
      cerr << "Card played doesn't need index" << endl;
      hand.addToPos(cardName, handIndex);
    }else if (s == "NeedIndex"){
      cerr << "Card played needs index" << endl;
      hand.addToPos(cardName, handIndex);
    }else if(s == "NoMagic"){
      cerr << "Not enough magic" << endl;
      hand.addToPos(cardName, handIndex);
    }else if(s == "NoRitual"){
      cerr << "No ritual to target" << endl;
      hand.addToPos(cardName, handIndex);
    }else if(s == "UsedOnRitual"){
      cerr << "Can't use on ritual" << endl;
      hand.addToPos(cardName, handIndex);
    }else if(s == "FieldMaxed"){
      cerr << "Field is full" << endl;
      hand.addToPos(cardName, handIndex);
    }else if(s == "No cards in graveyard"){
      cerr << "No cards in graveyard" << endl;
      hand.addToPos(cardName, handIndex);
    }else if(s == "NoEnchantments"){
      cerr << "This monster has no enchantments" << endl;
      hand.addToPos(cardName, handIndex);
    }else if (s == "FieldOutOfScope") {
      cerr << "Field Index Out of Scope" << endl;
      hand.addToPos(cardName, handIndex);
    }else if (s == "NoEffect"){
      cerr << "This monster has no effect" << endl;
      hand.addToPos(cardName, handIndex);
    }else if (s == "TriggerTypeEffect"){
      cerr << "Cannot activate trigger type effect" << endl;
      hand.addToPos(cardName, handIndex);
    }
  }
}

void Owner::play(int handIndex, int player, int fieldIndex) {
  try {
    string cardName = this->hand.getCardName(handIndex);
    int cost = this->cardList[cardName]->getCost();

    if(!testing && (this->magicCurr < cost)) throw string("NoMagic");

    if (player == 1) {
      string targetName = this->field.getName(fieldIndex);
      this->cardList[cardName]->play(fieldIndex, this);
      hand.destroyCard(handIndex);
      this->magicCurr -= cost;
      if(testing && this->magicCurr < 0) this->magicCurr = 0;
      this->notifyObservers(TriggerType::Xwindow, this, this->opponent, cardName);

      cout << cardName << " played on " << this->name << "'s " << targetName << endl;
    } else if (player == 2) {
      string targetName = this->opponent->getMonsterName(fieldIndex);
      this->cardList[cardName]->play(fieldIndex, this->opponent);
      hand.destroyCard(handIndex);
      this->magicCurr -= cost;
      if(testing && this->magicCurr < 0) this->magicCurr = 0;
      this->notifyObservers(TriggerType::Xwindow, this, this->opponent, cardName);

      cout << cardName << " played on " << this->opponent->getName() << "'s " << targetName << endl;
    } else {
      cerr << "Player index must be 1 or 2" << endl;
    }
  } catch (const string &s) {
    if (s == "HandOutOfScope") {
      cerr << "Hand Index Out of Scope" << endl;
    } else if (s == "FieldOutOfScope") {
      cerr << "Field Index Out of Scope" << endl;
    }else if (s == "NoNeedIndex"){
      cerr << "Card played doesn't need index" << endl;
    }else if (s == "NeedIndex"){
      cerr << "Card played needs index" << endl;
    }else if(s == "NoMagic"){
      cerr << "Not enough magic" << endl;
    }else if(s == "NoRitual"){
      cerr << "No ritual to target" << endl;
    }else if(s == "UsedOnRitual"){
      cerr << "Can't use on ritual" << endl;
    }else if(s == "FieldMaxed"){
      cerr << "Field is full" << endl;
    }else if(s == "No cards in graveyard"){
      cerr << "No cards in graveyard" << endl;
    }else if(s == "NoEnchantments"){
      cerr << "This monster has no enchantments" << endl;
    }else if (s == "NoEffect"){
      cerr << "This monster has no effect" << endl;
    }else if (s == "TriggerTypeEffect"){
      cerr << "Cannot activate trigger type effect" << endl;
    }
  }
}

string Owner::getMonsterName(int fieldIndex) const {
  return this->field.getName(fieldIndex);
}

int Owner::getAttack(int fieldIndex) const {
  return this->field.getAttack(fieldIndex);
}

int Owner::getDefense(int fieldIndex) const {
  return this->field.getDefense(fieldIndex);
}

void Owner::attack(int fieldIndex) {
  try {
    if(field.getMonster(fieldIndex)->getHasAttacked()) throw string("HasAttacked");

    int damage = this->field.getAttack(fieldIndex);
    this->opponent->getAttacked(damage);
    field.getMonster(fieldIndex)->changeHasAttacked(true);
  } catch (const string &s) {
    if (s == "FieldOutOfScope") {
      cerr << "Field Index Out of Scope" << endl;
    }else if (s == "HasAttacked"){
      cerr << "Monster has already attacked" << endl;
    }
  }
}

void Owner::attack(int myfieldIndex, int oppfieldIndex) {
  try {
    if(field.getMonster(myfieldIndex)->getHasAttacked()) throw string("HasAttacked");

    int damageDealt = this->field.getAttack(myfieldIndex);
    int damageTaken = this->opponent->getAttack(oppfieldIndex);
    this->changeStats(myfieldIndex, 0, -1*damageTaken);
    this->opponent->changeStats(oppfieldIndex, 0, -1*damageDealt);
    field.getMonster(myfieldIndex)->changeHasAttacked(true);
  } catch (const string &s) {
    if (s == "FieldOutOfScope") {
      cerr << "One of the Field Indices are out of scope" << endl;
    }else if(s == "HasAttacked"){
      cerr << "Monster has already attacked" << endl;
    }
  }
}

void Owner::destroy(int fieldIndex) {
  if(fieldIndex == 5){
    this->field.getRitual();
    this->field.playRitual(nullptr);
    this->remove(0);
  }else{
    string destroyed = this->field.destroy(fieldIndex);
    this->graveyard.addToGraveyard(destroyed);
    try {
      Ritual* maybeRitual = this->field.getRitual();
      if (maybeRitual != nullptr) {
        this->remove(fieldIndex+1);
      }
    } catch (const string &s) {
      if (s == "NoRitual") {
        this->remove(fieldIndex);
      }
    }

    this->notifyObservers(TriggerType::YouDestroy, this, this->opponent, destroyed);
    this->opponent->notifyObservers(TriggerType::OpponentDestroy, this->opponent, this, destroyed);
  }
}


void Owner::getAttacked(int damage) {
  this->life -= damage;
  cout << this->name << " suffered " << damage << " damage" << endl;
}

void Owner::changeStats(int fieldIndex, int attChange, int defChange) {
  this->field.changeStats(fieldIndex, attChange, defChange);
  if (this->field.getDefense(fieldIndex) <= 0) {
    this->destroy(fieldIndex);
  }
}

void Owner::discard(int handIndex) {
  try {
    this->hand.discard(handIndex);
  } catch (const string &s) {
    if (s == "HandOutOfScope") {
      cerr << "Hand Index Out of Scope" << endl;
    }
  }
}

void Owner::draw(int numCards) {
  while (numCards > 0) {
    try {
      string cardName = this->deck.draw();
      this->hand.addCard(cardName);
      cout << cardName << " was Drawn" << endl;
      this->notifyObservers(TriggerType::YouDraw, this, this->opponent, cardName);
      this->opponent->notifyObservers(TriggerType::OpponentDraw, this->opponent, this, cardName);
      numCards--;
    } catch (const string &s) {
      if (s == "NoCards") {
        cerr << "No cards left in deck" << endl;
        break;
      }
    }
  }
}

void Owner::shuffle() {
  this->deck.shuffle();
  cout << this->name << "'s deck was shuffled" << endl;
}

void Owner::endTurn() {
  this->isActive = false;
  string event = "End";
  this->notifyObservers(TriggerType::EndOfTurn, this, this->opponent, event);
  this->notifyObservers(TriggerType::Xwindow, this, this->opponent, event);
  this->opponent->makeActive();
  event = "Start";
  this->opponent->notifyObservers(TriggerType::StartOfTurn, this->opponent, this, event);
  this->notifyObservers(TriggerType::Xwindow, this, this->opponent, event);
  this->opponent->magicChange(1);
  for(int i = 0; i < field.size(); i++){
    field.getMonster(i)->changeHasAttacked(false);
  }
  cout << "Turn Ended" << endl;
}

void Owner::makeActive() {
  this->isActive = true;
}

void Owner::summon(Monster* monster) {
  this->field.summon(monster);
  this->attach(monster);
  this->notifyObservers(TriggerType::YouSummon, this, this->opponent, this->field.size() - 1, 1);
  this->opponent->notifyObservers(TriggerType::OpponentSummon, this->opponent, this, this->field.size() - 1, 2);
}

void Owner::playRitual(Ritual *r) {
  try {
    Ritual* temp = this->field.getRitual();
    if (temp != nullptr) {
      this->remove(0);
    }
  } catch (const string &s) {
  }
  this->field.playRitual(r);
  this->attach_to_front(r);
}

void Owner::playEnchantment(int fieldIndex, Enchantments* enchantment){
  this->field.playEnchantment(fieldIndex, enchantment);
  Monster* temp = this->field.getMonster(fieldIndex);
  try {
    Ritual* maybeRitual = this->field.getRitual();
    if (maybeRitual != nullptr) {
      this->swapObserver(fieldIndex + 1, temp);
    }
  } catch (const string &s) {
    if (s == "NoRitual") {
      this->swapObserver(fieldIndex, temp);
    }
  }
}

void Owner::use(int fieldIndex) {
  try {
    int cost = field.getMonster(fieldIndex)->getEffectCost();
    string monsterName = field.getMonster(fieldIndex)->getName();

    if(field.getMonster(fieldIndex)->getTriggerType() != TriggerType::None) throw string("TriggerTypeEffect");
    if(!testing && (this->magicCurr-cost < 0)) throw string("NoMagic");

    this->field.activate(fieldIndex, this, this->opponent);
    this->magicCurr -= cost;
    if(testing && this->magicCurr < 0) this->magicCurr = 0;

    cout << "Used " << this->name << "'s " << monsterName << "'s effect." << endl;
  } catch (const string &s) {
    if (s == "FieldOutOfScope") {
      cerr << "Field Index is Out of Scope" << endl;
    }else if (s == "NoNeedIndex"){
      cerr << "Card played doesn't need index" << endl;
    }else if (s == "NeedIndex"){
      cerr << "Card played needs index" << endl;
    }else if (s == "NoEffect"){
      cerr << "This monster has no effect" << endl;
    }else if (s == "TriggerTypeEffect"){
      cerr << "Cannot activate trigger type effect" << endl;
    }else if(s == "NoMagic"){
      cerr << "Not enough magic" << endl;
    }else if(s == "FieldMaxed"){
      cerr << "Field is full" << endl;
    }else if(s == "No cards in graveyard"){
      cerr << "No cards in graveyard" << endl;
    }else if(s == "NoEnchantments"){
      cerr << "This monster has no enchantments" << endl;
    }else if(s == "UsedOnRitual"){
      cerr << "Can't use on ritual" << endl;
    }else if(s == "NoRitual"){
      cerr << "No ritual to target" << endl;
    }
  }
}

void Owner::use(int fieldIndex, int player, int targFieldIndex) {
  try {
    int cost = field.getMonster(fieldIndex)->getEffectCost();
    string monsterName = field.getMonster(fieldIndex)->getName();
    string targetName;
    if(fieldIndex != 5){
      targetName = this->field.getName(fieldIndex);
    }else{
      targetName = this->field.getRitual()->getName();
    }

    if (player == 1) {
      if(field.getMonster(fieldIndex)->getTriggerType() != TriggerType::None) throw string("TriggerTypeEffect");
      if(!testing && (this->magicCurr-cost < 0)) throw string("NoMagic");

      this->field.activate(fieldIndex, this, targFieldIndex);
      this->magicCurr -= cost;
      if(testing && this->magicCurr < 0) this->magicCurr = 0;

      cout << "Used " << this->name << "'s " << monsterName << "'s effect on " << this->name << "'s " << targetName << endl;
    }else if (player == 2) {
      int cost = field.getMonster(fieldIndex)->getEffectCost();

      if(field.getMonster(fieldIndex)->getTriggerType() != TriggerType::None) throw string("TriggerTypeEffect");
      if(!testing && (this->magicCurr-cost < 0)) throw string("NoMagic");

      this->field.activate(fieldIndex, this->opponent, targFieldIndex);
      this->magicCurr -= cost;
      if(testing && this->magicCurr < 0) this->magicCurr = 0;

      cout << "Used " << this->name << "'s " << monsterName << "'s effect on " << this->opponent->getName() << "'s " << targetName << endl;
    }
  }catch (const string &s) {
    if (s == "FieldOutOfScope") {
      cerr << "Field Index is Out of Scope" << endl;
    }else if (s == "NoNeedIndex"){
      cerr << "Card played doesn't need index" << endl;
    }else if (s == "NeedIndex"){
      cerr << "Card played needs index" << endl;
    }else if (s == "NoEffect"){
      cerr << "This monster has no effect" << endl;
    }else if (s == "TriggerTypeEffect"){
      cerr << "Cannot activate trigger type effect" << endl;
    }else if(s == "NoMagic"){
      cerr << "Not enough magic" << endl;
    }else if(s == "FieldMaxed"){
      cerr << "Field is full" << endl;
    }else if(s == "No cards in graveyard"){
      cerr << "No cards in graveyard" << endl;
    }else if(s == "NoEnchantments"){
      cerr << "This monster has no enchantments" << endl;
    }else if(s == "UsedOnRitual"){
      cerr << "Can't use on ritual" << endl;
    }else if(s == "NoRitual"){
      cerr << "No ritual to target" << endl;
    }else {
      cerr << "Player Index must be 1 or 2" << endl;
    }
  }
}

void Owner::inspect(int fieldIndex) {
  try {
    vector<vector<card_template_t>> monster = this->field.makeCompleteTemplate(fieldIndex);
    for (unsigned int i = 0; i < monster.size(); i++) {
      for (int j = 0; j < 11; j++) {
        for (unsigned int k = 0; k < monster[i].size(); k++) {
          cout << monster[i][k][j];
        }
        cout << endl;
      }
    }
  } catch (const string &s) {
    if (s == "FieldOutOfScope") {
      cerr << "Field Index is Out of Scope" << endl;
    }
  }
}

void Owner::seeHand() const{
  vector<card_template_t> handDisplay(this->hand.size());
  for (int i = 0; i < this->hand.size(); i++) {
    string cardName = this->hand.getCardName(i);
    handDisplay[i] = this->cardList.at(cardName)->makeTemplate();
  }
  for (int i = 0; i < 11; i++) {
    for (int j = 0; j < this->hand.size(); j++) {
      cout << handDisplay[j][i];
    }
    cout << endl;
  }
}

void Owner::magicChange(int change) {
  this->magicCurr += change;
}

int Owner::getFieldSize() const{
  return this->field.size();
}

void Owner::activate(Aoe *a){
  for(int i = field.size()-1; i >= 0; i--){
    changeStats(i, a->getAttackChange(), a->getDefenseChange());
  }
}

void Owner::activate(Banish *b, int fieldIndex){
  destroy(fieldIndex);
}

void Owner::activate(Unsummon *u, int fieldIndex){
  if(fieldIndex == 5) throw string("UsedOnRitual");

  this->destroy(fieldIndex);
  string monsterName = this->graveyard.returnCard();
  this->graveyard.deleteCard();
  this->deck.putToBottom(monsterName);
}

void Owner::activate(Recharge *r){
  this->field.increaseCharge(r->getCharges());
}

void Owner::activate(Disenchant *d, int fieldIndex){
  if(fieldIndex == 5) throw string("UsedOnRitual");

  for(int i = 0; i < d->getNumOfDisenchant(); i++){
    this->field.disenchant(fieldIndex);
    Monster* temp = this->field.getMonster(fieldIndex);

    try {
      Ritual* maybeRitual = this->field.getRitual();
      if (maybeRitual != nullptr) {
        this->swapObserver(fieldIndex + 1, temp);
      }
    } catch (const string &s) {
      if (s == "NoRitual") {
        this->swapObserver(fieldIndex, temp);
      }
    }
  }
}

void Owner::activate(RaiseDead *r){
  for(int i = 0; i < r->getNumOfRaises(); i++){
    string monsterName = this->graveyard.returnCard();
    this->graveyard.deleteCard();
    this->cardList[monsterName]->play(this, this->opponent);
  }
}

void Owner::activate(Summon *s){
  for(int i = 0; i < s->getAmount(); i++){
    this->cardList[s->getName()]->play(this, this->opponent);
  }
}

void Owner::activate(SingleTarget *s, int fieldIndex){
  if(fieldIndex == 5) throw string("UsedOnRitual");

  changeStats(fieldIndex, s->getAttackChange(), s->getDefenseChange());
}

void Owner::activate(Standstill *s, int fieldIndex){
  if(fieldIndex == 5) throw string("UsedOnRitual");

  this->destroy(fieldIndex);
}

void Owner::activate(ChangeMagic *c){
  this->magicCurr += c->getMagicChange();
}

void Owner::activate(Draw *d, int cardsDrawn) {
  this->draw(cardsDrawn);
}

card_template_t Owner::makeTemplate() const{
  if(this->isActive){
    return display_player_card(1, this->name, this->life, this->magicCurr);
  }else{
    return display_player_card(2, this->name, this->life, this->magicCurr);
  }
}

ostream &operator<<(ostream &out, const Owner &o) {
  vector<card_template_t> line1(5);
  vector<card_template_t> line2(5);
  int i = 0;
  for (; i < o.getFieldSize(); i++) {
    line1[i] = o.field.getMonsterTemplate(i);
  }
  for (; i < 5; i++) {
    line1[i] = CARD_TEMPLATE_BORDER;
  }
  try {
    line2[0] = o.field.getRitual()->makeTemplate();
  } catch (string &s) {
    if (s == "NoRitual") {
      line2[0] = CARD_TEMPLATE_BORDER;
    }
  }
  line2[1] = CARD_TEMPLATE_EMPTY;
  line2[2] = o.makeTemplate();
  line2[3] = CARD_TEMPLATE_EMPTY;
  if (o.graveyard.size() > 0) {
    string name = o.graveyard.returnCard();
    line2[4] = o.cardList.at(name)->makeTemplate();
  } else {
    line2[4] = CARD_TEMPLATE_BORDER;
  }
  if (!(o.isActive)) {
    line1.swap(line2);
  } else {
    out << "\33[33m" << EXTERNAL_BORDER_CHAR_TOP_LEFT;
    for (int m = 0; m < 165; m++) {
      out << "\33[33m" << EXTERNAL_BORDER_CHAR_LEFT_RIGHT << "\033[0m";    //top 1st horizontal line
    }
    out << "\33[33m" << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl << "\033[0m";
    out << "\033[33m" << *o.opponent << "\033[36m";    // top 3  //change

    for (int l = 0; l < 10; l++) {

      out << "\033[33;5m"<< CENTRE_GRAPHIC[l] << endl <<"\33[0m";    //Sorcery word
    }
  }
  for (int j = 0; j < 11; j++) {
    out  << "\033[33m"<< EXTERNAL_BORDER_CHAR_UP_DOWN  << "\033[0m";    // row 1 4 left up down
    for (int k = 0; k < 5; k++) {
      if (o.isActive) {
        out  << "\033[36m" << line1[k][j]<< "\033[0m" ;
      } else {
        if (k == 0 || k == 4) {
          out  << "\033[34m" << line1[k][j]<< "\033[0m" ;
        } else if (k == 2){
          out  << "\033[31m" << line1[k][j]<< "\033[0m" ;
        } else {
          out  << line1[k][j];
        }
      }
    }
    out << "\033[33m"<< EXTERNAL_BORDER_CHAR_UP_DOWN<< "\033[0m";    // row 1 4 right up down
    out << endl;
  }
  for (int j = 0; j < 11; j++) {
    out  << "\033[33m"<< EXTERNAL_BORDER_CHAR_UP_DOWN  << "\033[0m";      // 2 5 left up down
    for (int k = 0; k < 5; k++) {
      if (!(o.isActive)) {
        out  << "\033[36m" << line2[k][j]<< "\033[0m" ;
      } else {
        if (k == 0 || k == 4) {
          out  << "\033[34m" << line2[k][j]<< "\033[0m" ;
        } else if (k == 2){
          out  << "\033[31m" << line2[k][j]<< "\033[0m" ;
        } else {
          out  << line2[k][j];
        }
      }
    }
    out  << "\033[33m" << EXTERNAL_BORDER_CHAR_UP_DOWN<< "\033[0m"  ;  // 2 5 right up down
    out << endl;
  }
  if (o.isActive) {

    out  << "\033[33m" << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT<< "\033[0m";
    for (int m = 0; m < 165; m++) {
      out  << "\033[33m"<< EXTERNAL_BORDER_CHAR_LEFT_RIGHT<< "\033[0m";    //bottom line
    }
    out << "\033[33m"<< EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT;    //right bottom coner
    out << endl;

  }
   out <<"\033[0m";
   return out;
}

