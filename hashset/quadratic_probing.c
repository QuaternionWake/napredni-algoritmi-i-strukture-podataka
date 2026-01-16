#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quadratic_probing.h"

#define MAX_LOAD 0.75

size_t hash(char *value, size_t set_size) {
    size_t sum = 0;
    size_t len = strlen(value);
    for (size_t i=0; i<len; i++) {
        sum += value[i];
    }
    return sum % set_size;
}

Hashset init_hashset(size_t size) {
    if (size < 10) size = 10;
    char **values = (char**)calloc(size, sizeof(char*));
    if (values == NULL) exit(EXIT_FAILURE);
    BucketState *bucket_state = (BucketState*)calloc(size, sizeof(BucketState));
    if (bucket_state == NULL) exit(EXIT_FAILURE);
    Hashset hashset = { values, bucket_state, size, 0 };
    return hashset;
}

void deinit_hashset(Hashset *hashset) {
    for (size_t i=0; i<hashset->size; i++) {
        if (hashset->values[i] != NULL) {
            free(hashset->values[i]);
        }
    }
    free(hashset->values);
    free(hashset->bucket_state);
    hashset->values = 0;
    hashset->size = 0;
    hashset->used_buckets = 0;
}

float hashset_load_factor(Hashset hashset) {
    return (float)hashset.used_buckets / hashset.size;
}

int hashset_insert(Hashset *hashset, char *value) {
    size_t base_index = hash(value, hashset->size);

    size_t insert_index = 0;
    char should_insert = 0;
    for (size_t offset=0; offset<hashset->size; offset++) {
        size_t index = (base_index + offset*offset) % hashset->size;
        if (!should_insert && hashset->bucket_state[index] != OCCUPIED) {
            should_insert = 1;
            insert_index = index;
        } else {
            if (strcmp(hashset->values[index], value) == 0) return 0;
        }
        if (hashset->bucket_state[index] == EMPTY) {
            break;
        }
    }

    if (should_insert) {
        size_t len = strlen(value) + 1;
        char* new_value = (char*)malloc(len);
        if (new_value == NULL) exit(EXIT_FAILURE);
        strcpy(new_value, value);
        hashset->values[insert_index] = new_value;
        hashset->bucket_state[insert_index] = OCCUPIED;
        hashset->used_buckets++;

        if (hashset_load_factor(*hashset) > MAX_LOAD) {
            hashset_rehash(hashset);
        }

        return 0;
    }

    return -1;
}

char* hashset_find(Hashset hashset, char *value) {
    size_t base_index = hash(value, hashset.size);

    for (size_t offset=0; offset<hashset.size; offset++) {
        size_t index = (base_index + offset*offset) % hashset.size;
        if (hashset.bucket_state[index] == EMPTY) {
            return NULL;
        }
        if (hashset.bucket_state[index] == OCCUPIED && strcmp(hashset.values[index], value) == 0) {
            return hashset.values[index];
        }
    }

    return NULL;
}

void hashset_delete(Hashset *hashset, char *value) {
    size_t base_index = hash(value, hashset->size);
    size_t delete_index;
    char should_delete = 0;

    for (size_t offset=0; offset<hashset->size; offset++) {
        size_t index = (base_index + offset*offset) % hashset->size;
        if (hashset->bucket_state[index] == EMPTY) {
            break;
        }
        if (hashset->bucket_state[index] == OCCUPIED && strcmp(hashset->values[index], value) == 0) {
            delete_index = index;
            should_delete = 1;
            break;
        }
    }

    if (!should_delete) return;

    free(hashset->values[delete_index]);
    hashset->values[delete_index] = 0;
    hashset->bucket_state[delete_index] = TOMBSTONE;
    hashset->used_buckets--;
}

int hashset_rehash(Hashset *hashset) {
    size_t new_size = hashset->size * 2;
    Hashset new = init_hashset(new_size);
    for (size_t i=0; i<hashset->size; i++) {
        if (hashset->values[i] != NULL) {
            int error = hashset_insert(&new, hashset->values[i]);
            if (error) {
                deinit_hashset(&new);
                return error;
            }
        }
    }

    deinit_hashset(hashset);
    *hashset = new;
    return 0;
}
