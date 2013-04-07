#pragma once

#include "rigidBody2D.h"

class ImmovableBody2D : public RigidBody2D
{
	public:
		ImmovableBody2D(Shape2D *s, glm::vec2 p, double a);
		~ImmovableBody2D(void);
		const Box2D getBoundingBox() const;
		
		glm::vec2 getPosition() const;
		double getAngle() const;

		void setPosition(glm::vec2 p);
		void setAngle(double a);
	private:
		glm::vec2 position;
		double angle;
	friend PhysicsEngine2D;
};

