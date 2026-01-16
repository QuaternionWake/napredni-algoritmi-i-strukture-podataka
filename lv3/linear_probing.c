#include <string.h>

#ifndef MAX
    #error MAX must be defined
#endif

char *lp_hashset[MAX] = { 0 };

void collision();
void no_space();
void already_there();
int hash(char*);

float lp_load_factor() {
    int count = 0;
    for (int i=0; i<MAX; i++) {
        if (lp_hashset[i] != NULL) {
            count++;
        }
    }
    return (float)count / MAX;
}

void lp_insert(char *value) {
    int index = hash(value);

    if (lp_hashset[index] == NULL) {
        if (lp_load_factor() <= 0.75) {
            lp_hashset[index] = value;
        }
    } else {
        if (strcmp(lp_hashset[index], value) == 0) return;
        collision();

        int idx = index+1;
        while (lp_hashset[idx] != NULL && idx != index) {
            if (strcmp(lp_hashset[idx], value) == 0) {
                already_there();
                return;
            }
            collision();

            idx++;
            if (idx == MAX) idx = 0;
        }

        if (idx == index) {
            no_space();
        } else if (lp_load_factor() <= 0.75) {
            lp_hashset[idx] = value;
        }
    }
}

