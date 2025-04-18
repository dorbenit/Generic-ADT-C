#include <stdio.h>
#include <stdlib.h>
#include "KeyValuePair.h"
struct key_value_pair_s {
    Element key;
    Element value;
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    EqualFunction equalKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
};

KeyValuePair createKeyValuePair(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                               EqualFunction equalKey, CopyFunction copyValue, FreeFunction freeValue,
                               PrintFunction printValue, Element key, Element value) {

    if (copyKey == NULL || freeKey == NULL || printKey == NULL || copyValue == NULL || freeValue == NULL ||
        printValue == NULL || key == NULL || value == NULL) {
        return NULL;
        }

    // Allocate memory for the key-value pair
    KeyValuePair pair = (KeyValuePair)malloc(sizeof(struct key_value_pair_s));
    if (pair == NULL) {
        return NULL;
    }
    // Copy the key
    pair->key = copyKey(key);
    if (pair->key == NULL) {
        free(pair); // Free the pair if copying the key fails
        return NULL;
    }
    // Copy the value
    pair->value = copyValue(value);
    if (pair->value == NULL) {

        freeKey(pair->key); // Free the copied key
        free(pair); // Free the pair
        return NULL;
    }

    pair->copyKey = copyKey;
    pair->freeKey = freeKey;
    pair->printKey = printKey;
    pair->equalKey = equalKey;
    pair->copyValue = copyValue;
    pair->freeValue = freeValue;
    pair->printValue = printValue;

    return pair;
}


status destroyKeyValuePair(KeyValuePair pair) {
    if (pair == NULL) {
        return failure;
    }
    // Free the key if it exists
    if (pair->key != NULL&&  pair->freeKey!=NULL ) {
        pair->freeKey(pair->key);
    }
    // Free the value if it exists
    if (pair->value != NULL&&  pair->freeValue != NULL ) {
        pair->freeValue(pair->value);
    }
    // Free the pair structure itself
    free(pair);
    return success;
}

status displayValue(KeyValuePair pair) {
    if (pair == NULL|| pair->value == NULL) {
        return failure;
    }
    pair->printValue(pair->value); // Use the print function to display the value
    return success;
}

status displayKey(KeyValuePair pair) {
    if (pair == NULL|| pair->key == NULL) {
        return failure;
    }
    pair->printKey(pair->key); // Use the print function to display the key
    return success;
}

Element getValue(KeyValuePair pair) {
    if (pair == NULL|| pair->value == NULL) {
        return NULL;
    }
    return pair->value; // Return the value
}

Element getKey(KeyValuePair pair) {
    if (pair == NULL|| pair->key == NULL) {
        return NULL;
    }
    return pair->copyKey(pair); // Return the key
}

bool isEqualKey(KeyValuePair pair,Element key) {
    if(pair == NULL || key == NULL || pair->key == NULL||pair->equalKey == NULL) {
        return false;
    }
    return pair->equalKey(pair->key, key); // Use the comparison function

}

status displayKeyValuePair(Element pair_element) {
    if (pair_element == NULL) {
        return failure;
    }

    KeyValuePair pair = (KeyValuePair)pair_element;


    if (pair->key == NULL || pair->value == NULL) {
        return failure;
    }
    pair->printKey(pair->key);  // Display the key
    pair->printValue(pair->value); // Display the value
    return success;
}