#define _ROAD_

#include "xgraph.h"

#include "zmod_client.h"

#include "lang.h"

#define SCREENSHOT

#define ISCREEN
//#define ACTINT
#define SHOW_LOGOS
#define SHOW_IMAGES

#ifdef QUICK_LOAD
#undef ISCREEN
#undef SHOW_IMAGES
#undef SHOW_LOGOS
#endif

#include "_xsound.h"

#include "runtime.h"

#include "game_surface_disp.h"
#include "backg.h"

#include "xjoystick.h"
#include "network.h"

#include "3d/3d_math.h"
#include "3d/3dgraph.h"
#include "3d/3dobject.h"
#include "fs/parser.h"

#include "actint/item_api.h"
#include "units/uvsapi.h"

#include "terra/world.h"
#include "terra/vmap.h"
#include "terra/render.h"

#include "particle/particle.h"
#include "particle/light.h"
#include "particle/partmap.h"
#include "particle/df.h"

#include "uvs/univang.h"
#include "uvs/screen.h"
#include "uvs/diagen.h"

#include "dast/poly3d.h"

#include "units/track.h"
#include "units/hobj.h"
#include "units/moveland.h"
#include "units/effect.h"
#include "units/items.h"
#include "units/sensor.h"
#include "units/mechos.h"
#include "terra/cpuid.h"

#ifdef ACTINT
#include "iscreen/ikeys.h"
#include "iscreen/hfont.h"
#include "iscreen/iscreen.h"
#include "iscreen/controls.h"
#include "iscreen/i_chat.h"
#include "actint/actint.h"
#endif

#include "palette.h"
#include "sound/hsound.h"

#include "camera_data.h"
#include "sqfont.h"
#include "random.h"
#include "master_boot_data.h"
#include "dbg_console.h"
#include "game_state.h"
#include "userinput/text_input.h"

#ifndef DBGCHECK
#define DBGCHECK
#endif

#ifdef MEMORY_STATISTICS
#define MEMSTAT(a) fmem < "\r\n------->>>>>> " < a < "\r\n";
#else
#define MEMSTAT(a)
#endif

#ifdef _DEBUG
XStream fmemory("memstats.dmp", XS_OUT);
#endif

/* ----------------------------- EXTERN SECTION ---------------------------- */
extern XStream fout;
extern uchar* iscrPal;
extern int MainRqCounter,AuxRqCounter;
extern int RQ_THREAD_COUNT;
extern int SlopeQualityFactor;
extern int camera_zmin;
extern int camera_slope_min;
extern int stop_camera;
extern int camera_moving_xy_enable;
extern int camera_moving_z_enable;
extern int camera_slope_enable;
extern int camera_rotate_enable;

extern int EngineNoise;
extern int BackgroundSound;

extern int aciGroundPressingEnabled;
extern bool aciKeyboardLocked;
extern int SoundVolumePanning;

#ifdef ACTINT
extern int aciLoadLog;
extern actIntDispatcher* aScrDisp;
#endif

extern int NumHumanModel;

extern int EffectInUsePriory,EffectInUse;

void iPreInitFirst();

/* --------------------------- PROTOTYPE SECTION --------------------------- */
void ShowImageMousePress(int fl, int x, int y);
void ShowImageKeyPress(SDL_Event *k);
void restore(void);
int NetInit(ServerFindChain* p);
void camera_reset();
int sqrint(int x);
void showF(int x0,int y0,int x1,int y1);
void showCell(void);
void showRadar(void);
void buildField(void);
void MechPrepare(void);
void hObjPrepare(void);
void cycleTor(int& x,int& y);
char* GetTargetName(const char* name);
void shotFlush(void);
void LoadingMessage(int flush = 0);
void vMapInit(void);
void theEND(void);
void aciSetCameraMenu(void);
void calc_view_factors();
void gameQuant(void);
void SetupPath(void);
char* getRC(void);

void GameTimerON_OFF(void);

void uvsRestoreVanger(void);

void MLload(void);
int MLquant(void);

#ifdef ACTINT
void aciLoadData(void);
void aInit(void);
void aRedraw(void);
void aKeyTrap(SDL_Event *k);
void actIntQuant(void);
void aciPrepareMenus(void);
int acsQuant(void);
void aciFreeAll(void);
void aciFreeUVS(void);
void aLoadFonts32(void);
char* Convert(const char* s,int back = 0);
char* ConvertUTF8(const char* s,int back = 0);
#ifndef ISCREEN
void aKeyInit(void);
#endif
#endif

#ifdef ISCREEN
void aci_LocationQuantPrepare(void);
void aci_LocationQuantFinit(void);
#endif

void KeyCenter(SDL_Event *key);
int distance(int,int);
extern int ibsout(int,int,void*,void*);
int sdlEventToCode(SDL_Event *event);

/* --------------------------- DEFINITION SECTION -------------------------- */

// Data for FPS analyse: counting ticks before debug data updating.
static constexpr int FPS_PERIOD = 50;
int fps_frame,fps_start;
char fps_string[20];

#ifdef MEMORY_STATISTICS
XStream fmem("MEMORY.DMP",XS_OUT);
int memQ,memIndex;
int memStart;
void memstatInit(void);
void memstatDumpLeak(void);
#endif

int page;
clock_t _Timer_;
int frame;
int Quit = 1;
int Dead;

XBuffer msg_buf(16000);

int view_lock = 0;
int debug_view = 0;
int loadingStatus = 1;

int GameQuantReturnValue = 0;

int XSIDE = 200;	  //200 	  270
int YSIDE = 170;	  //170 	  210
int XSIZE = 2*XSIDE + 1;
int YSIZE = 2*YSIDE + 1;

int MainRqCounter,AuxRqCounter;

int MuteLog = 0;
int DepthShow;

int SkipIntro = 0;

int zoom_delta;
int zoom_threshold;

int beebos;

int Redraw = 1;
int Pause = 0;
int FirstDraw = 1;

int speed_correction_enabled = 1;
int prev_frame_time = 0;

const char* mapFName = "wrlds.dat";

int ColorShow = 1;
int WorldPrm;
int shotNum;

int ExclusiveLog = 1;
int DIBLog = 0;
int MMXsuppress;
int SkipCD;

int CurrentWorld = 0;
int IsMainMenu = 0;

int TimerMode = 1;

extern int* AVI_index;

int TotalDrawFlag = 1;

int RecorderMode = 0;
char* RecorderName = NULL;

int COMPAS_RIGHT;
constexpr int DEFAULT_COMPAS_RIGHT = 80;
constexpr int HD_COMPAS_RIGHT = 340;

#ifdef _DEMO_
int aciCompleteGameFlag = 0;
#endif

int ShowImageMouseFlag = 0;
int ShowImageKeyFlag = 0;

extern int activeWTRACK;

