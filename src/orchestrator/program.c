#include "program.h"
#include <string.h>

struct program{
    char* name;
    char **argss;
};

Programa novoPrograma(char* name, char** args){
    Programa p = malloc(sizeof(struct program));
    p->name = strdup(name);
    p->argss = malloc(sizeof(args));
    int i = 0;
    while(args[i]){
        p->argss[i] = strdup(args[i]);
        i++;
    }
    return p;
}