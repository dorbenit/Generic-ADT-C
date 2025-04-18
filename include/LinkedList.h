#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "Defs.h"
typedef struct linkedlist_s *linkedlist;

/**
 * @brief Creates a new linked list.
 *
 * @param copyElement   A function that copies an element and returns a new pointer.
 * @param freeElement   A function that frees an element.
 * @param printElement  A function that prints an element.
 * @param equalFunc     A function that checks if two elements are equal.
 * @return A pointer to the new linked list, or NULL if there was a problem.
 */
linkedlist createLinkedList(CopyFunction copyElement, FreeFunction freeElement, PrintFunction printElement,EqualFunction equalFunc);
/**
 * @brief Destroys the linked list and frees all its elements.
 *
 * @param list A pointer to the linked list.
 * @return success if the list was destroyed, or failure if something went wrong.
 */
status destroyLinkedList(linkedlist list);
/**
 * @brief Adds a new element to the end of the list.
 *
 * @param list    A pointer to the linked list.
 * @param element The element to add (it will be copied internally).
 *
 * @return success on success, failure if parameters are invalid, or Memory_Problem if allocation failed.
 */
status appendNode(linkedlist list, Element element);

/**
 * @brief Deletes a specified element from the linked list.
 *
 * @param list    A pointer to the linked list.
 * @param element The element to delete (must match an existing element in the list).
 *
 * @return success on successful deletion, failure if the element is not found or parameters are invalid.
 */

status deleteNode(linkedlist list, Element element);
/**
 * @brief Prints all elements in the list.
 *
 * @param list A pointer to the linked list.
 * @return success on success, failure if the list is NULL.
 */
status displayList(linkedlist list);
/**
 * @brief Gets an element by its index in the list.
 *
 * @param list  A pointer to the linked list.
 * @param index The index of the element (1-based).
 *
 * @return A new copy of the element at the given index, or NULL if the index is invalid.
 * @Note that you will receive a copy of the data. Therefore, if you provided a deep copy, it is your responsibility to free the additional memory.
 * */
Element getDataByIndex(linkedlist list, int index);

/**
 * @brief Returns the number of elements in the list.
 *
 * @param list A pointer to the linked list.
 * @return The number of elements, or -1 if the list is NULL.
 */
int getLength(linkedlist list);

/**
 * @brief Searches for an element by key.
 *
 * @param list A pointer to the linked list.
 * @param key  The key to search for.
 *
 * @return A new copy of the element that matches the key, or NULL if not found.
*  @Note that you will receive a copy of the data. Therefore, if you provided a deep copy, it is your responsibility to free the additional memory.
* */
Element searchByKeyInList(linkedlist list, Element key);
/**
* @brief Returns the last element (tail) in the list.
*
* @param list A pointer to the linked list.
* @return A new copy of the last element, or NULL if the list is empty or invalid.
* @Note that you will receive a copy of the data. Therefore, if you provided a deep copy, it is your responsibility to free the additional memory.
* */
Element getTailContent(linkedlist list);
#endif