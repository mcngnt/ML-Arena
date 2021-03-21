#include "brain.h"


struct Bullet
{
	Vector pos;
	Vector dir;
} typedef Bullet;

class Agent
{
public:
	Agent(Brain* b);
	void move();
	void think(Agent* other);
	void print();
	void shoot();
	void apply_outputs();
	void move_bullet();
	void damage(Agent* other);
	void tick();
	void update(Agent* other);
	Brain* brain;
	Vector pos;
	float fitness = 0.f;
	std::vector<Bullet> bullets;
	int bulletNB = 0;
	int lives = 3;
	bool isAlive = true;
	int tickCount = 0;
	float angle = 0.f;
	float i_agentInAngle;

	float viewWide;
	float turnLeft = 0.f;
	float turnRight = 0.f;
	bool wantToShoot = false;
	float moveForwardSpeed = 0.f;
private:
	Vector oldPos;
	int lastShotDate = 0;
	float i_bulletInAngle;
	float i_viewWide;
	float i_shooted;
	float viewChange = 0.f;
	// float o_turnRight;
	// float o_turnLeft;
	float o_turnLeft;
	float o_turnRight;
	float o_shoot;
	float o_viewWide;
	float o_moveForward;
};

