#pragma once
#ifndef __DEBUGGL__
#define __DEBUGGL__

#include "debugInterface.h"
#include "../graphics/glEngine2D.h"
class glEngine2D;
class DebugInterface;

class DebugGL : public DebugInterface{
public:
	DebugGL(glEngine2D *ge);
	virtual ~DebugGL(){};
	virtual void debugVector(glm::vec2 startPoint, glm::vec2 vector);
	virtual void debugLine(glm::vec2 startPoint, glm::vec2 endPoint);
	void setEngine(glEngine2D *ge);

private:
	glEngine2D *engine;
};

#endif