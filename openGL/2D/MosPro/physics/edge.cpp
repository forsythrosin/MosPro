#include "edge.h"

MinkowskiPoint2D Edge::getMp1(){
	return mp1;
}
MinkowskiPoint2D Edge::getMp2(){
	return mp2;
}
glm::vec2 Edge::getN(){
	return n;
}
int Edge::getIndex(){
	return index;
}