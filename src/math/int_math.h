#pragma once

#include "base_math.h"

static constexpr int Pi_len = 11;
static constexpr int Pi = 1 << Pi_len;
static constexpr int PiX2 = Pi * 2;
static constexpr int ANGLE_CLAMP_MASK = PiX2 - 1; // Used to erase (set up to zero) bits out of int-angle range.

static constexpr int ArcCosLen = 12;
static constexpr int ArcCosMAX = 1 << ArcCosLen;
static constexpr int ArcTanLen = 12;
static constexpr int ArcTanMAX = 1 << ArcTanLen;
static constexpr int SqrtLen = 12;
static constexpr int SqrtMax = 1 << SqrtLen;

static constexpr double CNV_IPI_2_MPI = M_PI / double(Pi);
static constexpr double CNV_MPI_2_IPI = double(Pi) / M_PI;

static constexpr int N_POWER_MAX = 16;

// TODOf: look for usage of this constant
static constexpr int UNIT = 0x10000;	//32768;

static constexpr double DBL_EPS =  1e-15;

#ifdef TRACK_INT_INF_USAGE
// Ferdi: This is probably could be core of the all -inf bugs, so i created this define to track it.
#define INT_INF INT_INF_implementation()
inline int INT_INF_implementation()
{
	std::cout << "!!! Int infinity was used somewhere...\n";
	return 0x7FFFFFFF;
}
#else
static constexpr int INT_INF = 0x7FFFFFFF;
#endif

#define GOOD_SHR(x,n)	((x) < 0 ? -((-(x) + (1 << ((n) - 1))) >> (n)) : (((x) + (1 << ((n) - 1))) >> (n)))
#define DIV16(a,b)	  (a = ((a) << 16)/(b))
#define DIV16T(x,y)	((int)div_table_short[((x) & 0xFF) | (((y) << 8) & 0xFF00)] << 8)
#define MUL_CHAR(x,y)	     (mul_table[((x) & 0xFF) | (((y) << 8) & 0xFF00)])

extern int* IntSinIntTable;
extern int* IntCosIntTable;

#ifdef _STATIC_TABLES_
extern float FloatCosIntTable[PiX2];
extern char mul_table[256*256];
extern short div_table_short[256*256];
extern char power_table[256*(N_POWER_MAX - 1)];
#else
extern float* FloatCosIntTable;
extern char* mul_table;
extern short* div_table_short;
extern char* power_table;
#endif

// Distance between two angles for integer (Pi) and real (Pi) angles respectively
int DistPi(int s0,int s1);
double DistPIreal(double s0,double s1);

void make_tables();
void write_tables();

// Real Pi's Cos and Sin from integer angle.
inline float fSin(int angle)
{
    return FloatCosIntTable[(angle - Pi/2) & ANGLE_CLAMP_MASK];
}

inline float fCos(int angle)
{
    return FloatCosIntTable[angle & ANGLE_CLAMP_MASK];
}

int ArcCos(int Dx,int Abs);
int Atan2(int Dy,int Dx);
int Sqrt(int x);

// returns (x*y >> 7), where x - [-127,127], y - [-127,127]
#define MUL(x,y)	((int)mul_table[(x & 0xFF) | ((y << 8) & 0xFF00)])

//// returns ((y << 7)/x), where x - [-127..127], y - [0..256]
#define DIV_by_table(y,x)	 ((int)div_table[(x & 0xFF) | ((y << 8) & 0xFF00)])

// returns (x^n >> 7*(n - 1)), where x - [-127,127], n - [2,N_POWER_MAX]
#define POW(x,n)	((int)power_table[((n) - 2 << 8) + (x)])

/*
		About ANGLES.
      Angles are integers, where Pi is multiple 2. Therefore only (Pi_len + 1)
low digits are significant and You can use ANGLE_CLAMP_MASK to extract them. Moreover,
it is supported that  Matrix(angle,any_axis)*Matrix(-angle,any_axis) = I.
Make sure using Pi (integer constant) and M_PI (3.1416...). Apply intAng2Real and realAng2Int
for converting.
*/

inline double intAng2Real(int intAngle) 
{
    return double(intAngle)*CNV_IPI_2_MPI;
}

inline int realAng2Int(double radians) 
{
    return double(radians)*CNV_MPI_2_IPI;
}

// Integer Pi's Cos and Sin from integer angle.
inline int iCos(int x) 
{
    return IntCosIntTable[x & ANGLE_CLAMP_MASK]; 
}
inline int iSin(int x) 
{
    return IntSinIntTable[x & ANGLE_CLAMP_MASK]; 
}