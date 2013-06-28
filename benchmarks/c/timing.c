#include "timing.h"

#include <mach/mach.h>
#include <mach/mach_time.h>

#include <stdio.h>

static uint64_t start_time;

/* Credit links:
 * <http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x>
 * <http://developer.apple.com/library/mac/#qa/qa1398/_index.html>
 * <http://lists.apple.com/archives/darwin-kernel/2012/Sep/msg00002.html>
 */
uint64_t monotonic_nanosecond_time() {
  static mach_timebase_info_data_t timebase;
	if (timebase.denom == 0) {
		mach_timebase_info(&timebase);
	}
	return mach_absolute_time() * (timebase.numer / timebase.denom);
}

void start_timing() {
	start_time = monotonic_nanosecond_time();
}

void print_timing(char *title) {
	uint64_t end_time = monotonic_nanosecond_time();
	uint64_t elapsed_nano = end_time - start_time;
	printf("%s: %llu ns\n", title, elapsed_nano);
}