void MainMenuRTO::Init(int id)
{
	XGR_Obj.set_is_scaled_renderer(true);
	Dead = 0;
//	activeWTRACK = 0;
_MEM_STATISTIC_("BEFORE MAIN MENU INIT -> ");
#ifdef ISCREEN
	if(!(flags & RTO_INIT_FLAG)){
		LoadingMessage(1);
		iInit();
_MEM_STATISTIC_("AFTER MAIN iINIT INIT -> ");

		palTr -> set(NULL,iscrPal,0,255,&Quit);
		palTr -> quant();

		iQuantFirst();
		iQuantPrepare();
_MEM_STATISTIC_("AFTER IQUANTFIRST INIT -> ");

		//XGR_Flush(0,0,I_RES_X,I_RES_Y);

		SetFlag(RTO_INIT_FLAG);
		rtoSetNextID(RTO_PALETTE_TRANSFORM_ID,RTO_MAIN_MENU_ID);
//		  rtoSetNextID(RTO_ESCAVE_INGATE_ID,RTO_FIRST_ESCAVE_ID);
	}
	else {
		iKeyClear();

		XGR_MouseShow();
	}
#else
	aLoadFonts32();
#endif

	XGR_Obj.set_fullscreen(iGetOptionValue(iFULLSCREEN));
	iSetResolution(iGetOptionValue(iSCREEN_RESOLUTION));
_MEM_STATISTIC_("AFTER MAIN MENU INIT -> ");
}

int MainMenuRTO::Quant(void)
{
#ifdef ISCREEN
	int code;
	char* pal;

	MainMenuSoundQuant();
	if(flags & RTO_QUANT_FLAG){
		code = iQuantSecond();
		if(code){
			if(!iScrExitCode){
				pal = new char[768];
				i_slake_pal((unsigned char*)pal,32);
				delete[] pal;

				aciPrepareEndImage();
				return RTO_SHOW_IMAGE_ID;
			}
			rtoSetNextID(RTO_LOADING1_ID,RTO_FIRST_ESCAVE_ID);
			return RTO_LOADING1_ID;
		}
		return 0;
	}
	else {
		SetFlag(RTO_QUANT_FLAG);
		return RTO_PALETTE_TRANSFORM_ID;
	}

#else
	return RTO_LOADING1_ID;
#endif
}

void MainMenuRTO::Finit(void)
{
	XGR_Obj.set_is_scaled_renderer(false);
#ifdef ISCREEN

	if(flags & RTO_FINIT_FLAG){
		SoundVolumePanning = !iGetOptionValue(iPANNING_ON);
		aciGroundPressingEnabled = iGetOptionValue(iDESTR_MODE);
		EngineNoise = !iGetOptionValue(iMECH_SOUND);
		BackgroundSound = !iGetOptionValue(iBACK_SOUND);
		iFinitQuant();
		ClearFlag(RTO_ALL_FLAGS);

	}
	else
	{
		SetFlag(RTO_FINIT_FLAG);
	}
	XGR_MouseHide();
#endif
_MEM_STATISTIC_("AFTER MAIN MENU FINIT -> ");
}

void LoadingRTO1::Init(int id)
{
	if(!MuteLog && EffectInUsePriory)
	{
		if(!iGetOptionValue(iSOUND_ON))
		{
			SetSoundVolume(iGetOptionValue(iSOUND_VOLUME_CUR)*256/iGetOptionValue(iSOUND_VOLUME_MAX));
		} 
		else 
		{
			MuteLog = 1; EffectInUsePriory = EffectInUse = 0;
		}
	}

	if(!(flags & RTO_INIT_FLAG)){
		uniVangPrepare();
		uvsCreateItem_in_Crypt();
	}

#ifdef ACTINT
#ifndef ISCREEN
	aKeyInit();
#endif
	aInit();
#endif

#ifdef ACTINT
	if (XGR_Obj.get_screen_scale_x() == 1) {
		XSIDE = aScrDisp -> curIbs -> SideX;
		YSIDE = aScrDisp -> curIbs -> SideY;
	} else {
		XSIDE = XGR_MAXX / 2;
		YSIDE = XGR_MAXY / 2;
	}
	XSIZE = 2*XSIDE;
	YSIZE = 2*YSIDE;
#else
	XSIDE = (XGR_MAXX)/2 - 4;
	YSIDE = (XGR_MAXY)/2 - 4;
	XSIZE = 2*XSIDE;
	YSIZE = 2*YSIDE;
#endif

	set_key_handlers(&KeyCenter, NULL);

	graph3d_init();

	GeneralSystemInit();

//	palTr -> set(iscrPal,palbufInt,0,255,&Quit);
	palTr -> set(iscrPal,NULL,0,255,&Quit);

	Quit = 1;
	while(Quit){
		palTr -> quant();
		SDL_Delay(10);
	}


	LoadingMessage(1);
	diagenPrepare();
_MEM_STATISTIC_("AFTER LOADING RTO1 INIT -> ");
}

int LoadingRTO1::Quant(void)
{
	//XGR_Flip();
	if(!(flags & RTO_QUANT_FLAG)){
		SetFlag(RTO_QUANT_FLAG);
		return 0;
	}
#ifdef ISCREEN
	return NextID;
#else
	return RTO_LOADING2_ID;
#endif
}

void LoadingRTO1::Finit(void)
{
	ClearFlag(RTO_ALL_FLAGS);
_MEM_STATISTIC_("AFTER LOADING RTO1 FINIT -> ");
}

void EscaveOutRTO::Init(int id)
{
	XGR_Obj.fill(0, XGR_Obj.get_2d_rgba_render_buffer());
	XGR_Obj.set_is_scaled_renderer(true);
#ifdef ISCREEN
	iOutEscaveInit();
#endif
_MEM_STATISTIC_("AFTER ESCAVE INIT -> ");
}

int EscaveOutRTO::Quant(void)
{
#ifdef ISCREEN
	int val = iOutEscaveQuant();
	if(val){
		if(iAbortGameFlag){
			iAbortGameMode = 2;
			return RTO_LOAD_GAMEOVER_ID;
		}
		else
			return NextID;
	}
	//XGR_Flip();
	return 0;
#else
	return NextID;
#endif
}

void EscaveOutRTO::Finit(void)
{
	XGR_Obj.set_is_scaled_renderer(false);
#ifdef ISCREEN
	iOutEscaveFinit();
	aci_LocationQuantFinit();
	if(!iAbortGameFlag)
		uvsCloseQuant();
#endif
_MEM_STATISTIC_("AFTER ESCAVE FINIT -> ");
}

void FirstEscaveOutRTO::Init(int id)
{
	XGR_Obj.fill(0, XGR_Obj.get_2d_rgba_render_buffer());
	XGR_Obj.set_is_scaled_renderer(true);
#ifdef ISCREEN
#ifndef _ACI_SKIP_SHOP_
	iOutEscaveInit();
#endif
#endif
_MEM_STATISTIC_("AFTER FIRST ESCZVE INIT -> ");
}

int FirstEscaveOutRTO::Quant(void)
{
#ifdef ISCREEN
	int val;
#ifndef _ACI_SKIP_SHOP_
	val = iOutEscaveQuant();
#else
	val = 1;
#endif
	if(val){
		if(iAbortGameFlag){
			iAbortGameMode = 0;
			return RTO_LOAD_GAMEOVER_ID;
		}
		else
			return NextID;
	}
	//XGR_Flip();
	return 0;
#else
	return NextID;
#endif
}

