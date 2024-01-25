#include "list.h"
#include <stddef.h>

static List list_array[LIST_MAX_NUM_HEADS];
static Node node_array[LIST_MAX_NUM_NODES];

static bool first_list_created = false;
static List* free_list; //This pointer points to the next available empty list for use  
static Node* free_node; //This pointer points to the next available empty node for use  
//In case free_list is NULL that would mean that there are no empty lists and 
//when free_node is NULL that would mean that there are no empty nodes left

List *List_create(){

    //First I'll check if this is the first iteration of the list_create function 
    if(!first_list_created){
        for (int i = 0; i < LIST_MAX_NUM_HEADS-1; i++) {
                list_array[i].next_free_list = &list_array[i+1];
        }
        list_array[LIST_MAX_NUM_HEADS-1].next_free_list = NULL;

        for (int j = 0; j < LIST_MAX_NUM_NODES - 1; j++){
            node_array[j].next_free_node = &node_array[j+1];
        }
        node_array[LIST_MAX_NUM_NODES - 1].next_free_node = NULL;

        free_list = &list_array[0]; //Setting the free_list variable to the first list of the list array initially
        free_node = &node_array[0]; //Setting the free_node variable to the first node of the node array initially 

        free_list->head_node_pointer = NULL;
        free_list->tail_node_pointer = NULL;//Initializing the list, free_list points to a list so we dont need the indexes anymore 
        free_list->current_node_pointer = NULL;
        free_list->list_size = 0;
        free_list->state_curr_pointer = LIST_OOB_START;

        List* temp1 = free_list; //temporary pointer to the current list, as we need to return the pointer to the current list
        free_list = free_list->next_free_list; //free_list updated to point to the next updated free list.
        first_list_created = true;
        // temp1->next_free_list = NULL; //this for added safety as now this list is already used so it wont be used in findingout out the next free list ever again.
        return temp1;
    }

    else{
        if (free_list == NULL){
            return NULL;
        }
        else {
            free_list->head_node_pointer = NULL;
            free_list->tail_node_pointer = NULL; 
            free_list->current_node_pointer = NULL;
            free_list->list_size = 0;
            free_list->state_curr_pointer = LIST_OOB_START;

            List* temp2 = free_list;
            free_list = free_list->next_free_list;
            // temp2->next_free_list = NULL;              
            return temp2;
        }
    }
}

int List_count(List *pList){
    return pList->list_size;
}

