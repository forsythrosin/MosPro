#include "collision2D.h"
#include "movableBody2D.h"
#include "immovableBody2D.h"
#include "physicsEngine2D.h"
#include "../lib/debugGL.h"
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
	double e = 0.8;

	double m1, m2, i1, i2;
	float inverseInertia, lm1, lm2,theta1, theta2;
	glm::vec2 pv1, pv2, r1, r1Ort, r2, r2Ort, v2, v1, vr, n;

	m1 = a->getMass();
	m2 = b->getMass();
	i1 = a->getInertia();
	i2 = b->getInertia();

	//ps1 = m2/(m1+m2);
	//ps2 = m1/(m1+m2);

	inverseInertia = 1 / (1/m1 + 1/m2 + 1/i1 + 1/i2);
    lm1 = 1/m1 * inverseInertia;
    lm2 = 1/m2 * inverseInertia;

	pv1 = getPenVector() * lm1;
	pv2 = -1.0f * getPenVector() * lm2;

	lineP1 += pv2;
	lineP2 += pv2;

	r1 = getPoint() - a->getPosition();
	n = glm::normalize(getPenVector());

	theta1 = Collision2D::findCLosestRotationAngle(a, r1, n, a->getPosition() + pv1);
	//std::cout << "interpenetration rotation angle = " << theta1 << std::endl;
	theta2 = 0;

	a->teleport(pv1, theta1);
	b->teleport(pv2, theta2);

	r1 = getPoint() - a->getPosition();
	r1Ort = glm::vec2(-r1.y, r1.x);
	v1 = a->getVelocity() +  r1Ort * (float)a->getAngularVelocity();

	r2 = getPoint() - b->getPosition();
	r2Ort = glm::vec2(-r2.y, r2.x);
	v2 = b->getVelocity() +  r2Ort * (float)b->getAngularVelocity();
		
	vr = v2 - v1;
	
	if(glm::length(vr) < 0.1){
		e = 0;
	}

	if(glm::dot(getPenVector(),vr) > 0){
		//Friction
		double mu = 1;
		glm::vec2 t = glm::vec2(-n.y,n.x);
		double x = glm::dot(vr,t);
		double sign = (x > 0) ? 1 : ((x < 0) ? -1 : 0); //Is there a better way for this?
		t = (float)-sign*t;

		//Impulse
		double jr = -(1 + e) * glm::dot(vr, n)/(1.0/m1 + 1.0/m2 + (1.0/i1) * pow(glm::dot(n,r1Ort),2) + (1.0/i2) * pow(glm::dot(n,r2Ort),2));
		glm::vec2 j = (float)abs(jr)*n;

		//Friction Impulse
		double fjr = abs(glm::dot(vr,t))/((1/m1) + (1/m2) +  (1/i1) * pow(glm::dot(t,r1Ort),2) + (1/i2)*pow(glm::dot(t,r2Ort),2));
		glm::vec2 fj = (float)(mu*fjr)*t;

		a->impulse(getPoint(),j-fj);
		a->getEngine()->getDebug()->debugVector(getPoint(),fj);
		b->impulse(getPoint(),-j+fj);
	}
}

