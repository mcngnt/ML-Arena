#include "brain.h"

Brain::Brain()
{
	layerSizes = {4, 5, 5, 5};
	layerNB = 4;
	weightsNB = 0;
	for (int i = 1; i < layerNB-1; ++i)
	{
		weightsNB += layerSizes[i-1] * layerSizes[i];
	}
	for (int i = 0; i < weightsNB; ++i)
	{
		weights.push_back(rand_float(true));
	}
}

std::vector<float> Brain::think(std::vector<float> inputs)
{
	std::vector<float> neuronsValuesPrev = inputs;
	std::vector<float> neuronsValuesNext;
	int weightsCursor = 0;
	for (int i = 1; i < layerNB-1; ++i)
	{
		for (int j = 0; j < layerSizes[i]; ++j)
		{
			float result = 0.f;
			for (int k = 0; k < layerSizes[i-1]; ++k)
			{
				result += weights[weightsCursor] * neuronsValuesPrev[k];
				weightsCursor++;
			}
			// result = sigmoid(result);
			neuronsValuesNext.push_back(result);
		}
		neuronsValuesPrev = neuronsValuesNext;
		neuronsValuesNext.clear();
	}
	for (int i = 0; i < layerSizes[layerNB-1]; ++i)
	{
		neuronsValuesPrev[i] = sigmoid(neuronsValuesPrev[i]);
	}
	return neuronsValuesPrev;
}

void Brain::mutate()
{
	for (int i = 0; i < weightsNB; ++i)
	{
		if (rand_float(false) < MUTATE_RATE)
		{
			weights[i] = rand_float(true);
		}
	}
}
void Brain::crossover(Brain* x, Brain* y)
{
	for (int i = 0; i < weightsNB; ++i)
	{
		if (rand_float(false) > 0.2f)
		{
			weights[i] = x->weights[i];
		}
		else
		{
			weights[i] = y->weights[i];
		}
	}
}

bool compare_brains(Brain* a, Brain* b)
{
	return (a->fitness > b->fitness);
}