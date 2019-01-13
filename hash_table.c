#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

#define HT_SIZE 50

hash_table new_hash_table() {
    hash_table ht;
    ht.table_size = HT_SIZE;
    // Instantiating an array of list pointers.
    (ht.table) = (ht_node **)calloc(HT_SIZE, sizeof(ht_node *));

    return ht;
}

// D.Bernstein's string hashing function implementation.
// Using unsigned long long to prevent overflow on short string.
// Note that this function is likely to overflow if str is huge.
unsigned long long djb2_hash(const char *str) {
    
    unsigned long long hash = 5381;

    for(int i=0; i<strlen(str); i++) {
        hash = (hash*33) + str[i];
    }

    return hash;
}

_Bool key_equal(const char *key1, const char *key2) {
    return strcmp(key1, key2) == 0;
}

void insert_hash_table(hash_table ht, const char *key, int value) {
    int index = djb2_hash(key) % ht.table_size;
    ht_node *list = ht.table[index];
    // If key is already present into the hash table, overwrite its value...
    
    while(list != NULL) {
        if(key_equal(key, list->key)) {
            list->value = value;
            return;
        }

        list = list->next;
    }

    //.. Otherwise, add a new key-value pair on top of the list.
    ht_node *pair = (ht_node *)calloc(1, sizeof(ht_node));
    int key_len = strlen(key);

    // To be safe, we shall not copy key's address into pair->key.
    // Instead, we're gonna allocate(on the heap) enough space to copy the key, char by char. 
    pair->key = (char *)calloc(key_len+1, sizeof(char));
    strncpy(pair->key, key, key_len);
    pair->key[key_len + 1] = 0;

    pair->value = value;
    pair->next = ht.table[index];
    ht.table[index] = pair;
}

// Given an hash_table ht and a key, returns pointer to the value related to key.
// If no such key exists, returns NULL.
int *get_hash_table(hash_table ht, const char *key) {
    int *res = NULL;

    int index = djb2_hash(key) % ht.table_size;
    ht_node *list = ht.table[index];

    while(list != NULL) {
        if(key_equal(list->key, key)) {
            res = &(list->value);
            break;
        }

        list = list->next;
    }

    return res;
}

// Given an hash_table ht and a key, removes node having that key from ht.
void remove_hash_table(hash_table ht, const char *key) {
    int index = djb2_hash(key) % ht.table_size;
    ht_node *list = ht.table[index];

    // Since we want to delete a node from a singly-linked list, 
    // we have to keep info of the previous of the current node, to fix the links.
    ht_node *prev = NULL;

    while(list != NULL) {
        if(key_equal(list->key, key)) {
            // we are going to delete the head of the list
            if(prev == NULL) {
                ht.table[index] = list->next;
                free(list->key);
                free(list);
            }
            else {
                prev->next = list->next;
                free(list->key);
                free(list);
            }
            return;
        }
        prev = list;
        list = list->next;
    }
}