void Collision2D::resolve(MovableBody2D *a) {
	double e = 0.5;

	double m, i;
	float inverseInertia, lm, theta;
	glm::vec2 pv, r, rOrt, v, n;

	m = a->getMass();
	i = a->getInertia();

	inverseInertia = 1 / (1/m + 1/i);
	lm = 1/m * inverseInertia;

	pv = getPenVector() * lm;

	r = getPoint() - a->getPosition();
	n = glm::normalize(getPenVector());

	theta = Collision2D::findCLosestRotationAngle(a, r, n, a->getPosition() + pv);

	a->teleport(pv, theta);

	r = getPoint() - a->getPosition();
	rOrt = glm::vec2(-r.y, r.x);

	v = a->getVelocity() +  rOrt * (float)a->getAngularVelocity();

	if(glm::length(v) < 0.1){
		e = 0;
	}

	if(glm::dot(getPenVector(),v) < 0){

		//Friction
		double mu = 1;
		glm::vec2 t = glm::vec2(-n.y,n.x);
		double x = glm::dot(v,t);
		double sign = (x > 0) ? 1 : ((x < 0) ? -1 : 0); //Is there a better way for this?
		t = (float)-sign*t;

		//Impulse
		double jr = -(1 + e) * glm::dot(v, n)/(1.0/m + (1.0/i) * pow(glm::dot(n,rOrt),2));
		glm::vec2 j = (float)abs(jr)*n;

		//Friction
		double fjr = abs(glm::dot(v,t))/((1/m) + (1/i) *glm::dot(t,rOrt)*glm::dot(t,rOrt));
		glm::vec2 fj = (float)(mu*fjr)*t;

		a->impulse(getPoint(),j+fj);
		a->getEngine()->getDebug()->debugVector(getPoint(),fj);
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

float Collision2D::findCLosestRotationAngle(MovableBody2D *a, glm::vec2 r, glm::vec2 n, glm::vec2 p){
	float theta = 0;
	glm::vec2 v = lineP1 - lineP2;

	//std::cout << "tangent = " << v << std::endl;

	glm::vec2 rOrt = glm::vec2(-r.y, r.x);

	float xrt = pow(v.y, 2) * pow((2* lineP2.y* v.x-2* lineP2.x* v.y-2* p.y* v.x+2* p.x* v.y), 2) -
				4* (pow(v.y, 2)+pow(v.x, 2))* (pow(lineP2.y, 2) * pow(v.x, 2) - 2* lineP2.y * lineP2.x* v.y* v.x-2* lineP2.y* p.y* pow(v.x, 2) +
				2* lineP2.y* p.x* v.y* v.x+pow(lineP2.x, 2) * pow(v.y, 2)+2* lineP2.x* p.y* v.y* v.x-2* lineP2.x *
				p.x* pow(v.y, 2)+pow(p.y, 2) * pow(v.x, 2)-2* p.y* p.x* v.y* v.x+pow(p.x, 2) * pow(v.y, 2) -
				pow(r.x, 2) * pow(v.x, 2)-pow(r.y, 2) * pow(v.x, 2));
	float xrst = v.y* (2* lineP2.y* v.x-2* lineP2.x* v.y-2* p.y* v.x+2* p.x* v.y);
    float xqt = (2* (pow(v.y, 2)+pow(v.x, 2)));

	float x1 = (sqrt(abs(xrt)) - xrst) / xqt;
	float x2 = (-sqrt(abs(xrt)) - xrst) / xqt;

	float y11 = sqrt(glm::dot(r,r) - pow(x1, 2));
    float y12 = sqrt(glm::dot(r,r) - pow(x2, 2));
    float y21 = -y11;
    float y22 = -y12;

	glm::vec2 z[4];
	z[0] = glm::vec2(x1, y11);
	z[1] = glm::vec2(x1, y21);
	z[2] = glm::vec2(x2, y12);
	z[3] = glm::vec2(x2, y22);

	//std::cout << "z[0] = " << z[0] << ", z[1] = " << z[1] << std::endl;
	
	glm::vec2 q;
	for(int l = 0; l < 3; ++l){
		for(int m=l+1; m < 4; ++m){
			glm::vec2 c = z[l] + z[m];
			if(glm::length2(c) > 0.01 && glm::dot(c, r) > 0 && abs(glm::dot(c, v)) < 0.001){
				float theta1 = glm::acos(glm::dot(glm::normalize(z[l]), glm::normalize(r)));
				float theta2 = glm::acos(glm::dot(glm::normalize(z[m]), glm::normalize(r)));
				if(theta1 < theta2){
					theta = glm::sign(glm::dot(n, rOrt)) * theta1;
					q = z[l];
				}
				else{
					theta = glm::sign(glm::dot(n, rOrt)) * theta2;
					q = z[m];
				}
				point = p + q;
				if(abs(theta) > 1.57079632679 || theta != theta){
					/*std::cout << "loop is at: l = " << l << ", m = " << m << std::endl;
					std::cout << "r = " << r << ", v = " << v << ", denominator = " << xqt << std::endl;
					std::cout << "this must be the wrong rotation: " << theta << " rads" << std::endl;
					std::cout << "acos param: dot = " << glm::dot(glm::normalize(z[m]), glm::normalize(r)) << std::endl;
					std::cout << "theta1 = " << theta1 << ", theta2 = " << theta2 << std::endl;
					std::cout << "sign = " << glm::sign(glm::dot(n, rOrt)) << std::endl;
					std::cout << "position changed from: " << p << " to: " << point << std::endl;
					std::cout << "z[0] = " << z[0] << ", z[1] = " << z[1] << ", z[2] = "<< z[2] << ", z[3] = "<< z[3] << std::endl;*/
					theta = 0;
				}
				return theta;
			}
		}
	}
	return theta;
}