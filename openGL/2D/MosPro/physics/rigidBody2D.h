#ifndef __RIGIDBODY__
#define __RIGIDBODY__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/norm.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include "../graphics/shape2D.h"
#include "physicsEngine2D.h"
#include "../box2D.h"
#include <iostream>
#include <glm\glm.hpp>
#include "../glmIO.h"


class PhysicsEngine2D;

class RigidBody2D {
	public:
		RigidBody2D(Shape2D *s, glm::vec2 p, glm::vec2 v, double angle = 0, double w = 0);

		void step();
		void impulse(glm::vec2 anchor, glm::vec2 j);
		void teleport(glm::vec2 transVect);

		glm::vec2 getPosition();
		void setPosition(glm::vec2 pos);

		double getMass();
		double getInertia();
		const Box2D getBoundingBox() const;
		
		Shape2D* getShape();
		PhysicsEngine2D* getEngine();


		double getKineticEnergy();
		double getPotentialEnergy();
		
		double getAngularVelocity();
		glm::vec2 getVelocity();



	private:
		// position and velocity (linear and angular)
		glm::vec2 position;
		glm::vec2 velocity;
		double angle;
		double angularVelocity;

		// mass and inertia
		double mass;
		double inertia;
		Box2D localBoundingBox;
		glm::vec2 com;


		Shape2D* shape;
		PhysicsEngine2D* engine;


		void calculateMass();
		void calculateInertia();
		void calculateBoundingBox();


		glm::vec2 getFarthestPointInDirection(glm::vec2);
		glm::vec2 getCenterOfMass();


		
	friend PhysicsEngine2D;
};

#endif