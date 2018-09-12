CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
EXEC = sorcery
OBJECTS = gameConsole.o ascii_graphics.o aoe.o armour.o banish.o baseMonster.o buff.o card.o changeMagic.o deck.o disenchant.o draw.o effect.o enchantments.o field.o flip.o graveyard.o hand.o magicFatigue.o main.o monster.o owner.o raiseDead.o recharge.o ritual.o silence.o singleTarget.o spell.o standstill.o subject.o summon.o unsummon.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean

