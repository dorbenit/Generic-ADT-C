//
// Created by dorbe on 30/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Jerry.h"
#include "Defs.h"

int memory_failure_sign = 0;


Origin* create_origin(Planet* planet, char* dimension) {
    // Validate input arguments
    if (planet == NULL || dimension == NULL) {
        return NULL; // Return NULL if either the planet or dimension is missing
    }
    // Allocate memory for the Origin structure
    Origin* new_origin = (Origin*)malloc(sizeof(Origin));
    if (new_origin == NULL) {
        memory_failure_sign = 1; // Signal memory allocation failure
        return NULL; // Return NULL if allocation fails
    }
    // Allocate memory for the dimension string
    new_origin->dimension = (char*)malloc(strlen(dimension) + 1);
    if (new_origin->dimension == NULL) {
        free(new_origin); // Free the previously allocated Origin structure
        memory_failure_sign = 1; // Signal memory allocation failure
        return NULL; // Return NULL if allocation fails
    }
    // Copy the dimension string into the newly allocated memory
    strcpy(new_origin->dimension, dimension);
    // Link the planet to the Origin structure
    new_origin->planet = planet;

    return new_origin; // Return a pointer to the newly created Origin
}

/**
 * Destroys an Origin object, freeing its memory.
 * @param origin Pointer to the Origin to destroy.
 */
void destroy_origin(Origin* origin) {
    if (origin == NULL) {
        return;
    }

    // Free the dimension string
    if (origin->dimension != NULL) {
        free(origin->dimension);
        origin->dimension = NULL; // Avoid use-after-free
    }

    // I'm not free the planet now, it is managed globally

    // Free the origin itself
    free(origin);
}

Jerry* create_jerry(char* id, int happiness,char* dimension,PlanetsManager* manager, char* name, double x, double y, double z ) {
    // Validate that the inputs are not NULL
    if (id == NULL || dimension == NULL || manager == NULL || name == NULL) {
        return NULL;
    }
    // Allocate memory for the Jerry structure
    Jerry* new_jerry = (Jerry*)malloc(sizeof(Jerry));
    if (new_jerry == NULL) {
        memory_failure_sign = 1; // Indicate memory allocation failure
        return NULL;
    }
    // Allocate memory for the ID string
    new_jerry->id = (char*)malloc(strlen(id) + 1); // +1 for the null terminator
    if (new_jerry->id == NULL) {
        memory_failure_sign = 1; // Indicate memory allocation failure
        free(new_jerry);         // Free already allocated memory for Jerry
        return NULL;
    }
    // Copy the given ID into the allocated memory
    strcpy(new_jerry->id, id);
    new_jerry->happiness = happiness; // Assign the happiness level
    Planet* new_planet = create_planet(manager,name,x,y,z); // create planet only if not exist yet, else only return pointer
    if (new_planet == NULL) {
        memory_failure_sign = 1;
        free(new_jerry->id);
        free(new_jerry);
        return NULL;
    }
    new_jerry->origin = create_origin(new_planet,dimension); // create new origin to jerry
    if (new_jerry->origin  == NULL) {
        memory_failure_sign = 1;
        free(new_jerry->id);
        free(new_jerry);
        return NULL;
    }
    new_jerry->characteristics = NULL;  // No characteristics yet
    new_jerry->characteristics_count = 0; // Set characteristics count to 0

    return new_jerry; // Return pointer to the new jerry
}

void destroy_jerry(Jerry* jerry) {
    // Check if the input pointer is NULL
    if (jerry == NULL) {
        return; // No need to proceed if Jerry doesn't exist
    }
    // Free the memory allocated for the Jerry's ID
    if (jerry->id != NULL) {
        free(jerry->id);
    }
    // Free the dynamic array of characteristics if it exists
    if (jerry->characteristics != NULL) {
        // Destroy each characteristic in the array
        for (int i = 0; i < jerry->characteristics_count; i++) {
            destroy_physical_characteristic(jerry->characteristics[i]);
        }
        // Free the array itself
        free(jerry->characteristics);
    }
    // Free the memory allocated for the origin, if it exists
    if (jerry->origin != NULL) {
        destroy_origin(jerry->origin);
    }
    // Finally, free the memory allocated for the Jerry structure itself
    free(jerry);
}

