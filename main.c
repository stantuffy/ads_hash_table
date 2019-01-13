#include <stdio.h>
#include <assert.h>
#include "hash_table.h"

void print_hash_table(hash_table ht) {
    printf("\n");
    for(int i=0; i<ht.table_size; i++) {
        ht_node *list = ht.table[i];
        while(list != NULL) {
            printf("[\"%s\"] = %d\n", list->key, list->value);
            list = list->next;
        }
    }
}

void test_hash_table() {
    hash_table ht = new_hash_table();

    // Test: Insert/Get works
    insert_hash_table(ht, "Amatriciana", 10);
    assert((*get_hash_table(ht, "Amatriciana")) == 10);

    // Test: Remove works
    remove_hash_table(ht, "Amatriciana");
    assert(get_hash_table(ht, "Amatriciana") == NULL);

    // Inserting more values is ok
    insert_hash_table(ht, "Pecorino", 180);
    insert_hash_table(ht, "Olio", 9);
    insert_hash_table(ht, "Sale", -102);

    // Calling "remove" with non-existing keys is ok
    remove_hash_table(ht, "Non c'è!");

    remove_hash_table(ht, "Pecorino");

    // Printing the whole table
    print_hash_table(ht);

    printf("\n\n## ALL TESTS PASSED\n\n");
}

int main() {
    test_hash_table();

    return 0;
}