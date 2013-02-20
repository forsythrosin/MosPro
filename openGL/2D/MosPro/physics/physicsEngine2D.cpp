#include "physicsEngine2D.h"


PhysicsEngine2D::PhysicsEngine2D(void)
{
	bodies = std::vector<RigidBody2D*>();
	//collisionDetector = new CollisionDetector2D;
}


PhysicsEngine2D::~PhysicsEngine2D(void)
{
}



void PhysicsEngine2D::add(RigidBody2D* rb) {
	bodies.push_back(rb);
	rb->engine = this;
}

void PhysicsEngine2D::step() {
	for(unsigned int i = 0; i < bodies.size(); i++) {
		bodies[i]->step();
	}
	collisionResponse(collisionDetector->getCollisions(bodies));
}

glm::vec2 PhysicsEngine2D::getGravity() {
	return glm::vec2(0, -0);
}

void PhysicsEngine2D::collisionResponse(std::vector<Collision2D> collisions){
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

double PhysicsEngine2D::getTotalPotentialEnergy(){
	double e = 0.0;
	for(unsigned int i = 0; i < bodies.size(); i++){
		e += bodies[i]->getPotentialEnergy();
	}
	return e;
}
void PhysicsEngine2D::setDebug(DebugInterface* debug){
	this->debug = debug;
}

DebugInterface* PhysicsEngine2D::getDebug(){
	return debug;
}