#pragma once
//#ifndef __RIGIDBODY2D__
//#define __RIGIDBODY2D__

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/norm.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include "../graphics/shape2D.h"
#include "physicsEngine2D.h"
#include "../box2D.h"
#include "../glmIO.h"

class PhysicsEngine2D;

class RigidBody2D {
	public:
		RigidBody2D(Shape2D *s, glm::vec2 p, double angle = 0);

		virtual void step();
		
		glm::vec2 getPosition();
		void setPosition(glm::vec2 pos);

		const Box2D getBoundingBox() const;
		
		Shape2D* getShape();
		PhysicsEngine2D* getEngine();

		double getAngle();

	protected:
		// position and velocity (linear and angular)
		glm::vec2 position;
		double angle;

		Box2D localBoundingBox;
		glm::vec2 com;

		Shape2D* shape;
		PhysicsEngine2D* engine;

		void calculateBoundingBox();
		glm::vec2 getFarthestPointInDirection(glm::vec2);

		

	friend PhysicsEngine2D;
};

//#endif