/**
 * @file
 * Implementation of different hash functions.
 */

#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

size_t hash_map_default_hash_func(const void *key, size_t capacity);

unsigned char xPear16(unsigned char *x);

#endif /*HASH_FUNCTIONS_H*/
