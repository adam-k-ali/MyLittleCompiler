//
// Created by Adam Ali on 17/01/2023.
//

#ifndef COMPILER_DATA_H
#define COMPILER_DATA_H

#define NSYMBOLS 1024 // Size of symbol table
extern struct symtable Gsym[NSYMBOLS]; // Global symbol table
extern int Globs = 0; // Number of global symbols

int findglob(char *s) {
    int i;
    for (i = 0; i < Globs; i++) {
        if (strcmp(Gsym[i].name, s) == 0) {
            return i;
        }
    }
    return -1;
}

#endif //COMPILER_DATA_H
