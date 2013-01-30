#ifndef __GRAPHICSENGINE__
#define __GRAPHICSENGINE__
#include "shape.h"
#include <vector>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <iostream>
#include "shape.h"

class graphicsEngine{
public:
	graphicsEngine();
	void add(Shape s);
	void add(Shape s, double r, double g, double b);
	void add(Shape s, glm::vec3 c);
	void setColor(int i, double r,double g, double b);
	void setColor(int i);
	void bindBuffers();
	void render(GLuint shaderID);
	int getSizeBuffer();
	void update();
	void deleteBuffers();
	Shape* getShape(int i);
private:
	std::vector<glm::vec3> color;
	std::vector<GLint> colorBuffers;
	std::vector<Shape> shapeList;
	std::vector<GLint> vertexBuffers;
};
#endif