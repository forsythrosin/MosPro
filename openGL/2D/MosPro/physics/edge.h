#pragma once
//#ifndef __EDGEH__
//#define __EDGEH__
#include <glm/glm.hpp>
#include "minkowskiPoint2D.h"
class Edge{
public:
	Edge(MinkowskiPoint2D Tmp1, MinkowskiPoint2D Tmp2, int Tindex, glm::vec2 Tn):mp1(Tmp1), mp2(Tmp2), index(Tindex), n(Tn){}
	MinkowskiPoint2D getMp1();
	MinkowskiPoint2D getMp2();
	glm::vec2 getN();
	int getIndex();
private:
	MinkowskiPoint2D mp1, mp2;
	glm::vec2 n;
	int index;
};
//#endif


