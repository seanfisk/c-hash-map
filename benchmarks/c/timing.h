#ifndef TIMING_H
#define TIMING_H

#include <stdint.h>

uint64_t monotonic_nanosecond_time();
void start_timing();
void print_timing(char *title);

#endif