void FirstEscaveOutRTO::Finit(void)
{
	XGR_Obj.set_is_scaled_renderer(false);
#ifdef ISCREEN
#ifndef _ACI_SKIP_SHOP_
	iOutEscaveFinit();
	aci_LocationQuantFinit();
#endif
#endif
_MEM_STATISTIC_("AFTER FIRST ESCAVE FINIT -> ");
}

void LoadSurfaceRTO::Init(int id)
{
#ifdef ISCREEN
	FinishFirstShopPrepare(aciLoadLog);
	aciLoadLog = 0;
	i_change_res();
	LoadingMessage(1);
#endif

#ifdef _DEBUG
	StandScreenPrepare();
#endif
_MEM_STATISTIC_("\nBEFORE VMAP  -> ");
	vMapPrepare(mapFName,CurrentWorld);
	vMapInit();
_MEM_STATISTIC_("AFTER VMAP  -> ");

	LoadResourceSOUND(GetTargetName("sound/"), 0);
_MEM_STATISTIC_("AFTER SOUND  -> ");

_MEM_STATISTIC_("AFTER LOAD PARAM  -> ");
	MLload();
_MEM_STATISTIC_("AFTER ML LOAD  -> ");
	PrepareLight();
_MEM_STATISTIC_("AFTER PREPARE LIGHT  -> ");
	EffD.CalcWave();

	dastCreateResource("resource/bml/mole.bml");
_MEM_STATISTIC_("AFTER DAST  -> ");
//	dastCreateResourceSign("resource\\bml\\sign.fnt");

	GeneralTableInit();
_MEM_STATISTIC_("AFTER TABLE GENERAL  -> ");
	GeneralTableOpen();
_MEM_STATISTIC_("AFTER TABLE OPEN  -> ");

#ifdef ACTINT
	if (XGR_Obj.get_screen_scale_x() == 1) {
		curSurfaceDisp = new GameSurfaceDispatcher(aScrDisp -> curIbs -> CenterX,aScrDisp -> curIbs -> CenterY,XSIDE,YSIDE);
	} else {
		curSurfaceDisp = new GameSurfaceDispatcher(XGR_MAXX / 2, XGR_MAXY / 2, XGR_MAXX / 2, XGR_MAXY / 2);
	}
	COMPAS_RIGHT = DEFAULT_COMPAS_RIGHT;
#else
	curSurfaceDisp = new GameSurfaceDispatcher(XGR_MAXX/2,XGR_MAXY/2,XSIDE,YSIDE);
#endif
	Redraw = 1;

_MEM_STATISTIC_("AFTER curSurfaceDisp  -> ");
	loadingStatus = 0;

	vMap -> quant();

	uvsAddStationaryObjs();

	uvsRestoreVanger();

#ifndef NEW_TNT
	RestoreBarell();
#endif
	gameQuant();
#ifndef NEW_TNT
	RestoreFlagBarell();
#endif

#ifdef ISCREEN
	palTr -> set(NULL,palbufOrg,0,255);
#else
	XGR_SetPal(palbufOrg,0,255);
#endif

#ifdef _ACI_SKIP_SHOP_
	XGR_SetPal(palbuf,0,255);
#endif

	XGR_Flush(0,0,XGR_MAXX,XGR_MAXY);
_MEM_STATISTIC_("AFTER LOADING RTO2 INIT -> ");

    dbgConsole.init();
}

void FirstEscaveRTO::Init(int id)
{
	XGR_Obj.set_is_scaled_renderer(true);
_MEM_STATISTIC_("\nBEFORE FIRST ESCAVE RTO INIT -> ");
#ifdef ISCREEN
	CurrentWorld = 0;
	if(aciLoadLog){
		aciLoadData();
_MEM_STATISTIC_("AFTER ACILOADDATA INIT -> ");
	}
	FirstShopPrepare(aciLoadLog);
_MEM_STATISTIC_("AFTER FIRSTSHOP PREPARE INIT -> ");
#ifndef _ACI_SKIP_SHOP_
	aci_LocationQuantPrepare();
_MEM_STATISTIC_("AFTER LOADQUANT PREPARE INIT -> ");
	aciShowLocation();
_MEM_STATISTIC_("AFTER SHOWLOCATION INIT -> ");
#else
	aciPrepareMenus();
_MEM_STATISTIC_("AFTER PREPARE MENU INIT -> ");
#endif
#endif
_MEM_STATISTIC_("AFTER FIRST ESCAVE RTO INIT -> ");
}

int LoadSurfaceRTO::Quant(void)
{
	//XGR_Flip();
	if(!(flags & RTO_QUANT_FLAG)){
		SetFlag(RTO_QUANT_FLAG);
		return 0;
	}
#ifdef ISCREEN
	return NextID;
#else
	return RTO_GAME_QUANT_ID;
#endif
}

void LoadSurfaceRTO::Finit(void)
{
	ClearFlag(RTO_ALL_FLAGS);
_MEM_STATISTIC_("AFRET LOADING RTO2 FINIT -> ");
}

int FirstEscaveRTO::Quant(void)
{
//std::cout<<"FirstEscaveRTO::Quant"<<std::endl;

#ifdef ISCREEN
	int code;
#ifndef _ACI_SKIP_SHOP_
	code = iQuantSecond();
#else
	code = 1;
#endif
	if(code){
		if(!iScrExitCode)
			return RTO_SHOW_IMAGE_ID;

		rtoSetNextID(RTO_FIRST_ESCAVE_OUT_ID,RTO_LOADING2_ID);
		rtoSetNextID(RTO_LOADING2_ID,RTO_GAME_QUANT_ID);
		return RTO_FIRST_ESCAVE_OUT_ID;
	}
	//XGR_Flip();
	return 0;
#else
	return RTO_GAME_QUANT_ID;
#endif
}

void FirstEscaveRTO::Finit(void)
{
	XGR_Obj.set_is_scaled_renderer(false);
	if(flags & RTO_FINIT_FLAG){
		ClearFlag(RTO_ALL_FLAGS);
	}
	else {
		SetFlag(RTO_FINIT_FLAG);
	}
_MEM_STATISTIC_("AFTER FIRST ESCAVE FINIT -> ");
}

void GameQuantRTO::Init(int id)
{
	vMap -> lockHeap();
_MEM_STATISTIC_("AFTER GAME QUANT INIT -> ");
}

void GameQuantRTO::Finit() {
	XGR_Obj.clear_2d_surface();
}

int GameQuantRTO::Quant(void)
{
	int ret = 0;
	if(!Pause || globalGameState.inNetwork)
	{
		if(Pause) Pause++;

		gameQuant();
//		DBGCHECK
		frame++;
		if(++fps_frame == FPS_PERIOD)
        {
			sprintf(fps_string,"%.1f",(double)FPS_PERIOD/(SDL_GetTicks() - (int)fps_start)*1000);
#ifdef _DEBUG
			network_analysis(network_analysis_buffer,0);
#else
			if(curSurfaceDisp -> prmFlag & PRM_FPS && globalGameState.inNetwork)
				short_network_analysis(network_analysis_buffer);
#endif
			fps_frame = 0;
			fps_start = SDL_GetTicks();
        }

		if(Redraw)
        {
			XGR_Flush(0,0,XGR_MAXX,XGR_MAXY);
			Redraw = 0;
			frame = 0;
			_Timer_ = SDL_GetTicks();
			fps_start = SDL_GetTicks();
        }

//		if(!PalIterLock && !palTr -> quant()) pal_iter();
		if(!PalIterLock) PalCD.Quant();
	}
	else 
	{
		if(GameQuantReturnValue || acsQuant())
		{
			Pause = 0;
		}
	}

	ret = GameQuantReturnValue;
	GameQuantReturnValue = 0;
	//XGR_Flip();
	return ret;
}

