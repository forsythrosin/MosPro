#ifndef __PHYSICSENGINE2D__
#define __PHYSICSENGINE2D__
#include "rigidBody2D.h"
#include "collisionDetector2D.h"
#include <vector>
#include <glm/glm.hpp>
#include "collision2D.h"
#include <cmath>
#include "bspNode2D.h"
#include "../box2D.h"
#include "../lib/debugInterface.h"

class RigidBody2D;
class CollisionDetector2D;
class Collision2D;
class BSPNode2D;

class PhysicsEngine2D
{
	public:
		PhysicsEngine2D(Box2D bounds);
		~PhysicsEngine2D(void);
		void add(RigidBody2D* rb);
		void step();
		glm::vec2 getGravity();
		void collisionResponse(std::vector<Collision2D> collisions);

		double getTotalKineticEnergy();
		double getTotalPotentialEnergy();

		void setDebug(DebugInterface*);
		DebugInterface* getDebug();
		void updatePosition(RigidBody2D*);
	private:
		DebugInterface *debug;
		
	
		CollisionDetector2D* collisionDetector;
		std::vector<RigidBody2D*> bodies;
		BSPNode2D *bsp;
		Box2D bounds;
};

#endif