#include "bufferObject.h"

BufferObject::BufferObject(Shape2D* s){
	GLfloat* glBuffer = new GLfloat[s->getLocalVertices().size()*3];
	for(unsigned int j = 0; j < s->getLocalVertices().size(); j++){
		glBuffer[j*3+0] = s->getLocalVertices()[j].x;
		glBuffer[j*3+1] = s->getLocalVertices()[j].y;
		glBuffer[j*3+2] = 0;
	}
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glBuffer)*s->getLocalVertices().size()*3, glBuffer, GL_STATIC_DRAW);
	delete[] glBuffer;


	GLfloat* colorL = new GLfloat[s->getLocalVertices().size()*3];
	for(unsigned int j = 0; j < s->getLocalVertices().size(); j++){
		colorL[j*3+0] = s->getMaterial()[j%s->getMaterial().size()].x;
		colorL[j*3+1] = s->getMaterial()[j%s->getMaterial().size()].y;
		colorL[j*3+2] = s->getMaterial()[j%s->getMaterial().size()].z;
	}
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glBuffer)*s->getLocalVertices().size()*3, colorL, GL_STATIC_DRAW);
	delete[] colorL;
	shape = s;
}

BufferObject::~BufferObject(){
	glDeleteBuffers(1, &colorBuffer);
	glDeleteBuffers(1, &vertexBuffer);
}

GLuint BufferObject::getColorBuffer(){
	return this->colorBuffer;
}

GLuint BufferObject::getVertexBuffer(){
	return this->vertexBuffer;
}

Shape2D* BufferObject::getShape(){
	return shape;
}


