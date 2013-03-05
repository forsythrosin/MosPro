#pragma once


#include <vector>
#include <glm/glm.hpp>
#include <map>
#include <set>

class Edge;
class MinkowskiPoint2D;
class Collision2D;
class BSPNode2D;
class RigidBody2D;
class CollisionGroups;
typedef std::vector<MinkowskiPoint2D> simplex2D;

class CollisionDetector2D
{
	public:
		CollisionDetector2D(void);
		~CollisionDetector2D(void);
		void getCollisions(BSPNode2D *bsp, CollisionGroups *cgs);
		std::vector<Collision2D> getCollisions(std::vector<RigidBody2D*> &bodies);
		std::vector<Collision2D> getCollisions(BSPNode2D *bsp);
	private:
		bool gjk(RigidBody2D* a, RigidBody2D* b, simplex2D &s);
		Collision2D epa(RigidBody2D* a, RigidBody2D* b, simplex2D &s);
		bool containsOrigin(simplex2D &s, glm::vec2 &d);
		Edge findClosestEdge(simplex2D &s);
		const static double tolerance;
};
