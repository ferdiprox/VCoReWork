#pragma once 

#include <random>

#undef random
#define random(num) RND(num)

#define RNDSIGN  ((!RND(2)) ? -1 : 1)

extern unsigned int RNDVAL;
inline unsigned int RND(unsigned int m)
{
    if(!m) return 0;

	RNDVAL ^= RNDVAL >> 3;
	RNDVAL ^= RNDVAL << 28;
	RNDVAL &= 0x7FFFFFFF;

	return RNDVAL%m;
}

inline unsigned int realRND(unsigned int m) {
	if (!m) {
		return 0;
	}
	return rand()%m;
}