void EscaveRTO::Init(int id)
{
	XGR_Obj.set_is_scaled_renderer(true);
#ifdef ISCREEN
	uvsPrepareQuant();
	aci_LocationQuantPrepare();
	aciShowLocation();
#endif
_MEM_STATISTIC_("AFTER ESCAVE RTO INIT -> ");
}

int EscaveRTO::Quant(void)
{

#ifdef ISCREEN

	if(iQuantSecond()){
		if(!iScrExitCode)
			return RTO_SHOW_IMAGE_ID;

		rtoSetNextID(RTO_ESCAVE_OUT_ID,RTO_GAME_QUANT_ID);
		return RTO_ESCAVE_OUT_ID;
	}
	//XGR_Flip();
	return 0;
#else
	return RTO_GAME_QUANT_ID;
#endif
}

void EscaveRTO::Finit(void)
{
	XGR_Obj.set_is_scaled_renderer(false);
#ifdef ISCREEN
	if(flags & RTO_FINIT_FLAG){
		ClearFlag(RTO_ALL_FLAGS);
	}
	else {
		SetFlag(RTO_FINIT_FLAG);
	}
#endif
_MEM_STATISTIC_("AFTER ESCAVE RTO FINIT -> ");
#ifdef CDCHECK
	int mask = 1;
	int res = 0;
	int getCDdrives(void);
	int isCDok(int);
	int d = getCDdrives();
	for(int ii = 0;ii < 26;ii++,mask <<= 1)
		if(d & mask) res += isCDok(ii);
	if(!res) ErrH.Abort(AVInotFoundMSS);
#endif
}

void PaletteTransformRTO::Init(int) {
	XGR_Obj.set_is_scaled_renderer(true);
}

void PaletteTransformRTO::Finit() {
	XGR_Obj.set_is_scaled_renderer(false);
}

int PaletteTransformRTO::Quant(void)
{
	int val = palTr -> quant();
	if(!val) return NextID;
	//XGR_Flip();
	return 0;
}

void LoadGameoverRTO::Init(int id)
{
	ShowImageRTO* p = (ShowImageRTO*)xtGetRuntimeObject(RTO_SHOW_IMAGE_ID);
	p -> SetNumFiles(1);

	StopCDTRACK();

#ifdef MEMORY_STATISTICS
	memStart = 0;
#endif

#ifdef ACTINT
	XGR_MouseHide();
	extern int actIntLog;
	if(!actIntLog){
		palTr -> set(palbuf,NULL,0,255,&Quit);
		Quit = 1;
		int cnt = CLOCK();
		while(Quit){
			if(CLOCK() != cnt){
				palTr -> quant();
				cnt = CLOCK();
				xtClearMessageQueue();
				}
			}
		}
#endif

	aciFreeUVS();
	FreeAll(iAbortGameMode);
	iAbortGameMode = 1;
	LocalEffectFree();
	iAbortGameFlag = 0;
#ifdef ACTINT

	aciFreeAll();
#endif

	SetNext(RTO_SHOW_IMAGE_ID);
	rtoSetNextID(RTO_SHOW_IMAGE_ID,RTO_MAIN_MENU_ID);

	aciInitEndGame(globalGameState.gameoverTrigger);
}

int LoadGameoverRTO::Quant(void)
{
	return NextID;
}

void LoadGameoverRTO::Finit(void)
{
	EffectsOff();
}

void xtDoneApplication(void)
{
	restore();
}

void restore(void)
{
	KDWIN::destroy_server();
#ifdef _DEBUG
	network_analysis(network_analysis_buffer,1);
	fout < network_analysis_buffer.buf;
#endif
#ifdef MEMORY_STATISTICS
	memStart = 0;
#endif
	RestoreSOUND();
	SDL_Quit();

//	  win32_dump_mem();

//	char buf[20];
//	sprintf(buf,"%.3f",(double)frame/((int)SDL_GetTicks() - (int)_Timer_)*1000);
//	XCon < buf < " average fps\n";

//	delete sqr3_matr;
}

extern int light_modulation;
extern int WorldLightParam[WORLD_MAX][3];
extern int CurrentWorldLightParam;

void PalettePrepare(void) {
	std::cout<<"PalettePrepare"<<std::endl;
//	palbufC = new unsigned char[768];
//	palbufA = new unsigned char[768];
//	palbufOrg = new unsigned char[768];
	palbuf = palbufA;
	int k;
	memset(palbuf,0,768);
	int i,j;
	memset(palbufC,0,768);

	if(CurrentWorld < MAIN_WORLD_MAX - 1){
		WorldPalCurrent = WorldTable[CurrentWorld]->escT[0]->Pbunch->currentStage;
		light_modulation  = WorldLightParam[CurrentWorld][WorldPalCurrent];
		memcpy(palbufC,WorldPalData[WorldPalCurrent],768);
	}else{
		WorldPalCurrent = 0;
		light_modulation  = WorldLightParam[CurrentWorld][0];
		XStream fpal(GetTargetName(vMap -> paletteName),XS_IN);
		fpal.read(palbufC,768);
		fpal.close();
	};

	XStream ffp("resource/pal/objects.pal",XS_IN);
	ffp.seek(3*(ENDCOLOR[TERRAIN_MAX - 1] + 1),XS_BEG);
	ffp.read(palbufC + 3*(ENDCOLOR[TERRAIN_MAX - 1] + 1),768 - 3 - 3*(ENDCOLOR[TERRAIN_MAX - 1]));
	ffp.close();

	palbufC[0] = palbufC[1] = palbufC[2] = 0;
//	palbufC[3*BEGCOLOR[1]] = palbufC[3*BEGCOLOR[1] + 1] = palbufC[3*BEGCOLOR[1] + 2] = 1;

	for(i = 0;i < TERRAIN_MAX;i++){
		palbufC[3*BEGCOLOR[i] + 0] >>= 1;
		palbufC[3*BEGCOLOR[i] + 1] >>= 1;
		palbufC[3*BEGCOLOR[i] + 2] >>= 1;
		}

	palbuf = palbufC;

	for(i = 0;i < 16;i++) palbuf[3*(224 + i) + 0] = palbuf[3*(224 + i) + 1] = palbuf[3*(224 + i) + 2] = i*4; //(uchar)(10 + (pow((double)i/16.,.70)*UNIT)*54/UNIT);
	memcpy(palbufOrg,palbuf,768);

#if defined(ISCREEN) && defined(ACTINT)
//	memcpy(palbuf + 0*32*3,palbufOrg + 32*3,32*3);
//	memcpy(palbuf + 2*32*3,palbufOrg + 32*3,32*3);
//	memcpy(palbuf + 3*32*3,palbufOrg + 32*3,32*3);
//	memset(palbuf + 0*32*3,0,32*3);
//	memset(palbuf + 2*32*3,0,32*3);
//	memset(palbuf + 3*32*3,0,32*3);

	if(palbufInt) {
		delete[] palbufInt;
	}
	palbufInt = new uchar[768];
	uchar r = palbufOrg[3*(32 + 10) + 0];
	uchar g = palbufOrg[3*(32 + 10) + 1];
	uchar b = palbufOrg[3*(32 + 10) + 2];
	for(i = 0;i < 256;i++){
		palbufInt[i*3 + 0] = r;
		palbufInt[i*3 + 1] = g;
		palbufInt[i*3 + 2] = b;
		}
#endif
	if(CurrentWorld < MAIN_WORLD_MAX - 1) {
		for(k = 0;k < WorldPalNum;k++)	memcpy(WorldPalData[k] + 128*3,palbufOrg + 128*3,128*3);
	};

	if(CurrentWorld == WORLD_XPLO && ActD.SpobsDestroy){
		for(i = BEGCOLOR[SPOBS_PAL_TERRAIN]*3;i <= ENDCOLOR[SPOBS_PAL_TERRAIN]*3;i++)
			palbuf[i] = palbufSrc[i] = palbufOrg[i] = 5 * (i - BEGCOLOR[SPOBS_PAL_TERRAIN]*3) / (3*(ENDCOLOR[SPOBS_PAL_TERRAIN] - BEGCOLOR[SPOBS_PAL_TERRAIN]));
	};

	if(CurrentWorld == WORLD_THREALL && ActD.ThreallDestroy){
		for(j = 0;j < TERRAIN_MAX;j++){
			if(j == 3 || j == 5 || j == 6 || j == 4) break;
			for(i = BEGCOLOR[j];i <= ENDCOLOR[j];i++){
				palbufSrc[i*3] = palbufOrg[i*3] = 63 * (i - BEGCOLOR[j]) / (ENDCOLOR[j] - BEGCOLOR[j]);
				palbufSrc[i*3 + 1] = palbufOrg[i*3 + 1] = 63 *(i - BEGCOLOR[j]) / (ENDCOLOR[j] - BEGCOLOR[j]);
				palbufSrc[i*3 + 2] = palbufOrg[i*3 + 2] = 63 * (i - BEGCOLOR[j]) / (ENDCOLOR[j] - BEGCOLOR[j]);
			};
		};
	};
};

