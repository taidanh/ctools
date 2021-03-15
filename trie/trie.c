#include "trie.h"

#include "code.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

TrieNode *trie_node_create(uint16_t code) {
    // returns a node with the value code
    TrieNode *t = (TrieNode *) calloc(1, sizeof(TrieNode));
    if (t == NULL) {
        return NULL;
    }
    t->code = code;
    return t;
}

void trie_node_delete(TrieNode *n) {
    free(n);
    return;
}

TrieNode *trie_create(void) {
    // creates a trie with root as EMPT_CODE
    TrieNode *t = trie_node_create(EMPTY_CODE);
    if (t == NULL) {
        return NULL;
    }
    return t;
}

void trie_reset(TrieNode *root) {
    // deletes a trie except for the root
    for (uint16_t i = 0; i < ALPHABET; i += 1) {
        if (root->children[i] != NULL) {
            trie_delete(root->children[i]);
            root->children[i] = NULL;
        }
    }
}

void trie_delete(TrieNode *n) {
    if (n == NULL) {
        return;
    }
    for (uint16_t i = 0; i < ALPHABET; i += 1) {
        if (n->children[i] != NULL) {
            // recursively deletes the children
            trie_delete(n->children[i]);
        }
    }
    // once its out of the loop you know all the children have been deleted
    trie_node_delete(n);
    n = NULL;
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    // checks the posistion sym and returns based on that
    if (n->children[sym] != NULL) {
        return n->children[sym];
    }
    return NULL;
}
