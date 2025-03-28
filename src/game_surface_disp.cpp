#include "game_surface_disp.h"

#include "xgraph.h"
#include "xbuffer.h"

#include "terra/vmap.h"
#include "sound/hsound.h"
#include "uvs/univang.h"
#include "units/uvsapi.h"
#include "units/moveland.h"
#include "units/hobj.h"
#include "iscreen/iscreen.h"
#include "iscreen/i_chat.h"
#include "actint/actint.h"
#include "userinput/text_input.h"

#include "dbg_console.h"
#include "network.h"
#include "sqfont.h"
#include "backg.h"

// TODOf: move this shit into camera data (and not only)
void calc_view_factors();
void camera_reset();

void actIntQuant();

extern actIntDispatcher* aScrDisp;
extern int camera_zmin;
extern int FirstDraw;
extern int Redraw;
extern int MuteLog;
extern char fps_string[20];
extern XBuffer msg_buf;

GameSurfaceDispatcher::GameSurfaceDispatcher(int _x,int _y,int _xside,int _yside)
{
	xside = _xside;
	yside = _yside;
	xsize = 2*xside/* + 1*/;
	ysize = 2*yside/* + 1*/;

	sy = ysize;
	sx = xsize;

	_xI = _x; _yI = _y;
	x = _x - sx/2; y = _y - sy/2;

	xc = x + sx/2;
	yc = y + sy/2;

	ScreenCX = xc;
	ScreenCY = yc;

	UcutLeft = xc - xside;
	UcutRight = xc + xside;
	VcutUp = yc - yside;
	VcutDown = yc + yside;

	if (XGR_Obj.get_screen_scale_x() == 1.6f) {
		UcutRight = (XGR_MAXX - (800 - aScrDisp -> curIbs -> SizeX));
	}

	focus_flt = focus = 512;

	reset();
}

void GameSurfaceDispatcher::change(int Dx,int Dy,int mode,int xcenter,int ycenter)
{
	int xsize_old = xsize;
	if(mode) {
		if(xside + Dx > XGR_MAXX/2 - 2 || xside + Dx < 100) {
			return;
		}
		if(yside + Dy > XGR_MAXY/2 - 2 || yside + Dy < 100) {
			return;
		}

		xside += Dx;
		yside += Dy;
	} else {
		xside = Dx;
		yside = Dy;
	}

	xsize = 2*xside + 0;
	ysize = 2*yside + 0;

	sy = ysize;
	sx = xsize;

	if(mode) {
		x = _xI - sx/2;
		y = _yI - sy/2;
	} else {
		x = xcenter - xside;
		y = ycenter - yside;
	}

	xc = x + sx/2;
	yc = y + sy/2;

	ScreenCX = xc;
	ScreenCY = yc;

	UcutLeft = xc - xside;
	UcutRight = xc + xside;
	VcutUp = yc - yside;
	VcutDown = yc + yside;

	if (XGR_Obj.get_screen_scale_x() == 1.6f) {
		UcutRight = (XGR_MAXX - (I_RES_X - aScrDisp -> curIbs -> SizeX));
	}

	TurnSecX = TurnSecX*xsize/xsize_old;
	camera_zmin = camera_zmin*xsize/xsize_old;

	calc_view_factors();

	FirstDraw = 1;
	Redraw = 1;
}

void GameSurfaceDispatcher::reset(void)
{
	ViewZ=focus;
	TurnAngle = 0;
	prmFlag = 0;
	SlopeAngle = 0;
	DepthShow = 0;
	camera_zmin = TurnSecX = xsize / XGR_Obj.get_screen_scale_x();
	TurnSecY = ysize;
	TurnSideX = TurnSecX >> 1;
	TurnSideY = TurnSecY >> 1;
	ScaleMapFlt = 1;
	ScaleMapInvFlt = 1;
	ScaleMap = 256;
	ScaleMapInv = 256;

	if(ViewX == 0 && ViewY == 0) {
		ViewX = XCYCL(1517);
		ViewY = YCYCL(15879);
		vMap -> accept(ViewY - 100, ViewY + 100);
	} else {
		vMap -> accept(ViewY - 100, ViewY + 100);
		GeneralLoadReleaseFlag = 1;
	}

	camera_reset();
}

void GameSurfaceDispatcher::flush()
{
	XGR_Flush(xc - xside,yc - yside,xsize,ysize);
}

