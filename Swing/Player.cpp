#include <DxLib.h>
#include <math.h>
#include <memory>
#include <list>
#include "GameTask.h"
#include "Player.h"

Player::Player(char(&_keyData)[256], char(&_keyDataOld)[256]):keyData(_keyData), keyDataOld(_keyDataOld)
{
	life = 4;
	cirRadius = 100;
	angle = 0;
	angSpeed = (float)0.065;
	targetBall = 0;
	animCnt = 0;
	ClearBlockCnt = 0;
	stateInvincible = false;
	breakNow = false;
	breakOld = false;
	damageOld = false;
	enemyOld = false;

	for (int i = 0; i < 2; i++)
	{
		ball[i].Init("image/tileset.png", { 16,16 }, { 7,6 }, { (5 + (7 * i)), 0 }, 0);

		/////////�@���������@////////
		ball[i].Init("image/playerball.png", { 48, 48 }, { 2, 1 }, { i , 0 }, 0);
		/////////�@���������@////////

	}
	lpGameTask.camera->SetTarget(ball[targetBall]);
}

Player::~Player()
{

}

int Player::UpData()
{
	Circle();			//�~��]
	Collision();		//�����蔻�菔�X�̏���
	ChangeState();		//���G����
	return 0;
}

void Player::Circle()
{
	// �p�x�X�V
	angle += angSpeed;

	pos = ball[targetBall].GetPos();		//���̍��W(PlayerBall��Pos�Q��)
	pos.x += cos(angle) * (cirRadius + ball[(targetBall + 1) % 2].GetSize() / 2);			//��]���鋅�̍��W(����͏����ʒu���߂ɂ��Ȃ�)
	pos.y += sin(angle) * (cirRadius + ball[(targetBall + 1) % 2].GetSize() / 2);

	ball[(targetBall + 1) % 2].SetPos(pos);

	if (keyData[KEY_INPUT_SPACE] && !keyDataOld[KEY_INPUT_SPACE])
	{
		if (targetBall == 0)		//�����Ă��鋅��Ball[0]�̏ꍇ
		{
			targetBall++;			//����������Ball[1]�ɕύX����
			angle -= PI;
		}
		else if (targetBall == 1)
		{
			targetBall--;
			angle -= PI;
		}
	}
}

void Player::Collision()
{
	bool breakNow = false;
	bool damageNow = false;
	bool spinNow = false;
	bool enemyNow = false;
	//�����Ŷ�ׂ����ޯ�(�Ǐ])���������ɂ���
	lpGameTask.camera->SetTarget(ball[targetBall]);

	for (auto itr = ObjList.begin(); itr != ObjList.end();)		//��ڰ��
	{
		breakNow;
		//�����蔻��Ăяo��(�~�Ɖ~)
		if ((*itr)->CollisionChack_Circle_Circle(ball[(targetBall + 1) % 2].GetPos(), (ball[(targetBall + 1) % 2].GetSize())))
		{
			switch ((*itr)->GetID())
			{
				case CHIP_DAMAGE:
				damageNow = true;
				if (!damageOld)
				{
					(*itr)->CollisionProcessing();
				}
				break;

				case CHIP_SPIN:
				//�����Ŕ��˂̑��i˯đ΍���Ƃ�A�������傫��������ۯ��Ɋւ��Ă͗�O
				spinNow = true;
				if (!spinOld)
				{
					(*itr)->CollisionProcessing();
				}
				break;

				case CHIP_PL:
				enemyNow = true;
				if (!enemyOld)
				{
					(*itr)->CollisionProcessing();
				}
				break;

				default:
				if ((*itr)->CollisionProcessing())
				{
					itr = (ObjList.erase(itr));
				}
			}
			damageOld = damageNow;
			spinOld = spinNow;
			enemyOld = enemyNow;
		}
		if (itr != ObjList.end())
		{
			itr++;
		}
	}
	damageOld = damageNow;
	spinOld = spinNow;
	enemyOld = enemyNow;
}

void Player:: SizeUp()
{
	int size = ball[(targetBall + 1) % 2].GetSize();
	if (size <= 48)
	{
		size += 1;
	}
	ball[(targetBall + 1) % 2].SetSize(size);
}

void Player::ChangeState()
{
	invincibleCnt--;
	if (invincibleCnt <= 0)
	{
		stateInvincible = false;
		lpGameTask.camera->SetVibFlag(false);
	}
}

bool Player::FailChack()
{
	if (life == 0)
	{
		return true;
	}
	return false;
}

bool Player::ClearChack()
{
	if (ClearBlockCnt <= 0)
	{
		return true;
	}
	return false;
}

void Player::Draw()
{
	animCnt++;
	for (int i = 0; i < 2; ++i)
	{
		if (stateInvincible == true)
		{
			if (animCnt / 10 % 2 == 0)
			{
				ball[(targetBall + 1) % 2].Draw();		
			}
			ball[targetBall].Draw();
		}
		else 
		{
			ball[i].Draw();			//PlayerBall�׽��Draw(���L�q���Ă��Ȃ��̂Ōp����Obj��Draw)���Ăяo��
		}
	}

	//���ɕ\����
	DrawBox(600, 5, 600 + (20 * 4), 25, 0xff0000, true);					//�ő�̗�
	for (int i = 0; i < life; i++)
	{
		DrawBox(600 + (20 * i), 5, 620+ (20 * i), 25, 0x00ff00, true);		//���ݑ̗�
	}
	//���ɕ\�����A������������
}

int Player::GetLife()
{
	return life;
}

//�������Ăяo����� == ��Ұ�ނ��󂯂�
void Player::SetLife(const int & life)
{
	stateInvincible = true;					//��e���̖��G����
	invincibleCnt = 90;						//���G����(�ڰ�)
	this->life = life;
	lpGameTask.camera->SetVibFlag(true);
}

float Player::GetAngSpeed()
{
	return angSpeed;
}

void Player::SetAngSpeed(const float & angSpeed)
{
	this->angSpeed = angSpeed;
}

void Player::SetCleCnt(const int & ClearBlockCnt)
{
	this->ClearBlockCnt = ClearBlockCnt;
}


void Player::WarpPos(VECTOR2 pos)
{
	ball[targetBall].SetPos(pos);
}

bool Player::GetState()
{
	return stateInvincible;
}

int Player::GetCleCnt()
{
	return ClearBlockCnt;
}