#ifndef __OWNER_H__
#define __OWNER_H__
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "card.h"
#include "graveyard.h"
#include "deck.h"
#include "hand.h"
#include "field.h"
#include "spell.h"
#include "baseMonster.h"
#include "singleTarget.h"
#include "aoe.h"
#include "summon.h"
#include "banish.h"
#include "unsummon.h"
#include "recharge.h"
#include "disenchant.h"
#include "raiseDead.h"
#include "buff.h"
#include "magicFatigue.h"
#include "silence.h"
#include "changeMagic.h"
#include "standstill.h"
#include "draw.h"
#include "flip.h"
#include "armour.h"
#include "ascii_graphics.h"

class Owner: public Subject{
  std::map<std::string, Card*> cardList;
  Owner* opponent;
  Deck deck;
  Hand hand;
  Field field;
  Graveyard graveyard;
  int life;
  int magicCurr;
  std::string name;
  bool isActive;
  bool testing;

 public:
  Owner(bool isActive);
  ~Owner();

  void addOpponent(Owner* opp);

  void rename(std::string name);

  void initializeCards();

  void initializeDeck(std::istream &deck);

  void play(int handIndex);

  void play(int handIndex, int player, int fieldIndex);

  std::string getMonsterName(int fieldIndex) const;

  int getAttack(int fieldIndex) const;

  int getDefense(int fieldIndex) const;

  void attack(int fieldIndex);

  void attack(int myfieldIndex, int oppfieldIndex);

  void getAttacked(int damage);

  void changeStats(int fieldIndex, int attChange, int defChange);

  void discard(int handIndex);

  void destroy(int fieldIndex);

  void draw(int numCards);

  void shuffle();

  void endTurn();

  void makeActive();

  void summon(Monster* monster);

  void playRitual(Ritual *r);

  void playEnchantment(int fieldIndex, Enchantments* enchantment);

  void use(int fieldIndex);

  void use(int fieldIndex, int player, int targFieldIndex);

  void inspect(int fieldIndex);

  void seeHand() const;

  void magicChange(int change);

  int getFieldSize() const;

  void activate(Aoe *a);

  void activate(Banish *b, int fieldIndex);

  void activate(Unsummon *u, int fieldIndex);

  void activate(Recharge *r);

  void activate(Disenchant *d, int fieldIndex);

  void activate(RaiseDead *r);

  void activate(Summon *s);

  void activate(SingleTarget *s, int fieldIndex);

  void activate(Standstill *s, int fieldIndex);

  void activate(ChangeMagic *c);

  void activate(Draw *d, int cardsDrawn);

  bool lose() const;

  std::string getName() const;

  void setTesting(bool testing);

  card_template_t makeTemplate() const;

  friend std::ostream &operator<<(std::ostream &out, const Owner &o);

};

#endif

