#include "gravity2D.h"
#include "../lib/debugInterface.h"
#include "physicsEngine2D.h"
#include "mbStateMap.h"
#include "movableBody2D.h"

Gravity2D::Gravity2D(std::vector<MovableBody2D*> bodies)
{
	this->bodies = bodies;
	gravityConstant = glm::vec2(0, -0.001);
}
Gravity2D::Gravity2D(){
	gravityConstant = glm::vec2(0, -0.001);
}

Gravity2D::~Gravity2D(void)
{
}


glm::vec2 Gravity2D::getGravityConstant() {
	return gravityConstant;
}


void Gravity2D::applyForces(MBStateMap *in, MBStateMap *out) {
	for (int i = 0; i < bodies.size(); i++) {	
		bodies[i]->impulse(bodies[i]->getPosition(), gravityConstant*(float)bodies[i]->getMass(), &in->states[bodies[i]], &out->states[bodies[i]]);
	}
}

void Gravity2D::addBody(MovableBody2D *rb) {
	bodies.push_back(rb);
}
