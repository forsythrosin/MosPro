#include "collisionGroup.h"
#include "collision2D.h"
#include <iostream>
#include "../box2D.h"
#include "rigidBody2D.h"

CollisionGroup::CollisionGroup(Collision2D c){
	group.push_back(c);
}
CollisionGroup::CollisionGroup(){
}
void CollisionGroup::merge(CollisionGroup *cg){
	group.insert(group.end(), cg->group.begin(), cg->group.end());
	//std::cout << group.size() << std::endl;
}
void CollisionGroup::add(Collision2D c){
	group.push_back(c);
}

void CollisionGroup::resolve(){
	for(int i = 0; i < group.size(); i++){
		group[i].resolve();
	}
}

Box2D CollisionGroup::getBoundingBox() {
	Box2D accumulator;
	for(int i = 0; i < group.size(); i++){
		accumulator += group[i].getRb1()->getBoundingBox();
		accumulator += group[i].getRb2()->getBoundingBox();
	}
	return accumulator;
}