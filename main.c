// main.c
#include <stdint.h>
#include <stdio.h>
#include "profiler.h"

void test_fn() {
    for (volatile int i = 0; i < 1000; i++);    // volatile here to sya to the compilator to not rearange & execute in this order
}

int main() {
    uint64_t cycles = measure_once(test_fn);
    uint64_t cycles_n = measure_n(test_fn, 20);
    printf("Measure Once: %llu cycles\nMeasure N: %llu\n", (unsigned long long)cycles, (unsigned long long)cycles_n);
}
