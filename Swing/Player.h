#pragma once
#include "VECTOR2.h"
#include "PlayerBall.h"

#define PI		 (float)(3.14159265358979323846264338)

class Player
{
public:
	Player(char(&_keyData)[256], char(&_keyDataOld)[256]);
	~Player();

	int UpData();
	void Circle();
	void Collision();
	void SizeUp();
	void ChangeState();
	bool FailChack();
	bool ClearChack();
	void Draw();

	int GetLife();
	float GetAngSpeed();
	bool GetState();
	int GetCleCnt();

	void SetLife(const int &life);
	void SetAngSpeed(const float &angSpeed);
	void SetCleCnt(const int &ClearBlockCnt);

	void WarpPos(VECTOR2 pos);

private:
	int	  life;				//‘Ì—Í
	int	  cirRadius;		//‹…‚Æ‹…‚Æ‚Ì‹——£(‰~‚ğ•`‚­”¼Œa)
	float angle;			//Šp“x
	float angSpeed;			//Šp‘¬“x
	int invincibleCnt;		//–³“GŠÔ
	bool stateInvincible;	//–³“Gó‘Ô
	bool breakNow;
	bool breakOld;
	bool damageOld;
	bool spinOld;			//spin‚Ì‘½’i‘Îô
	bool enemyOld;
	int animCnt;			//±ÆÒ°¼®İ(–³“GŠÔ’†‚Í“_–Å‚³‚¹‚é)

	int ClearBlockCnt;		//c‚Á‚Ä‚¢‚é¸Ø±ÌŞÛ¯¸‚Ì”

	char(&keyData)[256];
	char(&keyDataOld)[256];

	int targetBall;			//Œ»İ²‚Æ‚È‚Á‚Ä‚¢‚é‹…
	//PlayerBall ball[2];		//PlayerŒ^‚Ì‹…A2‚Â‚ ‚é‚Ì‚Å[2]
	PlayerBall ball[2];
	VECTOR2 pos;
};