// List -> head_node_pointer -> item , //head points to the actual first node, that's it!!
void *List_first(List *pList) {
    if (pList->list_size == 0){
        pList->current_node_pointer = NULL;
        return NULL;
    }
    else {
        pList->current_node_pointer = pList->head_node_pointer;
        return pList->head_node_pointer->Item;
    }
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void *List_last(List *pList){
    if (pList-> list_size == 0){ 
        pList->current_node_pointer = NULL;
        return NULL;
    }

    else {
        pList->current_node_pointer = pList->tail_node_pointer;
        return pList->tail_node_pointer->Item;
    }
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer
// is returned and the current item is set to be beyond end of pList.
void *List_next(List *pList){

    if (pList->current_node_pointer == NULL){ //This is the case when the list that is given, its current pointer already points to a NULL

        if (pList->list_size == 0){
            pList->state_curr_pointer = LIST_OOB_END;
            return NULL;
        }

        else if(pList->state_curr_pointer == LIST_OOB_START){ //if the current pointer is beyond from the start of the list then make the head node the current node 
            pList->current_node_pointer = pList->head_node_pointer;
            return pList->current_node_pointer->Item;
        }
    }

    else { //This is the normal case given in the description
    pList->current_node_pointer = pList->current_node_pointer->next_pointer;
    if (pList->current_node_pointer == NULL){  //This line alone does not determine that the pointer points beyond the end, but the previous line and this line combinely make sense to check if the pointer is pointing beyond the list
        pList->state_curr_pointer = LIST_OOB_END;
        return NULL;
        }
    else {
        return pList->current_node_pointer->Item;
        }
    }
}

// Backs up pList's current item by one, and returns a pointer to the new current item.
// If this operation backs up the current item beyond the start of the pList, a NULL pointer
// is returned and the current item is set to be before the start of pList.
void *List_prev(List *pList){
    
    if (pList->current_node_pointer == NULL){
        
        if (pList->list_size == 0){
            pList->state_curr_pointer = LIST_OOB_START;
            return NULL;
        }

        else if (pList->state_curr_pointer == LIST_OOB_END){
            pList->current_node_pointer = pList->tail_node_pointer;
            return pList->current_node_pointer->Item;
        }
    }

    else {
    pList->current_node_pointer = pList->current_node_pointer->previous_pointer;
    if (pList->current_node_pointer == NULL){
        pList->state_curr_pointer = LIST_OOB_START;
        return NULL;
        }
    else {
        return pList->current_node_pointer->Item;
        }        
    }
}

// Returns a pointer to the current item in pList.
void *List_curr(List *pList){
    return pList->current_node_pointer->Item;
}

// Adds the new item to pList directly after the current item, and makes item the current item.
// If the current pointer is before the start of the pList, the item is added at the start. If
// the current pointer is beyond the end of the pList, the item is added at the end.
// Returns 0 on success, -1 on failure.
int List_insert_after(List *pList, void *pItem){
    
    if (free_node ==  NULL){ //free_node being null means there are no 
        return -1;
    }

    if (pList->list_size == 0 ){
        free_node->Item = pItem;
        free_node->next_pointer = NULL;
        free_node->previous_pointer = NULL;

        pList->head_node_pointer = free_node;
        pList->tail_node_pointer = free_node;
        pList->current_node_pointer = free_node;
        pList->list_size = 1;

        free_node = free_node->next_free_node;

    }
    else {
        if (pList->current_node_pointer != NULL){
            Node* temp3 = pList->current_node_pointer->next_pointer; //temp3 might be null if the current node pointer points to the tail of the list 
            pList->current_node_pointer->next_pointer = free_node;
            free_node->previous_pointer = pList->current_node_pointer;
            free_node->next_pointer = temp3;
            free_node->Item = pItem;
            if (temp3 != NULL){  
                temp3->previous_pointer = free_node;
            }
            else {
                pList->tail_node_pointer = free_node;
            }

            pList->current_node_pointer = free_node;
            free_node = free_node->next_free_node;
            pList->list_size++;
        }

        if (pList->current_node_pointer == NULL){
            if (pList->state_curr_pointer == LIST_OOB_START){

                free_node->previous_pointer = NULL;
                free_node->next_pointer = pList->head_node_pointer;
                free_node->Item = pItem;
                pList->head_node_pointer->previous_pointer = free_node;
                pList->head_node_pointer = free_node;
                pList->current_node_pointer = free_node;

                free_node = free_node->next_free_node;      
                pList->list_size++;
            }

            if (pList->state_curr_pointer == LIST_OOB_END){

                free_node->previous_pointer = pList->tail_node_pointer;
                free_node->next_pointer = NULL;
                free_node->Item = pItem;
                pList->tail_node_pointer->next_pointer = free_node;

                pList->tail_node_pointer = free_node;
                pList->current_node_pointer = free_node;

                free_node = free_node->next_free_node;
                pList->list_size++;
            }
        }
    }
    return 0;
}


// // Adds item to pList directly before the current item, and makes the new item the current one.
// // If the current pointer is before the start of the pList, the item is added at the start.
// // If the current pointer is beyond the end of the pList, the item is added at the end.
// // Returns 0 on success, -1 on failure.
int List_insert_before(List *pList, void *pItem){
    
    if (free_node ==  NULL){ //free_node being null means there are no 
        return -1;
    }    

    if (pList->list_size == 0 ){
        free_node->Item = pItem;
        free_node->next_pointer = NULL;
        free_node->previous_pointer = NULL;

        pList->head_node_pointer = free_node;
        pList->tail_node_pointer = free_node;
        pList->current_node_pointer = free_node;
        pList->list_size = 1;

        free_node = free_node->next_free_node;
    }    

    else {
        if (pList->current_node_pointer != NULL){
            Node* temp4 = pList->current_node_pointer->previous_pointer;
            pList->current_node_pointer->previous_pointer = free_node;
            free_node->next_pointer = pList->current_node_pointer;
            free_node->previous_pointer = temp4;
            free_node->Item = pItem;

            if (temp4 != NULL){  // temp4 will be pList->current_node_pointer->previous_pointer, so technically we will check if the current pointer points to head node or not.
                temp4->next_pointer = free_node;
            }
            else { //when current pointer was actually pointing to the head node
                pList->head_node_pointer = free_node;
            }

            pList->current_node_pointer = free_node;
            free_node = free_node->next_free_node;
            pList->list_size++;
        }
        
        if (pList->current_node_pointer == NULL){
            if (pList->state_curr_pointer == LIST_OOB_START){

                free_node->previous_pointer = NULL;
                free_node->next_pointer = pList->head_node_pointer;
                free_node->Item = pItem;
                pList->head_node_pointer->previous_pointer = free_node;
                pList->head_node_pointer = free_node;
                pList->current_node_pointer = free_node;

                free_node = free_node->next_free_node;      
                pList->list_size++;
            }

            if (pList->state_curr_pointer == LIST_OOB_END){

                free_node->previous_pointer = pList->tail_node_pointer;
                free_node->next_pointer = NULL;
                free_node->Item = pItem;
                pList->tail_node_pointer->next_pointer = free_node;

                pList->tail_node_pointer = free_node;
                pList->current_node_pointer = free_node;

                free_node = free_node->next_free_node;
                pList->list_size++;
            }
        }
    }
    return 0;
}

// Adds item to the end of pList, and makes the new item the current one.
// Returns 0 on success, -1 on failure.
int List_append(List *pList, void *pItem){
    
    if (free_node == NULL){
        return -1;
    }

    if (pList->list_size == 0 ){
        free_node->Item = pItem;
        free_node->next_pointer = NULL;
        free_node->previous_pointer = NULL;

        pList->head_node_pointer = free_node;
        pList->tail_node_pointer = free_node;
        pList->current_node_pointer = free_node;
        pList->list_size = 1;

        free_node = free_node->next_free_node;
    }        

    else {
            free_node->previous_pointer = pList->tail_node_pointer;
            free_node->next_pointer = NULL;
            free_node->Item = pItem;
            pList->tail_node_pointer->next_pointer = free_node;
            pList->tail_node_pointer = free_node;
            pList->current_node_pointer = free_node;

            free_node = free_node->next_free_node;
            pList->list_size++;      
    }
    return 0;
}


// Adds item to the front of pList, and makes the new item the current one.
// Returns 0 on success, -1 on failure.
int List_prepend(List *pList, void *pItem){

    if (free_node == NULL){
        return -1;
    }

    if (pList->list_size == 0 ){
        free_node->Item = pItem;
        free_node->next_pointer = NULL;
        free_node->previous_pointer = NULL;

        pList->head_node_pointer = free_node;
        pList->tail_node_pointer = free_node;
        pList->current_node_pointer = free_node;
        pList->list_size = 1;

        free_node = free_node->next_free_node;
    }  

    else {
            free_node->previous_pointer = NULL;
            free_node->next_pointer = pList->head_node_pointer;
            free_node->Item = pItem;
            pList->head_node_pointer->previous_pointer = free_node;
            pList->head_node_pointer = free_node;
            pList->current_node_pointer = free_node;

            free_node = free_node->next_free_node;      
            pList->list_size++;
    }
    return 0;
}


// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void *List_remove(List *pList){
    // printf("0");
    if (pList->current_node_pointer == NULL){ //description case
        if (pList->state_curr_pointer == LIST_OOB_START || pList->state_curr_pointer == LIST_OOB_END){
            return NULL;
        }
    }

    else {
    // printf("1");
        if (pList->list_size == 0){ //The above if statement might take care of this case, just adding for extra safety
            return NULL;
        }

        else { //case when the removal will happen for sure
            // printf("remove mode!!!");
            void* temp_data = pList->current_node_pointer->Item; //storing the address of the actual data, as the pointer to this data will be lost in the next code block
            Node* temp_next = pList->current_node_pointer->next_pointer;
            Node* temp_prev = pList->current_node_pointer->previous_pointer;
            // Node* temp_current = pList->current_node_pointer;
            //first empty the current node 
            pList->current_node_pointer->next_pointer = NULL;
            pList->current_node_pointer->previous_pointer = NULL;
            pList->current_node_pointer->Item = NULL;

             //IMPORTANT LOGIC HERE, 
            if (free_node != NULL){ //this case means that all the nodes havent been used yet from the nodes array
                Node* temp5 = free_node;
                free_node = pList->current_node_pointer;
                free_node->next_free_node = temp5;
            }
            else {
                free_node = pList->current_node_pointer;
            }


            if (pList->list_size == 1){ //when there is only one node in the list
                // printf("Single Remove!\n");
                pList->current_node_pointer = NULL;
                pList->head_node_pointer = NULL;
                pList->tail_node_pointer = NULL;
            }

            else if (pList->current_node_pointer == pList->head_node_pointer){ //when head node is to be removed
                // printf("Head Remove\n");
                temp_next->previous_pointer = NULL;
                pList->head_node_pointer = temp_next;
                pList->current_node_pointer = temp_next;
            }

            else if (pList->current_node_pointer == pList->tail_node_pointer){ //when tail node is to be removed
                // printf("Tail Remove \n");
                temp_prev->next_pointer = NULL;
                pList->tail_node_pointer = temp_prev;
                pList->current_node_pointer = temp_prev;
            }

            else { //This is the case when any non edge node is removed 
                // printf("Central Remove \n");
                temp_prev->next_pointer = temp_next;
                temp_next->previous_pointer = temp_prev;
                pList->current_node_pointer = temp_next;
            }
            // printf("remove ran");
            pList->list_size--;
            return temp_data;
        }
    }
    // printf("REMOVE DONE");
}

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void *List_trim(List *pList){

    if (pList->list_size == 0){
        return NULL;
    }

    else {
        Node* temp_prev = pList->tail_node_pointer->previous_pointer;
        void* temp_data = pList->tail_node_pointer->Item;

        pList->tail_node_pointer->next_pointer = NULL;
        pList->tail_node_pointer->previous_pointer = NULL;
        pList->tail_node_pointer->Item;

        //IMPORTANT LOGIC HERE, 
        if (free_node != NULL){ //this case means that all the nodes havent been used yet from the nodes array
            Node* temp6 = free_node;
            free_node = pList->tail_node_pointer;
            free_node->next_free_node = temp6;
        }
        else {
            free_node = pList->tail_node_pointer;
        }

        if (pList->list_size == 1){
            pList->current_node_pointer = NULL;
            pList->tail_node_pointer = NULL;
            pList->head_node_pointer = NULL;
        } 

        else {
            temp_prev->next_pointer = NULL;
            pList->tail_node_pointer = temp_prev;
            pList->current_node_pointer = temp_prev;
        }
        pList->list_size--;
        return temp_data;
    }
}


// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1.
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List *pList1, List *pList2){
    Node* temp_curr = pList1->current_node_pointer;
    pList1->tail_node_pointer->next_pointer = pList2->head_node_pointer;
    pList1->tail_node_pointer = pList2->tail_node_pointer;
    pList1->list_size += pList2->list_size;

    //reycling the list 
    if (free_list != NULL){
        List* temp = free_list;
        free_list = pList2;
        free_list->next_free_list = temp;
    }
    else {
        free_list = pList2;
    }

    pList2->current_node_pointer = NULL;
    pList2->tail_node_pointer = NULL;
    pList2->head_node_pointer = NULL;
    pList2->list_size = 0;
    pList2->state_curr_pointer = LIST_OOB_START;

    pList1->current_node_pointer = temp_curr;
}

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item.
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are
// available for future operations.
typedef void (*FREE_FN)(void *pItem);
void List_free(List *pList, FREE_FN pItemFreeFn){
    List_first(pList);
    int size = pList->list_size;
    
    for(int i=0; i< size; i++){
        void* temp_free_node = List_remove(pList);
        if (temp_free_node != NULL){
            (*pItemFreeFn)(temp_free_node);
        }
    };

    //recycling free lists
    if (free_list != NULL){
        List* temp = free_list;
        free_list = pList;
        free_list->next_free_list = temp;
    } 
    else {
        free_list = pList;
    }

    pList->current_node_pointer = NULL;
    pList->head_node_pointer = NULL;
    pList->tail_node_pointer = NULL;
    pList->list_size = 0;
    pList->state_curr_pointer = LIST_OOB_START;
}


// Search pList, starting at the current item, until the end is reached or a match is found.
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match,
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator.
//
// If a match is found, the current pointer is left at the matched item and the pointer to
// that item is returned. If no match is found, the current pointer is left beyond the end of
// the list and a NULL pointer is returned.
//
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
typedef bool (*COMPARATOR_FN)(void *pItem, void *pComparisonArg);
void *List_search(List *pList, COMPARATOR_FN pComparator, void *pComparisonArg){
    
    if (pList->list_size == 0){
        pList->current_node_pointer = NULL;
        pList->state_curr_pointer = LIST_OOB_END;
        return NULL;
    }
    else {
        if (pList->current_node_pointer == NULL){
            if (pList->state_curr_pointer == LIST_OOB_START){
                pList->current_node_pointer = pList->head_node_pointer;
            }
        }

        while (pList->current_node_pointer != NULL){
            int result = (*pComparator) (pList->current_node_pointer->Item, pComparisonArg);
            if (result == 1){
                return pList->current_node_pointer->Item;
            }
            else {
                pList->current_node_pointer = pList->current_node_pointer->next_pointer;
            }
        }
    }
    pList->current_node_pointer = NULL;
    pList->state_curr_pointer = LIST_OOB_END;
    return NULL;
}




