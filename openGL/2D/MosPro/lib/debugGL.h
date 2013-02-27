#pragma once
#include <glm/glm.hpp>
#include "debugInterface.h"

class glEngine2D;
class Box2D;

class DebugGL : public DebugInterface{
public:
	DebugGL(glEngine2D *ge);
	virtual ~DebugGL(){};
	virtual void debugVector(glm::vec2 startPoint, glm::vec2 vector);
	virtual void debugLine(glm::vec2 startPoint, glm::vec2 endPoint);
	virtual void debugBox(Box2D b);
	void setEngine(glEngine2D *ge);

private:
	glEngine2D *engine;
};
