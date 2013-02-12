#include "rigidBody2D.h"


RigidBody2D::RigidBody2D(Shape2D *s, glm::vec2 p, glm::vec2 v, double a, double w) {
	shape = s;
	position = p;
	angle = a;
	velocity = v;
	angularVelocity = w;

	com = getCenterOfMass();

	calculateMass();
	calculateInertia();

	//std::cout << "com: " << com;

	shape->setAttribs(position, angle, com);

}

void RigidBody2D::step() {

	glm::vec2 vBefore = velocity;
	velocity += engine->getGravity();
	
	glm::vec2 meanVelocity = 0.5f * (vBefore + velocity);

	angle += angularVelocity;
	std::cout << angle << std::endl;
	position += meanVelocity;

	shape->setAttribs(position, angle, com);


	// naive collision response with walls

	if (position.y < -10 || position.y > 10) {
		velocity.y *= -1;
	}

	if (position.x < -10 || position.x > 10) {
		velocity.x *= -1;
	}
}




glm::vec2 RigidBody2D::getCenterOfMass() {
	std::vector<glm::vec2> v = shape->getLocalVertices();
	int n = v.size();

	double cx = 0, cy = 0, doubleArea = 0;

	for (int i = 0; i < n - 1; i++) {
		double x0 = v[i].x;
		double x1 = v[i + 1].x;
		double y0 = v[i].y;
		double y1 = v[i + 1].y;

		cx += (x0 + x1)*(x0*y1 - x1*y0);
		cy += (y0 + y1)*(x0*y1 - x1*y0);
		doubleArea += x0*y1 - x1*y0;
	}

	cx /= 3 * doubleArea;
	cy /= 3 * doubleArea;
	
	return glm::vec2(cx, cy);	
}

void RigidBody2D::calculateInertia() {

	std::vector<glm::vec2> v = shape->getLocalVertices();
	int n = v.size();
	
	inertia = 0.0f;

	for (int i = 0; i < n - 1; i++) {
		glm::vec2 p0 = v[i];
		glm::vec2 p1 = v[i + 1];

		glm::vec2 b = p1 - p0;
		glm::vec2 bhat = glm::normalize(b);

		glm::vec2 a = glm::dot(p1, bhat) * bhat;
		glm::vec2 h = p1 - a;

		double aLen = sqrt(glm::length2(a));
		double bLen = sqrt(glm::length2(b));
		double hLen = sqrt(glm::length2(h));

		glm::vec2 c = (p0 + p1 / 3.0f);

		inertia += (bLen*bLen*bLen*hLen - bLen*bLen*hLen*aLen + bLen*hLen*aLen*aLen + bLen*hLen*hLen*hLen)
			       / 36.0f + bLen*hLen/2.0f * glm::length2(c);
	}
}

void RigidBody2D::calculateMass() {
	mass = 0;

	std::vector<glm::vec2> v = shape->getLocalVertices();
	int n = v.size();
		
	for (int i = 0; i < n - 1; i++) {
		double x0 = v[i].x;
		double x1 = v[i + 1].x;
		double y0 = v[i].y;
		double y1 = v[i + 1].y;

		mass += x0*y1 - x1*y0;
	}
	mass /= 2;
}

double RigidBody2D::getKineticEnergy() {
	return mass*glm::length2(velocity) / 2 + inertia*angularVelocity*angularVelocity / 2;
}

double RigidBody2D::getPotentialEnergy() {
	return 0.0; //mass * glm::dot(engine->getGravity(), position);
}

void RigidBody2D::impulse(glm::vec2 anchor, glm::vec2 j) {
	glm::vec2 r = anchor - position,
		      perp;
	perp = glm::vec2(-r.y,r.x);

	velocity += j / (float)mass;
	angularVelocity += glm::dot(perp, j) / inertia;
}

glm::vec2 RigidBody2D::getPosition() {
	return position;
}

Shape2D* RigidBody2D::getShape(){
	return this->shape;
}

double RigidBody2D::getMass(){
	return this->mass;
}
double RigidBody2D::getInertia(){
	return this->inertia;
}

void RigidBody2D::teleport(glm::vec2 transVect){
	position -= transVect;
	/*double vMagnitude = sqrt(glm::length2(velocity) - 2*abs(engine->getGravity().y) * transVect.y);
	if(velocity.x > 0 && velocity.y > 0){
		velocity /= (float)(glm::length(velocity) * vMagnitude);
	}*/
}

double RigidBody2D::getAngularVelocity(){
	return angularVelocity;
}

glm::vec2 RigidBody2D::getVelocity(){
	return velocity;
}