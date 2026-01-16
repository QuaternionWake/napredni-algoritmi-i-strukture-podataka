#include <math.h>
#include <string.h>

#ifndef MAX
    #error MAX must be defined
#endif

int digit_count(int n);

int midsquare(char *value) {
    int sum = 0;
    for (int i=0; i<strlen(value); i++) {
        sum += value[i];
    }

    long int sq = sum * sum;
    int max_len = digit_count(MAX-1);
    int key_len = digit_count(sq);

    int end = (key_len-max_len) / 2 + (key_len-max_len) % 2;
    sq = sq / (int)pow(10, end);
    return sq % (int)pow(10, max_len);
}
