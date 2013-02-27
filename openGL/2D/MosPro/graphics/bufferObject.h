#pragma once
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include "shape2D.h"

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
