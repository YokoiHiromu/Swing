#pragma once
#include "Obj.h"

class WarpBlock :
	public Obj
{
public:
	WarpBlock();
	~WarpBlock();
	bool CollisionProcessing(void);
};

