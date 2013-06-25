#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "hash_functions.h"
#include "memory.h"

size_t hash_map_default_hash_func(const void *key, size_t capacity, int len) {
	return *((size_t *) key) % capacity;
}

size_t xPear16(const void *x_copy, size_t capacity, int len) {
	int h, i, j;
	unsigned char ch;
	size_t hex;

	// to store h values
	struct {
		int a;
	} hh[8];

	// 256 values 0-255 in any (random) order suffices
	struct DAT {
		int a;
	}

	T[256] = {
		98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219, //  1
		61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115, //  2
		90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10, //  3
		237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121, //  4
		123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55, //  5
		59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222, //  6
		197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186, //  7
		39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99, //  8
		154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254, //  9
		133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139, // 10
		189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44, // 11
		183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12, // 12
		221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166, // 13
		3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117, // 14
		238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110, // 15
		43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239  // 16
	};

	char *x = safe_malloc(len);
	memcpy(x, x_copy, len);

	int r;
	ch = x[0]; // save first byte
	for(j = 0 ; j < 8; j++) {
		// standard Pearson hash (output is h)
		h=0;

		for(i = 0; i < len; i++) {
			r = abs(h ^ x[i]);
			h=T[r].a;
		}

		hh[j].a=h;	// store result
		x[0]=x[0]+1;	// increment first data byte by 1
	}

	x[0]=ch; // restore first byte

	safe_free(x);

	// concatenate the 8 stored values of h
	/*sprintf(hex,"%02X%02X%02X%02X%02X%02X%02X%02X",
	        hh[0].a, hh[1].a,
	        hh[2].a, hh[3].a,
	        hh[4].a, hh[5].a,
	        hh[6].a, hh[7].a);*/

	// For now let me do it this way, but Liu doesn't think this is a good thing
	for(int i = 0; i < 8; i++) {
		hex = hex << 8;
		hex = hex & hh[i].a;
	}

	return hex; // output 64-bit 16 hex bytes hash
}
