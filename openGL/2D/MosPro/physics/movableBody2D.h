#pragma once
//#ifndef __MOVABLEBODY2D__
//#define __MOVABLEBODY2D__

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/perpendicular.hpp>
//#include <glm/gtx/norm.hpp>
//#include <vector>
//#include <iostream>
//#include <math.h>
//#include "../graphics/shape2D.h"
//#include "physicsEngine2D.h"
//#include "../box2D.h"
//#include "../glmIO.h"
//#include "rigidBody2D.h"

class RigidBody2D;

class MovableBody2D : public RigidBody2D
{
	public:
		MovableBody2D::MovableBody2D(Shape2D *s, glm::vec2 p, double a, glm::vec2 v, double w);
		~MovableBody2D(void);

		void step();

		void impulse(glm::vec2 anchor, glm::vec2 j);
		void teleport(glm::vec2 transVect);

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
};



//#endif