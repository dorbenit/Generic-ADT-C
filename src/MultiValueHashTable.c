#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"
#include <stdlib.h>
struct MultiValueHashTable_s {
    hashTable ht;
    EqualFunction equalValue;
    CopyFunction copyValue;
    CopyFunction copyKey;
    FreeFunction freeValue;
    FreeFunction freeKey;
    PrintFunction printValue;
    PrintFunction printKey;
};
// Creates a new MultiValueHashTable
MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue ,FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,EqualFunction equalValue,TransformIntoNumberFunction transformIntoNumber, int hashNumber) {

    MultiValueHashTable mht = malloc(sizeof(struct MultiValueHashTable_s));
    if (mht == NULL) {
        return NULL;
    }
    // Create the base hash table
    mht->ht = createHashTable( (CopyFunction)copyKey,
    (FreeFunction)freeKey,
    (PrintFunction)printKey,
    (CopyFunction)copyValue,
    (FreeFunction)destroyLinkedList,
    (PrintFunction)printValue,
    (EqualFunction)equalKey,
    (TransformIntoNumberFunction)transformIntoNumber,
    hashNumber
);;
    if (mht->ht == NULL) {
        free(mht);
        return NULL;
    }
    // Assign function pointers
    mht->printValue = printValue;
    mht->printKey = printKey;
    mht->copyValue = copyValue;
    mht->equalValue = equalValue;
    mht->freeValue = freeValue;
    mht->freeKey = freeKey;
    mht->copyKey = copyKey;
    return mht; // Return the created MultiValueHashTable

}
// Destroys the MultiValueHashTable and frees all memory
status destroyMultiValueHashTable(MultiValueHashTable mht) {
    if (mht == NULL) {
        return failure;
    }
    // Destroy the base hash table
    status d_status = destroyHashTable(mht->ht);
    if (d_status == failure) {
        return failure;
    }
    // Free the MultiValueHashTable structure
    free(mht);
    return success;
}
// Adds a key-value pair to the MultiValueHashTable
status addToMultiValueHashTable(MultiValueHashTable mht,Element key, Element value) {
    if (mht == NULL|| key == NULL || value == NULL) {
        return failure;
    }
    // Lookup the list of values associated with the key
    Element value_list = lookupInHashTable(mht->ht,key);
    if (value_list == NULL) {
        // If no list exists, create a new linked list
        linkedlist new_list = createLinkedList(mht->copyValue,mht->freeValue,mht->printValue,mht->equalValue);
        if (new_list == NULL) {
            return Memory_Problem;
        }
        // Add the value to the new list
        if (appendNode(new_list,value) == failure) {
            destroyLinkedList(new_list);
            return failure;
        }
        // Add the list to the base hash table
        if (addToHashTable(mht->ht, key, new_list) == failure) {
            destroyLinkedList(new_list);
            return failure;
        }
        return success;
    }
    if (appendNode(value_list,value) == failure) {
        return failure;
    }
    return success;
}

linkedlist lookupInMultiValueHashTable(MultiValueHashTable mht, Element key) {
    if (mht == NULL || key == NULL|| mht->ht == NULL) {
        return NULL;
    }
    // Lookup the linked list in the base hash table
    linkedlist list = lookupInHashTable(mht->ht,key);
    if (list == NULL) {
        return NULL;
    }
    return list;
}
// Removes a value associated with a key in the MultiValueHashTable
status removeFromMultiValueHashTable(MultiValueHashTable mht,Element key, Element value) {
    if (mht == NULL || key == NULL || value == NULL) {
        return failure;
    }
    // Lookup the list of values associated with the key
    linkedlist value_list = lookupInHashTable(mht->ht,key);
    if (value_list == NULL) {
        return Not_Exist;
    }
    deleteNode(value_list,value); // Remove the value from the list also free the memory
    if (getLength(value_list)== 0) {
        removeFromHashTable(mht->ht,key); // Remove the key if the list is empty
    }
    return success;
}

// Displays the values associated with a key in the MultiValueHashTable
status displayMultiValueHashElementsByKey(MultiValueHashTable mht, Element key) {
    if (mht == NULL || key == NULL || mht->ht == NULL) {
        return failure;
    }
    // Lookup the list of values associated with the key
    linkedlist list = lookupInHashTable(mht->ht,key);
    if (list == NULL) {
        return Not_Exist;
    }
    mht->printKey(key); // Print the key
    displayList(list); // Display all values in the list
    return success;
}