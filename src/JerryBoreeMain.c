#include "MultiValueHashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"
#include "Jerry.h"
#include "LinkedList.h"
#define MAX_SIZE 300
/***
 * Compares two string elements for equality.
 * @param str1 A pointer to the first string element.
 * @param str2 A pointer to the second string element.
 * @return true if both strings are equal, false otherwise.
 */
bool equalStrings(Element str1, Element str2) {
    if (str1 == NULL || str2 == NULL) return false;
    return strcmp((char*)str1, (char*)str2) == 0;
}
/**
 * Prints the name of a physical characteristic.
 * @param name A pointer to the characteristic name to print.
 * @return status indicating success or failure.
 */
status printPhysicalCharacteristic(Element name) {
    if (name == NULL) return failure; // Return failure if input is NULL
    char* characteristic_name = (char*)name;
    printf("%s : \n", characteristic_name); // Print the characteristic name
    return success; // Return success
}

/**
 * Creates a deep copy of a string.
 * @param str A pointer to the string to copy.
 * @return A pointer to the new string, or NULL if input is NULL or memory allocation fails.
 */
Element deepCopyString(Element str) {
    if (str == NULL) return NULL; // Return NULL if input is NULL

    char* original = (char*)str;
    size_t length = strlen(original) + 1; // Include null terminator

    char* copy = (char*)malloc(length * sizeof(char)); // Allocate memory
    if (copy == NULL) return NULL; // Return NULL if memory allocation fails

    strcpy(copy, original); // Copy the string content
    return (Element)copy; // Return the copied string
}

/**
 * Performs a shallow copy of an element.
 * @param element A pointer to the element to copy.
 * @return The same pointer, or NULL if the input is NULL.
 */
Element shallowCopyElement(Element element) {
    return element; // Return the pointer as-is
}



/**
 * Compares two Jerry objects for equality based on their IDs.
 * @param j1 A pointer to the first Jerry object.
 * @param j2 A pointer to the second Jerry object.
 * @return true if both IDs are equal, false otherwise.
 */
bool equalJerry(Element j1, Element j2) {
    if (j1 == NULL || j2 == NULL) return false; // Return false if either input is NULL
    Jerry* jerry1 = (Jerry*)j1; // Cast to Jerry
    Jerry* jerry2 = (Jerry*)j2; // Cast to Jerry
    return strcmp(jerry1->id, jerry2->id) == 0; // Compare IDs
}

/**
 * A fake free function that does nothing.
 * @param element A pointer to the element to "free".
 */
void fakeFree(Element element) {
    (void)element; // Do nothing; suppress unused parameter warnings
}

/**
 * Prints the ID of a Jerry object.
 * @param id A pointer to the Jerry ID to print.
 * @return status indicating success or failure.
 */
status printJerryID(Element id) {
    if (id == NULL) return failure; // Return failure if input is NULL
    printf("Jerry ID: %s\n", (char*)id); // Print the ID
    return success; // Return success
}

/**
 * Prints the name of a physical characteristic.
 * @param characteristic A pointer to the PhysicalCharacteristics object.
 * @return status indicating success or failure.
 */
status printCharacteristicName(Element characteristic) {
    if (characteristic == NULL) return failure; // Return failure if input is NULL
    PhysicalCharacteristics* pc = (PhysicalCharacteristics*)characteristic; // Cast to PhysicalCharacteristics
    if (pc->name == NULL) return failure; // Return failure if name is NULL
    printf("%s:\n", pc->name); // Print the characteristic name
    return success; // Return success
}

/**
 * Frees a dynamically allocated string.
 * @param str A pointer to the string to free.
 */
void freeString(Element str) {
    if (str != NULL) {
        free(str); // Free the allocated memory
    }
}


/**
 * Calculates the sum of ASCII values of the characters in a string.
 * @param str A pointer to the string element.
 * @return The sum of ASCII values of the characters in the string, or -1 if the input is NULL.
 */
int stringToAsciiSum(Element str) {
    if (str == NULL) {
        return -1; // Invalid input
    }
    char* string = (char*)str; // Convert the pointer to a string
    int sum = 0;
    while (*string != '\0') {
        sum += (int)(*string); // Calculate ASCII sum
        string++;
    }
    return sum;
}

/***
 * Reads a configuration file to populate the PlanetsManager and a linked list of Jerries.
 * @param file_name The name of the configuration file.
 * @param manager A pointer to the PlanetsManager for managing planets.
 * @param Jerries A linked list to store the Jerry objects.
 * @return Status indicating Success, Invalid_Input, or Memory_Problem.
 */
