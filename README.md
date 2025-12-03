# Mini CPU Profiler

# Disclaimer

This project is still a work in progress. Please check the work branch for ongoing development.

## Project Overview

This project is a low-level CPU profiler written in C. The goal is to measure the execution time of functions in terms of CPU cycles using the `RDTSC` and `RDTSCP` instructions. This allows precise measurement of small code sections, taking into account CPU out-of-order execution and speculative execution.

The project is still in progress and currently focuses on providing a basic mechanism to measure the number of CPU cycles taken by a function.

## Current Features

- `start_tsc()`: Begin timing using `lfence` and `rdtsc` to ensure instruction serialization.  
- `stop_tsc()`: End timing using `rdtscp` and `lfence` to read a serialized timestamp counter.  
- `measure_once(fn)`: Measure the number of CPU cycles required to execute a single call to a function `fn`.  
- `measure_n(fn, n)`: Measure a function `fn` multiple times (`n` iterations) and return the **median** CPU cycles, mitigating the effect of outliers caused by interrupts or system events.  

## Motivation / Why This Matters

Modern CPUs are highly optimized and execute instructions **out-of-order**. Measuring execution time with standard timers often fails to capture **true instruction-level latency**.  

This profiler enables:

- Understanding **latency and throughput** at a micro-architectural level.  
- Observing the impact of **cache misses, TLB misses, and branch mispredictions**.  
- Developing micro-benchmarks that highlight CPU behavior beyond high-level timing functions.  


## Future Work
- mode to warmpup
- another benchmarks like pointer chasing, latency chain, branch mispredict
- generate CSV file for graphs
