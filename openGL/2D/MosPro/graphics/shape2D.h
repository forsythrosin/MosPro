
#ifndef __OBJECT2D__
#define __OBJECT2D__
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "geometry2D.h"
#include "material2D.h"
#define GLM_FORCE_RADIANS
class Shape2D{
public:
	Shape2D(Geometry2D* g = new Geometry2D, Material2D* m = new Material2D):geometry(g), material(m){};
	void setAttribs(glm::vec2 pos, double theta, glm::vec2 pivot);
	void setGeo(Geometry2D geo); //Not implemented
	void setMat(Material2D mat); //Not implemented
	std::vector<glm::vec2> getLocalVertices();
	std::vector<glm::vec2> getGlobalVertices();
	std::vector<glm::vec3> getMaterial();
	glm::mat4 getModel();
private:
	Geometry2D* geometry;
	Material2D* material;
	glm::mat4 modelMatrix;
	double scale;
};
#endif