status read_configuration_file(char* file_name, PlanetsManager* manager,linkedlist Jerries) {

    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        return Invlid_Input;
    }
    char buffer[MAX_SIZE]; // Buffer to store each line from the file
    int reading_planets = 0;
    int reading_jerries = 0;

    while (fgets(buffer, sizeof(buffer), file) && memory_failure_sign == 0) {
        // Remove the newline character at the end of the line (if exists)
        buffer[strcspn(buffer, "\n")] = '\0';

        // Check for section headers
        if (strcmp(buffer, "Planets") == 0) {
            reading_planets = 1;
            reading_jerries = 0;
            continue;
        }
        if (strcmp(buffer, "Jerries") == 0) {
            reading_jerries = 1;
            reading_planets = 0;
            continue;
        }

        // Process planets
        if (reading_planets) {
            char planet_name[MAX_SIZE];
            double x, y, z;

            // Parse planet details
            if (sscanf(buffer, "%299[^,],%lf,%lf,%lf", planet_name, &x, &y, &z) == 4) {
                Planet* planet = create_planet(manager, planet_name, x, y, z);
                if (planet == NULL) break;
            }
        }
        // Process Jerries and their physical characteristics
        if (reading_jerries) {
            // Check if the line starts with a tab (indicating a characteristic)
            if (buffer[0] == '\t') {
                char characteristic_name[MAX_SIZE];
                double characteristic_value;

                // Parse the characteristic
                if (sscanf(buffer + 1, "%299[^:]:%lf", characteristic_name, &characteristic_value) == 2) {
                    PhysicalCharacteristics* characteristic = create_characteristic(characteristic_name, characteristic_value);
                    if (characteristic == NULL) break;
                    // Add the characteristic to the last added Jerry
                    Jerry* last_jerrey = getTailContent(Jerries);
                    status s = add_physical_characteristic(last_jerrey,characteristic);
                    if (s == Memory_Problem) break;
                }
            } else {
                // Parse Jerry details
                char id[MAX_SIZE];
                char dimension[MAX_SIZE];
                char planet_name[MAX_SIZE];
                int happiness;

                if (sscanf(buffer, "%299[^,],%299[^,],%299[^,],%d", id, dimension, planet_name, &happiness) == 4) {
                    //create new Jerry
                    Jerry* jerry = create_jerry(id, happiness,dimension, manager,planet_name, 0,0, 0 );
                    if (jerry == NULL) {
                        break;
                    }
                    // Add the new Jerry to the list
                   status s = appendNode(Jerries, jerry);
                   if (s == Memory_Problem ) {
                       memory_failure_sign = 1;
                   }

                }
            }
        }
    }
    fclose(file);
    // Handle memory failure
    if (memory_failure_sign == 1) {
        return Memory_Problem;
    }
    return Success; // Success
}
/**
 * Frees all allocated memory for Jerries and planets.
 * @param Jerries A linked list containing all Jerry objects to be freed.
 * @param manager A pointer to the PlanetsManager managing all planets to be destroyed.
 */
void go_home(linkedlist Jerries,PlanetsManager* manager) {
    // Free all Jerries and their associated memory
    destroyLinkedList(Jerries);
    destroy_all_planets(manager); // Free all planets
}
/**
 * Finds the next prime number greater than or equal to the given number.
 * @param n The starting number to find the next prime.
 * @return The next prime number.
 */
int nextPrime(int n) {
    if (n < 2) {
        return 2;
    }

    while (true) {
       bool is_prime = true; // Assume the number is prime
        if (n < 2) {
            is_prime = false;
        } else if (n == 2 || n == 3) {
            is_prime = true;
        } else if (n % 2 == 0) {
            is_prime = false;
        } else {
            // Check divisibility up to sqrt(n)
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    is_prime = false;
                    break;
                }
            }
        }

        if (is_prime) {
            return n;
        }
        n++;
    }
}

/**
 * Adds all Jerries from the linked list to the hash table.
 * @param jerryList A linked list containing Jerries.
 * @param ht A hash table to which the Jerries will be added.
 * @return status Success if all Jerries were added, failure otherwise.
 */
