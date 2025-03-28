#pragma once

#define E_MAINMAP      24
#define E_AUXMAP       25

#define PRM_ROTMAP	0x0001
#define PRM_INFO	0x0002
#define PRM_FPS		0x0004
#define PRM_NETWORK	0x0008

struct GameSurfaceDispatcher 
{
	int xc,yc;
	int xside,yside;
	int xsize,ysize;
	int dx,dy;
	int _xI,_yI;
	int prmFlag;
	int sx,sy;
	int x,y;

	void update();
	void flush(void);
	void quant(void);
	void reset(void);
	void change(int Dx,int Dy,int mode = 1,int xcenter = -1,int ycenter = -1);

	GameSurfaceDispatcher(int _x,int _y,int _xside,int _yside);
};

extern GameSurfaceDispatcher* curSurfaceDisp;
