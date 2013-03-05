#pragma once

#include "rigidBody2D.h"
class Shape2D;

class MovableBody2D : public RigidBody2D
{
	public:
		MovableBody2D::MovableBody2D(Shape2D *s, glm::vec2 p, double a, glm::vec2 v, double w);
		~MovableBody2D(void);

		void step();

		void impulse(glm::vec2 anchor, glm::vec2 j);
		void teleport(glm::vec2 transVect, float rotation);

		// mass and inertia
		double getMass();
		double getInertia();
		

		double getKineticEnergy();
		double getPotentialEnergy();

	
		double getAngularVelocity();
		glm::vec2 getVelocity();

		void setVelocity(glm::vec2 velocity);
		void setAngularVelocity(double w);	

	


	private:
		glm::vec2 velocity;
		double angularVelocity;
	
		void calculateMass();
		void calculateInertia();
		

		double mass;
		double inertia;

		glm::vec2 getCenterOfMass();

	friend PhysicsEngine2D;
};
