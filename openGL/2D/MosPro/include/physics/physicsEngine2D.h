#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <cmath>
#include "../box2D.h"
#include "gravity2D.h"

class DebugInterface;

class CollisionDetector2D;
class RigidBody2D;
class MovableBody2D;
class ImmovableBody2D;

class Collision2D;
class BSPNode2D;
class ForceGenerator2D;


class PhysicsEngine2D
{
	public:
		PhysicsEngine2D(Box2D bounds);
		~PhysicsEngine2D(void);
		void add(MovableBody2D* rb);
		void add(ImmovableBody2D* rb);
		void add(ForceGenerator2D* fg);
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
		std::vector<MovableBody2D*> movableBodies;
		std::vector<ImmovableBody2D*> immovableBodies;
		std::vector<ForceGenerator2D*> forceGenerators;
		BSPNode2D *bsp;
		Box2D bounds;
		Gravity2D gravity;
};
