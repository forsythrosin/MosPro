#pragma once
//#ifndef __GLENGINE2D__
//#define __GLENGINE2D__
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <list>
#include <iostream>
#include <utility>
#include <cassert>

class Shape2D;
class BufferObject;
class TemporaryBufferObject;

class glEngine2D{
public:
	glEngine2D(glm::vec3 camera = glm::vec3(0.1f));
	void add(Shape2D* s);
	Shape2D*& get(int i);
	void setView(glm::mat4 view);
	void setCamera(glm::vec3 camera);
	void bindBuffers();
	void render();
	void deleteBuffers();
	void drawLine(glm::vec2 start, glm::vec2 end, glm::vec3 color = glm::vec3(1,0,0), double width = 2, unsigned int frames = 5);
	void drawVector(glm::vec2 orig, glm::vec2 direc, glm::vec3 color = glm::vec3(1,0,0), double width = 2, unsigned int frames = 5);
private:
	GLuint programID;
	GLuint modelID;
	GLuint colorID;
	std::list<TemporaryBufferObject*> temporaryBuffers;
	std::vector<Shape2D*> shapeList;
	std::list<BufferObject*> buffers;
	glm::mat4 viewMatrix;
};
//#endif


