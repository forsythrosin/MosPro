#include "bufferObject.h"

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