#include "collisionGroups.h"
#include "collision2D.h"
#include "collisionGroup.h"
#include <iostream>
#include "../box2D.h"

void CollisionGroups::addCollision(Collision2D c) {
	std::map<RigidBody2D*, CollisionGroup*>::iterator cgA, cgB;

	RigidBody2D *const a = (RigidBody2D* const) c.getRb1(),
			    *const b = (RigidBody2D* const) c.getRb1();
	
	cgA = rbToCg.find(a);
	cgB = rbToCg.find(b);

	if (cgA != rbToCg.end()) {
		if(cgB != rbToCg.end()){
			CollisionGroup* cg = mergeGroups(cgA->second, cgB->second);
			//delete cgA->second;
			cgA->second = cg;
			//delete cgB->second;
			cgB->second = cg;
		} else{
			cgA->second->add(c);
			rbToCg[b] = cgA->second;
		}
	} else if (cgB != rbToCg.end()) {
		cgB->second->add(c);
		rbToCg[a] = cgB->second;
	} else {
		CollisionGroup *cg = new CollisionGroup(c);
		rbToCg[a] = cg;
		rbToCg[b] = cg;
	}
}

CollisionGroup* CollisionGroups::mergeGroups(CollisionGroup* cgA, CollisionGroup* cgB){
	CollisionGroup* cg = new CollisionGroup;
	cg->merge(cgA);
	cg->merge(cgB);
	return cg;
}
std::vector<CollisionGroup*> CollisionGroups::getGroups(){
	std::set<CollisionGroup*> groups;
	std::map<RigidBody2D*, CollisionGroup*>::iterator it;
	for(it = rbToCg.begin(); it != rbToCg.end(); it++){
		groups.insert(it->second);
	}
	return std::vector<CollisionGroup*>(groups.begin(), groups.end());
}

void CollisionGroups::resolve(){
	std::vector<CollisionGroup*> groups = getGroups();
	std::cout << groups.size() << std::endl;
	for(int i = 0; i < groups.size(); i++){
		groups[i]->resolve();
	}
}

std::vector<Box2D> CollisionGroups::getBoxes() {
	std::vector<Box2D> boxes;
	std::vector<CollisionGroup*> groups = getGroups();
	for(int i = 0; i < groups.size(); i++){
		boxes.push_back(groups[i]->getBoundingBox());
	}
	return boxes;
}