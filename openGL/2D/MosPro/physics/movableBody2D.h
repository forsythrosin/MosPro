#pragma once

#include "rigidBody2D.h"
#include "mbState.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Shape2D;


class MovableBody2D : public RigidBody2D
{
	public:
		MovableBody2D::MovableBody2D(Shape2D *s, glm::vec2 p, double a, glm::vec2 v, double w);
		~MovableBody2D(void);

		void update();

		void impulse(glm::vec2 anchor, glm::vec2 j);
		void impulse(glm::vec2 anchor, glm::vec2 j, MBState *in, MBState *out);
		void move(MBState *in = NULL, MBState *out = NULL);

		void teleport(glm::vec2 transVect);

		// mass and inertia
		double getMass();
		double getInertia();
		

		double getKineticEnergy();
		double getPotentialEnergy();

		MBState getState();
		void setState(MBState state);
	
		double getAngularVelocity();
		glm::vec2 getVelocity();

		glm::vec2 getPointInGlobalCoordinates(glm::vec2 localCoordinates,  MBState *state);

		glm::vec2 getPosition() const;
		double getAngle() const;

		void setPosition(glm::vec2 p);
		void setAngle(double a);

		void setVelocity(glm::vec2 velocity);
		void setAngularVelocity(double w);	
		glm::vec2 getCenterOfMass();
	private:
		MBState currentState;

		void calculateMass();
		void calculateInertia();
		
		double mass;
		double inertia;

		void calculateCenterOfMass();
		

		glm::vec2 currentForce;

	friend PhysicsEngine2D;
};
