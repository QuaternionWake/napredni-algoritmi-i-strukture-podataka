#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct SkipList SkipList;
typedef struct SLNode SLNode;

#define MAX_HEIGHT 16

void set_null_from(SLNode *node[MAX_HEIGHT], int height) {
    for (int i=height; i<MAX_HEIGHT; i++) {
        node[i] = NULL;
    }
}

struct SkipList {
    SLNode *head[MAX_HEIGHT];
};

struct SLNode {
    int value;
    int height;
    SLNode *next[MAX_HEIGHT];
};

SkipList init_skip_list() {
    SkipList sl = {
        .head = NULL,
    };
    return sl;
}

void deinit_skip_list(SkipList *sl) {
    for (SLNode *node = sl->head[0]; node;) {
        SLNode *next = node->next[0];
        free(node);
        node = next;
    }
    set_null_from(sl->head, 0);
}

void sl_insert(SkipList *sl, int value) {
    SLNode *node = malloc(sizeof(SLNode));
    if (!node) {
        fprintf(stderr, "Out of memory");
        exit(EXIT_FAILURE);
    }
    node->value = value;

    int height = 1;
    {
        uint16_t random = rand() & 0x7FFF;
        while (random & 1) {
            height++;
            random >>= 1;
        };
    }
    node->height = height;

    if (!sl->head[0]) {
        set_null_from(node->next, 0);
        node->height = MAX_HEIGHT;
        for (int i=0; i<height; i++) {
            sl->head[i] = node;
        }
        return;
    }

    if (value < sl->head[0]->value) {
        for (int i=0; i<height; i++) {
            node->next[i] = sl->head[i];
            sl->head[i] = node;
        }
        set_null_from(node->next, height);
        return;
    }

    SLNode **prev_ptrs[MAX_HEIGHT] = {0};
    SLNode *current = NULL;
    for (int i=MAX_HEIGHT; i>0; i--) {
        prev_ptrs[i-1] = &sl->head[i-1];
        if (sl->head[i-1] && value < sl->head[i-1]->value) {
            current = sl->head[i-1];
            break;
        }
    }

    for (;current;) {
        SLNode *next = NULL;
        for (int i=current->height; i>0; i--) {
            prev_ptrs[i-1] = &current->next[i-1];
            if (current->next[i-1] && value >= current->next[i-1]->value) {
                next = current->next[i-1];
                break;
            }
        }
        current = next;
    }

    for (int i=0; i<height; i++) {
        node->next[i] = *prev_ptrs[i];
        *prev_ptrs[i] = node;
    }

    set_null_from(node->next, height);
}

SLNode* sl_find(SkipList sl, int value) {
    SLNode *node = NULL;
    for (int i=MAX_HEIGHT; i>0; i--) {
        if (sl.head[i-1] && value < sl.head[i-1]->value) {
            node = sl.head[i-1];
            break;
        }
    }
    for (;node;) {
        if (node->value == value) {
            return node;
        } else if (value < node->value) {
            return NULL;
        }

        SLNode *next = NULL;
        for (int i=node->height; i>0; i--) {
            if (node->next[i-1] && value >= node->next[i-1]->value) {
                node = next;
                break;
            }
        }
    }
    return NULL;
}
