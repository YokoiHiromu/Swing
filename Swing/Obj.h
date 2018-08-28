#pragma once
#include <vector>
#include <list>
#include <string>
#include "VECTOR2.h"
#include "MapCtl.h"

#define BLOCK_SIZE 32

#define IMAGE_ID(X) (ImageMng::GetInstance()->GetID(X))
using VEC_INT = std::vector<int>;

class Obj
{
public:
	Obj();
	~Obj();

	void Init(std::string filname, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, int speed);

	bool CollisionChack_Circle_Circle(VECTOR2 cirPos, int PlSize);		//â~ìØém
	void DamageProcessing();

	VECTOR2 GetPos();
	int GetSize();
	bool GetDFlag();
	CHIP_TYPE GetID();

	void SetPos(const VECTOR2 & pos);
	void SetSize(const int &size);
	void SetMode(const ENEMY_MODE &mode);

	virtual void Draw(void);
	void Draw(unsigned int id);
	virtual void UpData(void);
	virtual bool CollisionProcessing();
	virtual void Move();

	void ReverseMove(void);

	virtual void RandomSetChipID();

private:

	VECTOR2	divSize;		//ï`âÊ¡ØÃﬂÇÃª≤Ωﬁ
	VECTOR2	divCnt;			//ï`âÊ¡ØÃﬂêî
	VECTOR2	chipOffset;		//ï`âÊ¡ØÃﬂÇÃìÒéüå≥îzóÒè„ÇÃ≤“∞ºﬁID

	int DamageFlag = false;
	int invincibleCnt = 0;


protected:


	VECTOR2	pos;
	int size;		//Ãﬁ€Ø∏ÅAŒﬁ∞ŸÇÃëÂÇ´Ç≥(äÓëb)
	int Cl;
	bool hittingFlag = false;
	int image[70];
	ENEMY_MODE mode;
	
	CHIP_TYPE ID;

	std::string imageName;
	unsigned int animCnt;
	//std::vector <int> imageID;
};