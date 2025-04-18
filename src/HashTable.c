#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "KeyValuePair.h"
#include "HashTable.h"
struct hashTable_s {
    int size;
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction equalKey;
    TransformIntoNumberFunction transformIntoNumber;
    linkedlist* table;

};
KeyValuePair copyKeyValuePair(KeyValuePair pair_element) {
    if (pair_element == NULL) {
        return NULL;
    }
    //is allready copy by key and value before so also for deep and shallow copy  we can return just the pair.
    return pair_element;
}
/**
 * @brief Checks if the key extracted from a pair matches a given key.
 *
 * @param pair A pointer to the pair element (must contain a key).
 * @param key  A pointer to the key element to compare against.
 *
 * @return true if the key extracted from the pair matches the given key, false otherwise.
 *         Returns false if either pair or key is NULL.
 */
static bool EqualPairWithKey(Element pair,Element key) {
    if (pair == NULL|| key == NULL) {
        return false;
    }
    if (isEqualKey(pair,key)) {
        return true;
    }
    return false;
}



// Calculates the index in the hash table for a given key
static int calculateHashIndex(hashTable ht, Element key) {
    int transformedNumber = ht->transformIntoNumber(key); // Transform the key into a number

    if (transformedNumber < 0) {
        // Ensure the number is positive
        transformedNumber = -transformedNumber;
    }

    return transformedNumber % ht->size; // Modulo operation to map to bucket
}

hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber) {
    if(copyKey == NULL|| freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL|| printValue == NULL || equalKey == NULL || transformIntoNumber == NULL|| hashNumber < 1) {
        return NULL;
    }
    hashTable ht = malloc(sizeof(struct hashTable_s));
    if (ht == NULL) {
        return NULL;
    }
    ht->table = (linkedlist*)malloc(hashNumber * sizeof(linkedlist));
    if (ht->table == NULL) {
        free(ht);
        return NULL; // Memory allocation for table array failed
    }
    ht->size = hashNumber;
    ht->copyKey = copyKey;
    ht->freeKey = freeKey;
    ht->printKey = printKey;
    ht->copyValue = copyValue;
    ht->freeValue = freeValue;
    ht->printValue = printValue;
    ht->equalKey = equalKey;
    ht->transformIntoNumber = transformIntoNumber;

    // Initialize each bucket with an empty linked list
    for (int i = 0; i < hashNumber; i++) {
        ht->table[i] = createLinkedList(
            (CopyFunction)copyKeyValuePair,
            (FreeFunction)destroyKeyValuePair,
            (PrintFunction)displayKeyValuePair,
            (EqualFunction)EqualPairWithKey
        );
        if (ht->table[i] == NULL) {
            destroyHashTable(ht); // Clean up if list creation fails
            return NULL;;
        }


    }
    return ht;
}
// Adds a key-value pair to the hash table
status addToHashTable(hashTable ht, Element key, Element value) {
    if (key == NULL || value == NULL || ht == NULL) {
        return failure;
    }
    int index = calculateHashIndex(ht, key);
    if (index < 0 || index >= ht->size) {
        return failure;
    }

    linkedlist list = ht->table[index];
    if (list == NULL) {
        return failure;
    }

    // Check if the key already exists
    Element existingElement = searchByKeyInList(list, key);
    if (existingElement != NULL) {
        return failure;
    }

    // Create a new key-value pair
    KeyValuePair pair = createKeyValuePair(
        ht->copyKey, ht->freeKey, ht->printKey,
        ht->equalKey, ht->copyValue, ht->freeValue, ht->printValue,
        key, value
    );
    if (pair == NULL) {
        return failure; // Memory allocation failed
    }

    // Append the new pair to the bucket
    if (appendNode(list, pair) == failure) {
        destroyKeyValuePair(pair);
        return failure;
    }

    return success;
}


status destroyHashTable(hashTable ht) {
    if(ht == NULL) return failure;
    if (ht->table == NULL) {
        free(ht); // Free the hash table structure if no buckets are allocated
        return success;
    }
    // Destroy each linked list in the table
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i] != NULL) {
            destroyLinkedList(ht->table[i]);
        }
    }
    free(ht->table); // Free the table array
    free(ht); // Free the hash table structure
    return success;


}

Element lookupInHashTable(hashTable ht, Element key) {
    if (key == NULL || ht == NULL || ht->table == NULL) {
        return NULL;
    }
    int index = calculateHashIndex(ht, key);
    linkedlist list = ht->table[index];
    if (list == NULL) {
        return NULL; // Bucket is empty
    }
    KeyValuePair pair = (KeyValuePair)searchByKeyInList(list, key);
    if (pair == NULL) {
        return NULL;
    }
    return getValue(pair); // Return the value associated with the key
}

status removeFromHashTable(hashTable ht, Element key) {
    if (key == NULL || ht == NULL || ht->table == NULL) {
        return failure;
    }
    int index = calculateHashIndex(ht, key);
    linkedlist list = ht->table[index];
    if (list == NULL) {
        return failure;  // Bucket is empty
    }
    deleteNode(ht->table[index], key);
    return success;
}

// Displays all elements in the hash table
status displayHashElements(hashTable ht) {
    if (ht == NULL || ht->table == NULL) {
        return failure;
    }
    // Iterate over each bucket and display its elements
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i] != NULL) {
            displayList(ht->table[i]);
        }
    }
    return success;
}