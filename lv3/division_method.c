#include <string.h>

#ifndef MAX
    #error MAX must be defined
#endif

int division(char *key) {
    int sum = 0;
    for(int i=0; i<strlen(key); i++) {
        sum += key[i];
    }
	return sum % MAX;
}
