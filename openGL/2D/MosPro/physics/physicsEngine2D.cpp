#include "physicsEngine2D.h"


PhysicsEngine2D::PhysicsEngine2D(void)
{
	bodies = std::vector<RigidBody2D*>();
	bsp = new BSPNode2D(glm::vec2(20, 20), 2);
}


PhysicsEngine2D::~PhysicsEngine2D(void)
{
}



void PhysicsEngine2D::add(RigidBody2D* rb) {
	bodies.push_back(rb);
	bsp->updatePosition(rb);
	rb->engine = this;
}

void PhysicsEngine2D::step() {
	for(unsigned int i = 0; i < bodies.size(); i++) {
		bodies[i]->step();
	}
	collisionResponse(collisionDetector->getCollisions(bsp));
}

glm::vec2 PhysicsEngine2D::getGravity() {
	return glm::vec2(0, 0.0); //-0.0001);
}

void PhysicsEngine2D::collisionResponse(std::vector<Collision2D> collisions){
	// todo
	
	for(unsigned int i = 0; i < collisions.size(); i++){
		collisions[i].resolve();
	}
}

double PhysicsEngine2D::getTotalKineticEnergy() {
	double e = 0.0;
	for(unsigned int i = 0; i < bodies.size(); i++) {
		e += bodies[i]->getKineticEnergy();
	}
	return e;
}

void PhysicsEngine2D::updatePosition(RigidBody2D *rb) {
	bsp->updatePosition(rb);
}