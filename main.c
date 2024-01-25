#include "list.h"
#include <stdio.h>


void List_print(List* pList){
    Node* temp_curr = pList->current_node_pointer;
    List_first(pList);

    for (int i=0; i< pList->list_size; i++){
        printf( "%s\n", (char*)List_curr(pList));
        List_next(pList);
    }

    pList->current_node_pointer = temp_curr;
}

void print_size(List* pList){
    printf("List Size: %d\n", List_count(pList));
}

void func_free(void* pItem){
        pItem = NULL;
    }

bool compare_func(void* pItem, void* pCompaisonArg){
    int* item = (int*) pItem;
    int* arg = (int*) pCompaisonArg;

    if (*item == *arg){
        return true;
    }
    else {
        return false;
    }
}

int test1(){
    printf("<------------------------Test 1------------------------------------------------------------>\n");

    List* list1 = List_create();

    char* data1 = "Item 1";
    char* data2 = "Item 2";
    char* data3 = "Item 3";
    char* data4 = "Item 4";
    char* data5 = "Item 5";
    char* data6 = "Item 6";

    printf("List1 after creation and 6 insertions:\n");
    List_print(list1);
    List_append(list1,data1);
    List_append(list1,data2);
    List_append(list1,data3);
    List_append(list1,data4);
    List_append(list1,data5);
    List_append(list1,data6);

    printf("List1 after insertions using List_append function: \n");
    List_print(list1);

    printf("First item of List1: %s\n\n", (char*)List_first(list1));
    printf("Last item of List1: %s\n\n", (char*)List_last(list1));
    printf("Current item of List1: %s\n\n", (char*)List_curr(list1));
    printf("Number of items in List1: %d\n\n", List_count(list1));

    List_first(list1);
    List_next(list1);
    List_next(list1);
    printf("Current item after reseting it to the first item and then using List_next function twice: %s\n\n", (char*)List_curr(list1));

    List_prev(list1); 
    List_prev(list1); 

    printf("Now using List_prev function twice to go back to the first item, new current item: %s\n", (char*)List_curr(list1));
    return 0;
}

int test2(){
    printf("<------------------------Test 2------------------------------------------------------------>\n");
    List* list1 = List_create();

    char* data1 = "Item 1";
    char* data2 = "Item 2";
    char* data3 = "Item 3";
    char* data4 = "Item 4";
    char* data5 = "Item 5";
    char* data6 = "Item 6";
    char* data7 = "Item 7";
    char* data8 = "Item 8";
    char* data9 = "Item 9";
    char* data10 = "Item 10";
    char* data11 = "Item 11";
    char* data12 = "Item 12";

    printf("List1 after creation and 6 insertions:\n");

    List_append(list1,data1);
    List_append(list1,data2);
    List_append(list1,data3);
    List_append(list1,data4);
    List_append(list1,data5);
    List_append(list1,data6);
    List_print(list1);

    printf("Bringing the current pointer to the third item.\n\n");
    List_first(list1);
    List_next(list1);
    List_next(list1);
    printf("Now inserting three items after the third item. \n\n");
    printf("List1 after the insertions using List_insert_after: \n");
    List_insert_after(list1, data7);
    List_insert_after(list1, data8);
    List_insert_after(list1, data9);
    List_print(list1);

    printf("Now inserting 2 items before the current item. \n\n");
    List_insert_before(list1, data10);
    List_insert_before(list1, data11);
    printf("list1 after two insertion before the current item: \n\n");
    List_print(list1);
    return 0;
}

