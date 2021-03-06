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
	int	  life;				//体力
	int	  cirRadius;		//球と球との距離(円を描く半径)
	float angle;			//角度
	float angSpeed;			//角速度
	int invincibleCnt;		//無敵時間
	bool stateInvincible;	//無敵状態
	bool breakNow;
	bool breakOld;
	bool damageOld;
	bool spinOld;			//spinの多段対策
	bool enemyOld;
	int animCnt;			//ｱﾆﾒｰｼｮﾝ(無敵時間中は点滅させる)

	int ClearBlockCnt;		//残っているｸﾘｱﾌﾞﾛｯｸの数

	char(&keyData)[256];
	char(&keyDataOld)[256];

	int targetBall;			//現在軸となっている球
	//PlayerBall ball[2];		//Player型の球、2つあるので[2]
	PlayerBall ball[2];
	VECTOR2 pos;
};