status addAllJerriesToHashTable(linkedlist jerryList, hashTable ht) {
    if (jerryList == NULL || ht == NULL) {
        return failure;  // Input validation
    }

    int listLength = getLength(jerryList);
    if (listLength == -1) {
        return failure; // Invalid list length
    }

    for (int i = 1; i <= listLength; i++) { // מעבר על כל האיברים ברשימה לפי אינדקס
        Jerry* jerry = (Jerry*)getDataByIndex(jerryList, i); // קבלת האיבר הנוכחי
        if (jerry == NULL) {
            continue;  // Skip if the Jerry is NULL
        }

        // הוספת ה-Jerry לטבלת ההאש
        if (addToHashTable(ht, jerry->id, jerry) == failure) {
            return failure; // Return failure if adding failed
        }
    }

    return success; // Success if all Jerries were added
}

/**
 * Adds all Jerry characteristics to a multi-value hash table.
 * @param jerryList A linked list containing Jerries.
 * @param mht A multi-value hash table to which the characteristics will be added.
 * @return status Success if all characteristics were added, failure otherwise.
 */
status addAllcharToMultiHashTable(linkedlist jerryList, MultiValueHashTable mht) {
    if (jerryList == NULL || mht == NULL) {
        return failure;
    }

    int listLength = getLength(jerryList);
    if (listLength == -1) {
        return failure;
    }

    for (int i = 1; i <= listLength; i++) {
        Jerry* jerry = (Jerry*)getDataByIndex(jerryList, i);
        if (jerry == NULL) {
            continue;
        }
        // Add each characteristic
        for(int j = 0; j < jerry->characteristics_count; j++) {
            if (addToMultiValueHashTable(mht,jerry->characteristics[j]->name,jerry)==failure) {
                return failure; // Return failure if adding failed
            }
        }

    }
    // Success if all characteristics were added
    return success;
}

/**
 * Calculates the total number of characteristics across all Jerries in the list.
 * @param jerryList A linked list containing Jerries.
 * @return The total number of characteristics.
 */
int sumJerryCharacteristicsCount(linkedlist jerryList) {
    if (jerryList == NULL) {
        return 0; // Return 0 if the list is NULL
    }

    int totalCharacteristics = 0;
    int listLength = getLength(jerryList);
    if (listLength < 1) {
        return 0; // Return 0 if the list length is invalid
    }

    for (int i = 1; i <= listLength; i++) {
        Jerry* jerry = (Jerry*)getDataByIndex(jerryList, i);
        if (jerry != NULL) {
            totalCharacteristics += jerry->characteristics_count; // Sum up characteristics
        }
    }

    return totalCharacteristics; // Return the total
}

/***
 * Cleans up all resources associated with the daycare system.
 * @param manager A pointer to the PlanetsManager containing all planet data.
 * @param Jerries A linked list containing all Jerries.
 * @param ht A hash table containing Jerries.
 * @param mht A multi-value hash table containing Jerry characteristics.
 */
void cleanAll(PlanetsManager* manager,linkedlist Jerries,hashTable ht,MultiValueHashTable mht) {
    destroyMultiValueHashTable(mht); // Free the multi-value hash table
    destroyHashTable(ht); // Free the hash table
    destroyLinkedList(Jerries); // Free the linked list of Jerries
    destroy_all_planets(manager); // Free all planet data
}

/**
 * Checks if a planet exists in the PlanetsManager by name.
 * @param manager Pointer to the PlanetsManager structure.
 * @param planet_name Name of the planet to check.
 * @return true if the planet exists, false otherwise.
 */
bool is_planet_exists(PlanetsManager* manager, char* planet_name) {
    if (manager == NULL || planet_name == NULL) {
        return false;
    }
    for (int i = 0; i < manager->count; i++) {
        if (manager->planets[i] != NULL && strcmp(manager->planets[i]->name, planet_name) == 0) {
            return true;
        }
    }

    return false;
}

/**
 * Deletes all physical characteristics of a given Jerry from the MultiValueHashTable.
 * @param mht Pointer to the MultiValueHashTable.
 * @param jerry Pointer to the Jerry whose characteristics will be deleted.
 * @return status Success if deletion succeeded, failure otherwise.
 */
status deleteAllJerryCHARACTERISTICS(MultiValueHashTable mht,Jerry* jerry) {
    if (jerry == NULL|| mht == NULL) {
        return failure;
    }
    for (int i = 0; i < jerry->characteristics_count; i++) {
        if (jerry->characteristics[i] != NULL) {
            removeFromMultiValueHashTable(mht,jerry->characteristics[i]->name,jerry);
        }
    }
    return success;
}
/**
 * Finds the Jerry with the closest value to the target for a specific characteristic.
 * @param jerryList A linked list containing Jerries.
 * @param characteristic_name Name of the characteristic to compare.
 * @param target_value Target value to find the closest match.
 * @return A pointer to the closest Jerry, or NULL if no match is found.
 */
