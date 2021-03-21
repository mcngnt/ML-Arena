#include "arena.h"

Arena::Arena(Population pop_)
{
	pop = pop_;
	brainsPerPop = pop.brainsNB;
	fighterA = new Agent(pop.brains[0]);
	fighterB = new Agent(pop.brains[1]);
	fighterIDA = 0;
	fighterIDB = 1;
	fightsList[0][1] = true;
	fightsList[1][0] = true;
}

void Arena::assign_fitness()
{
	if (fighterA->isAlive == fighterB->isAlive)
	{
		pop.brains[fighterIDA]->fitness += 1.f;
		pop.brains[fighterIDB]->fitness += 1.f;
		return;
	}
	pop.brains[fighterIDA]->fitness += fighterA->isAlive * 3.f;
	pop.brains[fighterIDB]->fitness += fighterB->isAlive * 3.f;
}

bool Arena::do_tournament()
{
	fighterA->update(fighterB);
	fighterB->update(fighterA);
	tickFight++;

	if (tickFight > FIGHT_DURATION)
	{
		// printf("%d %d\n", fighterIDA, fighterIDB);
		tickFight = 0;
		assign_fitness();

		do
		{
			fighterIDB++;
			if (fighterIDB >= brainsPerPop)
			{
				fighterIDB = 0;
				fighterIDA++;
				if (fighterIDA >= brainsPerPop)
				{
					fighterIDA = 0;
					fighterIDB = 1;
					for (int i = 0; i < AGENTS_NB; ++i)
					{
						for (int j = 0; j < AGENTS_NB; ++j)
						{
							fightsList[i][j] = false;
						}
					}
					fightsList[0][1] = true;
					fightsList[1][0] = true;
					return false;
				}
			}
		}
		while(fighterIDB == fighterIDA || fightsList[fighterIDA][fighterIDB] == true);

		fightsList[fighterIDA][fighterIDB] = true;
		fightsList[fighterIDB][fighterIDA] = true;

		fighterA = new Agent(pop.brains[fighterIDA]);
		fighterB = new Agent(pop.brains[fighterIDB]);
	}
	return true;
}

void Arena::restart()
{
	pop.reset_fitness();
	fighterA = new Agent(pop.brains[0]);
	fighterB = new Agent(pop.brains[1]);
}

void Arena::update_pop()
{
	pop.select();
	pop.reproduce();
}