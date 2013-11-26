#pragma once
#include <vector>
#include <map>
class MovableBody2D;
class MBState;

class MBStateMap
{
public:
	MBStateMap(void);
	MBStateMap(std::vector<MovableBody2D*>, bool copyStates);

	~MBStateMap(void);
	std::map<MovableBody2D*, MBState> states;
	MBStateMap operator+ (const MBStateMap m) const;
	MBStateMap operator+= (const MBStateMap m);
	MBStateMap operator- (const MBStateMap m) const;
	MBStateMap operator* (const double s) const;
	MBStateMap operator/ (const double s) const;
};

