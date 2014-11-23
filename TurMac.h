//
//  TurMac.h
//  Máquina de Turing iB
//
//  Created by Ayrton Cavalieri on 19/11/2014.
//  Copyright (c) 2014 AyrtonC. All rights reserved.
//

#ifndef __Ma_quina_de_Turing__TurMac__
#define __Ma_quina_de_Turing__TurMac__

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Stack.h"

using namespace std;

typedef struct turmac** TurMac;

TurMac initTurMac(unsigned int tam);
void saveTurMac(std::string path, TurMac vet,unsigned int tam);
TurMac openTurMac(std::string path, unsigned int &tam);
TurMac dealocTurMac(TurMac mac, unsigned int tam);
bool isTurMacInitialized(TurMac mac);

TurMac insTran(TurMac Turmac, unsigned int state, char char_lido, char char_subst, char dir, unsigned int est_dest, bool inic, bool fin);
bool execTurMac(TurMac Turmac, unsigned int num_est, std::string &str);

#endif /* defined(__Ma_quina_de_Turing__TurMac__) */
