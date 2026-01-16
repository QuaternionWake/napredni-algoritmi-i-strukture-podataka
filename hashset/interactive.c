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

int main() {
    Hashset h = init_hashset(10);
    print_hashset(h);

    char quit = 0;
    while (!quit) {
        char *buf = (char*)calloc(100, sizeof(char));
        char op = getchar();
        char fail = 0;
        switch (op) {
            case 'i':
                scanf("%s\n", buf);
                fail = hashset_insert(&h, buf);
                if (fail) {
                    printf("Failed to insert %s\n", buf);
                }
                free(buf);
                break;
            case 'd':
                scanf("%s\n", buf);
                hashset_delete(&h, buf);
                free(buf);
                break;
            case 'f':
                scanf("%s\n", buf);
                char* addr = hashset_find(h, buf);
                printf("Found \"%s\" at address %p\n", buf, addr);
                free(buf);
                break;
            case 'p':
                print_hashset(h);
                free(buf);
                break;
            case 'q':
                free(buf);
                quit = 1;
                break;
            case '\n':
                break;
            default:
                printf("Unknown operation %c\n", op);
                free(buf);
        }
    }
    deinit_hashset(&h);
}
