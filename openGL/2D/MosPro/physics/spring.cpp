#include "spring.h"
#include "rigidBody2D.h";
#include "physicsEngine2D.h";
#include "../lib/debugInterface.h";

Spring::Spring(RigidBody2D *rb1, glm::vec2 anchor1, RigidBody2D *rb2, glm::vec2 anchor2, double length, double k, double b) {
	this->rb1 = rb1;
	this->rb2 = rb2;
	this->anchor1 = anchor1;
	this->anchor2 = anchor2;
	this->length = length;
	this->k = k;
	this->b = b;
}

void Spring::applyForces() {
	glm::vec2 a = rb1->getPointInGlobalCoordinates(anchor1),
		      b = rb2->getPointInGlobalCoordinates(anchor2);

	glm::vec2 ab = b - a;
	glm::vec2 f = (float)(k*(glm::length(ab) - length)) * glm::normalize(ab);
	
	glm::vec2 r1 = a - rb1->getPosition();
	glm::vec2 r1Ort = glm::vec2(-a.y, a.x);
	glm::vec2 v1 = rb1->getVelocity() +  r1Ort * (float)rb1->getAngularVelocity();

	glm::vec2 r2 = b - rb2->getPosition();
	glm::vec2 r2Ort = glm::vec2(-b.y, b.x);
	glm::vec2 v2 = rb2->getVelocity() +  r2Ort * (float)rb2->getAngularVelocity();

	glm::vec2 n = glm::normalize(ab);	
	glm::vec2 vr = v2 - v1;
	
	glm::vec2 dampingForce = glm::dot(vr, n) * n * b / 100.0f;
	
	
	
	
	rb1->impulse(a, f);
	rb2->impulse(b, -f);



	rb1->getEngine()->getDebug()->debugLine(a, b);
}



Spring::~Spring(void) {
}


