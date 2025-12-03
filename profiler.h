#ifndef PROFILER_H
#define PROFILER_H

#include <stdint.h>

typedef void (*bench_fn)(void) ;

uint64_t start_tsc();
uint64_t stop_tsc();
uint64_t measure_once(bench_fn fn);
uint64_t measure_n(bench_fn fn, int n);

#endif