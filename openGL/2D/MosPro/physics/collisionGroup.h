#pragma once
#include <vector>
#include <set>

class RigidBody2D;
class Collision2D;
class Box2D;

class CollisionGroup{
public:
	CollisionGroup(Collision2D);
	CollisionGroup();
	void merge(CollisionGroup*);
	void add(Collision2D);
	void resolve();
	Box2D getBoundingBox();
private:
	std::vector<Collision2D> group;
};
