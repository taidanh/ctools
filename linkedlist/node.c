#include "node.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *copystr(char *c) {
    // allocates memory and copies the string to it
    // returns the pointer of that memory
    if (c == NULL) {
        return NULL;
    }
    uint32_t len = strlen(c);

    char *newstr = (char *) calloc(len + 1, sizeof(char));
    if (newstr == NULL) {
        return NULL;
    }
    for (uint32_t i = 0; i < len; i += 1) {
        newstr[i] = tolower(c[i]);
    }
    newstr[len] = '\0';
    return newstr;
}

Node *node_create(char *oldspeak, char *newspeak) {
    // creates a node w/ specified old and newspeak
    // and points at nothing
    // returns pointer to Node
    Node *n = (Node *) calloc(1, sizeof(Node));
    n->oldspeak = copystr(oldspeak);
    n->newspeak = copystr(newspeak);
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void node_delete(Node **n) {
    free((*n)->oldspeak);
    free((*n)->newspeak);
    free(*n);
    *n = NULL;
    return;
}

void node_print(Node *n) {
    // changes what prints depending if old and newspeak
    // are defined
    if (n->newspeak != NULL && n->oldspeak != NULL) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    } else if (n->newspeak == NULL && n->oldspeak != NULL) {
        printf("%s\n", n->oldspeak);
    }
    return;
}
