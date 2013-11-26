#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/norm.hpp>
#include <vector>
#include <iostream>
#include "../box2D.h"

class Box2D;
class Shape2D;
class PhysicsEngine2D;

class RigidBody2D {
	public:
		RigidBody2D(Shape2D *s);

		virtual void step();
		virtual void impulse(glm::vec2 anchor, glm::vec2 j) {};
		virtual double getAngularVelocity();
		virtual glm::vec2 getVelocity();

		virtual void setPosition(glm::vec2 pos) = 0;
		virtual void setVelocity(glm::vec2 v) = 0;
		virtual void setAngle(double a) = 0;
		virtual glm::vec2 getPosition() const = 0;
		virtual double getAngle() const = 0;

		virtual const Box2D getBoundingBox() const;
		
		Shape2D* getShape();
		PhysicsEngine2D* getEngine();

		virtual glm::vec2 getPointInGlobalCoordinates(glm::vec2 localCoordinates);

	protected:
		Box2D localBoundingBox;
		glm::vec2 com;

		Shape2D* shape;
		PhysicsEngine2D* engine;

		void calculateBoundingBox();
		glm::vec2 getFarthestPointInDirection(glm::vec2);	

	friend class PhysicsEngine2D;
};
