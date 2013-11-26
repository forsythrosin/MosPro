#pragma once
#include "forceGenerator2D.h"
#include <glm/glm.hpp>

class RigidBody2D;

class Spring : public ForceGenerator2D
{
public:
	Spring(RigidBody2D *rb1, glm::vec2 anchor1, RigidBody2D *rb2, glm::vec2 anchor2, double length, double k, double b);
	~Spring(void);
	void applyForces();
private:
	RigidBody2D *rb1, *rb2;
	glm::vec2 anchor1, anchor2;
	double length, k, b;
};


