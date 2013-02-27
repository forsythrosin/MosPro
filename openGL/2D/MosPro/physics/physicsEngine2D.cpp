#include "physicsEngine2D.h"


PhysicsEngine2D::PhysicsEngine2D(Box2D bounds)
{
	this->bounds = bounds;
	movableBodies = std::vector<MovableBody2D*>();
	immovableBodies = std::vector<ImmovableBody2D*>();
	bsp = new BSPNode2D(glm::vec2(bounds.p1.x-bounds.p0.x, bounds.p1.y-bounds.p0.y), 3);
	
}


PhysicsEngine2D::~PhysicsEngine2D(void)
{
}



void PhysicsEngine2D::add(MovableBody2D* rb) {
	movableBodies.push_back(rb);
	bsp->updatePosition(rb);
	rb->engine = this;
}

void PhysicsEngine2D::add(ImmovableBody2D* rb) {
	immovableBodies.push_back(rb);
	bsp->updatePosition(rb);
	rb->engine = this;
}

void PhysicsEngine2D::step() {
	for(unsigned int i = 0; i < movableBodies.size(); i++) {
		MovableBody2D *rb = movableBodies[i];
		
		rb->step();
		glm::vec2 v = rb->getVelocity();

		if (rb->getPosition().x < bounds.p0.x || rb->getPosition().x > bounds.p1.x) {
			v.x *= -1;
			rb->setVelocity(v);
		}
		if (rb->getPosition().y < bounds.p0.y || rb->getPosition().y > bounds.p1.y) {
			v.y *= -1;
			rb->setVelocity(v);
		}


	}
	collisionResponse(collisionDetector->getCollisions(bsp));
	
	
	
	//collisionResponse(collisionDetector->getCollisions(bodies));
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