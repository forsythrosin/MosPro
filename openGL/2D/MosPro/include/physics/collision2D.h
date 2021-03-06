#pragma once

#include <glm/glm.hpp>
#include "../glmIO.h"
#include <iomanip>
#include <exception>

class MovableBody2D;
class RigidBody2D;

class Collision2D{
public:
	Collision2D(RigidBody2D* rb1N, RigidBody2D* rb2N, glm::vec2 p, glm::vec2 pVec):
	  rb1(rb1N), rb2(rb2N), point(p), penetrationVector(pVec){};
	RigidBody2D* getRb1();
	RigidBody2D* getRb2();
	RigidBody2D* getOther(RigidBody2D*);
	glm::vec2 getPoint();
	glm::vec2 getPenVector();
	void resolve();
private:
	void resolve(MovableBody2D *a);
	void resolve(MovableBody2D *a, MovableBody2D *b);
	RigidBody2D* rb1;
	RigidBody2D* rb2;
	glm::vec2 point, penetrationVector;
};

//#endif



