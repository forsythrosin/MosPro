#include "gravity2D.h"
#include "../lib/debugInterface.h"
#include "physicsEngine2D.h"

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


void Gravity2D::applyForces() {
	for (int i = 0; i < bodies.size(); i++) {
		//bodies[i]->getEngine()->getDebug()->debugVector(bodies[i]->getPosition(), gravityConstant*(float)bodies[i]->getMass());
		bodies[i]->impulse(bodies[i]->getPosition(), gravityConstant*(float)bodies[i]->getMass());
	}
}

void Gravity2D::addBody(MovableBody2D *rb) {
	bodies.push_back(rb);
}
