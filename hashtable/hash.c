#include "hash.h"

#include "speck.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
} HashTable;

HashTable *ht_create(uint32_t size, bool mtf) {
    // default hashtable as defined by pdf
    HashTable *ht = (HashTable *) calloc(1, sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x85ae998311115ae3;
        ht->salt[1] = 0xb6fac2ae33a40089;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    for (uint32_t i = 0; i < (*ht)->size; i += 1) {
        if ((*ht)->lists[i] != NULL) {
            ll_delete(&(*ht)->lists[i]);
        }
    }
    free((*ht)->lists);
    free(*ht);
    *ht = NULL;
    return;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    // gets the index to check with hash, makes sure there's a LL there
    // if not returns null else uses ll_lookup there
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    if (ht->lists[index] == NULL) {
        return NULL;
    }
    return ll_lookup(ht->lists[index], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    // creates a LL at index if it's not there
    // otherwise calls ll_insert at index
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    if (ht->lists[index] == NULL) {
        ht->lists[index] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[index], oldspeak, newspeak);
    return;
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i += 1) {
        if (ht->lists[i] != NULL) {
            ll_print(ht->lists[i]);
        }
    }
    return;
}
