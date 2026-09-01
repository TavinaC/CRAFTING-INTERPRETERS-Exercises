#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node* prev;
    struct Node* next;
    char* string;
} Node;

typedef struct DoublyLinkedList {
    Node* firstNode;
    Node* lastNode;
} List;

// insert [newNode] after [node]
void insertAfter(List* list, Node* node, Node* newNode) {
    newNode->prev = node;

    if (node->next == NULL) {
        list->lastNode = newNode;
    } else {
        newNode->next = node->next;
        node->next->prev = newNode;
    }

    node->next = newNode;
}

// insert [newNode] before [node]
void insertBefore(List* list, Node* node, Node* newNode) {
    newNode->next = node;

    if (node->prev == NULL) {
        list->firstNode = newNode;
    } else {
        newNode->prev = node->prev;
        node->prev->next = newNode;
    }

    node->prev = newNode;
}

// insert [newNode] at the beginning
void insertBeginning(List* list, Node* newNode) {
    if (list->firstNode == NULL) {
        list->firstNode = newNode;
        list->lastNode = newNode;
    } else {
        insertBefore(list, list->firstNode, newNode);
    }
}

// insert [newNode] at the end
void insertEnd(List* list, Node* newNode) {
    if (list->lastNode == NULL) {
        insertBeginning(list, newNode);
    } else {
        insertAfter(list, list->lastNode, newNode);
    }
}

void delete(List* list, Node* node) {
    if (node->prev == NULL) {
        list->firstNode = node->next;
    } else {
        node->prev->next = node->next;
    }

    if (node->next == NULL) {
        list->lastNode = node->prev;
    } else {
        node->next->prev = node->prev;
    }
}

Node* find(List* list, char* string) {
    Node* node = list->firstNode;

    while (node != NULL) {
        if (strcmp(node->string, string) == 0) {
            return node;
        }
        node = node->next;
    }

    // not found
    return NULL;
}

void printList(List* list) {
    Node* node = list->firstNode;

    if (node == NULL) {
        printf("Empty List");
    }

    while (node != NULL) {
        printf("%s ", node->string);
        node = node->next;
    }

    printf("\n");
}

Node* createNode(char* string){
    // allocate memory
    Node* newNode = malloc(sizeof(Node));
    newNode->string = malloc(strlen(string) + 1);

    //copy string to string field of the new Node
    strcpy(newNode->string, string);

    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

int main() {

    List* list = malloc(sizeof(List));
    list->firstNode = NULL;
    list->lastNode = NULL;

    printList(list);

    // Test insert & find functions
    insertBeginning(list, createNode("one"));
    printList(list);

    insertEnd(list, createNode("two"));
    printList(list);

    insertAfter(list, find(list, "one"), createNode("three"));
    printList(list);

    insertBefore(list, find(list, "two"), createNode("zero"));
    printList(list);

    // test delete function
    delete(list, find(list, "one"));
    printList(list);

    delete(list, find(list, "zero"));
    printList(list);

    return 0;
}