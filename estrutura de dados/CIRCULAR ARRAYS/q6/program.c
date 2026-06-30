#include "program.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Program{
    char name[65];
    char type[10];
    int priority;
    int load;
    int last_time;
    int first_time;
};

Program *program_construct(){
    Program *p = (Program*)calloc(1, sizeof(Program));

    return p;
}

Program *program_read(){
    Program *p = program_construct();
    scanf("%s %s %d %d %d", p->name, p->type, &p->priority, &p->load, &p->first_time);
    p->last_time = -1;

    return p;
}
int first_time(Program *p){
    return p->first_time;
}
int cmp_program(void *a, void *b){
    Program *p1 = (Program*)a;
    Program *p2 = (Program*)b;
    if(strcmp(p1->type, "SO") == 0){
        if(p1->priority != p2->priority){
            return p1->priority - p2->priority;
        }
        else if(p1->load != p2->load){
            return p1->load - p2->load;
        } 
    }
    else if(strcmp(p1->type, "USER")==0){
        if(p1->priority != p2->priority){
            return p1->priority - p2->priority;
        }
        else if(p1->last_time != p2->last_time){
            return p2->last_time - p1->last_time;
        }
    }
    else {
        return (strcmp(p1->name, p2->name));
    }
    
}
char *program_name(Program *p){
    return p->name;
}