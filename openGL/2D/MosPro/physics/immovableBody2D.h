#pragma once

#include "rigidBody2D.h"

class ImmovableBody2D : public RigidBody2D
{
	public:
		ImmovableBody2D(Shape2D *s, glm::vec2 p, double a);
		~ImmovableBody2D(void);

	friend PhysicsEngine2D;
};
