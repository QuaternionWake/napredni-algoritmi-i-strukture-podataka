#include <math.h>
#include <string.h>

#ifndef MAX
    #error MAX must be defined
#endif

int digit_count(int n);

int fs_inner(int n) {
    if (n < MAX) return n;
    int tmp = (int)pow(10, digit_count(n) - digit_count(MAX-1));
    return n/tmp + fs_inner(n % tmp);
}

int fold_shift(char *value) {
    int sum = 0;
    for (int i=0; i<strlen(value); i++) {
        sum += value[i];
    }
    return fs_inner(sum);
}