void KeyCenter(SDL_Event *key)
{
	extern int entry_scan_code;
	SDL_Keymod mod;

    text_input::inputFromSDL(*key);

	if(aciKeyboardLocked) {
#ifdef ACTINT
		aKeyTrap(key);
#endif
		return;
	}

	entry_scan_code = sdlEventToCode(key);
	switch(entry_scan_code)
	{
    case SDL_SCANCODE_GRAVE:
        dbgConsole.isOpen ^= 1;

        if(!aciKeyboardLocked)
        {
            aciKeyboardLocked = dbgConsole.isOpen;
        }
        break;
    case SDL_SCANCODE_ESCAPE:
#ifdef ESCAPE_EXIT
        disconnect_from_server();
        ErrH.Exit();
#endif
		if(!Pause)
		{
      	  	Pause = 1;
		}
//				  GameQuantReturnValue = RTO_LOAD_GAMEOVER_ID;
        break;
#ifndef ACTINT
    case SDL_SCANCODE_F1:
        curSurfaceDisp -> change(-3,-2);
        break;
    case SDL_SCANCODE_F2:
        curSurfaceDisp -> change(3,2);
        break;
#endif
#ifdef _DEBUG
    case SDL_SCANCODE_F12:
        DBGCHECK
        break;
#endif
#ifdef SCREENSHOT
//  		case SDL_SCANCODE_F4:
//  			creat_poster();
//  			break;
//		case SDL_SCANCODE_F11:
//			shotFlush();
//			break;
#endif
    case SDL_SCANCODE_F:
        mod = SDL_GetModState();
        if (mod&KMOD_CTRL) {
            curSurfaceDisp -> prmFlag ^= PRM_FPS;
        }

        break;
    case SDL_SCANCODE_F5:
        if(!Pause){
            camera_rotate_enable = 1 - camera_rotate_enable;
            aciSetCameraMenu();
        }
        break;
    case SDL_SCANCODE_F6:
        if(!Pause){
            camera_moving_xy_enable = 1 - camera_moving_xy_enable;
            camera_moving_z_enable = 1 - camera_moving_z_enable;
            aciSetCameraMenu();
        }
        break;
    case SDL_SCANCODE_F7:
        if(!Pause){
            camera_slope_enable = 1 - camera_slope_enable;
            aciSetCameraMenu();
        }
        break;
    }

	if (iKeyPressed(iKEY_ZOOM_IN)) {
		if(!Pause){
			if((camera_zmin -= 8) < curSurfaceDisp -> xsize*MIN_ZOOM >> 8)
				camera_zmin = curSurfaceDisp -> xsize*MIN_ZOOM >> 8;
		}
	}
	if (iKeyPressed(iKEY_ZOOM_OUT)) {
		if(!Pause){
			if((camera_zmin += 8) > curSurfaceDisp -> xsize*MAX_ZOOM >> 8)
				camera_zmin = curSurfaceDisp -> xsize*MAX_ZOOM >> 8;
		}
	}
	if (iKeyPressed(iKEY_ZOOM_STANDART)) {
		if(!Pause)
			camera_zmin = curSurfaceDisp -> xsize;
	}
	if (iKeyPressed(iKEY_SCREENSHOT)) {
		shotFlush();
	}

#ifdef ACTINT
	aKeyTrap(key);
#endif
}

