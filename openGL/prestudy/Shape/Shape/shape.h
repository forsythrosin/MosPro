
#ifndef __SHAPE__
#define __SHAPE__
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <GL/glew.h>
#include <iostream>
#include <ctime>

class Shape{
public:
	Shape();
	Shape(std::vector<glm::vec2> shape,double x, double y, double theta = 0, glm::vec2 v = glm::vec2(0), double w = 0);
	GLfloat* getShape();
	glm::vec2 getPosition();
	friend std::ostream& operator<< (std::ostream &out,Shape &s);
	void setPos(double x, double y);
	int getSize();
	glm::mat4 getMatrix();
	void setV(glm::vec2 v);
	void setW(double w);
	void setTheta(double theta);
	void setSize(double size);
	int getNumVertex();
	int getNumParam();
	void update();

private:
	int numParam;
	glm::vec2 position;
	GLfloat* vertexList;
	GLfloat* globalVertices;
	double theta;
	glm::vec2 v;
	double w;
	double size;
};
#endif