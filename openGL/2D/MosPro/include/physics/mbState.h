#include <glm/glm.hpp>

#pragma once
class MBState
{
public:
	MBState();
	glm::vec2 position;
	glm::vec2 velocity;
	double angle;
	double angularVelocity;

	MBState operator+ (const MBState m) const;
	MBState operator- (const MBState m) const;
	MBState operator* (const double s) const;
	MBState operator/ (const double s) const;
};

