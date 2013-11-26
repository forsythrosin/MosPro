#pragma once
#include "forceGenerator2D.h"
#include "movableBody2D.h"
#include <vector>
#include <glm/glm.hpp>

class MBStateMap;

class Gravity2D : public ForceGenerator2D
{
public:
	Gravity2D() ;
	Gravity2D(std::vector<MovableBody2D*> bodies);
	~Gravity2D(void);
	void applyForces(MBStateMap *in, MBStateMap *out);
	void addBody(MovableBody2D *rb);
	glm::vec2 getGravityConstant();
private:
	std::vector<MovableBody2D*> bodies;
	glm::vec2 gravityConstant;
};

