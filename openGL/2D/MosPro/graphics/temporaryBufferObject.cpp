#include "temporaryBufferObject.h"

bool TemporaryBufferObject::frameStep(){
	if(--frames == 0){
		return true;
	}
	return false;
}

