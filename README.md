# ML-Arena
 Agents learn to fight using machine learning and genetic algorithms.

## How does it work ?
Each agent (a green/purple dot) has a "brain" which is a 3 layers, fully-connected neural network. At the first generation, all the "neurons" of the neural networks are instantiated randomly. At the end of each generation (every 30 seconds), the best agents of the population are selected, reproduced and mutated to create the next generation of agents. The selection is tournament-based, every agent fight each other, the probability of being selected being directly influenced by the number of fights won. The use of a genetic algorithm allow slow improvements every generation, making the agents slightly better at aiming and shooting at each generation.

## Controls

- Hover mouse over an agent to see his stats
- Use Space to stop rendering the ganets to speed up the evolution
- Use S to show/hide the view rays

![](res/gen0.PNG)
Generation 1 (Agents don't know how to aim and shoot)

![](res/gen20.PNG)
Generation 20 (Agents start aiming and shooting)
