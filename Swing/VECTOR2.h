#pragma once

class VECTOR2
{
public:
	VECTOR2();
	VECTOR2(int x, int y);
	VECTOR2(double x, double y);
	~VECTOR2();
	int x;
	int y;
	// ������Z�q
	VECTOR2& operator = (const VECTOR2& vec);		//operator = :���ڰ�����Z�q�̵��ް۰�ށA���̎����Z�q�Ƃ��Ďg��Ȃ�

	//�Y�������Z�q
	int& operator[](int i);

	//	��r���Z�q
	bool operator == (const VECTOR2& vec) const;	//orerator�̌��͕Ԃ��^���ӎ�
	bool operator != (const VECTOR2& vec) const;	//true false������͕Ԃ��̂�bool�^

	//	�P�����Z�q
	VECTOR2& operator +  (const VECTOR2& vec);
	//VECTOR2& operator +  (int k);
	VECTOR2& operator += (const VECTOR2& vec);	 // �׽�͎��̕ۏႪ�Ȃ��̂� & (�Q��)������A��������x�Ȃ̂�const
	VECTOR2& operator += (int k);
	VECTOR2& operator -= (const VECTOR2& vec);   //���̏ꍇ���ӂƉE�ӂ𑫂��č��ӂɑ������̂�const
	VECTOR2& operator *= (int k);
	VECTOR2& operator /= (int k);

	VECTOR2 operator +()const;					 //��(3)�Ȃ�+(3)�ɂȂ� �� �ς��Ȃ� �z���Č����Ȃ�unsigend(��Βl)��
	VECTOR2 operator -() const;					 //��(3)�Ȃ�-(3)�ɂȂ� �� +-�����]����
};

	//�x�N�g���̉��Z
	//VECTOR2 + VECTOR2
	VECTOR2 operator + (const VECTOR2& v, const VECTOR2& w);
	//VECTOR2 - VECTOR2
	VECTOR2 operator - (const VECTOR2& v, const VECTOR2& w);
	//VECTOR2 + int
	VECTOR2 operator + (const VECTOR2& v, int k);
	//VECTOR2 + int
	VECTOR2 operator - (const VECTOR2& v, int k);
	//VECTOR2 * int 
	VECTOR2 operator * (const VECTOR2& v, int k);
	VECTOR2 operator * (int k, const VECTOR2& v);
	//VECTOR2 / int
	VECTOR2 operator / (const VECTOR2& v, int k);
	//VECTOR2 % int
	VECTOR2 operator % (const VECTOR2& v, int k);