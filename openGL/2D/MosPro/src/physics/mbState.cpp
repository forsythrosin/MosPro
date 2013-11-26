#include "mbState.h"


MBState::MBState() {
	position = glm::vec2(0);
	velocity = glm::vec2(0);
	angle = 0;
	angularVelocity = 0;
}

MBState MBState::operator+ (const MBState m) const {
	MBState result;
	
	result.position = position + m.position;
	result.velocity = velocity + m.velocity;
	result.angle = angle + m.angle;
	result.angularVelocity = angularVelocity + m.angularVelocity;

	return result;
}


MBState MBState::operator- (const MBState m) const {
	MBState result;
	
	result.position = position - m.position;
	result.velocity = velocity - m.velocity;
	result.angle = angle - m.angle;
	result.angularVelocity = angularVelocity - m.angularVelocity;

	return result;
}



MBState MBState::operator* (const double s) const {
	MBState result;
	
	result.position = position * (float) s;
	result.velocity = velocity * (float) s;
	result.angle = angle * (float) s;
	result.angularVelocity = angularVelocity * (float) s;

	return result;
}


MBState MBState::operator/ (double s) const {
	return *this*(1/s);
}