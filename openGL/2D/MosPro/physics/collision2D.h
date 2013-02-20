#pragma once
#ifndef __COLLISION2D__
#define __COLLISION2D__
#include "rigidBody2D.h"
#include "collision2D.h"
#include <glm/glm.hpp>
#include "../glmIO.h"
#include <iomanip>

class RigidBody2D;

class Collision2D{
public:
	Collision2D(RigidBody2D* rb1N, RigidBody2D* rb2N, glm::vec2 p, glm::vec2 pVec):
	  rb1(rb1N), rb2(rb2N), point(p), penetrationVector(pVec){};
	RigidBody2D* getRb1();
	RigidBody2D* getRb2();
	glm::vec2 getPoint();
	glm::vec2 getPenVector();
	void resolve();
private:
	RigidBody2D* rb1;
	RigidBody2D* rb2;
	glm::vec2 point, penetrationVector;
};

#endif

