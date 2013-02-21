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
void Collision2D::resolve(){
	double e = 1;

	double m1, m2, i1, i2, ps1, ps2;
	glm::vec2 pv1, pv2;

	m1 = getRb1()->getMass();
	m2 = getRb2()->getMass();
	i1 = getRb1()->getInertia();
	i2 = getRb2()->getInertia();

	ps1 = m2/(m1+m2);
	ps2 = m1/(m1+m2);

	pv1 = getPenVector() * (float)ps1;
	pv2 = -1.0f * getPenVector() * (float)ps2;



	
	glm::vec2 r1 = getPoint() - getRb1()->getPosition();
	glm::vec2 r1Ort = glm::vec2(-r1.y, r1.x);
	glm::vec2 v1 = getRb1()->getVelocity() +  r1Ort * (float)getRb1()->getAngularVelocity();

	glm::vec2 r2 = getPoint() - getRb2()->getPosition();
	glm::vec2 r2Ort = glm::vec2(-r2.y, r2.x);
	glm::vec2 v2 = getRb2()->getVelocity() +  r2Ort * (float)getRb2()->getAngularVelocity();

	glm::vec2 n = glm::normalize(getPenVector());

	getRb1()->teleport(pv1);
	getRb2()->teleport(pv2);
		
	glm::vec2 vr = v2 - v1;

	/*if (glm::length(vr) < 0.15){
		e = 0;
		std::cout << "e = 0" << std::endl;
	}*/

	if(glm::dot(getPenVector(),vr) > 0){
		double jr = -(1 + e) * glm::dot(vr, n)/(1.0/m1 + 1.0/m2 + (1.0/i1) * pow(glm::dot(n,r1Ort),2) + (1.0/i2) * pow(glm::dot(n,r2Ort),2));
		glm::vec2 j = (float)abs(jr)*n;
		getRb1()->impulse(getPoint(),j);
		getRb2()->impulse(getPoint(),-j);
	}
}
