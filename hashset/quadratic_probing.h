#include <stdlib.h>
#include <string.h>

size_t hash(char *value, size_t set_size);

typedef enum {
    EMPTY = 0, TOMBSTONE, OCCUPIED
} BucketState;

typedef struct {
    char **values;
    BucketState *bucket_state;
    size_t size;
    size_t used_buckets;
} Hashset;

Hashset init_hashset(size_t size);
void deinit_hashset(Hashset *hashset);
float hashset_load_factor(Hashset hashset);
int hashset_insert(Hashset *hashset, char *value);
char* hashset_find(Hashset hashset, char *value);
void hashset_delete(Hashset *hashset, char *value);
int hashset_rehash(Hashset *hashset);

