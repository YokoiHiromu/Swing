#pragma once
#include <vector>
#include "VECTOR2.h"

enum ENEMY_MODE{
	MODE_UP_DOWN,
	MODE_RIGHT_LEFT,
	MODE_MAX
};

/////////　こ↓こ↓　////////
enum CHIP_TYPE {
	CHIP_BLANK,
	CHIP_BREAK,
	CHIP_DAMAGE,
	CHIP_SPIN,
	CHIP_CLEAR,
	CHIP_PL,
	CHIP_ENEMY,
	CHIP_ENEMY2,
	CHIP_EDIT = 9,
	CHIP_CNT_X
};
/////////　こ↑こ↑　////////


struct DataHeader {
	char fileID[13];					// ファイルのID情報
	unsigned char verID;				// ふぁいるのVer番号
	unsigned char reserve1[2];			// アライメント 予約領域
	int sizeX;							// マップのサイズX
	int sizeY;							// マップのサイズY
	unsigned char reserve2[3];			// アライメント 予約領域
	unsigned char sum;					// SUM値
};

#define START_EDIT_CHIP	CHIP_BLANK
#define LAST_EDIT_CHIP CHIP_ENEMY

using VEC_CHIP = std::vector<CHIP_TYPE>;
using VEC_CHIP2 = std::vector<VEC_CHIP>;

using VEC_INT = std::vector<int>;
using VEC_INT2 = std::vector<VEC_INT>;

using VEC_MODE = std::vector<ENEMY_MODE>;
using VEC_MODE2 = std::vector<VEC_MODE>;

#define SET_MAP_ID(X,Y,Z) MapCtl::GetInstance().SetMapData(X,Y,Z)
#define SET_MAP_ID2(A,B,X,Y) MapCtl::GetInstance().SetMapData(A,B,X,Y)
#define GET_MAP_ID(X) MapCtl::GetInstance().GetMapData(X)
#define GET_MAP_ID2(X,Y) MapCtl::GetInstance().GetMapData(X,Y)
#define GET_MAP_SIZE(X,Y) MapCtl::GetInstance().GetMapSize(X,Y)
#define lpMapCtl MapCtl::GetInstance()
//#define GET_AREA_SIZE MapCtl::GetInstance().GetAreaSize()
//#define GET_MAP_SIZE MapCtl::GetInstance().GetChipSize()

class MapCtl
{
public:
	static void Create();
	static void Destroy();
	static MapCtl &GetInstance()
	{
		Create();
		return *s_Instance;
	}

	bool SetMapData(VECTOR2 pos, CHIP_TYPE id, int size);
	bool SetMapData(VECTOR2 pos, CHIP_TYPE id, int size, ENEMY_MODE mode);
	CHIP_TYPE GetMapData(VECTOR2 pos);
	CHIP_TYPE GetMapData(int x, int y);
	int GetMapSize(int x, int y);
	ENEMY_MODE GetEnemyMode(int x, int y);
	void GetMapData();
	int GetChipSize(void);
	int GetDrawOffset(void);

	VECTOR2 GetViewAreaSize(void);
	VECTOR2 GetAreaSize(void);

	bool MapSave(void);
	bool MapLoad(void);
	int MapInit(void);
	void MapDraw(void);
	void MapClear();

private:
	MapCtl();
	~MapCtl();
	static MapCtl *s_Instance;
	VEC_CHIP2 mapID;
	VEC_INT2 mapSize;
	VEC_MODE2 enemyMode;
};