#include "utils.h"
#include "vector.h"

class Brain
{
public:
	// Brain Structure :
	// 1st layer : Inputs,
	// 2, 3, 4, ..., Nth layer : Hidden Layer
	// N+1 layer : Output

	//        I \-/ H \-/ ... \-/ H - O
	//        I \-/ H \-/ ... \-/ H - O
	//        . \-/ . \-/ ... \-/ . - .
	//        . \-/ . \-/ ... \-/ . - .
	//        . \-/ . \-/ ... \-/ . - .
	//        I \-/ H \-/ ... \-/ H - O
	Brain();
	std::vector<float> think(std::vector<float> inputs);
	void mutate();
	void crossover(Brain* x, Brain* y);
	float fitness = 0.f;
	int id = 0;
	int generationAge = 0;
	float maxFitness;
	bool isSelected = false;
private:
	int layerNB;
	std::vector<int> layerSizes;
	std::vector<float> weights;
	int weightsNB;
};

bool compare_brains(Brain*, Brain*);