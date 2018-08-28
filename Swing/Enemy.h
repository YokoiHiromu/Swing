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
	int addMove;		//�ړ����̉��Z�l
	int moveDistance;	//�ݒu�n�_����̍��v���Z�l
	int moveLimit;		//���Z���E
	int moveInv;		//�������̒�~����

	int radius;
	float angle;			//�p�x
	float angSpeed;			//�p���x
};

