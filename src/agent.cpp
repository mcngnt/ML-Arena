#include "agent.h"

Agent::Agent(Brain* b)
{
	bullets.clear();
	pos = vec_from_angle_v(rand_float(false)*2.f*PI) * rand_float(false)*(ARENA_RADIUS);
	brain = b;	
	viewWide = rand_float(false) * PI/3.f;
	angle = rand_float(false) * 2.f * PI;
}

void Agent::move()
{
	if(!isAlive)
	{
		return;
	}
	angle += turnLeft/5.f;
	angle -= turnRight/5.f;
	angle = mod_2pi(angle);
	float speed = AGENT_SPEED *  moveForwardSpeed;
	Vector movePos = invert_v(vec_from_angle_v(angle));
	oldPos = pos;
	pos = pos + movePos * speed;
	if (get_norm_v(pos) > ARENA_RADIUS)
	{
		pos = oldPos;
	}
}

void Agent::shoot()
{
	if(!isAlive)
	{
		return;
	}
	if (wantToShoot && (tickCount - lastShotDate) > SHOOT_DELAY)
	{
		Bullet b;
		b.pos = pos;
		b.dir = invert_v(vec_from_angle_v(angle));
		bullets.push_back(b);
		bulletNB++;
		lastShotDate = tickCount;
	}
}

void Agent::move_bullet()
{
	for (int i = 0; i < bulletNB;)
	{
		if (get_norm_v(bullets[i].pos) > ARENA_RADIUS)
		{
			bullets.erase(bullets.begin() + i);
			bulletNB--;
			// printf("%f\n", brain);
			// brain->fitness -= .08f;
		}
		else
		{
			bullets[i].pos = bullets[i].pos + bullets[i].dir * BULLET_SPEED;
			i++;
		}
	}
}

void Agent::think(Agent* other)
{
	if(!isAlive)
	{
		return;
	}

	float angleOther = angle_btw_pos_v(pos, other->pos);
	float otherAngleDist = angle_dist(angleOther, angle);
	i_agentInAngle = (abs(otherAngleDist) < viewWide) * other->isAlive;

	bool doISeeBullet = false;
	for (int i = 0; i < other->bulletNB; ++i)
	{
		float angleBullet = angle_btw_pos_v(pos, other->bullets[i].pos);
		float bulletAngleDist = angle_dist(angleBullet, angle);
		i_bulletInAngle = abs(bulletAngleDist) < viewWide;
		if (i_bulletInAngle)
		{
			doISeeBullet = true;
			break;
		}
	}
	i_bulletInAngle = doISeeBullet;

	i_viewWide = viewWide;
	i_shooted = (tickCount - lastShotDate) < SHOOT_DELAY;

	// printf("%f %f %f %f\n", i_shooted, i_viewWide, i_bulletInAngle, i_agentInAngle);
	std::vector<float> inputs = {i_shooted, i_viewWide, i_bulletInAngle, i_agentInAngle};
	std::vector<float> outputs = brain->think(inputs);

	o_moveForward = neg_range(outputs[0]);
	// o_turnLeft = outputs[1];
	o_turnRight = outputs[1];
	o_turnLeft = outputs[2];
	o_shoot = outputs[3];
	o_viewWide = neg_range(outputs[4]);
}

