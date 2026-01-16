#include <stdlib.h>
#include <string.h>

#ifndef MAX
    #error MAX must be defined
#endif

struct sc_element {
    char *data;
    struct sc_element *next;
};

struct sc_element *sc_hashset[MAX] = { 0 };

void collision();
void already_there();
int hash(char*);

float sc_load_factor() {
    int count = 0;
    for (int i=0; i<MAX; i++) {
        for (struct sc_element *el = sc_hashset[i]; el!=NULL; el=el->next) {
            count++;
        }
    }
    return (float)count / MAX;
}

void sc_insert(char *value) {
    struct sc_element *new = malloc(sizeof(struct sc_element));
    new->data = value;
    new->next = NULL;

    int index = hash(value);
    if (sc_hashset[index] == NULL) {
        if (sc_load_factor() <= 0.75) {
            sc_hashset[index] = new;
        } 
    } else {
        collision();
        struct sc_element *tmp = sc_hashset[index];
        while (tmp) {
            if (strcmp(tmp->data, value) == 0) {
                already_there();
                return;
            }
            tmp = tmp->next;
        }
        if (sc_load_factor() <= 0.75) {
            new->next = sc_hashset[index];
            sc_hashset[index] = new;
        } 
    }
}
