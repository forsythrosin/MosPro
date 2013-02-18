
#ifndef __OBJECT2D__
#define __OBJECT2D__
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "geometry2D.h"
#include "material2D.h"
#include "glEngine2D.h"

class glEngine2D;

class Shape2D{
	friend glEngine2D;
public:
	Shape2D(Geometry2D* g = new Geometry2D, Material2D* m = new Material2D):geometry(g), material(m){};
	~Shape2D();
	void setAttribs(glm::vec2 pos, double theta, glm::vec2 pivot = glm::vec2(0));
	void setGeo(Geometry2D geo); //Not implemented
	void setMat(Material2D mat); //Not implemented
	std::vector<glm::vec2> getLocalVertices();
	std::vector<glm::vec2> getGlobalVertices();
	std::vector<glm::vec3> getMaterial();
	glEngine2D* getEngine();
	glm::mat4 getModel();
private:
	Geometry2D* geometry;
	Material2D* material;
	glm::mat4 modelMatrix;
	double scale;
	glEngine2D *engine;
};
#endif