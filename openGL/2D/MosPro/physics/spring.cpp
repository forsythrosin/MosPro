#include "spring.h"
#include "rigidBody2D.h";
#include "movableBody2D.h";
#include "physicsEngine2D.h";
#include "../lib/debugInterface.h";
#include "mbStateMap.h"
#include "../glmIO.h"
#include <iostream>

Spring::Spring(RigidBody2D *rb1, glm::vec2 anchor1, RigidBody2D *rb2, glm::vec2 anchor2, double length, double k, double b) {
	this->rb1 = rb1;
	this->rb2 = rb2;
	this->anchor1 = anchor1;
	this->anchor2 = anchor2;
	this->length = length;
	this->k = k;
	this->b = b;
}

void Spring::applyForces(MBStateMap *in, MBStateMap *out) {

	glm::vec2 a, b;

	MovableBody2D *mb1 = NULL;
	MovableBody2D *mb2 = NULL;

	

	try {
		mb1 = dynamic_cast<MovableBody2D*>(rb1);
	} catch(std::exception e) {};

	try {
		mb2 = dynamic_cast<MovableBody2D*>(rb2);
	} catch(std::exception e) {};

	if (mb1) {
		a = mb1->getPointInGlobalCoordinates(anchor1, &in->states[mb1]);
	} else {
		a = rb1->getPointInGlobalCoordinates(anchor1);
	}

	if (mb2) {
		b = mb2->getPointInGlobalCoordinates(anchor2, &in->states[mb2]);
	} else {
		b = rb1->getPointInGlobalCoordinates(anchor2);
	}

	MBState* s1 = &in->states[mb1];
	MBState* s2 = &in->states[mb2];
	

	glm::vec2 ab = b - a;
	glm::vec2 f = (float)(k*(glm::length(ab) - length)) * glm::normalize(ab);
	
	glm::vec2 r1, r1Ort, v1,
			  r2, r2Ort, v2;

	if (mb1) {
		r1 = a - s1->position;
		r1Ort = glm::vec2(-a.y, a.x);
		v1 = s1->velocity;// +  r1Ort * (float)s1->angularVelocity;
	} else {
		r1 = a - rb1->getPosition();
		r1Ort = glm::vec2(-a.y, a.x);
		v1 = rb1->getVelocity() +  r1Ort * (float)rb1->getAngularVelocity();
	}

	if (mb2) {
		r2 = b - s2->position;

		r2Ort = glm::vec2(-b.y, b.x);
		v2 = s2->velocity;
	} else {
		r2 = b - rb2->getPosition();
		r2Ort = glm::vec2(-b.y, b.x);
		v2 = rb2->getVelocity() +  r2Ort * (float)rb2->getAngularVelocity();
	}
	 	
	glm::vec2 n = glm::normalize(ab);	
	glm::vec2 vr = v2 - v1;
	glm::vec2 dampingForce = glm::vec2(0);

	
	if (mb1) {
		mb1->impulse(a, f - dampingForce, &in->states[mb1], &out->states[mb1]);
	}

	if (mb2) {
		mb2->impulse(b, -f + dampingForce, &in->states[mb2], &out->states[mb2]);
	}

	rb1->getEngine()->getDebug()->debugLine(a, b);
}



Spring::~Spring(void) {
}


