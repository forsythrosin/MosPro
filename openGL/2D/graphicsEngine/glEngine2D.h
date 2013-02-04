#ifndef __GLENGINE2D__
#define __GLENGINE2D__
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include "shape2D.h"
#include <vector>


class glEngine2D{
public:
	glEngine2D();
	void add(Shape2D s = Shape2D());
	Shape2D* get(int i);
	void bindBuffers();
	void render();
	void deleteBuffers();
private:
	GLuint programID;
	GLuint matrixID;
	std::vector<Shape2D> shapeList;
	std::vector<GLint> colorBuffers;
	std::vector<GLint> vertexBuffers;
};
#endif