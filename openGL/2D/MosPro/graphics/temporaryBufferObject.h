#ifndef __TEMPBUFFEROBJ__
#define __TEMPBUFFEROBJ__
#include "bufferObject.h"
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

class TemporaryBufferObject; 
class BufferObject;
class Shape2D;

class TemporaryBufferObject : public BufferObject{
public:
	TemporaryBufferObject(Shape2D* s, unsigned int frames):BufferObject(s){
		this->frames = frames;
	}
	bool frameStep();
private:
	unsigned int frames;
};
#endif