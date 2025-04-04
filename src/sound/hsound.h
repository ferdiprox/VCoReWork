#ifndef __HSOUND_H
#define __HSOUND_H

#include "../../lib/xsound/_xsound.h"

#include "../random.h"

#ifdef _DEBUG
//#define _NO_CDAUDIO_
#endif

enum EFFECT_VALUE {
	EFF_START,
	EFF_DRIVING,
	EFF_STOP,
	EFF_UNDERWATER,
	EFF_COPTERIG,
	EFF_CUTTERIG,
	EFF_CROTRIG,
	EFF_MECHOS_EXPLOSION,
	EFF_BACK_EXPLOSION,
	EFF_CRUSTER_EXPLOSION,
	EFF_MECHOS_COLLISION,
	EFF_SHOT_0,
	EFF_SHOT_1,
	EFF_SHOT_2,
	EFF_SHOT_3,
	EFF_SHOT_4,
	EFF_SHOT_5,
	EFF_SHOT_6,
	EFF_SELECT_0,
	EFF_SELECT_1,
	EFF_SELECT_2,
	EFF_BACKGROUND_0,
	EFF_BACKGROUND_1,
	EFF_BACKGROUND_2,
	EFF_BACKGROUND_3,
	EFF_BACKGROUND_4,
	EFF_BACKGROUND_5,
	EFF_DOOR,
	EFF_PASSAGE,
	EFF_PICK,
	EFF_DROP,
	EFF_CRACK,
	EFF_GLOBAL,
	EFF_BARREL,
	EFF_TAKE_ITEM,
	EFF_HIT,
	EFF_KIDPULL,
	EFF_KIDPUSH,
	EFF_CHARGE_GHORB,
	EFF_CHARGE_MACHOTIN,
	EFF_CHARGE_REPARE,
	EFF_CHARGE_ENERGE,
	EFF_CHARGE_SPIRAL,
	EFF_CHARGE_RIGS,
	EFF_CRASH,
	EFF_HORDE,
	
	EFF_CYCLE,
	EFF_FAILEDPASS,
	EFF_SHOCK0,
	EFF_SHOCK1,
	EFF_SHOCK2,
	EFF_SHOCK3,
	EFF_SHOCK4,
	EFF_SHOCK5,
	EFF_SUCCESS,
	EFF_FAILED,

	EFF_THUNDER,
	EFF_TOGGLE,
	EFF_BOLT,
	EFF_ACID,
	EFF_CHECKPOINT,
	EFF_SWAMP,
	EFF_TEAR,
	EFF_HIDEOUT,
	EFF_GROW,

	EFF_NOISE,
	EFF_TALK0,
	EFF_TALK01,
	EFF_TALK02,
	EFF_TALK1,
	EFF_TALK11,
	EFF_TALK12,
	EFF_TALK2,
	EFF_TALK21,
	EFF_TALK22,
	EFF_WINDOW,

	EFF_OUTIN,
	EFF_SWARM,
	EFF_ANGRY,
	EFF_GETOUT,
	EFF_GATE,
	EFF_STEP0,
	EFF_STEP1,
	EFF_STEP2,
	EFF_HAND,
	EFF_SCRATCH0,
	EFF_SCRATCH1,
	EFF_CLAP,

	EFF_MECH_MESSIAN,
	EFF_PROCTRACTOR,
	EFF_BOOTSECTOR,
	EFF_END_LARVA,
	EFF_END_CYCLE_LARVA,
	EFF_UNICUM_MECHOS_1,
	EFF_UNICUM_MECHOS_2,
	EFF_DESTROY_TERRAIN,
	EFF_DISCHARGE,

	EFF_PROTRACTOR_FUNCTION,
	EFF_PROTRACTOR_RESIZE,
	EFF_PROTRACTOR_BARRIER,
	EFF_MESSIAN_CLOAK,
//	EFF_MESSIAN_LUCK,
	EFF_MESSIAN_BEEBSOSPY,
	EFF_MESSIAN_FIRE,

	EFF_SPOPS_ALIES,
	EFF_BEEP,
	EFF_DAMAGE,
	EFF_SHOT_RAFFA,
	
	EFF_MAX
	};

enum SPEECH_VALUE {
	SPEECH_MUFLER,

	SPEECH_MAX
	};