void calc_view_factors()
{

	//if(!(XRec.flags & (XRC_RECORD_MODE | XRC_PLAY_MODE)) && prev_frame_time)
	//Stalkerg
	// Ferdi: there was '|' instead of '||'. i think that it is the typo, but need to check it.
	if((speed_correction_enabled || globalGameState.inNetwork) && prev_frame_time){
		int dt = SDL_GetTicks() - prev_frame_time;
		if(dt > 15 && dt < 200) {
			speed_correction_factor = (double)dt*((double)STANDART_FRAME_RATE/1000.0)*speed_correction_tau + speed_correction_factor*(1 - speed_correction_tau);
		}
	} else {
		speed_correction_factor = 1;
	}
	//speed_correction_factor = 1;
	//std::cout<<"DT::"<<SDL_GetTicks() - prev_frame_time<<std::endl;

	prev_frame_time = SDL_GetTicks();

	cycleTor(ViewX,ViewY);
	TurnSecY = curSurfaceDisp -> ysize*TurnSecX/curSurfaceDisp -> xsize;
	TurnSideX = TurnSecX >> 1;
	TurnSideY = TurnSecY >> 1;
	ViewZ = focus*TurnSecX/curSurfaceDisp -> xsize;
	ScaleMapFlt = (double)TurnSecX/curSurfaceDisp -> xsize;
	ScaleMapInvFlt = (double)curSurfaceDisp -> xsize/TurnSecX;
	ScaleMap = round(ScaleMapFlt*256);
	ScaleMapInv = round(ScaleMapInvFlt*256);
	DepthShow = SlopeAngle < -Pi/512;

	ModulatedNORMAL = (double)NORMAL*light_modulation/256.;
	Light = Vector(DBV(ModulatedNORMAL,0,ModulatedNORMAL*SHADOWDEEP/256.).norm(ModulatedNORMAL));

	CurrShadowDirection =  DBV(-fCos(TurnAngle),-fSin(TurnAngle),(double)SHADOWDEEP/256.);

	if(DepthShow){
		A_g2s = DBM(SlopeAngle,X_AXIS)*DBM(TurnAngle,Z_AXIS);
		A_s2g = DBM(-TurnAngle,Z_AXIS)*DBM(-SlopeAngle,X_AXIS);
	} else {
		A_g2s = DBM(TurnAngle,Z_AXIS);
		A_s2g = DBM(-TurnAngle,Z_AXIS);
	}

	A_g2sZ = A_g2s*DBM(1,1,-1,DIAGONAL);

	sinTurnInvFlt = sinTurnFlt = fSin(TurnAngle);
	cosTurnInvFlt =cosTurnFlt = fCos(TurnAngle);
	sinTurnFlt *= ScaleMapInvFlt;
	cosTurnFlt *= ScaleMapInvFlt;
	sinTurnInvFlt *= ScaleMapFlt;
	cosTurnInvFlt *= ScaleMapFlt;

	sinTurn = round(UNIT*sinTurnFlt);
	cosTurn = round(UNIT*cosTurnFlt);
	sinTurnInv = round(UNIT*sinTurnInvFlt);
	cosTurnInv = round(UNIT*cosTurnInvFlt);

	// Inverse factors calculation
	double M_x = A_g2s[0]*focus_flt;
	double N_x = A_g2s[1]*focus_flt;
	double M_y = A_g2s[3]*focus_flt;
	double N_y = A_g2s[4]*focus_flt;
	double M_z = A_g2s[6];
	double N_z = A_g2s[7];
	double H = ViewZ << 16;

	Ha = N_y*H;
	Va = -N_x*H;

	Hb = -M_y*H;
	Vb = M_x*H;

	Oc = M_x*N_y - M_y*N_x;
	Hc = M_y*N_z - M_z*N_y;
	Vc = M_z*N_x - M_x*N_z;
}

void gameQuant(void)
{
	curSurfaceDisp -> update();
	if(loadingStatus) LoadingMessage();
	curSurfaceDisp -> flush();
}

void PrintError(char* error, char* msg)
{
	std::cout<<"--------------------------------\n";
	std::cout<<error<<"\n";
	std::cout<<msg<<"\n";
	std::cout<<"--------------------------------\n";
}

void ShowImageRTO::Init(int id)
{
	XGR_Obj.set_is_scaled_renderer(true);
#ifdef SHOW_IMAGES
	int i;
	short sx,sy;

	XStream fh(0);
	XBuffer* XBuf = new XBuffer(1024);

	unsigned char* buf;
	char* pname;

	//NEED SEE
	set_key_handlers(&ShowImageKeyPress, NULL);
	XGR_MouseSetPressHandler(XGM_LEFT_BUTTON, ShowImageMousePress);
	XGR_MouseSetPressHandler(XGM_RIGHT_BUTTON, ShowImageMousePress);

	XBuf -> init();
	if(!(Flags[curFile] & IMG_RTO_NO_IMAGE)){
		if(Flags[curFile] & IMG_RTO_CD_IMAGE){
			*XBuf < iVideoPathDefault < fileNames[curFile];

			if(!fh.open(XBuf -> buf,XS_IN)){
				XBuf -> init();
				*XBuf < iVideoPath < fileNames[curFile];
				if(!fh.open(XBuf -> buf,XS_IN)){
					Flags[curFile] |= IMG_RTO_NO_IMAGE;
				}
				else
					fh.close();
			}
			else
				fh.close();
		}
		else
			*XBuf < fileNames[curFile];
	}

	pname = strdup(XBuf -> buf);
	memcpy(pname + strlen(pname) - 3,"pal",3);

	char* pal = new char[768];
	char* tpal = new char[768];
	memset(tpal,0,768);

	XStream ff(pname,XS_IN);
	ff.read(pal,768);
	ff.close();

	XGR_SetPal(tpal,0,255);

	if(!(Flags[curFile] & IMG_RTO_NO_IMAGE)){
		ff.open(XBuf -> buf,XS_IN);
		ff > sx > sy;

		if(!(Flags[curFile] & IMG_RTO_KEEP_IMAGE)){
			for(i = 0; i < sy; i ++){
				buf = XGR_GetVideoLine(i);
				ff.read(buf,sx);
			}
			imageData = NULL;
		}
		else {
			imageSX = sx;
			imageSY = sy;
			imageData = new char[sx * sy];
			ff.read(imageData,sx * sy);
			XGR_PutSpr(0,0,sx,sy,imageData,XGR_BLACK_FON);
		}
		ff.close();
	}
	else {
		XGR_Fill(0);
	}
	XGR_Flush(0,0,XGR_MAXX,XGR_MAXY);

	PalEvidence(tpal,pal);

	count = CLOCK();

	delete[] pal;
	delete[] tpal;
	free(pname);

	delete XBuf;

	ShowImageMouseFlag = 0;
	ShowImageKeyFlag = 0;

	switch(globalGameState.gameoverTrigger){
		case GAME_OVER_EXPLOSION:
			LastStartWTRACK(ST_GAMEOVER);
			break;
		case GAME_OVER_INFERNAL_LOCKED:
			LastStartWTRACK(ST_THEEND);
			break;
		case GAME_OVER_SPOBS_LOCKED:
			LastStartWTRACK(ST_THEEND);
			break;
		case GAME_OVER_ALL_LOCKED:
			LastStartWTRACK(ST_THEEND_DOUBLE);
			break;
		case GAME_OVER_LUCKY:
			LastStartWTRACK(ST_INTRO);
			break;
		case GAME_OVER_LAMPASSO:
			LastStartWTRACK(ST_GAMEOVER);
			break;
		case GAME_OVER_ABORT:
			LastStartWTRACK(ST_INTRO);
			break;
		case GAME_OVER_NETWORK:
			break;
		}

	globalGameState.gameoverTrigger
#endif
_MEM_STATISTIC_("AFTER SHOW IMAGE RTO INIT -> ");
}


