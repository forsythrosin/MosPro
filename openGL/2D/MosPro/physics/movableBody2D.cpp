#include "movableBody2D.h"
#include "physicsEngine2D.h"
#include "../graphics/shape2D.h"
#include "../lib/debugInterface.h"

MovableBody2D::MovableBody2D(Shape2D *s, glm::vec2 p, double a, glm::vec2 v, double w) : RigidBody2D(s, p, a) {
	velocity = v;
	angularVelocity = w;
	com = getCenterOfMass();

	calculateMass();
	calculateInertia();

}

void MovableBody2D::step() {

	glm::vec2 vBefore = velocity;
	velocity += engine->getGravity();
	
	glm::vec2 meanVelocity = 0.5f * (vBefore + velocity);

	angle += angularVelocity;
	setPosition(position + meanVelocity);
	
	//position += meanVelocity;

	shape->setAttribs(position, angle, com);

	//getEngine()->getDebug()->debugBox(getBoundingBox());


	// naive collision response with walls

}


glm::vec2 MovableBody2D::getCenterOfMass() {
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


void MovableBody2D::calculateMass() {
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


void MovableBody2D::impulse(glm::vec2 anchor, glm::vec2 j) {
	glm::vec2 r = anchor - position,
		      perp;
	perp = glm::vec2(-r.y,r.x);

	velocity += j / (float)mass;
	angularVelocity += glm::dot(perp, j) / inertia;
}

void MovableBody2D::calculateInertia() {

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

double MovableBody2D::getKineticEnergy() {
	return mass*glm::length2(velocity) / 2 + inertia*angularVelocity*angularVelocity / 2;
}

double MovableBody2D::getPotentialEnergy() {
	return mass * glm::dot(-engine->getGravity(), position);
}


double MovableBody2D::getMass(){
	return this->mass;
}
double MovableBody2D::getInertia(){
	return this->inertia;
}

MovableBody2D::~MovableBody2D(void) {
}


void MovableBody2D::teleport(glm::vec2 transVect){
	setPosition(position + transVect);
	
	if(glm::length(velocity) > 0 ){
		double vMagnitude = sqrt( abs(pow(glm::length(velocity),2 ) - 2*abs(engine->getGravity().y) * transVect.y));
		velocity = glm::normalize(velocity)*(float)vMagnitude;
	}

}


double MovableBody2D::getAngularVelocity(){
	return angularVelocity;
}

glm::vec2 MovableBody2D::getVelocity(){
	return velocity;
}


void MovableBody2D::setVelocity(glm::vec2 velocity) {
	this->velocity = velocity;
}

void MovableBody2D::setAngularVelocity(double w) {
	this->angularVelocity = w;
}