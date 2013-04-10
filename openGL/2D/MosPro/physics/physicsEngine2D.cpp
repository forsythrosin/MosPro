#include "physicsEngine2D.h"
#include "bspNode2D.h"
#include "rigidBody2D.h"
#include "movableBody2D.h"
#include "immovableBody2D.h"
#include "collision2D.h"
#include "collisionDetector2D.h"
#include "mbStateMap.h"

#include <iostream>

PhysicsEngine2D::PhysicsEngine2D(Box2D bounds)
{
	this->bounds = bounds;
	movableBodies = std::vector<MovableBody2D*>();
	immovableBodies = std::vector<ImmovableBody2D*>();
	bsp = new BSPNode2D(glm::vec2(bounds.p1.x-bounds.p0.x, bounds.p1.y-bounds.p0.y), 3);
	gravity = Gravity2D();
	forceGenerators.push_back(&gravity);
}


PhysicsEngine2D::~PhysicsEngine2D(void)
{
}

std::vector<MovableBody2D*> PhysicsEngine2D::getMovableBodies() {
	return movableBodies;
}



void PhysicsEngine2D::add(MovableBody2D *rb) {
	movableBodies.push_back(rb);
	gravity.addBody(rb);

	bsp->updatePosition(rb);
	rb->engine = this;
	
}

void PhysicsEngine2D::add(ImmovableBody2D *rb) {
	immovableBodies.push_back(rb);
	bsp->updatePosition((RigidBody2D*)rb);
	rb->engine = this;
}

void PhysicsEngine2D::add(ForceGenerator2D *fg) {
	forceGenerators.push_back(fg);
}

void PhysicsEngine2D::generateState(MBStateMap *in, MBStateMap *out) {
	for(unsigned int i = 0; i < forceGenerators.size(); i++) {
		ForceGenerator2D *fg = forceGenerators[i];
		fg->applyForces(in, out);
	}

	for(unsigned int i = 0; i < movableBodies.size(); i++) {
		movableBodies[i]->move(&in->states[movableBodies[i]], &out->states[movableBodies[i]]);
	}
}

void PhysicsEngine2D::step() {
	MBStateMap y(movableBodies, true);

	MBStateMap k1(movableBodies, false);
	MBStateMap k2(movableBodies, false);
	MBStateMap k3(movableBodies, false);
	MBStateMap k4(movableBodies, false);

	generateState(&y, &k1);
	generateState(&(y + k1/2), &k2);
	generateState(&(y + k2/2), &k3);
	generateState(&(y + k3), &k4);
	y += (k1 + k2*2 + k3*2 + k4)/6;

	//std::cout << y.states[0].velocity << std::endl;
	

	for(unsigned int i = 0; i < movableBodies.size(); i++) {
		MovableBody2D* mb = movableBodies[i];
		mb->setState(y.states[mb]);
		mb->update();
	}
	collisionResponse(collisionDetector->getCollisions(bsp));
}


void PhysicsEngine2D::collisionResponse(std::vector<Collision2D> collisions){
	// todo
	
	for(unsigned int i = 0; i < collisions.size(); i++){
		collisions[i].resolve();
	}
}

glm::vec2 PhysicsEngine2D::getGravity() {
	return gravity.getGravityConstant();
}

double PhysicsEngine2D::getTotalKineticEnergy() {
	double e = 0.0;
	for(unsigned int i = 0; i < movableBodies.size(); i++) {
		e += movableBodies[i]->getKineticEnergy();
	}
	return e;
}


double PhysicsEngine2D::getTotalPotentialEnergy(){
	double e = 0.0;
	for(unsigned int i = 0; i < movableBodies.size(); i++){
		e += movableBodies[i]->getPotentialEnergy();
	}
	return e;
}
void PhysicsEngine2D::setDebug(DebugInterface* debug){
	this->debug = debug;
}

DebugInterface* PhysicsEngine2D::getDebug(){
	return debug;
}

void PhysicsEngine2D::updatePosition(RigidBody2D *rb) {
	bsp->updatePosition(rb);
}