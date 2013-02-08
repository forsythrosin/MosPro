#ifndef __BUFFEROBJ__
#define __BUFFEROBJ__
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

class BufferObject{
public:
	BufferObject(GLuint color, GLuint vertex):colorBuffer(color), vertexBuffer(vertex){};
	~BufferObject();
	GLuint getColorBuffer();
	GLuint getVertexBuffer();
private:
	GLuint colorBuffer;
	GLuint vertexBuffer;
};


#endif