void ShowAviRTO::Init(int id)
{
#ifdef SHOW_LOGOS



/*
	int x,y,sx,sy;

	XBuffer* XBuf = new XBuffer(1024);
	char* avi_pal,*pal,*tpal;

	if(!(Flags[curFile] & AVI_RTO_HICOLOR)){
		pal = new char[768];
		tpal = new char[768];
		memset(tpal,0,768);
	}

	set_key_nadlers(ShowImageKeyPress,NULL);
	XGR_MouseSetPressHandler(XGM_LEFT_BUTTON,ShowImageMousePress);
	XGR_MouseSetPressHandler(XGM_RIGHT_BUTTON,ShowImageMousePress);

	XBuf -> init();
	*XBuf < iVideoPathDefault < fileNames[curFile];

//	OLD XTOOL
//	if(!AVIopen(XBuf -> buf,AVI_NOTIMER | AVI_NODRAW | AVI_NOPALETTE | AVI_NO_SOUND,0,&aviBuf)){
	if(!AVIopen(XBuf -> buf,AVI_NOTIMER | AVI_NODRAW | AVI_NOPALETTE,0,&aviBuf)){
		XBuf -> init();
		*XBuf < iVideoPath < fileNames[curFile];
//		OLD XTOOL
//		if(!AVIopen(XBuf -> buf,AVI_NOTIMER | AVI_NODRAW | AVI_NOPALETTE | AVI_NO_SOUND,0,&aviBuf)){
		if(!AVIopen(XBuf -> buf,AVI_NOTIMER | AVI_NODRAW | AVI_NOPALETTE,0,&aviBuf)){
			aviBuf = NULL;
		}
	}

	if(aviBuf){
		if(!(Flags[curFile] & AVI_RTO_HICOLOR)){
			if(XGR_Obj.flags & XGR_HICOLOR)
				XGR_ReInit(800,600,emode);

			XGR_Fill(0);
			XGR_SetPal(tpal,0,255);
			XGR_Flush(0,0,XGR_MAXX,XGR_MAXY);
		}
		else {
			if(!(XGR_Obj.flags & XGR_HICOLOR)){
				if(XGR_ReInit(800,600,emode | XGR_HICOLOR)){
					XGR_ReInit(800,600,emode);
					aviBuf = NULL;
				}
			}
			else {
//				OLD XTOOL
//				XGR_Fill16RGB(0,0,0);
				XGR_Fill16(0);
				XGR_Flush(0,0,XGR_MAXX - 1,XGR_MAXY - 1);
			}
		}

		if(aviBuf){
			sx = AVIwidth(aviBuf);
			sy = AVIheight(aviBuf);

			x = (XGR_MAXX - sx) / 2;
			y = (XGR_MAXY - sy) / 2;

			if(!(Flags[curFile] & AVI_RTO_HICOLOR)){
				avi_pal = (char*)AVIGetPalette(aviBuf);
				memcpy(pal,avi_pal,768);

				AVIplay(aviBuf,x,y);
				AVIdraw(aviBuf);
				AVIstop(aviBuf);
				AVIclose(aviBuf);

				PalEvidence(tpal,pal);

				if(!AVIopen(XBuf -> buf,0,0,&aviBuf))
					ErrH.Abort(AVInotFoundMSS);
			}
			else {
				AVIstop(aviBuf);
				AVIclose(aviBuf);
//				OLD XTOOL
//				if(!AVIopen(XBuf -> buf,AVI_HICOLOR,0,&aviBuf))
				if(!AVIopen(XBuf -> buf,AVI_LOOPING,0,&aviBuf))
					ErrH.Abort(AVInotFoundMSS);
			}
			AVIplay(aviBuf,x,y);
		}
	}
	count = CLOCK();

	ShowImageMouseFlag = 0;
	ShowImageKeyFlag = 0;

	if(!(Flags[curFile] & AVI_RTO_HICOLOR)){
		delete pal;
		delete tpal;
	}
	delete XBuf;
*/
#endif
_MEM_STATISTIC_("AFTER SHOW IMAGE RTO INIT -> ");
}

int ShowImageRTO::Quant(void)
{
	int ret_flag = 1;
#ifdef SHOW_IMAGES
	LastSoundQuant();
	if(Flags[curFile] & IMG_RTO_SHOW_TEXT){
		ret_flag = aciTextQuant();
	}
	else {
		if(!(Flags[curFile & IMG_RTO_CDTRACK_TIME])){
			if((count + 10000) > CLOCK()){
				ret_flag = 0;
			}
		}
		else
			ret_flag = 0;

		if(ShowImageKeyFlag || ShowImageMouseFlag){
			ret_flag = 1;
		}
	}
#endif
	if(ret_flag){
		curFile ++;
		if(curFile >= numFiles)
			return NextID;
	}
	else {
		return 0;
	}

	return ID;
}

int ShowAviRTO::Quant(void)
{
#ifdef SHOW_LOGOS
/*
	int ret = 0;
	if(aviBuf){
		if(ShowImageKeyFlag || ShowImageMouseFlag){
			ret = 1;
		}
//		OLD XTOOL
//		if(AVIactive(aviBuf)){
			count= CLOCK();
//		}
//		else {
//			if((count + 100) < CLOCK())
//				ret = 1;
//		}

		if(!ret) return 0;
	}
*/
#endif
	curFile ++;
	if(curFile >= numFiles){
		return NextID;
	}

	return ID;
}

void ShowImageRTO::Finit(void)
{
	XGR_Obj.set_is_scaled_renderer(false);
#ifdef SHOW_IMAGES
	char* pal;
	pal = new char[768];
	i_slake_pal((unsigned char*)pal,32);
	delete[] pal;

	if(imageData) delete imageData;
#endif
_MEM_STATISTIC_("AFTER SHOW IMAGE RTO 4 FINIT -> ");
}

void ShowAviRTO::Finit(void)
{
#ifdef SHOW_LOGOS
/*
	char* pal;

	if(aviBuf){
		AVIstop(aviBuf);
		AVIclose(aviBuf);

		if(XGR_Obj.flags & XGR_HICOLOR && curFile >= numFiles) XGR_ReInit(800,600,emode);

		if(!(Flags[curFile - 1] & AVI_RTO_HICOLOR)){
			pal = new char[768];
			i_slake_pal((unsigned char*)pal,32);
			delete pal;
		}
	}
	else {
		if(XGR_Obj.flags & XGR_HICOLOR && curFile >= numFiles) XGR_ReInit(800,600,emode);
	}
*/
#endif
_MEM_STATISTIC_("AFTER SHOW IMAGE RTO 4 FINIT -> ");
}

void set_map_to_fullscreen()
{
	curSurfaceDisp -> change(
		XGR_MAXX / 2,
		XGR_MAXY / 2,
		0,
		XGR_MAXX / 2,
		XGR_MAXY / 2);
	Redraw = 1;

	COMPAS_RIGHT = DEFAULT_COMPAS_RIGHT;
}

void set_map_to_ibs(ibsObject* ibs)
{
	if (XGR_Obj.get_screen_scale_x() == 1) {
		curSurfaceDisp -> change(
			ibs->SideX,
			ibs->SideY,
			0,
			ibs->CenterX,
			ibs->CenterY);
		Redraw = 1;

		COMPAS_RIGHT = DEFAULT_COMPAS_RIGHT;
	} else {
		set_map_to_fullscreen();
	}
}

