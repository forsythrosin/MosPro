#include "collision2D.h"
#include "movableBody2D.h"
#include "immovableBody2D.h"
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

void Collision2D::resolve(MovableBody2D *a, MovableBody2D *b) {
	double e = 1;

	double m1, m2, i1, i2, ps1, ps2;
	glm::vec2 pv1, pv2;

	m1 = a->getMass();
	m2 = a->getMass();
	i1 = b->getInertia();
	i2 = b->getInertia();

	ps1 = m2/(m1+m2);
	ps2 = m1/(m1+m2);

	pv1 = getPenVector() * (float)ps1;
	pv2 = -1.0f * getPenVector() * (float)ps2;

	glm::vec2 r1 = getPoint() - a->getPosition();
	glm::vec2 r1Ort = glm::vec2(-r1.y, r1.x);
	glm::vec2 v1 = a->getVelocity() +  r1Ort * (float)a->getAngularVelocity();

	glm::vec2 r2 = getPoint() - b->getPosition();
	glm::vec2 r2Ort = glm::vec2(-r2.y, r2.x);
	glm::vec2 v2 = b->getVelocity() +  r2Ort * (float)b->getAngularVelocity();

	glm::vec2 n = glm::normalize(getPenVector());

	a->teleport(pv1);
	b->teleport(pv2);
		
	glm::vec2 vr = v2 - v1;

	if(glm::dot(getPenVector(),vr) > 0){
		double jr = -(1 + e) * glm::dot(vr, n)/(1.0/m1 + 1.0/m2 + (1.0/i1) * pow(glm::dot(n,r1Ort),2) + (1.0/i2) * pow(glm::dot(n,r2Ort),2));
		glm::vec2 j = (float)abs(jr)*n;
		a->impulse(getPoint(),j);
		b->impulse(getPoint(),-j);
	}
}

void Collision2D::resolve(MovableBody2D *a) {
	double e = 1;

	double m, i;
	glm::vec2 pv;

	m = a->getMass();
	i = a->getInertia();

	pv = getPenVector();

	glm::vec2 r = getPoint() - a->getPosition();
	glm::vec2 rOrt = glm::vec2(-r.y, r.x);
	glm::vec2 v = a->getVelocity() +  rOrt * (float)a->getAngularVelocity();

	glm::vec2 n = glm::normalize(getPenVector());
	a->teleport(pv);
		
	if(glm::dot(getPenVector(),v) > 0){
		double jr = -(1 + e) * glm::dot(v, n)/(1.0/m + (1.0/i) * pow(glm::dot(n,rOrt),2));
		glm::vec2 j = (float)abs(jr)*n;
		a->impulse(getPoint(),j);
	}


}


void Collision2D::resolve(){

	MovableBody2D *a = NULL;
	MovableBody2D *b = NULL;

	try {
		a = dynamic_cast<MovableBody2D*>(rb1);
	} catch(std::exception e) {};

	try {
		b = dynamic_cast<MovableBody2D*>(rb2);
	} catch(std::exception e) {};

	if (a && b) {
		resolve(a, b);
	} else if (a = a ? a : b) {
		resolve(a);
	} else {
		assert(false);
	}

}
