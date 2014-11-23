//
//  Stack.cpp
//  Máquina de Turing iB
//
//  Created by Ayrton Cavalieri on 23/11/2014.
//  Copyright (c) 2014 AyrtonC. All rights reserved.
//

#include "Stack.h"

struct stack{
    void *info;
    struct stack *prox;
};

struct stack* init(){
    return NULL;
}

struct stack* push(struct stack *l, void *info){
    struct stack *_new = (struct stack*)malloc(sizeof(struct stack));
    _new->info = info;
    _new->prox = l;
    return _new;
}

void* pop(struct stack **l){
    if(l == NULL)
        return NULL;
    void *ret = (*l)->info;
    struct stack *p = (*l)->prox;
    free((*l));
    (*l) = p;
    return ret;
}

bool isEmpty(struct stack *l){
    return l == NULL ? true : false;
}

struct stack* freeStack(struct stack *l){
    struct stack *t, *p;
    for(p = l; p != NULL; p = t){
        t = p->prox;
        free(p->info);
        free(p);
    }
    return NULL;
}
