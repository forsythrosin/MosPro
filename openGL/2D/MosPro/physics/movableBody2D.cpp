#include "movableBody2D.h"
#include "physicsEngine2D.h"
#include "../graphics/shape2D.h"
#include "../lib/debugInterface.h"
#include "mbState.h"

MovableBody2D::MovableBody2D(Shape2D *s, glm::vec2 p, double a, glm::vec2 v, double w) : RigidBody2D(s) {
	
	currentState = MBState();

	setPosition(p);
	setAngle(a);

	currentState.velocity = v;
	currentState.angularVelocity = w;
	calculateCenterOfMass();

	calculateMass();
	calculateInertia();

	shape->setAttribs(p, a, com);
}


void MovableBody2D::update() {
	shape->setAttribs(currentState.position, currentState.angle, com);
}


glm::vec2 MovableBody2D::getCenterOfMass() {
	return com;
}

void MovableBody2D::calculateCenterOfMass() {
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
	
	com = glm::vec2(cx, cy);	
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
	glm::vec2 r = anchor - currentState.position,
		      perp;
	perp = glm::vec2(-r.y,r.x);

	currentState.velocity += j / (float)mass;
	currentState.angularVelocity += glm::dot(perp, j) / inertia;
}


glm::vec2 MovableBody2D::getPointInGlobalCoordinates(glm::vec2 localCoordinates, MBState *state) {
	glm::vec4 v(localCoordinates, 0, 1);

	glm::mat4 modelMatrix = glm::translate(
			glm::mat4(1.0f), 
			glm::vec3(state->position.x, state->position.y, 0.0f)
		)*
		glm::rotate<glm::lowp_float>(
			glm::mat4(1.0f),
			glm::degrees(state->angle),
			glm::vec3(0.0f,0.0f,1.0f)
		)*
		glm::translate(
			glm::mat4(1.0f),
			glm::vec3(-getCenterOfMass(), 0));

	v = modelMatrix*v;
	return glm::vec2(v.x, v.y);
}


void MovableBody2D::impulse(glm::vec2 anchor, glm::vec2 j, MBState *in, MBState *out) {
	in = in ? in : &currentState;
	out = out ? out : &currentState;
	
	glm::vec2 r = anchor - in->position,
		      perp;
	perp = glm::vec2(-r.y,r.x);

	out->velocity += j / (float)mass;
	out->angularVelocity += glm::dot(perp, j) / inertia;
}

void MovableBody2D::move(MBState *in, MBState *out) {
	out->position += in->velocity;
	out->angle += in->angularVelocity;
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
	return mass*glm::length2(currentState.velocity) / 2 + inertia*currentState.angularVelocity*currentState.angularVelocity / 2;
}

double MovableBody2D::getPotentialEnergy() {
	return mass * glm::dot(-engine->getGravity(), currentState.position);
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
	glm::vec2 &position = currentState.position;
	glm::vec2 &velocity = currentState.velocity;

	setPosition(position + transVect);

	if(glm::length(velocity) > 0 ){
		double vMagnitude = sqrt( abs(pow(glm::length(velocity),2 ) - 2*abs(engine->getGravity().y) * transVect.y));
		velocity = glm::normalize(velocity)*(float)vMagnitude;
	}
}


glm::vec2 MovableBody2D::getPosition() const {
	return currentState.position;
}

double MovableBody2D::getAngle() const {
	return currentState.angle;
}


void MovableBody2D::setPosition(glm::vec2 p) {
	this->currentState.position = p;
	if (engine) {
		engine->updatePosition(this);
	}	
}

void MovableBody2D::setAngle(double a) {
	this->currentState.angle = a;
}


MBState MovableBody2D::getState() {
	return currentState;
}

void MovableBody2D::setState(MBState state) {
	currentState = state;
	if (engine) {
		engine->updatePosition(this);
	}	
}


double MovableBody2D::getAngularVelocity(){
	return currentState.angularVelocity;
}

glm::vec2 MovableBody2D::getVelocity(){
	return currentState.velocity;
}


void MovableBody2D::setVelocity(glm::vec2 velocity) {
	this->currentState.velocity = velocity;
}

void MovableBody2D::setAngularVelocity(double w) {
	this->currentState.angularVelocity = w;
}