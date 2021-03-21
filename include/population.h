 #include "agent.h"

int select_agent_in_pop(std::vector<Brain*> brains);

class Population
{
public:
	Population(int agentsNB_ = 0, std::string name_ = "X");
	void select();
	void reproduce();
	void reset_fitness();
	std::vector<Brain*> brains;
	int brainsNB = 0;
	int generationID = 0;
	int idCursor = 0;
	float generationMaxFitness = 1.f;
	std::string name;
};