Planet* create_planet(PlanetsManager* manager,char* name, double x, double y, double z) {
    if (name == NULL) {
        return NULL;
    }
    // Check if the planet already exists in the plantes list
    if (manager->planets!=NULL) {
        for (int i = 0; i < manager->count ; i++) {
            if (strcmp(manager->planets[i]->name, name) == 0) {
                return manager->planets[i]; // return pointer to the planet if alredy exist
            }
        }
    }
    // Initialize the  list if it's NULL (for the first planet)
    if (manager->planets == NULL) {
       manager->planets = (Planet**)malloc(sizeof(Planet*));
        if (manager->planets == NULL) {
            memory_failure_sign = 1;
            return NULL;
        }
    } else {
        // Reallocate memory for the list to add a new planet
        Planet** temp = (Planet**)realloc(manager->planets, (manager->count + 1) * sizeof(Planet*));
        if (temp == NULL) {
            memory_failure_sign = 1;
            return NULL;
        }
        manager->planets = temp;
    }

    // Allocate memory for the new planet
    Planet* new_planet = (Planet*)malloc(sizeof(Planet));
    if (new_planet == NULL) {
        memory_failure_sign = 1;
        return NULL;
    }

    // Allocate memory for the planet name
    new_planet->name = (char*)malloc(strlen(name) + 1);
    if (new_planet->name == NULL) {
        free(new_planet);
        memory_failure_sign = 1;
        return NULL;
    }
    strcpy(new_planet->name, name);
    // Assign coordinates
    new_planet->x = x;
    new_planet->y = y;
    new_planet->z = z;

    // Add the new planet to the global list
    Planet** temp = realloc(manager->planets, (manager->count + 1) * sizeof(Planet*));
    if (temp == NULL) {
        free(new_planet->name);
        free(new_planet);
        memory_failure_sign = 1;
        return NULL;
    }
    manager->planets = temp;
    manager->planets[manager->count] = new_planet;
    manager->count++;
    return manager->planets[manager->count - 1]; // return the pointer to the new plant
}



// Frees the memory allocated for a single Planet object
void destroy_planet(Planet* planet) {
    if (planet == NULL) {
        return; // If the pointer is NULL, there is nothing to free
    }
    // Free the dynamically allocated name of the planet
    if (planet->name != NULL) {
        free(planet->name);
    }
    // Free the memory for the Planet structure itself
    free(planet);
}
void destroy_all_planets(PlanetsManager* manager) {
    // Check if the manager or its list is NULL
    if (manager == NULL || manager->planets == NULL) {
        return; // If there's nothing to free, exit the function
    }

    // Iterate through the list of planets and free each one
    for (int i = 0; i < manager->count; i++) {
        destroy_planet(manager->planets[i]); // Destroy each planet
    }
    // Free the array of pointers to planets

    free(manager->planets);
    // Reset the manager's fields
    manager->planets = NULL;
    manager->count = 0;
}





PhysicalCharacteristics* create_characteristic(char* name, double value) {
    // Validate input argument: name must not be NULL
    if (name == NULL) {
        return NULL; // Return NULL if name is missing
    }
    // Allocate memory for the PhysicalCharacteristics structure
    PhysicalCharacteristics* new_characteristic = (PhysicalCharacteristics*)malloc(sizeof(PhysicalCharacteristics));
    if (new_characteristic == NULL) {
        memory_failure_sign = 1; // Signal memory allocation failure
        return NULL; // Return NULL if allocation fails
    }
    // Allocate memory for the name string
    new_characteristic->name = (char*)malloc(strlen(name) + 1);
    if (new_characteristic->name == NULL) {
        free(new_characteristic); // Free the allocated structure on failure
        memory_failure_sign = 1; // Signal memory allocation failure
        return NULL; // Return NULL if allocation fails
    }
    // Copy the name into the allocated memory
    strcpy(new_characteristic->name, name);
    // Assign the value to the characteristic
    new_characteristic->value = value;
    // Return a pointer to the newly created PhysicalCharacteristics structure
    return new_characteristic;
}


bool does_characteristic_exist(Jerry* jerry, char* characteristic_name) {
    // Check if the input arguments are valid
    if (jerry == NULL || characteristic_name == NULL) {
        return false; // Return false if Jerry or characteristic_name is NULL
    }
    // Check if Jerry has no characteristics yet
    if (jerry->characteristics == NULL) {
        return false; // Return false as no characteristics exist
    }
    // Iterate over the characteristics to find a match
    for (int i = 0; i < jerry->characteristics_count; i++) {
        if (strcmp(jerry->characteristics[i]->name, characteristic_name) == 0) {
            return true; // Return true if the characteristic exists
        }
    }
    return false; // Return false if the characteristic is not found
}

PhysicalCharacteristics* get_characteristic(Jerry* jerry, char* characteristic_name) {
    if (jerry == NULL || characteristic_name == NULL) {
        return NULL;
    }

    for (int i = 0; i < jerry->characteristics_count; i++) {
        if (strcmp(jerry->characteristics[i]->name, characteristic_name) == 0) {
            return jerry->characteristics[i];
        }
    }
    return NULL;
}