void GameSurfaceDispatcher::update()
{
	static XBuffer status;
	static int blink,clcnt;

	if(!MuteLog && ((ConTimer.counter&7) == 0)) 
	{
		SoundQuant();
	}

	if(GeneralSystemSkip) 
	{
		actIntQuant();
	}

	uvsQuant();

	if(GeneralSystemSkip && !ChangeWorldSkipQuant)
	{
        BackD.restore();
        MLquant();
        GameD.Quant();

		if(DepthShow) 
        {
            //Наклон изображения
            vMap -> SlopTurnSkip(TurnAngle,SlopeAngle,ViewZ,focus,ViewX,ViewY,xc,yc,xsize/2,ysize/2);
		}
        else
        {
			if(TurnAngle) 
            {
				//Вращение
				vMap -> turning(TurnSecX,-TurnAngle,ViewX,ViewY,xc,yc,xside,yside);
			} 
            else 
            {
				vMap -> scaling(TurnSecX,ViewX,ViewY,xc,yc,xside,yside);
			}
		}


		//Отрисовка 3д моделей
		GameD.DrawQuant();
	}

	if(!FirstDraw) {
		//zmod chat onscreen
		if (message_dispatcher.ListSize>0 && message_dispatcher.new_messages) {
			XBuffer zChat;
			int zColor = zCOLOR_WHITE;
			int zCount = 0;
			MessageElement* msg = message_dispatcher.last();
   			while (msg && zCount < zCHAT_ROWLIMIT && msg->time + zCHAT_TIMELIMIT > SDL_GetTicks()) {
				zCount++;

				switch(msg->color) {
					case 0:	zColor = zCOLOR_GREEN;	break;
					case 1:	zColor = zCOLOR_ORANGE;	break;
					case 2:	zColor = zCOLOR_BLUE;	break;
					case 3:	zColor = zCOLOR_YELLOW;	break;
					case 4:	zColor = zCOLOR_RED;	break;
					case 5:	zColor = zCOLOR_WHITE;	break;
					case 6:	zColor = zCOLOR_GRAY;	break;
					case 7:	zColor = zCOLOR_BLACK;	break;
					case 8:	zColor = zCOLOR_CAMOUFLAGE;	break;
					case 9:	zColor = zCOLOR_PATROL;	break;
					default:zColor = zCOLOR_WHITE;
				}

				if (msg->message[0]=='$' && msg->message[1]==':')
					zColor = zCOLOR_RED;

				zChat.init();
				zChat < msg->message;
				if (!iChatMUTE) 
                {
					zchatfont.draw(
						xc-xside+80,
						yc-yside+20+(zCHAT_ROWLIMIT*zCHAT_ROWHEIGHT)-(zCount*zCHAT_ROWHEIGHT),
						(unsigned char*)(zChat.GetBuf()),
						zColor,
						zCOLOR_TRANSPARENT
					);
				}

				if(msg == message_dispatcher.first()) break;
				msg = (MessageElement*)msg->prev;
  			}

			message_dispatcher.new_messages = zCount;
		}

		// All Debug Messages should be placed here
		if(prmFlag & PRM_FPS) {
			sysfont.draw(xc + xside - 150,yc - yside + 80,(unsigned char*)fps_string,224 + 15,-1);
			status.init();

			status <= ViewX < " " <= ViewY;

			sysfont.draw(xc + xside - 150,yc - yside + 96,(unsigned char*)status.GetBuf(),224 + 15,-1);

			if(globalGameState.inNetwork)
				sysfont.drawtext(xc - xside + 3,yc - yside + 32,network_analysis_buffer.buf,255,-1);

            status.init();
            status < "Speed_correction_factor: " <= speed_correction_factor < "\n";
            sysfont.drawtext(xc - xside + 3,yc + yside - 60,status.buf,255,-1);
		}

		msg_buf.init();

        // TODOf: revive (probably could add a command into debug console to toggle thi)
		//if(StandLog) 
		//{
		//	ScreenQuant();
		//}

//2D Rendring in game.
#ifdef ACTINT
		XGR_Obj.set_2d_render_buffer();
		//XGR_Obj.fill(2);
		if(GeneralSystemSkip) {
			aScrDisp -> redraw();
		}
		aScrDisp -> flush();
		//aScrDisp->pal_flush();
		XGR_Obj.set_default_render_buffer();
		aScrDisp -> text_redraw();
#endif

        dbgConsole.update();
	}

	FirstDraw = 0;

    text_input::endFrame();
}

GameSurfaceDispatcher* curSurfaceDisp = 0;
