/**
 * @file
 * Implementation of different hash functions.
 */

#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

/**
 * The default hash function. This is the function to be used if the user does not explicitly provide any hash function. It is a basic <EM> mod </EM> operator.
 * @param key key to hash
 * @param capacity maximum size of the map
 * @param len the size of the key passed as the first argument
 * @return an offset within the range `[0, capacity)`
 */
size_t hash_map_default_hash_func(const void *key, size_t capacity, int len);

/**
 * The Pearson hash function. Both the explanation and code are derived from <A HREF="http://en.wikipedia.org/wiki/Pearson_hashing">Wikipedia</A>
 * @param key key to hash
 * @param capacity maximum size of the map
 * @param len the size of the key passed as the first argument
 * @return an offset within the range `[0, capacity)`
 */
size_t xPear16(const void *x, size_t capacity, int len);

#endif /*HASH_FUNCTIONS_H*/
