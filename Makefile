CXX = g++
CXXFLAGS = -std=c++14 -Werror=vla -Wall -MMD
EXEC = sorcery
OBJECTS = main.o activatedabilitydata.o activatedeffect.o ascii_graphics.o attackable.o card.o carddata.o deck.o decorator.o effect.o enchantment.o enchantmentabilitydata.o enchantmenteffect.o hand.o minion.o player.o ritual.o spell.o textdisplay.o triggereffect.o triggerabilitydata.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
