#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
} node;

node* add(node *prev, int val) {
    node* newNode = malloc(sizeof(node));
    newNode->value = val;

    if (prev) {
        newNode->next = prev->next;
        prev->next = newNode;
    } else {
        newNode->next = NULL;
    }

    return newNode;
}

int main() {
    node* head = add(NULL, 1);
    add(head, 2);
    add(head, 3);
    add(head, 4);
    add(head, 5);

    node* cur = head;
    while (cur) {
        printf("%d\n", cur->value);
        cur = cur->next;
    }
}