Jerry* find_closest_jerry(linkedlist jerryList, char* characteristic_name, double target_value) {
    if (jerryList == NULL || characteristic_name == NULL) {
        return NULL;
    }

    Jerry* closest_jerry = NULL;
    double closest_diff = -1; // Initialize with a special negative marker
    int list_length = getLength(jerryList);
    for (int i = 1; i <= list_length; i++) {
        Jerry* current_jerry = (Jerry*)getDataByIndex(jerryList, i);
        if (current_jerry == NULL) {
            continue; // Skip if the current object is NULL
        }
        // Find the characteristic in the current Jerry
        PhysicalCharacteristics* characteristic = get_characteristic(current_jerry, characteristic_name);
        if (characteristic != NULL) {
            // Calculate the absolute difference
            double diff;
            if (characteristic->value > target_value) {
                diff = characteristic->value - target_value;
            } else {
                diff = target_value - characteristic->value;
            }

            // Update the closest Jerry if it's the first or closer than the previous
            if (closest_jerry == NULL || diff < closest_diff) {
                closest_diff = diff;
                closest_jerry = current_jerry;
            }
        }
    }
    // Return the closest Jerry
    return closest_jerry;
}

/**
 * Finds the saddest Jerry in a list.
 * @param Jerries A linked list containing Jerries.
 * @return A pointer to the saddest Jerry, or NULL if the list is empty.
 */
Jerry* find_the_saddest_jerry(linkedlist Jerries) {
    if (Jerries == NULL) {
        return NULL;
    }
    int list_length = getLength(Jerries);
    if (list_length <=0) {
        return NULL;
    }
    Jerry* most_sad_jerry = NULL;
    int lowest_happiness = 101; // Initialize above the maximum happiness
    for (int i = 1; i <= list_length; i++) {
        Jerry* current_jerry = (Jerry*)getDataByIndex(Jerries, i);
        if (current_jerry == NULL) {
            continue; // Skip if the current object is NULL
        }
        int happiness = current_jerry->happiness;
        if (happiness < lowest_happiness) {
            lowest_happiness = happiness;
            most_sad_jerry = current_jerry;
        }
    }
    return most_sad_jerry;
}
/**
 * Prints all planets in the PlanetsManager.
 * @param manager Pointer to the PlanetsManager structure.
 * @return status Success if all planets were printed, Not_Exist if no planets exist.
 */
status print_all_planets(PlanetsManager* manager) {
    if (manager == NULL||manager->planets == NULL||manager->count == 0) {
        return Not_Exist; // No planets to print
    }
    for (int i = 0; i < manager->count; i++) {
        print_planet(manager->planets[i]); // Print each planet
    }
    return Success; // Successfully printed all planets
}

status interact_with_fake_beth(linkedlist Jerries) {
    if (Jerries == NULL) {
        printf("The list of Jerries is empty!\n");
        return failure;
    }

    int list_length = getLength(Jerries);
    if (list_length <= 0) {
        printf("No Jerries to interact with!\n");
        return failure;
    }

    for (int i = 1; i <= list_length; i++) {
        Jerry* current_jerry = (Jerry*)getDataByIndex(Jerries, i);
        if (current_jerry == NULL) {
            continue; // Skip invalid entries
        }

        if (current_jerry->happiness >= 20) {
            current_jerry->happiness += 15;
            if (current_jerry->happiness > 100) {
                current_jerry->happiness = 100; // Limit to 100
            }
        } else {
            current_jerry->happiness -= 5;
            if (current_jerry->happiness < 0) {
                current_jerry->happiness = 0;  // Limit to 0
            }
        }

    }
    displayList(Jerries);
    return success;
}

status play_golf_with_jerries(linkedlist Jerries) {
    if (Jerries == NULL) {
        return failure;
    }

    int list_length = getLength(Jerries);
    if (list_length <= 0) {
        return failure;
    }

    for (int i = 1; i <= list_length; i++) {
        Jerry* current_jerry = (Jerry*)getDataByIndex(Jerries, i);
        if (current_jerry == NULL) {
            continue; // Skip invalid entries
        }

        if (current_jerry->happiness >= 50) {
            current_jerry->happiness += 10;
            if (current_jerry->happiness > 100) {
                current_jerry->happiness = 100; // Limit to 100
            }
        } else {
            current_jerry->happiness -= 10;
            if (current_jerry->happiness < 0) {
                current_jerry->happiness = 0;  // Limit to 0
            }
        }

    }
    // Display the updated list
    displayList(Jerries);
    return success;
}

