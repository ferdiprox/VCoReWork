#pragma once 

#include <cmath>

// Undef names that will be used in custom variables in the future

#ifdef Pi
#undef Pi
#endif 

#ifdef M_PI
#undef M_PI
#endif

#ifdef PI
#undef PI
#endif

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

static constexpr double M_PI = 3.14159265358979323846;

inline double max(double x,double y){ return x > y ? x : y; }
inline double min(double x,double y){ return x < y ? x : y; }

inline int max(int x,int y){ return x > y ? x : y; }
inline int min(int x,int y){ return x < y ? x : y; }

inline int max(int x,int y,int z){ return max(max(x,y),z); }
inline int min(int x,int y,int z){ return min(min(x,y),z); }

inline int maxa(int x,int y){ return abs(x) > abs(y) ? x : y; }
inline int maxa(int x,int y,int z){ return maxa(maxa(x,y),z); }

inline int mina(int x,int y){ return abs(x) < abs(y) ? x : y; }
inline int mina(int x,int y,int z){ return mina(mina(x,y),z); }


inline double fmax(double x,double y){ return x > y ? x : y; }
inline double fmax(double x,double y,double z){ return fmax(fmax(x,y),z); }

inline double fmaxa(double x,double y){ return fabs(x) > fabs(y) ? x : y; }
inline double fmaxa(double x,double y,double z){ return fmaxa(fmaxa(x,y),z); }

inline double fmin(double x,double y){ return x < y ? x : y; }
inline double fmin(double x,double y,double z){ return fmin(fmin(x,y),z); }

inline double fmina(double x,double y){ return fabs(x) < fabs(y) ? x : y; }
inline double fmina(double x,double y,double z){ return fmina(fmina(x,y),z); }


inline int round_sin(int x){ return x >= 0 ? (x + (1 << 14)) >> 15 : -((-x + (1 << 14)) >> 15); }

inline void xorSwap(int& a, int& b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

template <class T> 
inline T sqr(const T& x){ return x*x; }

template <class T> 
inline int SIGN(const T& x) { return x ? (x > 0 ? 1 : -1 ) : 0; }

inline bool isPowerOf2(int x)
{
	return (x) && !(x & (x - 1));
}

// TODO(amdmi3): very inefficient; rewrite
inline int bitSR(int x) {
	unsigned int a = abs(x);
	for (int i = 31; i > 0; i--)
		if (a & (1 << i))
			return i;

	return 0;
}
