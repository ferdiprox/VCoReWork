#pragma once

#include "math/int_math.h"

#define MIN(a,b)	(((a) < (b))?(a):(b))
#define MAX(a,b)	(((a) > (b))?(a):(b))

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

const uint MAP_POWER_X = 11;
const uint map_size_x = 1 << MAP_POWER_X;
const uint clip_mask_x = map_size_x - 1;
const uint TOR_POWER = 1;
const uint TOR_XSIZE = TOR_POWER*map_size_x;

extern uint MAP_POWER_Y;
extern uint map_size_y;
extern uint clip_mask_y;
extern uint iclip_mask_y;
extern uint clip_mask;
extern uint TOR_YSIZE;

#define XCYCL(x)	((x) & clip_mask_x)
#define YCYCL(y)	((y) & clip_mask_y)
#define iXCYCL(x)	((x) & clip_mask_x)
#define iYCYCL(y)	((y) & iclip_mask_y)

#ifdef _SURMAP_
const int MAX_RADIUS = 175;
#else
const int MAX_RADIUS = 48;
#endif

extern const char* mapFName;

extern int ColorShow;
extern unsigned char* palbuf,*palbufA,*palbufC;

inline void cycleTor(int& x,int& y)
{
	x &= TOR_XSIZE - 1;
	y &= TOR_YSIZE - 1;
}

#define PCSIDE	   64
#define PC_MAX	   2*PCSIDE + 1

#define mSQRT(a,b)	sqrt((a)*(double)(a) + (b)*(double)(b))
#define mATAN2(a,b)	((int)(atan2((double)-b,(double)a)*PiX2/(2.*_PI)) & ANGLE_CLAMP_MASK)

extern void* _video;

#define EXTERNAL_USE

char* GetTargetName(const char* name);

#define UP_LAYER	0
#define DOWN_LAYER	1

#define COL1		255
#define COL2		252
#define COL3		250
#define COL4		249
#define COL5		251

#ifdef _ROAD_
#define CLOCK()		(SDL_GetTicks()*18/1000)

#endif
#ifdef _DEBUG
extern int __GlobalSize__;
extern  XStream fmemory;
#define _MEM_STATISTIC_(a) fmemory < a <= __GlobalSize__ < "\tclock\t" <= CLOCK() < "\n";
#else
#define _MEM_STATISTIC_(a) ;
#endif
