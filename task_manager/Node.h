#ifndef NODE_H
#define NODE_H

#include "Task.h"

typedef struct Node {
    Task data;
    Node* next;
    Node* prev;

    Node(Task data) {
        this->data = data;
        prev = NULL;
        next = NULL;
    }
} NODE;

#endif // NODE_H