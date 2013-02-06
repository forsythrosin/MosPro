#include "glEngine2D.h"
#include <common/shader.hpp>
#include <common/shader.cpp>
#include <iostream>
glEngine2D::glEngine2D(){
	programID = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
	matrixID = glGetUniformLocation(programID, "MVP");
}

void glEngine2D::add(Shape2D* s){
	shapeList.push_back(s);
}

Shape2D*& glEngine2D::get(int i){
	return shapeList[i];
}

void glEngine2D::bindBuffers(){
	for(unsigned int i = 0; i < shapeList.size();i++){
		GLfloat* glBuffer = new GLfloat[shapeList[i]->getLocalVertices().size()*3];
		for(unsigned int j = 0; j < shapeList[i]->getLocalVertices().size(); j++){
			glBuffer[j*3+0] = shapeList[i]->getLocalVertices()[j].x;
			glBuffer[j*3+1] = shapeList[i]->getLocalVertices()[j].y;
			glBuffer[j*3+2] = 0;

		}
		GLuint vertexBuffer;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glBuffer)*shapeList[i]->getLocalVertices().size()*3, glBuffer, GL_STATIC_DRAW);
		vertexBuffers.push_back(vertexBuffer);
		delete[] glBuffer;


		GLuint colorBuffer;
		GLfloat* colorL = new GLfloat[shapeList[i]->getLocalVertices().size()*3];
		for(unsigned int j = 0; j < shapeList[i]->getLocalVertices().size(); j++){
			colorL[j*3+0] = shapeList[i]->getMaterial()[j%shapeList[i]->getMaterial().size()].x;
			std::cout << " " << colorL[j*3+0];
			colorL[j*3+1] = shapeList[i]->getMaterial()[j%shapeList[i]->getMaterial().size()].y;
			std::cout << " " << colorL[j*3+1];
			colorL[j*3+2] = shapeList[i]->getMaterial()[j%shapeList[i]->getMaterial().size()].z;
			std::cout << " " << colorL[j*3+2] << std::endl;
		}
		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glBuffer)*shapeList[i]->getLocalVertices().size()*3, colorL, GL_STATIC_DRAW);
		colorBuffers.push_back(colorBuffer);
		delete[] colorL;
	}
}


void glEngine2D::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(unsigned int i = 0; i < vertexBuffers.size(); i++){

		glUseProgram(programID);
		glm::mat4 t = shapeList[i]->getModel();
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &shapeList[i]->getModel()[0][0]);


		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);


		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers.at(i));
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);


		glBindBuffer(GL_ARRAY_BUFFER, colorBuffers.at(i));
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);
		glDrawArrays(GL_TRIANGLE_FAN, 0, shapeList.at(i)->getLocalVertices().size());
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	glfwSwapBuffers();
}

void glEngine2D::deleteBuffers(){
}