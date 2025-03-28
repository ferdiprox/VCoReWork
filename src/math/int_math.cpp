#include "int_math.h"

#include <cstring>

int* IntSinIntTable;
int* IntCosIntTable;

/******************************************************************************
		Creating tables, Sqrt(), Atan2(), ArcCos()
******************************************************************************/
#ifndef _STATIC_TABLES_
short unsigned int* ArcCosTable;
short unsigned int* ArcTanTable;
short unsigned int* SqrtTable;

float* FloatCosIntTable;
char* mul_table;
short* div_table_short;
char* power_table;
#else
short unsigned int ArcCosTable[ArcCosMAX + 1];
short unsigned int ArcTanTable[ArcTanMAX + 1];
short unsigned int SqrtTable[SqrtMax];

float FloatCosIntTable[2*Pi];
char mul_table[256*256];
short div_table_short[256*256];
char power_table[256*(N_POWER_MAX - 1)];
#endif

int tables_are_made = 0;
void make_tables()
{
	int i;
	if(tables_are_made)
		return;
	tables_are_made = 1;

#ifndef _STATIC_TABLES_
	int size = 2*Pi*sizeof(float) + ((ArcCosMAX + 1) + (ArcTanMAX + 1) + SqrtMax)*sizeof(short int);

	FloatCosIntTable = new float[size]; 
	ArcCosTable = (short unsigned int*)(FloatCosIntTable + 2*Pi);
	ArcTanTable = ArcCosTable + ArcCosMAX + 1;
	SqrtTable = ArcTanTable + ArcTanMAX + 1;

	mul_table = new char[256*256]; 
	memset(mul_table, 0, 256*256);
	div_table_short = new short[256*256]; // TODO uninitialised value(s)
	power_table = new char [256*(N_POWER_MAX - 1)];
#endif

	for(i = 0;i < 2*Pi;i++)
		FloatCosIntTable[i] = (float)cos(intAng2Real(i));

	for(i = 0;i <= ArcCosMAX;i++)
		ArcCosTable[i] = (int)(double(Pi)*acos(((double)i)/ArcCosMAX)/M_PI);
	for(i = 0;i <= ArcTanMAX;i++)
		ArcTanTable[i] = (int)(double(Pi)*atan(((double)i)/ArcTanMAX)/M_PI);
	for(i = 0;i < SqrtMax;i++)
		SqrtTable[i] = (int)(sqrt((double)i) + .5);

	int x,y;
	for(x = -127;x <= 127;x++){
		for(y = -127;y <= 127;y++)
			mul_table[(x & 0xFF) | ((y << 8) & 0xFF00)] = GOOD_SHR(x*y,7);
		for(y = 0;y <= 255;y++){
			div_table_short[(x & 0xFF) | ((y << 8) & 0xFF00)] = y ? (x << 8)/y : 0;
			}
		}

	int n;
	for(n = 2;n <= N_POWER_MAX;n++){
		for(x = -127;x <= 127;x++){
			y = x;
			for(i = 1;i < n;i++)
				y = GOOD_SHR(y*x,7);
			power_table[((n - 2) << 8) + (x & 0xFF)] = y;
			}
		}
}
int ArcCos(int Dx,int Abs)
{
	if(!Abs)
		return 0;
	if(Dx >= 0){
		if(Dx >= Abs)
			return 0;
		return ArcCosTable[(((unsigned int )Dx) << ArcCosLen)/Abs];
		}
	else{
		if(-Dx >= Abs)
			return Pi;
		return Pi - ArcCosTable[(((unsigned int )-Dx) << ArcCosLen)/Abs];
		}
}
int Atan2(int Dy,int Dx)
{
	if(!Dx && !Dy)
		return 0;

	int Q = 0,S = 0;
	if(Dy >= 0){
		if(Dx < 0){
			Dx = -Dx;
			Q = Pi;
			S = 1;
			}
		}
	else
		if(Dx < 0){
			Dy = -Dy;
			Dx = -Dx;
			Q = Pi;
			}
		else{
			Dy = -Dy;
			Q = 2*Pi;
			S = 1;
			}

	unsigned int Ind;
	int Val;
	if(Dx >= Dy){
		Ind = Dy;
		Val = ArcTanTable[(Ind << ArcTanLen)/Dx];
		}
	else{
		Ind = Dx;
		Val = Pi/2 - ArcTanTable[(Ind << ArcTanLen)/Dy];
		}
	return Q + (S ? -Val : Val);
}

int Sqrt(int x)
{
	if(x < 0)
		x = 0;
	int len = bitSR(x);
	if(len >= SqrtLen){
		int shift = len - SqrtLen + 1;
		if(shift & 1)
			shift++;
		return SqrtTable[x >> shift] << (shift >> 1);
		}
	return SqrtTable[x];
}
int DistPi(int s0,int s1)
{
	s0 &= ANGLE_CLAMP_MASK;
	s1 &= ANGLE_CLAMP_MASK;
	int d0 = s0 - s1;
	int ad0 = abs(d0);
	int d1 = 2*Pi - ad0;
	if(ad0 < d1) return d0;
	return s0 > s1 ? -(2*Pi - s0 + s1) : 2*Pi - s1 + s0;
}
double DistPI(double s0,double s1)
{
	s0 = asin(sin(s0));
	s1 = asin(sin(s1));
	double d0 = s0 - s1;
	double ad0 = fabs(d0);
	double d1 = 2*M_PI - ad0;
	if(ad0 < d1) return d0;
	return s0 > s1 ? -(2*M_PI - s0 + s1) : 2*M_PI - s1 + s0;
}
