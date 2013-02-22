#pragma once
#ifndef __DEBUGINTER__
#define __DEBUGINTER__

#include <glm/glm.hpp>
#include "../box2D.h"

class DebugInterface{
public:
	virtual ~DebugInterface(){};
	virtual void debugVector(glm::vec2 startPoint, glm::vec2 vector) = 0;
	virtual void debugLine(glm::vec2 startPoint, glm::vec2 endPoint) = 0;
	virtual void debugBox(Box2D) = 0;
};
#endif