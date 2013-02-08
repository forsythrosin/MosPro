#include "physicsEngine2D.h"


PhysicsEngine2D::PhysicsEngine2D(void)
{
	bodies = std::vector<RigidBody2D*>();
}


PhysicsEngine2D::~PhysicsEngine2D(void)
{
}



void PhysicsEngine2D::add(RigidBody2D* rb) {
	bodies.push_back(rb);
	rb->engine = this;
}

void PhysicsEngine2D::step() {
	for(int i = 0; i < bodies.size(); i++) {
		RigidBody2D* b = bodies[i];
		b->step();
	}
}

glm::vec2 PhysicsEngine2D::getGravity() {
	return glm::vec2(0, -0.0001);
}