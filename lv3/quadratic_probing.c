#include <stdio.h>
#include <string.h>

#ifndef MAX
    #error MAX must be defined
#endif

char *qp_hashset[MAX] = { 0 };

void collision();
void no_space();
void already_there();
int hash(char*);

float qp_load_factor() {
    int count = 0;
    for (int i=0; i<MAX; i++) {
        if (qp_hashset[i] != NULL) {
            count++;
        }
    }
    return (float)count / MAX;
}

void qp_insert(char *value) {
    int index = hash(value);

    for (int i=0; i<MAX; i++) {
        int idx = (index + i*i) % MAX;
        if (qp_hashset[idx] == NULL) {
            if (qp_load_factor() <= 0.75) {
                qp_hashset[idx] = value;
            }
            return;
        } else if (strcmp(qp_hashset[idx], value) == 0) {
            already_there();
            return;
        }
        collision();
    }

    no_space();
}
