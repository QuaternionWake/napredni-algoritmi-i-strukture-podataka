#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ll.c"
#include "sl.c"

#ifndef N
    #error N must be defined
#endif

#define N_SEARCHES 100

int main() {
    time_t t1, t2;
    LinkedList ll = init_linked_list();

    t1 = clock();
    for (int i=0; i<N; i++) {
        ll_insert(&ll, rand());
    }
    t2 = clock();
    printf("LL creation time: %ldms\n", (t2-t1)*1000/CLOCKS_PER_SEC);

    t1 = clock();
    for (int i=0; i<N_SEARCHES; i++) {
        ll_find(ll, rand());
    }
    t2 = clock();
    printf("LL search time: %ldms\n", (t2-t1)*1000/CLOCKS_PER_SEC);

    deinit_linked_list(&ll);
    SkipList sl = init_skip_list();

    t1 = clock();
    for (int i=0; i<N; i++) {
        sl_insert(&sl, rand());
    }
    t2 = clock();
    printf("SL creation time: %ldms\n", (t2-t1)*1000/CLOCKS_PER_SEC);

    t1 = clock();
    for (int i=0; i<N; i++) {
        sl_find(sl, rand());
    }
    t2 = clock();
    printf("SL search time: %ldms\n", (t2-t1)*1000/CLOCKS_PER_SEC);

    deinit_skip_list(&sl);
}
