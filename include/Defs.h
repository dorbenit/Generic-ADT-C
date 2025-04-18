#ifndef DEFS_H_
#define DEFS_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum e_bool { false, true } bool;
typedef void * Element;
typedef enum e_status {
    Success,         // Indicates that the operation was completed successfully.
    Invlid_Input,    // Indicates that the input provided to the function was invalid (e.g., NULL pointer or out-of-bounds values).
    Memory_Problem,  // Indicates that a memory allocation or reallocation failed due to insufficient memory.
    Alreaqdy_Exist,  // Indicates that an item (e.g., characteristic or planet) already exists and cannot be added again.
    Not_Exist,       // Indicates that the requested item does not exist in the current data structures.
    zero_jerries,     // Indicates that there are no Jerries matching the requested condition (e.g., no Jerries from a specific planet or with a specific characteristic).
    success,
    failure
} status;
typedef Element(*CopyFunction) (Element);
typedef status(*FreeFunction) (Element);
typedef status(*PrintFunction) (Element);
typedef int(*TransformIntoNumberFunction) (Element);
typedef bool(*EqualFunction) (Element, Element);
#endif //DEFS_H