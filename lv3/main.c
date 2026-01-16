#include <stdio.h>
#include <time.h>

int digit_count(int n) {
    int broj = 0;
    while (n != 0) {
        broj++;
        n /= 10;
    }
    return broj;
}

#ifndef MAX
    #error MAX must be defined
#endif

#include "division_method.c"
#include "folding_method.c"
#include "mid-square_method.c"

#include "separate_chaining.c"
#include "linear_probing.c"
#include "quadratic_probing.c"
#include "double_hashing.c"

#include "words.c"

int collision_count;

void collision() { collision_count++; }
void no_space() {}
void already_there() {}
int hash(char *value) { return division(value) % MAX; }

int main() {
    int len = sizeof(words)/sizeof(words[0]);
    clock_t t0, t1;
    printf("MAX: %d\n", MAX);

    collision_count = 0;
    t0 = clock();
    for (int i=0; i<len; i++) sc_insert(words[i]);
    t1 = clock();
    printf("\tSeparate chaining: %d collisions, %ldns\n", collision_count, (t1-t0)*1000000 / CLOCKS_PER_SEC);

    collision_count = 0;
    t0 = clock();
    for (int i=0; i<len; i++) lp_insert(words[i]);
    t1 = clock();
    printf("\t   Linear probing: %d collisions, %ldns\n", collision_count, (t1-t0)*1000000 / CLOCKS_PER_SEC);

    collision_count = 0;
    t0 = clock();
    for (int i=0; i<len; i++) qp_insert(words[i]);
    t1 = clock();
    printf("\tQuadratic probing: %d collisions, %ldns\n", collision_count, (t1-t0)*1000000 / CLOCKS_PER_SEC);

    collision_count = 0;
    t0 = clock();
    for (int i=0; i<len; i++) dh_insert(words[i]);
    t1 = clock();
    printf("\t   Double hashing: %d collisions, %ldns\n", collision_count, (t1-t0)*1000000 / CLOCKS_PER_SEC);
}
