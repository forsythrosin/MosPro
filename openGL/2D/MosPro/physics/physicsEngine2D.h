#ifndef __PHYSICSENGINE2D__
#define __PHYSICSENGINE2D__
#include "rigidBody2D.h"
#include "collisionDetector2D.h"
#include <vector>
#include <glm/glm.hpp>

class RigidBody2D;
class CollisionDetector2D;

class PhysicsEngine2D
{
	public:
		PhysicsEngine2D(void);
		~PhysicsEngine2D(void);
		void add(RigidBody2D* rb);
		void step();
		glm::vec2 getGravity();

	private:

		CollisionDetector2D* collisionDetector;
		std::vector<RigidBody2D*> bodies;

	
};

#endif