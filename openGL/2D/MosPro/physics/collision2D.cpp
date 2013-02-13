#include "collision2D.h"


RigidBody2D* Collision2D::getRb1(){
	return rb1;
}
RigidBody2D* Collision2D::getRb2(){
	return rb2;
}
glm::vec2 Collision2D::getPoint(){
	return point;
}
glm::vec2 Collision2D::getPenVector(){
	return penetrationVector;
}