#define ST_INTRO	2
#define ST_FOSTRAL	3
#define ST_GLORX	4
#define ST_NECROSS	5
#define ST_XPLO		6
#define ST_SECRETS	7
#define ST_GAMEOVER	8
#define ST_THEEND	9
#define ST_THEEND_DOUBLE	10
#define ST_DOUBLE	11

void InstallSOUND(void);
void RestoreSOUND(void); 
void LoadResourceSOUND(const char*, int surface = 1);
void EffectsOnOff(void);
void EffectsOn(int surface = 1);
void EffectsOff(void);
void SetSoundVolume(int value);
void SoundQuant(void);
void SoundEscaveOff(void);
void SetMotorSound(int speed);
void SetMotorFile( int type );

void StartSPEECH(SPEECH_VALUE SpeechValue);
void StartEFFECT(EFFECT_VALUE EffectValue,int loop = 0, int pan = 0);
void StopEFFECT(EFFECT_VALUE EffectValue);

void StartCDTRACK(void);
void PauseCDTRACK(void);
void ResumeCDTRACK(void);
void StopCDTRACK(void);
void StartWTRACK(void);
void SlowCDTRACK(void);
void MainMenuSoundQuant(int TRACK = ST_INTRO);

void LocalEffectFree(void);

extern int sndBackgroundMax,sndStepMax,sndScratchMax;
extern int SoundFlag;
extern int EngineNoise,Backgroundound;

const int SoundCopterig = 0x00000001;
const int SoundCrotrig = 0x00000002;
const int SoundCutterig = 0x00000004;
const int SoundUnderWater = 0x00000008; 
const int SoundMotor = 0x00000010;

#define SOUND_START_MOTOR()	if(EngineNoise) StartEFFECT(EFF_DRIVING,1);
#define SOUND_STOP_MOTOR()	if(EngineNoise) StopEFFECT(EFF_DRIVING);
#define SOUND_MOTOR_PARAMETER(speed) if(EngineNoise) SetMotorSound(speed);
#define SOUND_OBJECT_TO_OBJECT_COLLISION()	StartEFFECT(EFF_MECHOS_COLLISION);

#define SOUND_UNDERWATER_START()	StartEFFECT(EFF_UNDERWATER,1);
#define SOUND_UNDERWATER_STOP()		StopEFFECT(EFF_UNDERWATER);

#define SOUND_COPTERIG_START()	StartEFFECT(EFF_COPTERIG,1);
#define SOUND_COPTERIG_STOP()	StopEFFECT(EFF_COPTERIG);

#define SOUND_CUTTERIG_START()	StartEFFECT(EFF_CUTTERIG,1);
#define SOUND_CUTTERIG_STOP()	StopEFFECT(EFF_CUTTERIG);

#define SOUND_CROTRIG_START()	StartEFFECT(EFF_CROTRIG,1);
#define SOUND_CROTRIG_STOP()	StopEFFECT(EFF_CROTRIG);

#define SOUND_ENTRANCE(p)	StartEFFECT(EFF_DOOR, 0, p);
#define SOUND_PASSAGE(p) 	StartEFFECT(EFF_PASSAGE, 0, p);
#define SOUND_PASSAGE_START(p) 	StartEFFECT(EFF_PASSAGE, 1, p);
#define SOUND_PASSAGE_STOP(p) 	StopEFFECT(EFF_PASSAGE);

#define SOUND_BEEB_DEATH(p)	StartEFFECT(EFF_CRACK, 0, p);

#define SOUND_MACHOTINE_SHOT(p)		StartEFFECT(EFF_SHOT_0, 0, p);
#define SOUND_SPEETLE_SHOT(p)		StartEFFECT(EFF_SHOT_2, 0, p);
#define SOUND_GHORB_SHOT(p)		StartEFFECT(EFF_SHOT_3, 0, p);
#define SOUND_GHORB_BIG_SHOT(p)		StartEFFECT(EFF_SHOT_4, 0, p);
#define SOUND_BEEBBANOZA_SHOT(p) 	StartEFFECT(EFF_SHOT_6, 0, p);
#define SOUND_CRUSTEST_SHOT(p)		StartEFFECT(EFF_SHOT_5, 0, p);
#define SOUND_TERMINATOR_SHOT(p) 	StartEFFECT(EFF_SHOT_1, 0, p);
#define SOUND_AMPUTATOR_SHOT(p) 	StartEFFECT(EFF_SHOT_1, 0, p);
#define SOUND_DEGRADATOR_SHOT(p) 	StartEFFECT(EFF_SHOT_1, 0, p);
#define SOUND_INCARNATOR_SHOT(p) 	StartEFFECT(EFF_SHOT_1, 0, p);
#define SOUND_RAFFA_SHOT(p) 	StartEFFECT(EFF_SHOT_RAFFA, 0, p);