void Agent::apply_outputs()
{
	// o_moveForward = neg_range(outputs[0]);
	// o_turnRight = outputs[1] * (outputs[1] > 0.1f);
	// o_turnLeft = outputs[2] * (outputs[2] > 0.1f);
	// o_shoot = neg_range(outputs[3]);
	// o_viewWide = outputs[4];
	// o_viewWide = neg_range(outputs[4]);
	// viewWide += (abs(o_viewWide) > 0.1f)*neg_range(o_viewWide > 0);
	// // viewWide += (neg_range((float)o_viewWide)/100.f)*(abs(o_viewWide) > 0.2f);
	// // viewWide = o_viewWide*(PI/3.f);
	// viewWide = clamp(viewWide, PI/200.f, PI/3.f);
	// moveForwardSpeed = neg_range(o_moveForward) * (abs(neg_range(o_moveForward)) > 0.2f);
	// if (o_turnLeft > o_turnRight)
	// {
	// 	turnAmount = o_turnLeft;
	// }
	// else
	// {
	// 	turnAmount = -o_turnRight;
	// // }
	// turnAmount = o_turnLeft - o_turnRight;
	// turnAmount *= (abs(turnAmount) > 0.2f);
	turnLeft = o_turnLeft;
	turnRight = o_turnRight;
	wantToShoot = o_shoot > 0.5f;
	viewWide += (abs(neg_range(o_viewWide) > 0.2f)) * neg_range(o_viewWide > 0) * 0.001f;
	viewWide = clamp(viewWide, PI/100.f, PI/3.f);
	moveForwardSpeed = neg_range(o_moveForward);
	moveForwardSpeed *= (abs(moveForwardSpeed) > 0.1f);
	// turnAmount = o_turnLeft - o_turnRight;
	// turnAmount = neg_range(o_turn);
	// turnAmount *= (abs(turnAmount) > 0.1f);
	wantToShoot = o_shoot > .5f;
	viewWide += neg_range(o_viewWide) * (abs(neg_range(o_viewWide)) > 0.1f) * 0.01f;
	viewWide = clamp(viewWide, PI/100.f, PI/3.f);
	// std::vector<float> outputs = {o_moveForward, o_turnRight, o_turnLeft, o_shoot, o_viewWide};
	// int maxId = 0;
	// float max = 0.f;
	// for (int i = 0; i < 5; ++i)
	// {
	// 	if (abs(outputs[i]) > max)
	// 	{
	// 		max = abs(outputs[i]);
	// 		maxId = i;
	// 	}
	// }
	// moveForwardSpeed = 0.f;
	// turnRight = 0.f;
	// turnLeft = 0.f;
	// wantToShoot = false;
	// viewChange = 0.f;
	// switch (maxId)
	// {
	//     case 0:
	//     	moveForwardSpeed = o_moveForward;
	//         break;
	
	//     case 1:
	//     	turnRight = o_turnLeft;
	//     	break;
	//     case 2:
	//     	turnLeft = o_turnRight;
	//     	break;
	//     case 3:
	//     	wantToShoot = true;
	//     	break;
	//     case 4:
	//     	viewChange = o_viewWide;
	//     	break;
	// }

	// viewWide += viewChange * 0.1f;
	// viewWide = clamp(viewWide, PI/100.f, PI/3.f);
}

// void Agent::print()
// {
// 	printf("-----\n i_agentInAngle %f\n i_bulletInAngle %f\n i_viewWide %f\n i_shooted %f\n\n o_shoot %f\n o_turnRight %f\n o_turnLeft %f\n o_moveForward %f\n o_viewWide %f\n\n Fitness %f\n-----", i_agentInAngle, i_bulletInAngle, i_viewWide, i_shooted, o_shoot, o_turnRight, o_turnLeft, o_moveForward, o_viewWide, fitness);
// }

void Agent::damage(Agent* other)
{
	if(!isAlive)
	{
		return;
	}
	for (int i = 0; i < other->bulletNB;)
	{
		if (dist_v(pos, other->bullets[i].pos) < BULLET_RADIUS)
		{
			lives--;
			other->bullets.erase(other->bullets.begin() + i);
			other->bulletNB--;
			// other->brain->fitness += 1.f;
			// brain->fitness-=0.1f;
			if (lives <= 0)
			{
				isAlive = false;
				bullets.clear();
				bulletNB = 0;
			}
		}
		else
		{
			i++;
		}
	}
}

void Agent::tick()
{
	tickCount++;
}

void Agent::update(Agent* other)
{
	think(other);
	apply_outputs();
	move();
	shoot();
	move_bullet();
	damage(other);
	tick();
}