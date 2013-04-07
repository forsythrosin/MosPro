#include "rigidBody2D.h"
#include "physicsEngine2D.h"
#include "../box2D.h"
#include <math.h>

#include "../graphics/shape2D.h"

RigidBody2D::RigidBody2D(Shape2D *s) {
	shape = s;
	
	calculateBoundingBox();
	engine = NULL;

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
	return localBoundingBox + getPosition();
}


glm::vec2 RigidBody2D::getPointInGlobalCoordinates(glm::vec2 localCoordinates) {
	return shape->getPointInGlobalCoordinates(localCoordinates);
}



Shape2D* RigidBody2D::getShape(){
	return this->shape;
}


PhysicsEngine2D* RigidBody2D::getEngine(){
	return engine;
}

glm::vec2 RigidBody2D::getVelocity() {
	return glm::vec2(0);
}

double RigidBody2D::getAngularVelocity() {
	return 0;
}