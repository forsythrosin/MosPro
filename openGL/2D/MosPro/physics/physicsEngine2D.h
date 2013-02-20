#ifndef __PHYSICSENGINE2D__
#define __PHYSICSENGINE2D__
#include "rigidBody2D.h"
#include "collisionDetector2D.h"
#include <vector>
#include <glm/glm.hpp>
#include "collision2D.h"
#include <cmath>
<<<<<<< HEAD
#include "../lib/debugInterface.h"
=======
#include "BSPNode2D.h"
>>>>>>> 655d2db90a9523a46ceff7c434c13f7dd4b85cc2

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
		double getTotalPotentialEnergy();

		void setDebug(DebugInterface*);
		DebugInterface* getDebug();
	private:
		DebugInterface *debug;
		void updatePosition(RigidBody2D*);
	
		CollisionDetector2D* collisionDetector;
		std::vector<RigidBody2D*> bodies;
		BSPNode2D *bsp;
};

#endif