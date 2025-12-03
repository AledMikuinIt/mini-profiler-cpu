#include "profiler.h"
#include <stdint.h>
#include <stdlib.h>   // for qsort

// Start the TSC measurement w/ lfence & rdtsc & ASM

uint64_t start_tsc() {
    unsigned lo, hi;
    __asm__ volatile (
        "lfence\n\t"    // stop the speculative with lfence
        "rdtsc\n\t"     // read the TSC
        : "=a"(lo), "=d"(hi)    // a takes the 32 low bits from EAX and d takes the 32 high bits from EDX
        :
        : "memory"          // Clobber that says that its memory
    );

    return ((uint64_t)hi << 32) | lo;   // return the 64 bits uint , shift 32 bits on the left for the hi and then OR the low bitss

}

// End the TSC measurement w/ rdtscp & lfence & ASM

uint64_t stop_tsc() {
    unsigned lo, hi;
    __asm__ volatile (
        "rdtscp\n\t"    // read the TSC serialized
        "lfence\n\t"    // lfence to stop the re arrangement
        : "=a"(lo), "=d"(hi)    // a takes 32 bits low etc
        : 
        : "rcx", "memory"   // Clobber that says that memory goes in the rcx so do not modify (to the compiler)
    );

    return ((uint64_t)hi << 32) | lo;   // return a 64 unit bits with the 32 high | 32 low 

}

// Measure the function time once

uint64_t measure_once(bench_fn fn) {
    uint64_t begin = start_tsc();
    fn();       // measure the function
    uint64_t end = stop_tsc();
    return end - begin;
}


// Compare function for uint64 for qsort
int cmp_uint64(const void *a, const void *b) {
    uint64_t ua = *(const uint64_t*)a;  // cast to a const ptr for test all As
    uint64_t ub = *(const uint64_t*)b;  // cast to a const ptr for test all Bs
    if (ua < ub) return -1; // a is less than b
    if (ua > ub) return 1;  // a is more than b
    return 0;
}


// Measure the function N times w/ warmup

uint64_t measure_n(bench_fn fn, int n) {

    uint64_t med[n];    // alloc a n sized median array

    fn();               // warmup the function for the CPU cache, volatile in fn so it doesnt be rearranged
    for(int i = 0; i<n; i++) {  // test N numbers of times
        med[i] = measure_once(fn);
    }
    qsort(med, n, sizeof(uint64_t), cmp_uint64);    // sort the results to get the median

    return med[n/2];    // return the median
}