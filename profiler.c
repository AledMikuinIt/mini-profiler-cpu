#include "profiler.h"

// Début de la mesure avec lfence & rdtsc

uint64_t start_tsc() {
    unsigned lo, hi;
    __asm__ volatile (
        "lfence\n\t"    // stop charger/exec spéculative via lfence
        "rdtsc\n\t"     // lit ke tsc 
        : "=a"(lo), "=d"(hi)
        :
        : "memory"
    );

    return ((uint64_t)hi << 32) | lo;

}

// Fin de la mesure aved rdtsc & lfence

uint64_t stop_tsc() {
    unsigned lo, hi;
    __asm__ volatile (
        "rdtscp\n\t"    // lit le TSC sérialisé
        "lfence\n\t"    // lfence pour empecher de re ordonnement
        : "=a"(lo), "=d"(hi)
        : 
        : "rcx", "memory"
    );

    return ((uint64_t)hi << 32) | lo;

}

// Mesurer une exec d'une fonction fn

uint64_t measure_once(becnh_fn fn) {
    uint64_t begin = start_tsc();
    fn();       // ce qu'on mesure
    uint64_t end = stop_tsc();
    return end - begin;
}