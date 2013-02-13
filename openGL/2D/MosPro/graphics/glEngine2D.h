#ifndef __GLENGINE2D__
#define __GLENGINE2D__
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <vector>
#include "shape2D.h"
#include "bufferObject.h"
#include "../lib/shader.hpp"
#include <iostream>



class glEngine2D{
public:

	glEngine2D(glm::vec3 camera = glm::vec3(0.1f));
	void add(Shape2D* s = new Shape2D);
	Shape2D*& get(int i);
	void setView(glm::mat4 view);
	void setCamera(glm::vec3 camera);
	void bindBuffers();
	void render();
	void deleteBuffers();

private:
	GLuint programID;
	GLuint modelID;
	GLuint viewID;
	std::vector<Shape2D*> shapeList;
	std::vector<BufferObject*> buffers;
	glm::mat4 viewMatrix;
};
#endif