status adjust_tv_picture_settings(linkedlist Jerries) {
    if (Jerries == NULL) {
        return failure;
    }

    int list_length = getLength(Jerries);
    if (list_length <= 0) {
        return failure;
    }

    for (int i = 1; i <= list_length; i++) {
        Jerry* current_jerry = (Jerry*)getDataByIndex(Jerries, i);
        if (current_jerry == NULL) {
            continue; // Skip invalid entries
        }

        current_jerry->happiness += 20;
        if (current_jerry->happiness > 100) {
            current_jerry->happiness = 100; // Limit to 100
        }
    }
    // Display the updated list
    displayList(Jerries);
    return success;
}
/**
 * Handles adding a new Jerry to the daycare.
 * @param manager A pointer to the PlanetsManager for managing planets.
 * @param Jerries A linked list of all Jerries in the daycare.
 * @param ht A hash table for Jerry lookups by ID.
 * @return Status indicating success, memory problems, invalid input, or if the Jerry already exists.
 */
status handle_case_1(PlanetsManager* manager, linkedlist Jerries, hashTable ht) {
    printf("What is your Jerry's ID ? \n");
                char id[MAX_SIZE];
                if (scanf("%s", id) != 1) {
                    while (getchar() != '\n'); // Clear invalid input
                    return Invlid_Input;
                }
                // Find the Jerry by ID
                Jerry* jerry = lookupInHashTable(ht,id);
                if (jerry != NULL) {
                    printf("Rick did you forgot ? you already left him here ! \n");
                    while (getchar() != '\n');
                    return Not_Exist;
                }
                printf("What planet is your Jerry from ? \n");
                char planet_name[MAX_SIZE];
                if (scanf("%s", planet_name) != 1) {
                    while (getchar() != '\n');
                    return Invlid_Input;
                }
                if (!is_planet_exists(manager,planet_name)) {
                    printf("%s is not a known planet ! \n",planet_name);
                    while (getchar() != '\n');
                    return Not_Exist;
                }
                printf("What is your Jerry's dimension ? \n");
                char dimension[MAX_SIZE];
                if (scanf("%s", dimension) != 1) {
                    while (getchar() != '\n');
                    return Invlid_Input;
                }
                printf("How happy is your Jerry now ? \n");
                int happiness;
                if (scanf("%d", &happiness) != 1) {
                    while (getchar() != '\n');
                    return Invlid_Input;
                }
                if (happiness > 100) {
                    happiness = 100;
                } else if (happiness < 0) {
                    happiness = 0;
                }
                Jerry* new_jerry = create_jerry(id,happiness,dimension,manager, planet_name,0,0,0);
                if(appendNode(Jerries,new_jerry)== failure) {
                    memory_failure_sign = 1;
                    return Memory_Problem;
                };
                if(addToHashTable(ht,new_jerry->id,new_jerry)== failure) {
                    memory_failure_sign = 1;
                    return Memory_Problem;
                };
                print_jerry(new_jerry);
                while (getchar() != '\n');
                return success;
}
/**
 * Handles adding a physical characteristic to an existing Jerry.
 * @param ht A hash table for Jerry lookups by ID.
 * @param mht A multi-value hash table for managing physical characteristics.
 * @return Status indicating success, memory problems, invalid input, or if the characteristic already exists.
 */
status handle_case_2(hashTable ht,MultiValueHashTable mht) {
    printf("What is your Jerry's ID ? \n");
    char id[MAX_SIZE];
    if (scanf("%s", id) != 1) {
        while (getchar() != '\n'); // Clear invalid input
        return Invlid_Input;
    }
    Jerry* jerry = lookupInHashTable(ht,id);
    if (jerry == NULL) {
        printf("Rick this Jerry is not in the daycare ! \n");
        while (getchar() != '\n');
        return Not_Exist;
    }
    printf("What physical characteristic can you add to Jerry - %s ? \n",id);
    char characteristic_name[MAX_SIZE];
    if (scanf("%s", characteristic_name) != 1) {
        while (getchar() != '\n');
        return Invlid_Input;
    }
    if(does_characteristic_exist(jerry,characteristic_name)) {
        printf("The information about his %s already available to the daycare ! \n",characteristic_name);
        while (getchar() != '\n');
        return Alreaqdy_Exist;
    }
    printf("What is the value of his %s ? \n",characteristic_name);
    double value;
    if (scanf("%lf", &value) != 1) {
        while (getchar() != '\n');
        return Invlid_Input;
    }
    PhysicalCharacteristics* physicalCharacteristics = create_characteristic(characteristic_name,value);
    add_physical_characteristic(jerry,physicalCharacteristics);
    if(addToMultiValueHashTable(mht,physicalCharacteristics->name,jerry)== failure) {
        memory_failure_sign = 1;
        return Memory_Problem;
    };
    displayMultiValueHashElementsByKey(mht,physicalCharacteristics->name);
    while (getchar() != '\n');
    return success;

}
/**
 * Handles removing a physical characteristic from an existing Jerry.
 * @param ht A hash table for Jerry lookups by ID.
 * @param mht A multi-value hash table for managing physical characteristics.
 * @return Status indicating success, memory problems, invalid input, or if the characteristic does not exist.
 */
