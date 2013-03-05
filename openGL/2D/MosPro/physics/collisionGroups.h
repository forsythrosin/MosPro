#pragma once
#include <vector>
#include <map>
#include <set>
class CollisionGroup;
class Collision2D;
class RigidBody2D;
class Box2D;

class CollisionGroups{
public:
	void addCollision(Collision2D c);
	void resolve();
	std::vector<Box2D> CollisionGroups::getBoxes();
private:
	std::vector<CollisionGroup*> getGroups();
	CollisionGroup* mergeGroups(CollisionGroup*, CollisionGroup*);
	std::map<RigidBody2D*, CollisionGroup*> rbToCg;
};