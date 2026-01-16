#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList LinkedList;
typedef struct LLNode LLNode;

struct LinkedList {
    LLNode *head;
};

struct LLNode {
    int value;
    LLNode *next;
};

LinkedList init_linked_list() {
    LinkedList ll = {
        .head = NULL,
    };
    return ll;
}

void deinit_linked_list(LinkedList *ll) {
    for (LLNode *node = ll->head; node;) {
        LLNode *next = node->next;
        free(node);
        node = next;
    }
    ll->head = NULL;
}

void ll_insert(LinkedList *ll, int value) {
    LLNode *node = malloc(sizeof(LLNode));
    if (!node) {
        fprintf(stderr, "Out of memory");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = ll->head;
    ll->head = node;
}

LLNode* ll_find(LinkedList ll, int value) {
    for (LLNode *node = ll.head; node; node = node->next) {
        if (node->value == value) {
            return node;
        }
    }
    return NULL;
}
