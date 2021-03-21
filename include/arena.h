	#include "population.h"

class Arena
{
public:
	Arena(Population pop_);
	bool do_tournament();
	void assign_fitness();
	void restart();
	void update_pop();
	Population pop;
	int tickFight = 0;
	int generationID;
	int  brainsPerPop;
	int fighterIDA = 0;
	int fighterIDB = 0;
	bool fightsList[AGENTS_NB][AGENTS_NB] = {{false}};
	Agent* fighterA;
	Agent* fighterB;
};