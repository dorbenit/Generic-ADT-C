#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "KeyValuePair.h"
typedef struct node_t {
    Element content ;
    struct node_t* next;
} Node;

struct linkedlist_s {
    Node* head;
    Node* tail;
    int length;
    CopyFunction copyElement;
    FreeFunction freeElement;
    PrintFunction printElement;
    EqualFunction equalFunc;
};


Node* create_node(Element content, CopyFunction copyElement) {
    if (content == NULL || copyElement == NULL) {
        return NULL;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL; // Memory allocation failed
    }
    new_node->content = copyElement(content);
    if (new_node->content == NULL) {
        free(new_node); // Free node if content copy fails
        return NULL;
    }
    new_node->next = NULL; // Initialize next to NULL
    return new_node;
}

void free_node(Node* node,FreeFunction freeElement) {
    if (node == NULL) {
        return;
    }
    if (node->content != NULL && freeElement != NULL) {
        freeElement(node->content); // Free the node's content using the provided function
    }
    free(node); // Free the node itself
}

linkedlist createLinkedList(CopyFunction copyElement, FreeFunction freeElement, PrintFunction printElement,EqualFunction equalFunc) {
    if (copyElement == NULL || freeElement == NULL || printElement == NULL|| equalFunc == NULL) {
        return NULL;
    }
    linkedlist new_list = (linkedlist)malloc(sizeof(struct linkedlist_s));
    if (new_list == NULL) {
        return NULL;
    }
    // Initialize the linked list structure
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->length = 0;
    new_list->copyElement = copyElement;
    new_list->freeElement = freeElement;
    new_list->printElement = printElement;
    new_list->equalFunc = equalFunc;
    return new_list;

}

status destroyLinkedList(linkedlist list) {
    if (list == NULL) {
        return failure; // Invalid input, cannot destroy
    }
    Node* curr = list->head;
    Node* next_node = NULL;
    while (curr != NULL) {
        next_node = curr->next; // Save the next node
        free_node(curr,list->freeElement); // Free the current node
        curr = next_node; // Move to the next node
    }
    free(list); // Free the linked list structure itself
    return success;
}

status appendNode(linkedlist list, Element element) {
    if (list == NULL || element == NULL) {
        return failure;
    }
    Node* new_node = create_node(element, list->copyElement);
    if (new_node == NULL) {
        return  Memory_Problem; // Memory allocation failed
    }
    if (list->tail == NULL) {
        // If the list is empty, set head and tail to the new node
        list->head = new_node;
        list->tail = new_node;

    }
    // Otherwise, append to the end of the list
    else {
        list->tail->next = new_node;
        list->tail = new_node;

    }
    // Increment the list length
    list->length++;
   return success;
}

status deleteNode(linkedlist list, Element element) {
    if (list == NULL || element == NULL) {
        return failure;
    }
    Node* curr = list->head;
    Node* prev = NULL;
    while (curr != NULL) {
        // Found the node to delete
        if (list->equalFunc(curr->content, element)) {
            if (prev == NULL) {
                // Node to delete is the head
                list->head = curr->next;
                if (list->head == NULL) {
                    list->tail = NULL;
                }
            } else {
                // Node to delete is in the middle or end
                prev->next = curr->next;
                if (list->tail == curr) {
                    list->tail = prev;
                }
            }
            free_node(curr,list->freeElement); // Free the node
            list->length--; // Decrement the list length
            return success;
        }
        prev = curr; // Move to the next node
        curr = curr->next;
    }
    return Not_Exist; // Element not found

}

status displayList(linkedlist list) {
    if (list == NULL) {
        return failure;
    }
    Node* curr = list->head;
    while (curr != NULL) {
        list->printElement(curr->content); // Print each element
        curr = curr->next; // Move to the next node
    }
    return success;

}

Element getDataByIndex(linkedlist list, int index) {
    if (list == NULL || index < 1 || index > list->length) {
        return NULL;
    }
    Node* curr = list->head;
    int currentIndex = 1;
    while (curr != NULL && currentIndex < index) {
        curr = curr->next; // Traverse the list
        currentIndex++;
    }
    if (curr == NULL) {
        return NULL; // Index out of range
    }
    return list->copyElement(curr->content);  // Return the content at the index
}

int getLength(linkedlist list) {
    if (list == NULL) {
        return -1; // Invalid input
    }
    return list->length; // Return the length of the list
}

Element searchByKeyInList(linkedlist list, Element key) {
    if (list == NULL || key == NULL ) {
        return NULL;
    }
    Node* curr = list->head;
    while (curr != NULL) {
        if (list->equalFunc(curr->content, key)) {
            return list->copyElement(curr->content); // Return the matching element
        }
        curr = curr->next; // Move to the next node
    }
    return NULL; // No matching element found
}

Element getTailContent(linkedlist list) {
    if (list == NULL || list->tail == NULL) {
        return NULL; // Invalid input or empty list
    }
    return list->copyElement(list->tail->content);  // Return the content of the last node
}