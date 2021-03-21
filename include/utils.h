#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <vector.h>

#define SCREEN_W 1080
#define SCREEN_H 720

#define PI 3.14

#define SHOOT_DELAY 45.f
#define BULLET_RADIUS 20.f
#define BULLET_SPEED 10.f
#define AGENT_SPEED 10.f
#define FIGHT_DURATION 2000
#define ARENA_RADIUS SCREEN_H/2.f
#define AGENTS_NB 20
#define MUTATE_RATE 0.1f

float rand_float(bool);
float rad_to_deg(float);
float sigmoid(float);
float mod_2pi(float);
float angle_dist(float, float);
float clamp(float, float, float);
float sign(float);
float neg_range(float);

#endif