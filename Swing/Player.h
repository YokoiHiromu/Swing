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
	int	  life;				//�̗�
	int	  cirRadius;		//���Ƌ��Ƃ̋���(�~��`�����a)
	float angle;			//�p�x
	float angSpeed;			//�p���x
	int invincibleCnt;		//���G����
	bool stateInvincible;	//���G���
	bool breakNow;
	bool breakOld;
	bool damageOld;
	bool spinOld;			//spin�̑��i�΍�
	bool enemyOld;
	int animCnt;			//��Ұ���(���G���Ԓ��͓_�ł�����)

	int ClearBlockCnt;		//�c���Ă���ر��ۯ��̐�

	char(&keyData)[256];
	char(&keyDataOld)[256];

	int targetBall;			//���ݎ��ƂȂ��Ă��鋅
	//PlayerBall ball[2];		//Player�^�̋��A2����̂�[2]
	PlayerBall ball[2];
	VECTOR2 pos;
};