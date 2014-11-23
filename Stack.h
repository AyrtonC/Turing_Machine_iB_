//
//  Stack.h
//  Máquina de Turing iB
//
//  Created by Ayrton Cavalieri on 23/11/2014.
//  Copyright (c) 2014 AyrtonC. All rights reserved.
//

#ifndef __Ma_quina_de_Turing_iB__Stack__
#define __Ma_quina_de_Turing_iB__Stack__

#include <stdlib.h>

typedef struct stack* Stack;

Stack init();
Stack push(Stack l, void *info);
void* pop(Stack *l);
bool isEmpty(Stack l);
struct stack* freeStack(struct stack *l);

#endif /* defined(__Ma_quina_de_Turing_iB__Stack__) */
