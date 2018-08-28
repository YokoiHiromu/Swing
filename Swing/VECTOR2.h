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
	// 代入演算子
	VECTOR2& operator = (const VECTOR2& vec);		//operator = :ｵﾍﾟﾚｰﾀｰ演算子のｵｰﾊﾞｰﾛｰﾄﾞ、この時演算子として使わない

	//添え字演算子
	int& operator[](int i);

	//	比較演算子
	bool operator == (const VECTOR2& vec) const;	//oreratorの後ろは返す型を意識
	bool operator != (const VECTOR2& vec) const;	//true falseを今回は返すのでbool型

	//	単項演算子
	VECTOR2& operator +  (const VECTOR2& vec);
	//VECTOR2& operator +  (int k);
	VECTOR2& operator += (const VECTOR2& vec);	 // ｸﾗｽは実体保障がないので & (参照)をつける、書き換えxなのでconst
	VECTOR2& operator += (int k);
	VECTOR2& operator -= (const VECTOR2& vec);   //この場合左辺と右辺を足して左辺に代入するのでconst
	VECTOR2& operator *= (int k);
	VECTOR2& operator /= (int k);

	VECTOR2 operator +()const;					 //例(3)なら+(3)になる → 変わらない 布いて言うならunsigend(絶対値)に
	VECTOR2 operator -() const;					 //例(3)なら-(3)になる → +-が反転する
};

	//ベクトルの演算
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