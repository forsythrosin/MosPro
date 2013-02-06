#include "rigidBody2D.h"
#include <iostream>

RigidBody2D::RigidBody2D(Shape2D *s, glm::vec2 p, glm::vec2 v, double a, double w) {
	shape = s;
	position = p;
	angle = a;
	velocity = v;
	angularVelocity = w;

	glm::vec2 com = getCenterOfMass();
	position += com;

	calculateMass();
	calculateInertia();

}

void RigidBody2D::step() {

	glm::vec2 vBefore = velocity;
	velocity += engine->getGravity();
	
	glm::vec2 meanVelocity = 0.5f * (vBefore + velocity);

	angle += angularVelocity;
	position += meanVelocity;

	shape->setAttribs(position, angle, 1.0);


	// naive collision response with walls

	if (position.y < -1 || position.y > 1) {
		velocity.y *= -1;
	}

	if (position.x < -1 || position.x > 1) {
		velocity.x *= -1;
	}
}



// Private methods

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
	
	glm::perp(r, perp);

	velocity.x += j.x / mass;
	velocity.y += j.y / mass;

	angularVelocity += glm::dot(perp, j) / inertia;
}