#pragma once
#include "Obj.h"
#include "VECTOR2.h"

class BreakBlock :
	public Obj
{
public:
	BreakBlock();
	~BreakBlock();
	bool CollisionProcessing(void);

private:
};