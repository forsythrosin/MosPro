#include "rigidBody2D.h"
#include "physicsEngine2D.h"
#include "../box2D.h"
#include <math.h>

#include "../graphics/shape2D.h"

RigidBody2D::RigidBody2D(Shape2D *s, glm::vec2 p, double a) {
	shape = s;
	position = p;
	angle = a;
	calculateBoundingBox();
	
	shape->setAttribs(position, angle, com);
}

void RigidBody2D::step() {
	// do nothing.
}






void RigidBody2D::calculateBoundingBox() {
	std::vector<glm::vec2> v = shape->getLocalVertices();
	int n = v.size();
	
	double distance, max = glm::length(v[0] - com);

	for (int i = 0; i < n; i++) {
		distance = glm::length(v[i] - com);
		if (distance > max) {
			max = distance;
		}
	}
	
	localBoundingBox = Box2D(-max, -max, max, max);
}

const Box2D RigidBody2D::getBoundingBox() const {
	return localBoundingBox + position;
}






void RigidBody2D::setPosition(glm::vec2 position) {
	this->position = position;
	if (engine) {
		engine->updatePosition(this);
	}	
}

glm::vec2 RigidBody2D::getPosition() {
	return position;
}

Shape2D* RigidBody2D::getShape(){
	return this->shape;
}


double RigidBody2D::getAngle(){
	return angle;
}


PhysicsEngine2D* RigidBody2D::getEngine(){
	return engine;
}