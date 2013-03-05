#pragma once

#include <glm/glm.hpp>
#include "../glmIO.h"
#include <iomanip>
#include <exception>

class MovableBody2D;
class RigidBody2D;

class Collision2D{
public:
	Collision2D(RigidBody2D* rb1N, RigidBody2D* rb2N, glm::vec2 p, glm::vec2 pVec, glm::vec2 lineP1, glm::vec2 lineP2):
	  rb1(rb1N), rb2(rb2N), point(p), penetrationVector(pVec), lineP1(lineP1), lineP2(lineP2){};
	RigidBody2D* getRb1();
	RigidBody2D* getRb2();
	glm::vec2 getPoint();
	glm::vec2 getPenVector();
	void resolve();
private:
	void resolve(MovableBody2D *a);
	void resolve(MovableBody2D *a, MovableBody2D *b);
	float findCLosestRotationAngle(MovableBody2D *a, glm::vec2 r, glm::vec2 n, glm::vec2 p);
	RigidBody2D* rb1;
	RigidBody2D* rb2;
	glm::vec2 point, penetrationVector, lineP1, lineP2;
};

//#endif



