#include <stdio.h>

#include "quadratic_probing.h"

void print_hashset(Hashset h) {
    printf("Size: %ld, Used buckets: %ld, Load factor: %.3f\n", h.size, h.used_buckets, hashset_load_factor(h));
    for (size_t i=0; i<h.size; i++) {
        switch (h.bucket_state[i]) {
        case EMPTY:
            printf("    %4ld: EMPTY\n", i);
            break;
        case TOMBSTONE:
            printf("    %4ld: TOMBSTONE\n", i);
            break;
        case OCCUPIED:
            printf("    %4ld: \"%s\"\n", i, h.values[i]);
            break;
        }
    }
    printf("\n");
}

char *strings[] = {
    "Kava", "Fakultet", "Algoritmi", "Monitor", "Pivo", "Pizza", "Hashset", "Hash funkcija", "Jednosmjerna"
};

char *find[] = {
    "Fakultet", "Hashset", "Mapa"
};

char *delete[] = {
    "Algoritmi", "Monitor", "Pivo", "Hashset", "Mapa"
};

char *colliding[] = {
    "abc", "acb", "bac", "bca", "cab", "cba", "abcd"
};

char *multi_colliding[] = {
    "d", "dd", "ddd", "dddd", "g", "gd", "gdd" 
};

char *reinsert[] = {
    "abcd", "abdc", "badc"
};

int main() {
    Hashset h = init_hashset(10);
    print_hashset(h);

    int failed_inserts = 0;
    for (int i=0; i<9; i++) {
        int error = hashset_insert(&h, strings[i]);
        if (error) {
            printf("Failed to insert \"%s\"\n", strings[i]);
            failed_inserts++;
            continue;
        }
        print_hashset(h);
    }
    printf("%d failed inserts\n", failed_inserts);

    for (int i=0; i<3; i++) {
        char* result = hashset_find(h, find[i]);
        if (result == NULL) {
            printf("Failed to find \"%s\"\n", find[i]);
        } else {
            printf("Found \"%s\" at address %p\n", find[i], result);
        }
    }

    for (int i=0; i<5; i++) {
        printf("Deleting \"%s\"\n", delete[i]);
        hashset_delete(&h, delete[i]);
        print_hashset(h);
    }

    for (int i=0; i<3; i++) {
        char* result = hashset_find(h, find[i]);
        if (result == NULL) {
            printf("Failed to find \"%s\"\n", find[i]);
        } else {
            printf("Found \"%s\" at address %p\n", find[i], result);
        }
    }

    deinit_hashset(&h);
    h = init_hashset(10);

    failed_inserts = 0;
    for (int i=0; i<7; i++) {
        int error = hashset_insert(&h, colliding[i]);
        if (error) {
            printf("Failed to insert \"%s\"\n", colliding[i]);
            failed_inserts++;
            continue;
        }
        print_hashset(h);
    }
    printf("%d failed inserts\n", failed_inserts);

    deinit_hashset(&h);
    h = init_hashset(10);

    failed_inserts = 0;
    for (int i=0; i<7; i++) {
        int error = hashset_insert(&h, multi_colliding[i]);
        if (error) {
            printf("Failed to insert \"%s\"\n", multi_colliding[i]);
            failed_inserts++;
            continue;
        }
        print_hashset(h);
    }
    printf("%d failed inserts\n", failed_inserts);

    hashset_delete(&h, multi_colliding[2]);
    print_hashset(h);
    hashset_delete(&h, multi_colliding[0]);
    print_hashset(h);

    for (int i=0; i<7; i++) {
        char* result = hashset_find(h, multi_colliding[i]);
        if (result == NULL) {
            printf("Failed to find \"%s\"\n", multi_colliding[i]);
        } else {
            printf("Found \"%s\" at address %p\n", multi_colliding[i], result);
        }
    }

    deinit_hashset(&h);
    h = init_hashset(10);

    failed_inserts = 0;
    for (int i=0; i<3; i++) {
        int error = hashset_insert(&h, reinsert[i]);
        if (error) {
            printf("Failed to insert \"%s\"\n", reinsert[i]);
            failed_inserts++;
            continue;
        }
        print_hashset(h);
    }
    printf("%d failed inserts\n", failed_inserts);

    hashset_delete(&h, reinsert[1]);
    print_hashset(h);
    hashset_insert(&h, reinsert[2]);
    print_hashset(h);

    deinit_hashset(&h);
}