#define SOUND_GLOBAL()				StartEFFECT((EFFECT_VALUE)((int)EFF_BACKGROUND_0 + realRND(sndBackgroundMax)));

#define SOUND_BARREL_DESTROY(p)		StartEFFECT(EFF_BARREL, 0, p);

#define SOUND_TAKE_ITEM(p)		StartEFFECT(EFF_TAKE_ITEM, 0, p);
#define SOUND_HIT(p)				StartEFFECT(EFF_HIT, 0, p);

#define SOUND_EXPLOSION(p)	      {	StartEFFECT(EFF_MECHOS_EXPLOSION, 0, p); StartEFFECT(EFF_BACK_EXPLOSION, 0, p);}
#define SOUND_EXPLOSION_CRUSTER(p)	{StartEFFECT(EFF_CRUSTER_EXPLOSION, 0, p);StartEFFECT(EFF_BACK_EXPLOSION, 0, p);}


#define SOUND_KIDPULL()				StartEFFECT(EFF_KIDPULL);
#define SOUND_KIDPUSH()				StartEFFECT(EFF_KIDPUSH);

#define SOUND_SELECT()				StartEFFECT((EFFECT_VALUE)((int)EFF_SELECT_0 + realRND(3)));
#define SOUND_PICK()				StartEFFECT(EFF_PICK);
#define SOUND_DROP()				StartEFFECT(EFF_DROP);

#define SOUND_CHARGE()			StartEFFECT(EFF_CHARGE_GHORB);
#define SOUND_CHARGE_GHORB()			StartEFFECT(EFF_CHARGE_GHORB);
#define SOUND_CHARGE_MACHOTIN()			StartEFFECT(EFF_CHARGE_MACHOTIN);
#define SOUND_CHARGE_REPARE()			StartEFFECT(EFF_CHARGE_REPARE);
#define SOUND_CHARGE_ENERGE()			StartEFFECT(EFF_CHARGE_ENERGE);
#define SOUND_CHARGE_SPIRAL()			StartEFFECT(EFF_CHARGE_SPIRAL);
#define SOUND_CHARGE_RIGS()			StartEFFECT(EFF_CHARGE_RIGS);

#define SOUND_CRASH()			StartEFFECT(EFF_CRASH);
#define SOUND_HORDE(p)			StartEFFECT(EFF_HORDE, 0, p);

#define SOUND_CYCLE()			StartEFFECT(EFF_CYCLE);
#define SOUND_FAILEDPASS()	StartEFFECT(EFF_FAILEDPASS);
#define SOUND_SHOCK()			StartEFFECT((EFFECT_VALUE)((int)EFF_SHOCK0 + realRND(6)));
#define SOUND_SUCCESS()			StartEFFECT(EFF_SUCCESS);
#define SOUND_FAILED()			StartEFFECT(EFF_FAILED);

#define SOUND_THUNDER(p)			StartEFFECT(EFF_THUNDER, 0, p);
#define SOUND_TOGGLE()			StartEFFECT(EFF_TOGGLE);
#define SOUND_BOLT()			StartEFFECT(EFF_BOLT);
#define SOUND_ACID()			StartEFFECT(EFF_ACID);
#define SOUND_CHECKPOINT()	StartEFFECT(EFF_CHECKPOINT);
#define SOUND_SWAMP(p)			{ StartEFFECT(EFF_SWAMP, 0, p); }
#define SOUND_TEAR(p)			{ StartEFFECT(EFF_TEAR, 0, p); }
#define SOUND_HIDEOUT(p)			StartEFFECT(EFF_HIDEOUT, 0, p);
#define SOUND_GROW(p)			StartEFFECT(EFF_GROW, 0, p);

#define SOUND_NOISE()			StartEFFECT(EFF_NOISE);
#define SOUND_TALK0()			StartEFFECT((EFFECT_VALUE)((int)EFF_TALK0 + realRND(3)));
#define SOUND_TALK1()			StartEFFECT((EFFECT_VALUE)((int)EFF_TALK1 + realRND(3)));
#define SOUND_TALK2()			StartEFFECT((EFFECT_VALUE)((int)EFF_TALK2 + realRND(3)));
#define SOUND_WINDOW()			StartEFFECT(EFF_WINDOW);

