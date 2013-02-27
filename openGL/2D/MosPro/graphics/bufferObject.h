#pragma once
//#ifndef __BUFFEROBJ__
//#define __BUFFEROBJ__
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include "shape2D.h"

class Shape2D;


class BufferObject{
public:
	BufferObject(Shape2D* s);
	virtual ~BufferObject();
	GLuint getColorBuffer();
	GLuint getVertexBuffer();
	Shape2D* getShape();
protected:
	Shape2D* shape;
	GLuint vertexBuffer;
};


//#endif