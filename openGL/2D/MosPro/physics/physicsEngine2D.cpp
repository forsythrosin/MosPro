#include "physicsEngine2D.h"


PhysicsEngine2D::PhysicsEngine2D(void)
{
	bodies = std::vector<RigidBody2D*>();
	//collisionDetector = new CollisionDetector2D;
}


PhysicsEngine2D::~PhysicsEngine2D(void)
{
}



void PhysicsEngine2D::add(RigidBody2D* rb) {
	bodies.push_back(rb);
	rb->engine = this;
}

void PhysicsEngine2D::step() {
	for(int i = 0; i < bodies.size(); i++) {
		bodies[i]->step();
	}
	collisionResponse(collisionDetector->getCollisions(bodies));
}

glm::vec2 PhysicsEngine2D::getGravity() {
	return glm::vec2(0, -0.0001);
}

void PhysicsEngine2D::collisionResponse(std::vector<Collision2D> collisions){
	double e = 0.5;
	double m1, m2, i1, i2, ps1, ps2;
	glm::vec2 pv1, pv2;
	for(int i = 0; i < collisions.size(); i++){
		m1 = collisions[i].getRb1()->getMass();
		m2 = collisions[i].getRb1()->getMass();
		i1 = collisions[i].getRb1()->getInertia();
		i2 = collisions[i].getRb1()->getInertia();

		ps1 = m1*m2/(m1+m2)/m1;
		ps2 = m1*m2/(m1+m2)/m2;

		pv1 = collisions[i].getPenVector() * (float)ps1;
		pv2 = -1.0f * collisions[i].getPenVector() * (float)ps1;

		collisions[i].getRb1()->teleport(pv1);
		collisions[i].getRb2()->teleport(pv2);
		
		glm::vec2 r1 = collisions[i].getPoint() - collisions[i].getRb1()->getPosition();
		glm::vec2 r1Ort = glm::vec2(-r1.y, r1.x);
		glm::vec2 v1 = collisions[i].getRb1()->getVelocity() +  r1Ort * (float)collisions[i].getRb1()->getAngularVelocity();

		glm::vec2 r2 = collisions[i].getPoint() - collisions[i].getRb2()->getPosition();
		glm::vec2 r2Ort = glm::vec2(-r2.y, r2.x);
		glm::vec2 v2 = collisions[i].getRb2()->getVelocity() +  r2Ort * (float)collisions[i].getRb2()->getAngularVelocity();

		glm::vec2 n = glm::normalize(collisions[i].getPenVector());

		glm::vec2 vr = v2 - v1;

		if (abs(glm::dot(n,vr)) < 0.15){
			e = 0;
		}
		if(glm::dot(collisions[i].getPenVector(),vr) > 0){
			glm::vec2 jr = (-(float)(1 + e) * vr * n)/(float)(1/m1 + 1/m2 + 1/i1 * pow(glm::dot(n,r1Ort),2) + i/i2 * pow(glm::dot(n,r2Ort),2));
			glm::vec2 j = glm::length(jr)*n;
			collisions[i].getRb1()->impulse(collisions[i].getPoint(),j);
			collisions[i].getRb2()->impulse(collisions[i].getPoint(),-j);
		}
	}
}