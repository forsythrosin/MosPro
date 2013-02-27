#pragma once
//#ifndef __IMMOVABLEBODY2D__
//#define __IMMOVABLEBODY2D__

#include "rigidBody2D.h"

class RigidBody2D;

class ImmovableBody2D : public RigidBody2D
{
public:
	ImmovableBody2D(void);
	~ImmovableBody2D(void);
};

//#endif


