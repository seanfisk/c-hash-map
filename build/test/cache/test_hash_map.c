#include "memory.h"
#include "linked_list.h"
#include "hash_map.h"










static hash_map *map;



extern int __malloc_counter;



void setUp() {

 map = safe_malloc(sizeof(hash_map));

 hash_map_init(map, 1000, (hash_map_comparator) strcmp, ((void*)0));

}



void test_set_get() {

 hash_map_set(map, "key", "value");

 UnityAssertEqualString((const char*)("value"), (const char*)((char *) hash_map_get(map, "key")), (((void*)0)), (_U_UINT)22);



 hash_map_set(map, "key", "value2");

 UnityAssertEqualString((const char*)("value2"), (const char*)((char *) hash_map_get(map, "key")), (((void*)0)), (_U_UINT)25);



 hash_map_set(map, "key2", "value3");

 UnityAssertEqualString((const char*)("value3"), (const char*)((char *) hash_map_get(map, "key2")), (((void*)0)), (_U_UINT)28);

}



void test_get_invalid_key() {

 if ((((hash_map_get(map, "invalid_key"))) == ((void*)0))) {} else {UnityFail( (" Expected NULL"), (_U_UINT)(_U_UINT)(_U_UINT)32);;};

}



void test_default_hash_func() {

 uint64_t i1 = 1, i2 = 1001;





 UnityAssertEqualNumber((_U_SINT)((map->hash_func(&i1, map->capacity))), (_U_SINT)((map->hash_func(&i2, map->capacity))), (((void*)0)), (_U_UINT)40, UNITY_DISPLAY_STYLE_UINT);







 UnityAssertEqualNumber((_U_SINT)((map->hash_func("1234567890", map->capacity))), (_U_SINT)((map->hash_func("1234567809", map->capacity))), (((void*)0)), (_U_UINT)44, UNITY_DISPLAY_STYLE_UINT);





}



void test_collision() {



 hash_map_set(map, "1234567890", "9090");

 hash_map_set(map, "1234567809", "0909");



 UnityAssertEqualString((const char*)("9090"), (const char*)(hash_map_get(map, "1234567890")), (((void*)0)), (_U_UINT)53);

 UnityAssertEqualString((const char*)("0909"), (const char*)(hash_map_get(map, "1234567809")), (((void*)0)), (_U_UINT)54);

}



void tearDown() {

 hash_map_free(map);



 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((__malloc_counter)), (((void*)0)), (_U_UINT)60, UNITY_DISPLAY_STYLE_INT);

}