status handle_case_3(hashTable ht,MultiValueHashTable mht) {
    printf("What is your Jerry's ID ? \n");
    char id[MAX_SIZE];
    if (scanf("%s", id) != 1) {
        while (getchar() != '\n');
        return Invlid_Input;
    }

    Jerry* jerry = lookupInHashTable(ht,id);
    if (jerry == NULL) {
        printf("Rick this Jerry is not in the daycare ! \n");
        while (getchar() != '\n');
        return Not_Exist;
    }
    printf("What physical characteristic do you want to remove from Jerry - %s ? \n",id);
    char characteristic_name[MAX_SIZE];
    if (scanf("%s", characteristic_name) != 1) {
        while (getchar() != '\n');
        return Invlid_Input;
    }
    PhysicalCharacteristics* characteristic_ptr = NULL;
    if(!does_characteristic_exist(jerry,characteristic_name)) {
        printf("The information about his %s not available to the daycare ! \n",characteristic_name);
        while (getchar() != '\n');
        return Not_Exist;
    }
    if(removeFromMultiValueHashTable(mht,characteristic_name,jerry)== failure) {
        memory_failure_sign = 1;
        return Memory_Problem;
    };
    remove_physical_characteristic(jerry,characteristic_name);
    print_jerry(jerry);
    while (getchar() != '\n');
    return success;
}
/**
 * Handles removing a Jerry from the daycare, including all its characteristics.
 * @param Jerries A linked list of all Jerries in the daycare.
 * @param ht A hash table for Jerry lookups by ID.
 * @param mht A multi-value hash table for managing physical characteristics.
 * @return Status indicating success or if the Jerry does not exist.
 */
status handle_case_4(linkedlist Jerries,hashTable ht,MultiValueHashTable mht) {
    printf("What is your Jerry's ID ? \n");
    char id[MAX_SIZE];
    if (scanf("%s", id) != 1) {
        while (getchar() != '\n');
        return Invlid_Input;
    }
    Jerry* jerry = lookupInHashTable(ht,id);
    if (jerry == NULL) {
        printf("Rick this Jerry is not in the daycare ! \n");
        while (getchar() != '\n');
        return Not_Exist;
    }
    deleteAllJerryCHARACTERISTICS(mht,jerry);
    removeFromHashTable(ht,jerry->id);
    deleteNode(Jerries,jerry);
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
    while (getchar() != '\n');
    return success;
}
/**
 * Handles finding the closest match for a Jerry based on a physical characteristic.
 * @param Jerries A linked list of all Jerries in the daycare.
 * @param ht A hash table for Jerry lookups by ID.
 * @param mht A multi-value hash table for managing physical characteristics.
 * @return Status indicating success, memory problems, or if no match is found.
 */
status handle_case_5(linkedlist Jerries, hashTable ht,MultiValueHashTable mht) {
    printf("What do you remember about your Jerry ? \n");
    char characteristic_name[MAX_SIZE];
    if (scanf("%s", characteristic_name) != 1) {
        while (getchar() != '\n');
        return Invlid_Input;
    }
    linkedlist value_list = lookupInMultiValueHashTable(mht,characteristic_name);
    if (value_list == NULL) {
        printf("Rick we can not help you - we do not know any Jerry's %s ! \n",characteristic_name);
        while (getchar() != '\n');
        return Not_Exist;
    }

    printf("What do you remember about the value of his %s ? \n",characteristic_name);
    double value;
    if (scanf("%lf", &value) != 1) {
        while (getchar() != '\n');
        return Invlid_Input;
    }
    Jerry* close_jerry = find_closest_jerry(value_list,characteristic_name,value);
    printf("Rick this is the most suitable Jerry we found : \n");
    print_jerry(close_jerry);
    deleteAllJerryCHARACTERISTICS(mht,close_jerry);
    removeFromHashTable(ht,close_jerry->id);
    deleteNode(Jerries,close_jerry);
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
    while (getchar() != '\n');
    return success;
}
/**
 * Handles finding and removing the saddest Jerry in the daycare.
 * @param Jerries A linked list of all Jerries in the daycare.
 * @param ht A hash table for Jerry lookups by ID.
 * @param mht A multi-value hash table for managing physical characteristics.
 * @return Status indicating success or if no Jerries are in the daycare.
 */
