#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "open62541.h"
#include "open62541.c"
#define time_per_test 30
#define progress_resolution 500

struct timespec ts,ts2;
uint64_t get_milliseconds(){

clock_gettime(CLOCK_MONOTONIC_RAW,&ts);
return ts.tv_sec*1000000+ts.tv_nsec/1000;
	}
