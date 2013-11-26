#pragma once

class MBStateMap;

class ForceGenerator2D
{
	public:
		virtual void applyForces(MBStateMap *in, MBStateMap *out) = 0;
};

