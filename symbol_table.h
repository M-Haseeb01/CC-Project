#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct Symbol {
    char* name;
    int value;
    struct Symbol* next;
} Symbol;

void set_symbol(const char* name, int value);
int get_symbol(const char* name);
void free_symbols();

#endif
