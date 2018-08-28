#pragma once
#include "Obj.h"

class SpinBall :
	public Obj
{
public:
	SpinBall();
	~SpinBall();
	bool CollisionProcessing(void);
};