#include "task.h"
#include <string.h>
#include "program.h"

struct task{
    int id;
    int time;
    int p;
    Programa programa;
    Programa* pipeline;
};

Tarefa novaTarefa(int id, int time, char* name, char** args, Programa* pipeline){
    if(id == 0){
        Tarefa t = malloc(sizeof(struct task));
        t->id = 0;
        t->time = time;
        return t;
    }
    if(pipeline == NULL){
        Tarefa t = malloc(sizeof(struct task));
        t->p = 0;
        t->id = id;
        t->time = time;
        Programa p = novoPrograma(name, args);
        t->programa = p;
        return t;
    }
    else{
        Tarefa t = malloc(sizeof(struct task));
        t->p = 1;
        t->id = id;
        t->time = time;
        t->pipeline = pipeline;
        return t;
    }
}

int getID(Tarefa t){
    return t->id;
}

Programa getPrograma(Tarefa t){
    return t->programa;
}

int getPipelineStatus(Tarefa t){
    return t->p;
}

Programa* getPipeline(Tarefa t){
    return t->pipeline;
}

int getTime(Tarefa t){
    return t->time;
}