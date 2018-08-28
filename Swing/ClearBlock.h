#pragma once
#include "Obj.h"

class ClearBlock :
	public Obj
{
public:
	ClearBlock();
	~ClearBlock();
	bool CollisionProcessing(void);
	//void Draw(void);

private:
};