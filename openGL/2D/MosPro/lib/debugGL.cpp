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

void DebugGL::debugBox(Box2D box){
	engine->drawLine(box.p0, glm::vec2(box.p1.x, box.p0.y), glm::vec3(1.0f,0.0f,0.0f), 0.1, 2);
	engine->drawLine(glm::vec2(box.p1.x, box.p0.y), box.p1, glm::vec3(1.0f,0.0f,0.0f), 0.1, 2);

	engine->drawLine(box.p1, glm::vec2(box.p0.x, box.p1.y), glm::vec3(1.0f,0.0f,0.0f), 0.1, 2);
	engine->drawLine(glm::vec2(box.p0.x, box.p1.y), box.p0, glm::vec3(1.0f,0.0f,0.0f), 0.1, 2);
}

void DebugGL::setEngine(glEngine2D *ge){
	engine = ge;
}

