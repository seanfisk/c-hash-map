/**
 * @file
 * Implementation of different hash functions.
 */

#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

size_t hash_map_default_hash_func(const void *key, size_t capacity);

size_t xPear16(unsigned char *x, size_t capacity, int len);
unsigned char xPear16_helper(unsigned char *x, size_t capacity, int len);

#endif /*HASH_FUNCTIONS_H*/
