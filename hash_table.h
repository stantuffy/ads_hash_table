#ifndef _HASH_TABLE_C
#define _HASH_TABLE_C

// Hash table using string as keys, and int as values

typedef struct ht_node {
    char *key;
    int value;
    struct ht_node *next;
} ht_node;

typedef struct hash_table {
    ht_node **table; // table is an array of lists
    int table_size;
} hash_table;

hash_table new_hash_table();

unsigned long long djb2_hash(const char *str);

_Bool key_equal(const char *key1, const char *key2);

void insert_hash_table(hash_table ht, const char *key, int value);

int *get_hash_table(hash_table ht, const char *key);

void remove_hash_table(hash_table ht, const char *key);

#endif