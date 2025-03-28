#include "zmod_client.h"


#include <time.h>
#include <SDL.h>

int z_time = 0;
int z_time_tic = 0;
int z_time_cnt = 0;
int z_time_all = 0;
int z_time_avg = 0;

void z_time_init() {
	z_time_tic = SDL_GetTicks();
}

void z_time_collect() {
	z_time = SDL_GetTicks() - z_time_tic;
	z_time_all += z_time;
	z_time_cnt++;
	z_time_avg = z_time_all / z_time_cnt;
}