#ifdef SCREENSHOT
void shotFlush(void)
{
	static int curShotNumber;

	XBuffer out_buf;

	while(true) {
		XBuffer buf;
		buf < "Vangers";
		if(curShotNumber < 1000)
			buf < "0";
		if(curShotNumber < 100)
			buf < "0";
		if(curShotNumber < 10)
			buf < "0";
		buf <= curShotNumber;

		buf < ".bmp";
		std::fstream filestr(buf.GetBuf(), std::ios::in);
		if (!filestr.is_open()) {
			out_buf < buf.GetBuf();
			break;
		}
		filestr.close();
		curShotNumber++;
	}
	std::cout<<"ScreenShot name:"<<out_buf.GetBuf()<<std::endl;
	SDL_Surface* screenshotSurface = XGR_Obj.get_screenshot();
	SDL_SaveBMP(screenshotSurface, out_buf.GetBuf());
	SDL_FreeSurface(screenshotSurface);
}
#endif

#ifdef MEMORY_STATISTICS
//const MEMPTR_MAX = 1 << 15;
const int MEMPTR_MAX = 1 << 23;
void* memPtr[MEMPTR_MAX];
int memSize[MEMPTR_MAX];
int memId[MEMPTR_MAX];
int memNcnt,memDcnt;

void* operator new(unsigned int sz)
{
	if(!sz) return NULL;
	void* p = malloc(sz);
	if(memStart){
		memPtr[memIndex] = p;
		memSize[memIndex] = sz;
		memId[memIndex] = memNcnt;
		if(++memIndex == MEMPTR_MAX) ErrH.Abort("memStat: overflow");
		memQ += sz;
//		fmem < "new:\t\t" <= sz < "\t\ttotal:\t\t" <= memQ < "\t\t" <= memNcnt < "\r\n";
		memNcnt++;
		}
	return p;
}

void operator delete(void* p)
{
	int i;
	if(memStart){
		for(i = 0;i < memIndex;i++)
			if(memPtr[i] == p){
				memQ -= memSize[i];
				break;
				}
		if(i < memIndex){
//			fmem < "delete:\t\t" <= memSize[i] < "\t\ttotal:\t\t" <= memQ < "\t\t" <= memDcnt < "\r\n";
			memDcnt++;
			memPtr[i] = NULL;
			memSize[i] = 0;
			}
		}
	free(p);
}

void memstatInit(void)
{
//	static int log = 1;
//	if(log){ log--; return; }
	memset(memPtr,0,MEMPTR_MAX*sizeof(void*));
	memset(memSize,0,MEMPTR_MAX*sizeof(int));
	memIndex = 0;
	memStart = 1;
	memNcnt = memDcnt = 0;
}

void memstatDumpLeak(void)
{
	if(!memStart) return;
	for(int i = 0;i < memIndex;i++)
		if(memPtr[i]){
			fmem < "leak:\t\t" <= memId[i] < "\t\tsize: " <= memSize[i] < "\r\n";
			}
	memStart = 0;
}
#endif

void LoadingMessage(int flush)
{
	if(flush)
	{
		char col255[3] = { 60,40,0 };
		XGR_SetPal(col255,255,1);

		char col0[3] = { 0,0,0 };
		XGR_SetPal(col0,0,1);

		XGR_Fill(0);
	}

	char* str = getRC();
	sysfont.draw(8,XGR_MAXY - 35,(unsigned char*)str,255,-1);
	XBuffer buf;
	if (lang() == RUSSIAN) {
        buf < Convert(zSTR_LOADING_800_RU);
	} else if (lang() == GERMAN) {
        buf < "(C)1997-2014. Alle Rechte vorbehalten. Release Version 1.3. Gleich geht's weiter...";
	} else {
        buf < "(C)1997-2014 All Rights Reserved. Release Version 1.3 Loading. Please wait...";
	}
	int len = MAX(strlen(str),strlen(buf.GetBuf()));
	sysfont.draw(8,XGR_MAXY - 20,(unsigned char*)(buf.GetBuf()),255,-1);
	XGR_LineTo(8,XGR_MAXY - 45,len*8 + 5 + 16,2,255);
	XGR_LineTo(8 + len*8 + 11,XGR_MAXY - 45 - 7,2*7,3,255);
}

void theEND(void)
{
	EffectsOff();
	//if(XGR_MAXX != 800)
	//	if(XGR_ReInit(800,600,emode)) ErrH.Abort(ErrorVideoMss);
#ifdef ISCREEN
//	if(Dead) ShowImage("resource\\iscreen\\bitmap\\corpse.bmp");
//	ShowImage("resource\\iscreen\\bitmap\\email.bmp");
#endif
}

void rtoSetNextID(int id,int next)
{
	BaseRTO* p = (BaseRTO*)xtGetRuntimeObject(id);
	if(p) p -> SetNext(next);
}

void rtoSetFlag(int id,int fl)
{
	BaseRTO* p = (BaseRTO*)xtGetRuntimeObject(id);
	if(p) p -> SetFlag(fl);
}

void rtoClearFlag(int id,int fl)
{
	BaseRTO* p = (BaseRTO*)xtGetRuntimeObject(id);
	if(p) p -> ClearFlag(fl);
}

ShowImageRTO::ShowImageRTO(void)
{
	int i;
	ID = RTO_SHOW_IMAGE_ID;
	Timer = RTO_IMAGE_TIMER;
	numFiles = 0;

	imageData = NULL;

	Flags = new int[RTO_SHOW_IMAGE_MAX];
	memset(Flags,0,sizeof(int) * RTO_SHOW_IMAGE_MAX);

	fileNames = new char*[RTO_SHOW_IMAGE_MAX];
	for(i = 0; i < RTO_SHOW_IMAGE_MAX; i ++)
		fileNames[i] = new char[256];
}

ShowAviRTO::ShowAviRTO(void)
{
	int i;
	ID = RTO_SHOW_AVI_ID;
	Timer = RTO_IMAGE_TIMER;
}

char* getRC(void)
{
#ifdef _DEMO_
	return "VANGERS Cover Demo (c)1997-98 All Rights Reserved";
#else
#ifdef BETA_TESTING
	static char* str = getOwner();
	if(!str) ErrH.Abort("Software is NOT properly registered. Please, buf to developers!");
	return str;
#else
    static XBuffer b(128);
    b.init();
    const char* sub[6] = { "The Vandals and the Heroes of the Bouillon of Spawn...",
                           "The Fitters of the Emmet Cults...",
                           "The Mechanix of Own Fate...",
                           "The Hearse-Riders of the Cursed Crossroads...",
                           "Exodus to Otherworld...",
                           "One for the Road..."
    };
    if (lang() == RUSSIAN) {
        b < ConvertUTF8("Vangers: ");
        b < ConvertUTF8(sub[realRND(5)]);
    } else {
        b < "VANGERS: ";
        b < sub[realRND(6)];
    }
    return b.GetBuf();
#endif
#endif
}

void GameTimerON_OFF(void)
{
	GameQuantRTO* p = (GameQuantRTO*)xtGetRuntimeObject(RTO_GAME_QUANT_ID);
	if(!p) return;
	if(!p -> Timer) p -> SetTimer(RTO_GAME_QUANT_TIMER);
	else p -> SetTimer(0);
}

void ShowImageMousePress(int fl, int x, int y)
{
	ShowImageMouseFlag = 1;
}

void ShowImageKeyPress(SDL_Event *k)
{
	ShowImageKeyFlag = 1;
}


bool SetAchievement(std::string name) {
	std::cout<<"Set achievement:"<<name<<std::endl;
	return true;
}
