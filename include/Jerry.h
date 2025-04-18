// Jerry.h
// This header file defines the main structures and functions used to manage Jerry objects, their characteristics, planets, and origins.

#ifndef JERRY_H
#define JERRY_H
#include "Defs.h"
// External flag to indicate memory problems
extern int memory_failure_sign;
// Structures
/**
 * Represents a planet in the universe.
 * Contains the planet's name and its coordinates in 3D space.
 */
typedef struct Planet_struct {
    char* name;  // Unique planet name
    double x;    // X coordinate
    double y;    // Y coordinate
    double z;    // Z coordinate
} Planet;

/**
 * Represents the origin of a Jerry.
 * Includes the planet and the dimension the Jerry is from.
 */
typedef struct Origin_struct {
    Planet* planet;   // Pointer to the planet (shared by multiple Jerries)
    char* dimension;  // Dimension identifier
} Origin;

/**
 * Represents a single physical characteristic of a Jerry.
 * Includes the name of the characteristic and its value.
 */
typedef struct PhysicalCharacteristics_struct {
    char* name;   // The name of the characteristic (e.g., Height, Weight)
    double value; // The value of the characteristic
} PhysicalCharacteristics;

/**
 * Represents a single Jerry.
 * Contains an ID, happiness level, origin information, and a dynamic array of physical characteristics.
 */
typedef struct Jerry_struct {
    char* id;                           // Unique Jerry ID
    int happiness;                      // Happiness level (0-100)
    Origin* origin;                     // Pointer to the origin
    PhysicalCharacteristics** characteristics; // Dynamic array of characteristics
    int characteristics_count;          // Number of characteristics
} Jerry;

/**
 * Manages an array of planets.
 * Tracks the list of planets and their count.
 */
typedef struct PlanetsManager {
    Planet** planets; // Array of pointers to planets
    int count;        // Number of planets
} PlanetsManager;

// Function Declarations

// --- Jerry Management ---
/**
 * Creates a new Jerry object using all the necessary information.
 * @param id The unique ID of the Jerry.
 * @param happiness The happiness level of the Jerry (0-100).
 * @param dimension The dimension where the Jerry originates.
 * @param manager A pointer to the PlanetsManager that manages all planets.
 * @param name The name of the planet where the Jerry originates.
 * @param x The X coordinate of the planet (used if the planet needs to be created).
 * @param y The Y coordinate of the planet (used if the planet needs to be created).
 * @param z The Z coordinate of the planet (used if the planet needs to be created).
 * @return A pointer to the newly created Jerry, or NULL if allocation fails or invalid input is provided.
 */
Jerry* create_jerry(char* id, int happiness,char* dimension,PlanetsManager* manager, char* name, double x, double y, double z );

/**
 * Destroys a Jerry object, freeing all associated memory.
 * @param jerry Pointer to the Jerry to destroy.
 */
void destroy_jerry(Jerry* jerry);

/**
 * Prints a Jerry's details, including its characteristics.
 * @param jerry The Jerry to print.
 * @return Status indicating success or invalid input.
 */
status print_jerry(Jerry* jerry);

// --- Planet Management ---
/**
 * Creates a new planet and adds it to the PlanetsManager. If the planet already exist just return the pointer to the planet
 * @param manager The PlanetsManager to which the planet will be added.
 * @param name The unique name of the planet.
 * @param x The X coordinate of the planet.
 * @param y The Y coordinate of the planet.
 * @param z The Z coordinate of the planet.
 * @return A pointer to the newly created Planet, or NULL if allocation fails.
 */
Planet* create_planet(PlanetsManager* manager, char* name, double x, double y, double z);

/**
 * Destroys a Planet object, freeing its memory.
 * @param planet Pointer to the Planet to destroy.
 */
void destroy_planet(Planet* planet);

/**
 * Destroys all planets managed by a PlanetsManager.
 * @param manager Pointer to the PlanetsManager.
 */
void destroy_all_planets(PlanetsManager* manager);

/**
 * Prints the details of a planet.
 * @param planet The Planet to print.
 * @return Status indicating success or invalid input.
 */
status print_planet(Planet* planet);

// --- Origin Management ---
/**
 * Creates a new Origin object.
 * @param planet Pointer to the Planet the Origin is associated with.
 * @param dimension The dimension name.
 * @return A pointer to the newly created Origin, or NULL if allocation fails.
 */
Origin* create_origin(Planet* planet, char* dimension);

// --- Physical Characteristics Management ---
/**
 * Creates a new physical characteristic.
 * @param name The name of the characteristic.
 * @param value The value of the characteristic.
 * @return A pointer to the newly created PhysicalCharacteristic, or NULL if allocation fails.
 */
PhysicalCharacteristics* create_characteristic(char* name, double value);

/**
 * Destroys a physical characteristic, freeing its memory.
 * @param characteristic Pointer to the PhysicalCharacteristic to destroy.
 */
void destroy_physical_characteristic(PhysicalCharacteristics* characteristic);

/**
 * Checks if a Jerry has a specific physical characteristic.
 * @param jerry The Jerry to check.
 * @param characteristic_name The name of the characteristic to check for.
 * @return True if the characteristic exists, false otherwise.
 */
bool does_characteristic_exist(Jerry* jerry, char* characteristic_name);

/**
 * Adds a physical characteristic to a Jerry.
 * @param jerry The Jerry to which the characteristic will be added.
 * @param characteristic The PhysicalCharacteristic to add.
 * @return Status indicating success, memory problem, or duplicate characteristic.
 */
status add_physical_characteristic(Jerry* jerry, PhysicalCharacteristics* characteristic);

/**
 * Removes a physical characteristic from a Jerry.
 * @param jerry The Jerry from which the characteristic will be removed.
 * @param characteristic_name The name of the characteristic to remove.
 * @return Status indicating success, memory problem, or not found.
 */
status remove_physical_characteristic(Jerry* jerry,  char* characteristic_name);

/**
 * Retrieves a physical characteristic of a Jerry by its name.
 * @param jerry A pointer to the Jerry object.
 * @param characteristic_name The name of the physical characteristic to retrieve.
 * @return A pointer to the PhysicalCharacteristics object if found, or NULL if the characteristic does not exist.
 */
PhysicalCharacteristics* get_characteristic(Jerry* jerry, char* characteristic_name);
#endif // JERRY_H