#ifndef __PHYSICSENGINE2D__
#define __PHYSICSENGINE2D__
#include "rigidBody2D.h"
#include "collisionDetector2D.h"
#include <vector>
#include <glm/glm.hpp>
#include "collision2D.h"
#include <cmath>
#include "BSPNode2D.h"

class RigidBody2D;
class CollisionDetector2D;
class Collision2D;
class BSPNode2D;

class PhysicsEngine2D
{
	public:
		PhysicsEngine2D(void);
		~PhysicsEngine2D(void);
		void add(RigidBody2D* rb);
		void step();
		glm::vec2 getGravity();
		void collisionResponse(std::vector<Collision2D> collisions);
		double getTotalKineticEnergy();
		void updatePosition(RigidBody2D*);

	private:
		CollisionDetector2D* collisionDetector;
		std::vector<RigidBody2D*> bodies;
		BSPNode2D *bsp;
};

#endif