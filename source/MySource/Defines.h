#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "FloatOperator.h"

// 画面サイズ
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)

// リソースパス
#define ASSET(path)	"Assets/"path

#define DEB (1)

enum Texture_Kind
{
	NULL_TEX,
	NUMBERS,
	EXPLOSION,
	FLASH,
	BOOSTGAUGE,
	AIM,
	SMOKE,
	TEX_BULLET,
	TITLE,
	PVP,
	PVE,
	TUTORIAL,
	TUTORIAL1,
	TUTORIAL2,
	TUTORIAL3,
	TUTORIAL4,
	TUTORIAL5,
	TUTORIAL6,
	TUTORIAL7,
	TUTORIAL8,
	LOGO,
	VICTORY,
	BB,
	KILLS,

	MAX_KIND,
};
namespace ANIME
{
	enum ANIME_STATE
	{
		WAIT,
		PLAY,
		STOP,
		END,
	};
}

// 扇
struct Fan
{
	Float2 Position;
	float FanDegree;
	float Length;
	float RotateDegree;
};

#endif // __DEFINES_H__