#include "memory.h"
#include "linked_list.h"






static linked_list *list;

static linked_list *dynamic_list;



int intp_equal(const int *l, const int *r) {



 return *l - *r;

}



void setUp() {

 list = safe_malloc(sizeof(linked_list));



 linked_list_init(list, (linked_list_comparator) intp_equal, (linked_list_destructor) ((void*)0));



 dynamic_list = safe_malloc(sizeof(linked_list));

 linked_list_init(dynamic_list, (linked_list_comparator) intp_equal, (linked_list_destructor) safe_free);

}



void test_empty_list() {

 if ((((linked_list_head(list))) == ((void*)0))) {} else {UnityFail( (" Expected NULL"), (_U_UINT)(_U_UINT)(_U_UINT)27);;};

 if ((((linked_list_head(dynamic_list))) == ((void*)0))) {} else {UnityFail( (" Expected NULL"), (_U_UINT)(_U_UINT)(_U_UINT)28);;};

}



void test_append() {

 int data[] = {111, 131, 35, 42};



 unsigned i;

 for(i = 0; i < sizeof(data) / sizeof(*data); ++i) {

  linked_list_append(list, &data[i]);

 }



 linked_list_node *node;

 for(i = 0, node = linked_list_head(list); node != ((void*)0); ++i, node = node->next) {

  UnityAssertEqualNumber((_U_SINT)((data[i])), (_U_SINT)((*(int*)node->data)), (((void*)0)), (_U_UINT)41, UNITY_DISPLAY_STYLE_INT);

 }

}



void test_append_dynamic() {

 int data_length = 6;



 int i;

 for (i = 0; i < data_length; ++i) {

  int *data = (int *) safe_malloc(sizeof(int));

  *data = i * 100;

  linked_list_append(dynamic_list, data);

 }



 linked_list_node *node;

 for (i = 0, node = linked_list_head(dynamic_list); node != ((void*)0); ++i, node = node->next) {

  UnityAssertEqualNumber((_U_SINT)((i * 100)), (_U_SINT)((*(int*)node->data)), (((void*)0)), (_U_UINT)57, UNITY_DISPLAY_STYLE_INT);

 }

}



void test_prepend() {

 int data[] = {111, 131, 35, 42};

 int data_length = sizeof(data) / sizeof(*data);



 unsigned i;

 for(i = 0; i < data_length; ++i) {

  linked_list_prepend(list, &data[i]);

 }



 linked_list_node *node;

 for(i = data_length-1, node = linked_list_head(list); node != ((void*)0); --i, node = node->next) {

  UnityAssertEqualNumber((_U_SINT)((data[i])), (_U_SINT)((*(int*)node->data)), (((void*)0)), (_U_UINT)72, UNITY_DISPLAY_STYLE_INT);

 }

}



void test_prepend_dynamic() {

 int data_length = 6;



 int i;

 for(i = 0; i < data_length; ++i) {

  int *data = (int *) safe_malloc(sizeof(int));

  *data = i * 100;

  linked_list_prepend(dynamic_list, data);

 }



 linked_list_node *node;

 for(i = data_length-1, node = linked_list_head(dynamic_list); node != ((void*)0); --i, node = node->next) {

  UnityAssertEqualNumber((_U_SINT)((i * 100)), (_U_SINT)((*(int*)node->data)), (((void*)0)), (_U_UINT)88, UNITY_DISPLAY_STYLE_INT);

 }

}



void test_remove_first_beginning() {

 int data_before[] = {23, -37, -83, 92, 131, -13};

 int data_after[] = {-37, -83, 92, 131, -13};



 unsigned i;

 for(i = 0; i < sizeof(data_before) / sizeof(*data_before); ++i) {

  linked_list_append(list, &data_before[i]);

 }



 int to_remove = 23;

 linked_list_remove_first(list, &to_remove);



 linked_list_node *node;

 for(i = 0, node = linked_list_head(list); node; ++i, node = node->next) {

  UnityAssertEqualNumber((_U_SINT)((data_after[i])), (_U_SINT)((*(int*)node->data)), (((void*)0)), (_U_UINT)106, UNITY_DISPLAY_STYLE_INT);

 }

}



void test_remove_first_middle() {

 int data_before[] = {23, -37, -83, 92, 131, -13};

 int data_after[] = {23, -37, -83, 92, -13};



 unsigned i;

 for(i = 0; i < sizeof(data_before) / sizeof(*data_before); ++i) {

  linked_list_append(list, &data_before[i]);

 }



 int to_remove = 131;

 linked_list_remove_first(list, &to_remove);



 linked_list_node *node;

 for(i = 0, node = linked_list_head(list); node; ++i, node = node->next) {

  UnityAssertEqualNumber((_U_SINT)((data_after[i])), (_U_SINT)((*(int*)node->data)), (((void*)0)), (_U_UINT)124, UNITY_DISPLAY_STYLE_INT);

 }

}



void test_remove_first_end() {

 int data_before[] = {23, -37, -83, 92, 131, -13};

 int data_after[] = {23, -37, -83, 92, 131};



 unsigned i;

 for(i = 0; i < sizeof(data_before) / sizeof(*data_before); ++i) {

  linked_list_append(list, &data_before[i]);

 }



 int to_remove = -13;

 linked_list_remove_first(list, &to_remove);



 linked_list_node *node;

 for(i = 0, node = linked_list_head(list); node; ++i, node = node->next) {

  UnityAssertEqualNumber((_U_SINT)((data_after[i])), (_U_SINT)((*(int*)node->data)), (((void*)0)), (_U_UINT)142, UNITY_DISPLAY_STYLE_INT);

 }

}



void test_remove_string() {

 linked_list *list_str = safe_malloc(sizeof(linked_list));

 linked_list_init(list_str, (linked_list_comparator)strcmp, (linked_list_destructor) ((void*)0));



 char *data_before[] = {"babak", "sean", "liu", "someone else"};

 char *data_after[] = {"babak", "liu", "someone else"};



 unsigned i;

 for(i = 0; i < sizeof(data_before) / sizeof(*data_before); ++i) {

  linked_list_append(list, data_before[i]);

 }



 linked_list_remove_first(list, "sean");



 linked_list_node *node;

 for(i = 0, node = linked_list_head(list); node; ++i, node = node->next) {

  UnityAssertEqualString((const char*)(data_after[i]), (const char*)((char*)node->data), (((void*)0)), (_U_UINT)162);

 }



 linked_list_free(list_str);

}



void tearDown() {

 linked_list_free(list);

 linked_list_free(dynamic_list);



 UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((__malloc_counter)), (((void*)0)), (_U_UINT)172, UNITY_DISPLAY_STYLE_INT);

}
