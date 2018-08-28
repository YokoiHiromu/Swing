#pragma once
#include "Obj.h"

class DamageBlock :
	public Obj
{
public:
	DamageBlock();
	~DamageBlock();
	bool CollisionProcessing(void);

};