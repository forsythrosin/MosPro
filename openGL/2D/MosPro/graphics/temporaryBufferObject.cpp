#include "temporaryBufferObject.h"

bool TemporaryBufferObject::frameStep(){
	if(frames-- == 0){
		return true;
	}
	return false;
}
TemporaryBufferObject::~TemporaryBufferObject(){
	delete shape->getMaterial();
	delete shape->getGeometry();
	delete shape;
}
