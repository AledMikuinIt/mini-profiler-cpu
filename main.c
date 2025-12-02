// main.c
#include <stdio.h>
#include "profiler.h"

void test_fn() {
    for (volatile int i = 0; i < 1000; i++);
}

int main() {
    uint64_t cycles = measure_once(test_fn);
    printf("Mesure : %llu cycles\n", (unsigned long long)cycles);
}
