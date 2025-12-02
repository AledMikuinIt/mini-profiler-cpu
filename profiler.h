#ifndef PROFILER_H
#define PROFILER_H

#include <stdint.h>

typedef void (*becnh_fn)(void) ;

uint64_t start_tsc();
uint64_t stop_tsc();
uint64_t measure_once(becnh_fn fn);

#endif