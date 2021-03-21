#include "population.h"
#include <string.h>

int select_agent_in_pop(std::vector<Brain*> brains, float fitnessSum)
{
	int index = 0;
	float r = rand_float(false) * fitnessSum;
	while (r > 0)
	{
	    r -= brains[index]->fitness;
	    index++;
	}
	index--;
	return index;

}

Population::Population(int brainsNB_, std::string name_)
{
	brainsNB = brainsNB_;
	name = name_;
	for (int i = 0; i < brainsNB; ++i)
	{
		brains.push_back(new Brain());
		brains[i]->id = idCursor;
		idCursor++;
	}
}

void Population::reproduce()
{
	// printf("%s\n", "start reproduce");
	float fitnessSum = 0.f;
	for (int i = 0; i < brainsNB/2; ++i)
	{
		// printf("%f Fit %d \n", brains[i]->fitness, i);
		fitnessSum += brains[i]->fitness;
	}

	for (int i = 0; i < brainsNB/2; ++i)
	{
		int parentAID = select_agent_in_pop(brains, fitnessSum);
		int parentBID = select_agent_in_pop(brains, fitnessSum);
		while (parentBID == parentAID)
		{
		    parentBID = select_agent_in_pop(brains, fitnessSum);
		}
		// printf("%d %d\n", parentAID, parentBID);
		Brain* b = new Brain();
		b->crossover(brains[parentAID], brains[parentBID]);
		b->mutate();
		b->id = idCursor;
		idCursor++;
		brains.push_back(b);
	}
	generationID++;
	// printf("%s\n", "end reproduce");
}

void Population::select()
{
	for (int i = 0; i < brainsNB; ++i)
	{
		brains[i]->isSelected = false;
	}
	float maxFitness = 0.f;
	float fitnessSum = 0.f;
	for (int i = 0; i < brainsNB; ++i)
	{
		if (brains[i]->fitness < 0.f)
		{
			brains[i]->fitness = 0.f;
		}
		brains[i]->generationAge++;
		fitnessSum += brains[i]->fitness;
		if (brains[i]->fitness > maxFitness)
		{
			maxFitness = brains[i]->fitness;
		}
	}
	generationMaxFitness = maxFitness;
	printf("-----\n Population %s\n Generation : %d\n Best Fitness : %f\n-----",name.c_str(), generationID, maxFitness);
	int acceptedNB = 0;
	while(acceptedNB <= brainsNB/2)
	{
		int acceptId = select_agent_in_pop(brains, fitnessSum);
		if (brains[acceptId]->isSelected == false)
		{
			brains[acceptId]->isSelected = true;
			acceptedNB++;
		}
	}
	for (int i = 0; i < brainsNB/2+1;)
	{
		if (brains[i]->isSelected == false)
		{
			brains.erase(brains.begin() + i);
		}
		else
		{
			i++;
		}
	}
	// printf("%s\n", "end select");
}

void Population::reset_fitness()
{
	for (int i = 0; i < brainsNB; ++i)
	{
		if (brains[i]->fitness > brains[i]->maxFitness)
		{
			brains[i]->maxFitness = brains[i]->fitness;
		}
		brains[i]->fitness = 0.f;
	}
}