#define	SOUND_OUTIN()			StartEFFECT(EFF_OUTIN);
#define	SOUND_SWARM()			StartEFFECT(EFF_SWARM);
#define	SOUND_ANGRY()			StartEFFECT(EFF_ANGRY);
#define	SOUND_GETOUT()			StartEFFECT(EFF_GETOUT);
#define	SOUND_GATE()			StartEFFECT(EFF_GATE);
#define	SOUND_STEP()			StartEFFECT((EFFECT_VALUE)((int)EFF_STEP0 + realRND(sndStepMax)));
#define	SOUND_HAND()			StartEFFECT(EFF_HAND);
#define	SOUND_PUT()			StartEFFECT(EFF_PUT);
#define	SOUND_SCRATCH()			StartEFFECT((EFFECT_VALUE)((int)EFF_SCRATCH0 + realRND(sndScratchMax)));
#define	SOUND_CLAP()			StartEFFECT(EFF_CLAP);

#define	SOUND_BUTTON0()			StartEFFECT(EFF_BUTTON0);
#define	SOUND_BUTTON1()			StartEFFECT(EFF_BUTTON1);
#define	SOUND_BUTTON2()			StartEFFECT(EFF_BUTTON2);
#define	SOUND_BUTTON3()			StartEFFECT(EFF_BUTTON3);
#define	SOUND_BUTTON4()			StartEFFECT(EFF_BUTTON4);
#define	SOUND_MUSIC()			StartEFFECT(EFF_MUSIC);

#define	SOUND_MESSIAH()			StartEFFECT(EFF_MECH_MESSIAN);
#define	SOUND_MESSIAH_START()			StartEFFECT(EFF_MECH_MESSIAN,1);
#define	SOUND_MESSIAH_STOP()			StopEFFECT(EFF_MECH_MESSIAN);
#define	SOUND_PROCTRACTOR()	StartEFFECT(EFF_PROCTRACTOR);
#define	SOUND_PROCTRACTOR_START()	StartEFFECT(EFF_PROCTRACTOR,1);
#define	SOUND_PROCTRACTOR_STOP()	StopEFFECT(EFF_PROCTRACTOR);
#define	SOUND_BOOT()			  StartEFFECT(EFF_BOOTSECTOR);
#define	SOUND_BOOT_START()			  StartEFFECT(EFF_BOOTSECTOR,1);
#define	SOUND_BOOT_STOP()			  StopEFFECT(EFF_BOOTSECTOR);
#define	SOUND_LARVA()	                StartEFFECT(EFF_END_LARVA);
#define	SOUND_END_LARVA()	  StartEFFECT(EFF_END_CYCLE_LARVA);
#define	SOUND_UNICUM_1()			StartEFFECT(EFF_UNICUM_MECHOS_1);
#define	SOUND_UNICUM_2() 			StartEFFECT(EFF_UNICUM_MECHOS_2);
#define	SOUND_DESTROY_TERRAIN()			StartEFFECT(EFF_DESTROY_TERRAIN);

#define	SOUND_PR_FUNCTION_START()			StartEFFECT(EFF_PROTRACTOR_FUNCTION,1);
#define	SOUND_PR_FUNCTION_STOP()			StopEFFECT(EFF_PROTRACTOR_FUNCTION);
#define	SOUND_PR_RESIZE()			StartEFFECT(EFF_PROTRACTOR_RESIZE);
#define	SOUND_PR_BARRIER()			StartEFFECT(EFF_PROTRACTOR_BARRIER);
#define	SOUND_MES_LUCK()			StartEFFECT(EFF_MESSIAN_LUCK);
#define	SOUND_MES_BEEBSOSPY()			StartEFFECT(EFF_MESSIAN_BEEBSOSPY);
#define	SOUND_MES_FIRE()			StartEFFECT(EFF_MESSIAN_FIRE);
#define	SOUND_MES_CLOAK()			StartEFFECT(EFF_MESSIAN_CLOAK);
#define	SOUND_DISCHARGE()			  StartEFFECT(EFF_DISCHARGE);
#define	SOUND_SPOPS_ALIES()			  StartEFFECT(EFF_SPOPS_ALIES);

#define	SOUND_BEEP()			  StartEFFECT(EFF_BEEP);
#define	SOUND_DAMAGE()			  StartEFFECT(EFF_DAMAGE);

void LastSoundQuant(void);
void LastStartWTRACK(int TRACK);

#endif