#pragma once
#include "Obj.h"
class Enemy :
	public Obj
{
public:
	Enemy();
	~Enemy();
	void UpData();
	bool CollisionProcessing(void);
	void Move(void);
	void Draw(void);

private:
	int addMove;		//ˆÚ“®‚Ì‰ÁZ’l
	int moveDistance;	//İ’u’n“_‚©‚ç‚Ì‡Œv‰ÁZ’l
	int moveLimit;		//‰ÁZŒÀŠE
	int moveInv;		//‰•œ‚Ì’â~ŠÔ

	int radius;
	float angle;			//Šp“x
	float angSpeed;			//Šp‘¬“x
};

