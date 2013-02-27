#pragma once

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include "bufferObject.h"

class TemporaryBufferObject : public BufferObject{
public:
	TemporaryBufferObject(Shape2D* s, unsigned int frames):BufferObject(s){
		this->frames = frames;
	}
	bool frameStep();
	virtual ~TemporaryBufferObject();
private:
	unsigned int frames;
};
