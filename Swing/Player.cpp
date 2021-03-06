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

		/////////　こ↓こ↓　////////
		ball[i].Init("image/playerball.png", { 48, 48 }, { 2, 1 }, { i , 0 }, 0);
		/////////　こ↑こ↑　////////

	}
	lpGameTask.camera->SetTarget(ball[targetBall]);
}

Player::~Player()
{

}

int Player::UpData()
{
	Circle();			//円回転
	Collision();		//あたり判定諸々の処理
	ChangeState();		//無敵処理
	return 0;
}

void Player::Circle()
{
	// 角度更新
	angle += angSpeed;

	pos = ball[targetBall].GetPos();		//軸の座標(PlayerBallのPos参照)
	pos.x += cos(angle) * (cirRadius + ball[(targetBall + 1) % 2].GetSize() / 2);			//回転する球の座標(初回は初期位置決めにもなる)
	pos.y += sin(angle) * (cirRadius + ball[(targetBall + 1) % 2].GetSize() / 2);

	ball[(targetBall + 1) % 2].SetPos(pos);

	if (keyData[KEY_INPUT_SPACE] && !keyDataOld[KEY_INPUT_SPACE])
	{
		if (targetBall == 0)		//動いている球がBall[0]の場合
		{
			targetBall++;			//動かす球をBall[1]に変更する
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
	//ここでｶﾒﾗのﾀｰｹﾞｯﾄ(追従)を条件式にする
	lpGameTask.camera->SetTarget(ball[targetBall]);

	for (auto itr = ObjList.begin(); itr != ObjList.end();)		//ｲﾃﾚｰﾀｰ
	{
		breakNow;
		//あたり判定呼び出し(円と円)
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
				//ここで反射の多段ﾋｯﾄ対策をとる、ただし大きい壊れるﾌﾞﾛｯｸに関しては例外
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
			ball[i].Draw();			//PlayerBallｸﾗｽのDraw(を記述していないので継承元ObjのDraw)を呼び出し
		}
	}

	//仮に表示中
	DrawBox(600, 5, 600 + (20 * 4), 25, 0xff0000, true);					//最大体力
	for (int i = 0; i < life; i++)
	{
		DrawBox(600 + (20 * i), 5, 620+ (20 * i), 25, 0x00ff00, true);		//現在体力
	}
	//仮に表示中、ここをいじる
}

int Player::GetLife()
{
	return life;
}

//ここが呼び出される == ﾀﾞﾒｰｼﾞを受けた
void Player::SetLife(const int & life)
{
	stateInvincible = true;					//被弾時の無敵時間
	invincibleCnt = 90;						//無敵時間(ﾌﾚｰﾑ)
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