int test3(){
    printf("<------------------------Test 3------------------------------------------------------------>\n");
    List* list1 = List_create();

    char* data1 = "Item 1";
    char* data2 = "Item 2";
    char* data3 = "Item 3";
    char* data4 = "Item 4";
    char* data5 = "Item 5";
    char* data6 = "Item 6";

    printf("Appending 3 items to list1. \n\n");
    List_append(list1, data4);
    List_append(list1, data5);
    List_append(list1, data6);
    printf("List1 after appending: \n");
    List_print(list1);
    printf("\n\n");
    printf("Now prepending 3 items to list1. \n\n");
    List_prepend(list1, data1);
    List_prepend(list1, data2);
    List_prepend(list1, data3);
    printf("List1 after prepending: \n");
    List_print(list1);

    return 0;
}

int test4(){
    printf("<------------------------Test 4------------------------------------------------------------>\n");
    List* list1 = List_create();

    char* data1 = "Item 1";
    char* data2 = "Item 2";
    char* data3 = "Item 3";
    char* data4 = "Item 4";
    char* data5 = "Item 5";
    char* data6 = "Item 6";
    char* data7 = "Item 7";
    char* data8 = "Item 8";
    char* data9 = "Item 9";
    char* data10 = "Item 10";

    List_append(list1, data1);
    List_append(list1, data2);
    List_append(list1, data3);
    List_append(list1, data4);
    List_append(list1, data5);
    List_append(list1, data6);
    List_append(list1, data7);
    List_append(list1, data8);
    List_append(list1, data9);
    List_append(list1, data10);

    printf("List1 after insertions: \n");
    List_print(list1);
    print_size(list1);

    List_first(list1);
    List_next(list1);
    List_next(list1);

    printf("Setting the current pointer to the third item. \n");
    printf("Removing 3 items starting from current item. \n\n");
    printf("List1 after 3 removals: \n\n");
    List_remove(list1);
    List_remove(list1);
    List_remove(list1);

    List_print(list1);
    print_size(list1);

    printf("Now trimming 3 items from List1. \n\n");
    List_trim(list1);
    List_trim(list1);
    List_trim(list1);
    printf("List1 after trimming: \n\n");
    List_print(list1);
    print_size(list1);
    return 0;
}

int test5(){
    printf("<------------------------Test 5------------------------------------------------------------>\n");
    List* list1 = List_create();
    List* list2 = List_create();

    char* data1 = "Item 1";
    char* data2 = "Item 2";
    char* data3 = "Item 3";
    char* data4 = "Item 4";
    char* data5 = "Item 5";
    char* data6 = "Item 6";
    char* data7 = "Item 7"; 
    char* data8 = "Item 8";

    List_append(list1, data1);
    List_append(list1, data2);
    List_append(list1, data3);

    List_append(list2, data4);
    List_append(list2, data5);
    List_append(list2, data6);

    printf("\nList1 after insertion: \n");
    print_size(list1);
    List_print(list1);

    printf("\nList2 after insertion: \n");
    print_size(list2);
    List_print(list2);

    printf("\nConcatenating the two lists --------------------->\n");
    List_concat(list1, list2);
    printf("List1 after concatenation: \n");
    List_print(list1);
    print_size(list1);


    printf("List2 after concatenation: \n");
    List_print(list2);
    print_size(list2);
    printf("--------------------------------------\n");

    printf("Adding some new elements to check for current pointer! \n");
    List_insert_before(list1, data7);
    List_insert_before(list1, data8);

    printf("List1 after doing insertion before the current pointer: \n");
    List_print(list1);
    return 0;
}

int test6(){
    printf("<------------------------Test 6------------------------------------------------------------>\n");
    List* list1 = List_create();
    List* list2 = List_create();

    char* data1 = "Item 1";
    char* data2 = "Item 2";
    char* data3 = "Item 3";
    char* data4 = "Item 4";
    char* data5 = "Item 5";
    char* data6 = "Item 6";
    char* data7 = "Item 7"; 
    char* data8 = "Item 8";

    List_append(list1, data1);
    List_append(list1, data2);
    List_append(list1, data3);

    List_append(list2, data4);
    List_append(list2, data5);
    List_append(list2, data6);

    printf("\nList1 after insertion: \n");
    print_size(list1);
    List_print(list1);

    printf("\nList2 after insertion: \n");
    print_size(list2);
    List_print(list2);

    printf("\nNow freeing list2. \n\n");
    List_free(list2, func_free);
    printf("List2 after freeing: \n");
    List_print(list2);
    print_size(list2);

    return 0;
}

