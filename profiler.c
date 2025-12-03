#include "profiler.h"

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
        : "rcx", "memory"   // Clobber that says that memory goes in the rcx so do not modify (to the compilator)
    );

    return ((uint64_t)hi << 32) | lo;   // return a 64 unit bits with the 32 high | 32 low 

}

// Measure the function time

uint64_t measure_once(becnh_fn fn) {
    uint64_t begin = start_tsc();
    fn();       // measure the function
    uint64_t end = stop_tsc();
    return end - begin;
}