status add_physical_characteristic(Jerry* jerry, PhysicalCharacteristics* characteristic) {
    // Check if the input arguments are valid
    if (jerry == NULL || characteristic == NULL) {
        return Invlid_Input; // Return invalid input if Jerry or characteristic is NULL
    }
    // Check if the characteristic already exists
    if (does_characteristic_exist(jerry, characteristic->name)) {
        return Alreaqdy_Exist; // Return already exists if the characteristic is found
    }
    // Allocate memory for the characteristics array if not already allocated
    if (jerry->characteristics == NULL) {
        jerry->characteristics = (PhysicalCharacteristics**)malloc(sizeof(PhysicalCharacteristics*));
        if (jerry->characteristics == NULL) {
            memory_failure_sign = 1; // Signal memory allocation failure
            return Memory_Problem; // Return memory problem status
        }
    } else {
        // Reallocate memory to add the new characteristic
        PhysicalCharacteristics** temp = (PhysicalCharacteristics**)realloc(
            jerry->characteristics,
            (jerry->characteristics_count + 1) * sizeof(PhysicalCharacteristics*)
        );
        if (temp == NULL) { // Check for memory allocation failure
            memory_failure_sign = 1; // Signal memory allocation failure
            return Memory_Problem; // Return memory problem status
        }
        jerry->characteristics = temp; // Update pointer to the new array
    }
    // Add the new characteristic to the array
    jerry->characteristics[jerry->characteristics_count] = characteristic;
    jerry->characteristics_count++; // Increment the count of characteristics
    return Success; // Return success status
}
void destroy_physical_characteristic(PhysicalCharacteristics* characteristic) {
    if (characteristic == NULL) {
        return; // Nothing to free if the pointer is NULL
    }
    // Free the dynamically allocated name
    free(characteristic->name);
    // Free the characteristic itself
    free(characteristic);
}
status remove_physical_characteristic(Jerry* jerry,  char* characteristic_name) {
    // Check for NULL inputs or uninitialized array
    if (jerry == NULL || characteristic_name == NULL|| jerry->characteristics == NULL) {
        return Invlid_Input;
    }
    // Check if characteristic exists
    if (!does_characteristic_exist(jerry, characteristic_name)) {
        return Not_Exist;
    }
    int index = -1;
    for (int i = 0; i <jerry->characteristics_count;i++) {
        if (strcmp(jerry->characteristics[i]->name, characteristic_name) == 0) {
            index = i;
            break; // Found the characteristic, exit loop
        }
    }
    // Free the memory of the characteristic being removed
    destroy_physical_characteristic(jerry->characteristics[index]);
    for (int i = index;i<jerry->characteristics_count-1;i++) {
        jerry->characteristics[i] = jerry->characteristics[i+1];
    }
    // Reduce the count of characteristics
    jerry->characteristics_count--;
    // Handle the case where the count is now zero

    if (jerry->characteristics_count == 0) {
        free(jerry->characteristics);
        jerry->characteristics = NULL;
        return Success;
    }
    // Reallocate memory
    PhysicalCharacteristics** temp = realloc(jerry->characteristics, (jerry->characteristics_count) * sizeof(PhysicalCharacteristics*));
    if (temp == NULL) {
        memory_failure_sign = 1;
        return Memory_Problem; // Array remains valid, but memory isn't reduced
    }
    jerry->characteristics = temp; // Update pointer to new array
    return Success;
}

status print_jerry(Jerry* jerry) {
    if (jerry == NULL || jerry->id == NULL) {
        return Invlid_Input;
    }
    // Print Jerry's ID & Happiness level
    printf("Jerry , ID - %s : \n", jerry->id);
    printf("Happiness level : %d \n", jerry->happiness);

    // Print Jerry's origin and planet details
    if (jerry->origin == NULL || jerry->origin->planet == NULL) {
        return Invlid_Input;
    }
    printf("Origin : %s \n", jerry->origin->dimension);
    printf("Planet : %s (%.2f,%.2f,%.2f) \n",
           jerry->origin->planet->name,
           jerry->origin->planet->x,
           jerry->origin->planet->y,
           jerry->origin->planet->z);

    // Print Jerry's physical characteristics only if they exist
    if (jerry->characteristics_count > 0 && jerry->characteristics != NULL) {
        printf("Jerry's physical Characteristics available : \n");
        printf("\t");

        // Print all characteristics on one line with proper spacing
        for (int i = 0; i < jerry->characteristics_count; i++) {
            if (i > 0) {
                printf(" , ");
            }
            if (i == jerry->characteristics_count - 1) {
                printf("%s : %.2f \n", jerry->characteristics[i]->name, jerry->characteristics[i]->value);
            } else {
                printf("%s : %.2f", jerry->characteristics[i]->name, jerry->characteristics[i]->value);
            }
        }
    }

    return Success;
}


status print_planet(Planet* planet) {
    if (planet == NULL || planet->name == NULL) {
        return Invlid_Input; // Invalid input
    }

    // Print the planet details in the specified format
    printf("Planet : %s (%.2f,%.2f,%.2f) \n",
           planet->name, planet->x, planet->y, planet->z);

    return Success; // Printing succeeded
}