int search_test(){
    printf("<------------------------SEARCH TEST------------------------------------------------------------>\n");
    List* list1 = List_create();

    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int data4 = 4;
    int data5 = 5;
    int data6 = 6;

    int dataX = 1;
    int dataY = 45;

    List_append(list1, &data1);
    List_append(list1, &data2);
    List_append(list1, &data3);
    List_append(list1, &data4);
    List_append(list1, &data5);
    List_append(list1, &data6);

    printf("List1 : 1,2,3,4,5,6\n\n");
    print_size(list1);
    List_first(list1);
    void* result = List_search(list1, compare_func, &dataX);
    printf("Searching for an item with value 3 in List1: \n");
    if (result == NULL){
        printf("Item not found! \n\n");
    }
    else {
        printf("Item found: %d, 1 means item is there in the list, search was successfull!\n\n", *(int*)result);
    }

    printf("Searching for an item with value 45 in List1: \n");

    void* result2 = List_search(list1, compare_func, &dataY);
    if (result2 == NULL){
        printf("Item not found!\n\n");
    }
    else {
        printf("Item found: %d", *(int*)result2);
    }

    return 0;
}

int advance_test(){
    printf("<------------------------ADVANCE TEST------------------------------------------------------------>\n");
    List* list = List_create();

    char* data1 = "Item 1";
    char* data2 = "Item 2";
    char* data3 = "Item 3";
    char* data4 = "Item 4";
    char* data5 = "Item 5";
    char* data6 = "Item 6";
    char* data7 = "Item 7";
    char* data8 = "Item 8";
    char* data9 = "Item 9";
    char* data10 = "Item 10";
    char* data11 = "Item 11";
    char* data12 = "Item 12";

    printf("List1: \n");
    List_print(list);
    print_size(list);

    printf("Now appending 3 items and then prepending 3 items in the list\n\n");
    List_append(list, data1);
    List_append(list, data2);
    List_append(list, data3);
    List_prepend(list, data4);
    List_prepend(list, data5);
    List_prepend(list, data6);

    printf("List1: \n");
    List_print(list);
    print_size(list);

    printf("Now trimming two items from the list. \n\n");
    List_trim(list);
    List_trim(list);
    printf("List after trimming: \n");
    List_print(list);
    printf("Now bringing the current pointer to the second item and then removing it. \n\n");
    List_first(list);
    List_next(list);
    List_remove(list);
    
    printf("List1 after removal: \n");
    List_print(list);

    printf("\nNow going to the previous item of the current item and inserting an item after that: \n");
    List_prev(list);
    List_insert_after(list, data7);
    printf("List: \n");
    List_print(list);
    printf("\nNow making the last item the current item and inserting an item before it. \n");
    List_last(list);
    List_insert_before(list, data8);
    printf("List: \n");
    List_print(list);
    print_size(list);
    printf("\nNow creating a second list that has 4 items. \n");
    List* second_list = List_create();
    List_append(second_list,data9);
    List_append(second_list,data10);
    List_append(second_list,data11);
    List_append(second_list,data12);
    printf("Second List: \n");
    List_print(second_list);
    print_size(second_list);

    printf("\nConcatenating the second list to the list. \n");
    List_concat(list, second_list);
    printf("\nList after concatenation: \n");
    List_print(list);
    print_size(list);

    printf("Now freeing the list. \n");
    List_free(list, func_free);
    printf("List after freeing: \n");
    List_print(list);
    print_size(list);

    return 0;
}



int main(){
    
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    search_test();
    advance_test();

    return 0;
}