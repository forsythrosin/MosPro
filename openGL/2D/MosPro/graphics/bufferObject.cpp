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
	shape = s;
}

BufferObject::~BufferObject(){
	glDeleteBuffers(1, &vertexBuffer);
}

GLuint BufferObject::getVertexBuffer(){
	return this->vertexBuffer;
}

Shape2D* BufferObject::getShape(){
	return shape;
}


