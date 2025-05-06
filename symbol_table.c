#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symbol_table.h"

#define TABLE_SIZE 101

static Symbol* table[TABLE_SIZE];

unsigned hash(const char* s) {
    unsigned h = 0;
    while (*s) h = (h << 4) + *s++;
    return h % TABLE_SIZE;
}

void set_symbol(const char* name, int value) {
    unsigned idx = hash(name);
    Symbol* sym = table[idx];
    while (sym) {
        if (strcmp(sym->name, name) == 0) {
            sym->value = value;
            return;
        }
        sym = sym->next;
    }
    sym = malloc(sizeof(Symbol));
    sym->name = strdup(name);
    sym->value = value;
    sym->next = table[idx];
    table[idx] = sym;
}

int get_symbol(const char* name) {
    unsigned idx = hash(name);
    Symbol* sym = table[idx];
    while (sym) {
        if (strcmp(sym->name, name) == 0) return sym->value;
        sym = sym->next;
    }
    fprintf(stderr, "Undefined variable: %s\n", name);
    return 0;
}

void free_symbols() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol* sym = table[i];
        while (sym) {
            Symbol* tmp = sym;
            sym = sym->next;
            free(tmp->name);
            free(tmp);
        }
        table[i] = NULL;
    }
}
