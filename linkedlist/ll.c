#include "ll.h"

#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
} LinkedList;

void ll_mtf(LinkedList *ll, Node *mtf) {
    // rearranges the prev and next so that the
    // specified items gets moved to fron and no
    // nodes get disconnected
    if (ll->head->next == mtf) {
        // prevents pointing at self
        return;
    }
    Node *next = mtf->next;
    Node *prev = mtf->prev;
    Node *second = ll->head->next;

    next->prev = prev;
    prev->next = next;

    mtf->next = second;
    mtf->prev = ll->head;

    ll->head->next = mtf;
    second->prev = mtf;
    return;
}

LinkedList *ll_create(bool mtf) {
    // creates HEAD and TAIL nodes pointing at eachother and NULL
    LinkedList *ll = (LinkedList *) calloc(1, sizeof(LinkedList));
    ll->length = 0;
    ll->head = node_create(NULL, NULL);
    ll->tail = node_create(NULL, NULL);
    ll->head->next = ll->tail;
    ll->head->prev = NULL;
    ll->tail->prev = ll->head;
    ll->tail->next = NULL;
    ll->mtf = mtf;
    return ll;
}

void ll_delete(LinkedList **ll) {
    Node *current = (*ll)->head->next;
    Node *next;
    while (current != (*ll)->tail) {
        next = current->next;
        node_delete(&current);
        current = next;
    }
    node_delete(&(*ll)->head);
    node_delete(&(*ll)->tail);
    free(*ll);
    *ll = NULL;
    return;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    // looks through the LL and if the oldspeak is found
    // it returns the pointer and moves to front if specified
    Node *current = ll->head->next;
    while (current != ll->tail) {
        if (strcmp(oldspeak, current->oldspeak) == 0) {
            if (ll->mtf == true) {
                ll_mtf(ll, current);
            }
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    // makes sure the oldspeak isn't already in the LL
    // and if it isn't it addes it behind head
    if (ll_lookup(ll, oldspeak) == NULL) {
        Node *next = ll->head->next;
        Node *new = node_create(oldspeak, newspeak);
        new->next = next;
        new->prev = ll->head;
        ll->head->next = new;
        next->prev = new;
        ll->length += 1;
    } else {
        // if not found in the LL then quit
        return;
    }
    return;
}

void ll_print(LinkedList *ll) {
    Node *current = ll->head->next;
    while (current != ll->tail) {
        node_print(current);
        current = current->next;
    }
    return;
}
