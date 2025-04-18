#ifndef MultiValueHashTable_H
#define MultiValueHashTable_H
#include "Defs.h"
#include "LinkedList.h"
typedef struct MultiValueHashTable_s* MultiValueHashTable;
/**
 * Creates a multi-value hash table that associates keys with multiple values.
 * This is implemented as a hash table where each key maps to a linked list of values.
 *
 * @param copyKey Function to copy a key.
 * @param freeKey Function to free a key.
 * @param printKey Function to print a key.
 * @param copyValue Function to copy a value.
 * @param freeValue Function to free a value.
 * @param printValue Function to print a value.
 * @param equalKey Function to compare keys for equality.
 * @param equalValue Function to compare values for equality.
 * @param transformIntoNumber Function to transform a key into a hash number.
 * @param hashNumber The number of buckets in the hash table.
 *
 * @return A pointer to the created multi-value hash table, or NULL if creation fails.
 */
MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                                              CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
                                              EqualFunction equalKey, EqualFunction equalValue,
                                              TransformIntoNumberFunction transformIntoNumber, int hashNumber);

/**
 * Destroys a multi-value hash table and frees all associated memory.
 *
 * @param mht The multi-value hash table to destroy.
 *
 * @return Status indicating success or failure.
 */
status destroyMultiValueHashTable(MultiValueHashTable mht);

/**
 * Adds a value to the multi-value hash table under the specified key.
 * If the key does not exist, it creates a new entry with the key and associates the value with it.
 *
 * @param mht The multi-value hash table.
 * @param key The key to which the value will be associated.
 * @param value The value to add.
 *
 * @return Status indicating success or failure.
 */
status addToMultiValueHashTable(MultiValueHashTable mht, Element key, Element value);

/**
 * Looks up the list of values associated with a specific key in the multi-value hash table.
 *
 * @param mht The multi-value hash table.
 * @param key The key to look up.
 * @return A pointer to the linked list of values associated with the key, or NULL if the key does not exist.
 */
linkedlist lookupInMultiValueHashTable(MultiValueHashTable mht, Element key);

/**
 * Removes a specific value associated with a key in the multi-value hash table.
 * If the value is the last one associated with the key, the key is also removed from the table.
 * @param mht The multi-value hash table.
 * @param key The key from which the value will be removed.
 * @param value The value to remove.
 *
 * @return Status indicating success or failure.
 */
status removeFromMultiValueHashTable(MultiValueHashTable mht, Element key, Element value);

/**
 * Displays all values associated with a specific key in the multi-value hash table.
 *
 * @param mht The multi-value hash table.
 * @param key The key whose associated values will be displayed.
 *
 * @return Status indicating success or failure.
 */
status displayMultiValueHashElementsByKey(MultiValueHashTable mht, Element key);
#endif