status handle_case_6(linkedlist Jerries, hashTable ht,MultiValueHashTable mht) {
    if (getLength(Jerries) < 1) {
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return zero_jerries;
    }
    Jerry* jerry = find_the_saddest_jerry(Jerries);
    printf("Rick this is the most suitable Jerry we found : \n");
    print_jerry(jerry);
    deleteAllJerryCHARACTERISTICS(mht,jerry);
    removeFromHashTable(ht,jerry->id);
    deleteNode(Jerries,jerry);
    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
    return success;
}
/**
 * Handles displaying daycare information based on user choice.
 * @param manager A pointer to the PlanetsManager for managing planets.
 * @param Jerries A linked list of all Jerries in the daycare.
 * @param mht A multi-value hash table for managing physical characteristics.
 */
void handle_case_7(PlanetsManager* manager, linkedlist Jerries, MultiValueHashTable mht) {
    while (true) {
        printf("What information do you want to know ? \n");
        printf("1 : All Jerries \n");
        printf("2 : All Jerries by physical characteristics \n");
        printf("3 : All known planets \n");

        char input[MAX_SIZE];
        if (fgets(input, MAX_SIZE, stdin) == NULL) {
            printf("Rick this option is not known to the daycare ! \n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline
        if (strlen(input) != 1 || input[0] < '1' || input[0] > '3') {
            printf("Rick this option is not known to the daycare ! \n");
            break;
        }
        int choice7 = input[0] - '0';

        switch (choice7) {
            case 1: {
                if (getLength(Jerries) < 1) {
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                displayList(Jerries);
                break;
            }
            case 2: {
                printf("What physical characteristics ? \n");
                char characteristic_name[MAX_SIZE];
                if (scanf("%s", characteristic_name) != 1) {
                    while (getchar() != '\n'); // Clear input buffer
                    break;
                }
                linkedlist value_list = lookupInMultiValueHashTable(mht, characteristic_name);
                if (value_list == NULL) {
                    printf("Rick we can not help you - we do not know any Jerry's %s ! \n", characteristic_name);
                    while (getchar() != '\n');
                    break;
                }
                displayMultiValueHashElementsByKey(mht, characteristic_name);
                while (getchar() != '\n');
                break;
            }
            case 3: {
                print_all_planets(manager);
                break;
            }
        }
        break; // Exit the while loop after handling the choice
    }
}
/**
 * Handles engaging Jerries in activities based on user choice.
 * @param Jerries A linked list of all Jerries in the daycare.
 */
void handle_case_8(linkedlist Jerries) {
    while (true) {
        if (getLength(Jerries) < 1) {
            printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
            break;
        }
        printf("What activity do you want the Jerries to partake in ? \n");
        printf("1 : Interact with fake Beth \n");
        printf("2 : Play golf \n");
        printf("3 : Adjust the picture settings on the TV \n");

        char input[MAX_SIZE];
        if (fgets(input, MAX_SIZE, stdin) == NULL) {
            printf("Rick this option is not known to the daycare ! \n");
            break;
        }
        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline
        if (strlen(input) != 1 || input[0] < '1' || input[0] > '3') {
            printf("Rick this option is not known to the daycare ! \n");
            break;
        }
        int choice8 = input[0] - '0';
        switch (choice8) {
            case 1: {
                printf("The activity is now over ! \n");
                interact_with_fake_beth(Jerries);
                break;
            }
            case 2: {
                printf("The activity is now over ! \n");
                play_golf_with_jerries(Jerries);
                break;
            }
            case 3: {
                printf("The activity is now over ! \n");
                adjust_tv_picture_settings(Jerries);
                break;
            }
        }
        break; // Exit the while loop after one activity
    }
}





void menu(PlanetsManager* manager,linkedlist Jerries,hashTable ht,MultiValueHashTable mht) {
    while (true) {
        if (memory_failure_sign == 1) {
            printf("Memory Problem\n");
            cleanAll(manager,Jerries,ht,mht);
            exit(0);
        }

        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");

        char input[MAX_SIZE];
        if (fgets(input, MAX_SIZE, stdin) == NULL) {
            printf("Rick this option is not known to the daycare ! \n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) != 1 || input[0] < '1' || input[0] > '9') {
            printf("Rick this option is not known to the daycare ! \n");
            continue;
        }
        int choice = input[0] - '0';

        switch (choice) {
            case 1: {
                handle_case_1(manager, Jerries, ht);
                break;

            }
            case 2: {
                handle_case_2(ht,mht);
                break;

            }

            case 3: {
                handle_case_3(ht,mht);
                break;
            }
            case 4: {
                handle_case_4(Jerries,ht,mht);
                break;
            }
            case 5: {
                handle_case_5(Jerries,ht,mht);
                break;
            }
            case 6: {
                handle_case_6(Jerries,ht,mht);
                break;
            }
            case 7: {
                handle_case_7(manager,Jerries,mht);
                break;

            }
            case 8: {
                handle_case_8(Jerries);
                break;
            }


            case 9: {
                    cleanAll(manager,Jerries,ht,mht);
                    printf("The daycare is now clean and close ! \n");
                    exit(0);
                }

            }

        }
    }
int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }
    // Parse input arguments
    int number_of_planets = atoi(argv[1]);
    char* configuration_file = argv[2];

    // Initialize PlanetsManager and Jerries array
    PlanetsManager manager = {NULL, 0};

    // Initialize PlanetsManager and the linked list for Jerries
    linkedlist Jerries = createLinkedList( (CopyFunction)shallowCopyElement,
    (FreeFunction)destroy_jerry,
    (PrintFunction)print_jerry,
    (EqualFunction)equalJerry
   );
    if (Jerries == NULL) {
        fprintf(stdout, "Memory Problem\n");
        // No memory has been allocated yet, so nothing to clean up
        return 1;
    }
    // Read the configuration file and populate the data structures
    status s = read_configuration_file(configuration_file, &manager,Jerries);

    // Exit the program and clean up all allocated memory if there is a memory problem
    if (s == Memory_Problem || memory_failure_sign) {
        fprintf(stdout, "Memory Problem\n");
        go_home(Jerries,&manager);
        return 1;
    }
    // Compute hash table sizes based on the number of Jerries and characteristics
    int hashSize;
    hashSize = nextPrime(getLength(Jerries));
    if (hashSize<3) {
        hashSize = 11; // Good defult number
    }
    int total_characteristics = sumJerryCharacteristicsCount(Jerries);
    int multihashsize = nextPrime(total_characteristics);
    if(multihashsize < hashSize) {
        multihashsize = hashSize;
    }
    // Create hash table for Jerry objects
    hashTable ht = createHashTable((CopyFunction)deepCopyString,(FreeFunction)freeString,(PrintFunction)printJerryID,(CopyFunction)shallowCopyElement,(FreeFunction)fakeFree,(PrintFunction)print_jerry,(EqualFunction)equalStrings,(TransformIntoNumberFunction)stringToAsciiSum,hashSize);
    if(ht == NULL) {
        fprintf(stdout, "Memory Problem\n");
        go_home(Jerries,&manager);
        return 1;
    }
    // Create multi-value hash table for physical characteristics
    MultiValueHashTable mht = createMultiValueHashTable((CopyFunction)deepCopyString,(FreeFunction) freeString,(PrintFunction) printPhysicalCharacteristic,(CopyFunction)shallowCopyElement,(FreeFunction) fakeFree,(PrintFunction)print_jerry,(EqualFunction)equalStrings,(EqualFunction)equalJerry,(TransformIntoNumberFunction)stringToAsciiSum,multihashsize);
    if(mht == NULL) {
        fprintf(stdout, "Memory Problem\n");
        cleanAll(&manager,Jerries,ht,mht);
        return 1;
    }
    if(addAllJerriesToHashTable(Jerries,ht)==failure) {
        fprintf(stdout, "Memory Problem\n");
        cleanAll(&manager,Jerries,ht,mht);
        return 1;
    }
    if(addAllcharToMultiHashTable(Jerries,mht)==failure) {
        fprintf(stdout, "Memory Problem\n");
        cleanAll(&manager,Jerries,ht,mht);
        return 1;
    }
    // Display the menu for user interaction
    menu(&manager,Jerries,ht,mht);
     return 0;
}