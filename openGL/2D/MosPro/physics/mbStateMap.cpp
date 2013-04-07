#include "mbStateMap.h"
#include "movableBody2D.h"
#include <iostream>
#include "../glmIO.h"

MBStateMap::MBStateMap(void)
{
}

MBStateMap::MBStateMap(std::vector<MovableBody2D*> v, bool copyState)
{
	if (copyState) {
		for (int i = 0; i < v.size(); i++) {
			//std::cout << v[i]->getState().position;
			this->states[v[i]] = v[i]->getState();
		}
	} else {
		for (int i = 0; i < v.size(); i++) {
			this->states[v[i]] = MBState();
		}
	}
}


MBStateMap::~MBStateMap(void)
{
}


MBStateMap MBStateMap::operator+ (const MBStateMap m) const {
	MBStateMap result;
	for(std::map<MovableBody2D*, MBState>::const_iterator it = states.begin(); it != states.end(); it++) {
		result.states[it->first] = it->second + m.states.at(it->first); 
	}
	return result;
}

MBStateMap MBStateMap::operator+= (const MBStateMap m) {
	*this = *this + m;
	return *this + m;
}



MBStateMap MBStateMap::operator- (const MBStateMap m) const {
	MBStateMap result;
	for(std::map<MovableBody2D*, MBState>::const_iterator it = states.begin(); it != states.end(); it++) {
		result.states[it->first] = it->second - m.states.at(it->first); 
	}
	return result;
}


MBStateMap MBStateMap::operator* (const double s) const {
	MBStateMap result;
	for(std::map<MovableBody2D*, MBState>::const_iterator it = states.begin(); it != states.end(); it++) {
		result.states[it->first] = it->second * s;
	}
	return result;
}


MBStateMap MBStateMap::operator/ (double s) const {
	return *this*(1/s);
}