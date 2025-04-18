#ifndef KeyValuePair_h
#define KeyValuePair_h
#include "Defs.h"
typedef struct key_value_pair_s *KeyValuePair;
/**
 * Creates a new key-value pair with the given key and value.
 *
 * @param copyKey A function to copy the key.
 * @param freeKey A function to free the memory of the key.
 * @param printKey A function to print the key.
 * @param equalKey A function to compare two keys for equality.
 * @param copyValue A function to copy the value.
 * @param freeValue A function to free the memory of the value.
 * @param printValue A function to print the value.
 * @param key The key to be stored in the pair.
 * @param value The value to be stored in the pair.
 * @return A pointer to the created key-value pair, or NULL on failure.
 */
KeyValuePair createKeyValuePair(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,EqualFunction equalKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, Element key,Element value);
/**
 * Destroys a key-value pair and frees its associated memory.
 *
 * @param pair The key-value pair to destroy.
 * @return Status indicating success or failure.
 */
status destroyKeyValuePair(KeyValuePair pair);
/**
 * Displays the value in the key-value pair.
 *
 * @param pair The key-value pair whose value should be displayed.
 * @return Status indicating success or failure.
 */
status displayValue(KeyValuePair pair);
/**
 * Displays the key in the key-value pair.
 *
 * @param pair The key-value pair whose key should be displayed.
 * @return Status indicating success or failure.
 */
status displayKey(KeyValuePair pair);

/**
 * Retrieves the value from the key-value pair.
 *
 * @param pair The key-value pair to retrieve the value from.
 * @return A copy of the value stored in the pair.
 * @note If you provided a deep copy function, it is your responsibility to free the returned value.
 */
Element getValue(KeyValuePair pair);
/**
 * Retrieves the key from the key-value pair.
 *
 * @param pair The key-value pair to retrieve the value from.
 * @return A copy of the value stored in the pair.
 * @note If you provided a deep copy function, it is your responsibility to free the returned key.
 */
Element getKey(KeyValuePair pair);
/**
 * Checks if the given key matches the key in the key-value pair.
 *
 * @param pair The key-value pair to check.
 * @param key The key to compare.
 * @return True if the keys are equal, false otherwise.
 */
bool isEqualKey(KeyValuePair pair,Element key);
/**
 * Displays the entire key-value pair (key and value).
 *
 * @param pair_element The key-value pair to display.
 * @return Status indicating success or failure.
 */
status displayKeyValuePair(Element pair_element);
#endif