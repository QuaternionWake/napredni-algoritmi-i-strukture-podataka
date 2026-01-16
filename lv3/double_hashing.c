#include <string.h>

#ifndef MAX
    #error MAX must be defined
#endif
#define R 7

char *dh_hashset[MAX] = { 0 };

void collision();
void no_space();
void already_there();
int hash(char*);

int hash2(char *key){
    int sum = 0;
    for (int i=0; i<strlen(key); i++) {
        sum += key[i];
    }
    return R - (sum % R);
}

float dh_load_factor() {
    int count = 0;
    for (int i=0; i<MAX; i++) {
        if (dh_hashset[i] != NULL) {
            count++;
        }
    }
    return (float)count / MAX;
}

void dh_insert(char *value) {
    int index = hash(value);
    if (dh_hashset[index] == NULL) {
        if (dh_load_factor() <= 0.75) {
            dh_hashset[index] = value;
        }
        return;
    } else if (strcmp(dh_hashset[index], value) == 0) {
        already_there();
        return;
    }
    collision();

    int offset = hash2(value);
    for (int i=1; i<MAX; i++) {
        int idx = (index + i*offset) % MAX;
        if (dh_hashset[idx] == NULL) {
            if (dh_load_factor() <= 0.75) {
                dh_hashset[idx] = value;
            }
            return;
        } else if (strcmp(dh_hashset[idx], value) == 0) {
            already_there();
            return;
        }
        collision();
    }

    no_space();
}
