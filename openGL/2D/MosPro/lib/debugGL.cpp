#include "debugGL.h"

DebugGL::DebugGL(glEngine2D *ge){
		engine = ge;
}

void DebugGL::debugVector(glm::vec2 startPoint, glm::vec2 vector){
	engine->drawVector(startPoint, vector,glm::vec3(1.0f,0.0f,0.0f), 0.1, 5);
}

void DebugGL::debugLine(glm::vec2 startPoint, glm::vec2 endPoint){
	engine->drawLine(startPoint, endPoint, glm::vec3(1.0f,0.0f,0.0f), 0.1, 5);
}

void DebugGL::setEngine(glEngine2D *ge){
	engine = ge;
}