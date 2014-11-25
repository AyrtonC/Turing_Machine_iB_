//
//  TurMac.cpp
//  Máquina de Turing iB
//
//  Created by Ayrton Cavalieri on 19/11/2014.
//  Copyright (c) 2014 AyrtonC. All rights reserved.
//

#include "TurMac.h"

struct turmac{
    char caracter_lido, caracter_subst;
    char direcao;
    unsigned int estado_dest;
    bool inicial, final;
    struct turmac *prox;
};

struct turmac** initTurMac(unsigned int tam){
    struct turmac **init = (struct turmac**)malloc(tam*sizeof(struct turmac*));
    if(init != NULL){
        for(int i = 0; i < tam; i++){
            init[i] = NULL;
        }
    }
    return init;
}

void saveTurMac(std::string path, struct turmac **vet,unsigned int tam){
    FILE *out = fopen(path.c_str(), "wb");
    struct turmac *p;
    if(out == NULL){
        printf("Error saving Turing Machine!\n");
        return;
    }
    fwrite(&tam, sizeof(unsigned int), 1, out);
    for(unsigned int i = 0; i < tam; i++){
        for(p = vet[i]; p != NULL; p = p->prox){
            fwrite(&i, sizeof(unsigned int), 1, out);
            fwrite(p, sizeof(struct turmac), 1, out);
        }
    }
    fclose(out);
}

struct turmac** openTurMac(std::string path, unsigned int &tam){
    unsigned int state;
    struct turmac temp;
    FILE *in = fopen(path.c_str(), "rb");
    tam = 0;
    if(in == NULL){
        printf("Error opening Turing Machine!\n");
        return NULL;
    }
    fread(&tam, sizeof(unsigned int), 1, in);
    struct turmac **vet = initTurMac(tam);
    if(!isTurMacInitialized(vet)){
        fclose(in);
        return NULL;
    }
    do{
        fread(&state, sizeof(unsigned int), 1, in);
        fread(&temp, sizeof(struct turmac), 1, in);
        if(!feof(in))
            vet = insTran(vet, state, temp.caracter_lido, temp.caracter_subst, temp.direcao, temp.estado_dest, temp.inicial, temp.final);
    }while(!feof(in));
    fclose(in);
    return vet;
}

struct turmac** dealocTurMac(struct turmac **mac, unsigned int tam){
    struct turmac *t = NULL;
    for(int i = 0; i < tam; i++){
        for(struct turmac *p = mac[i]; p != NULL; p = t){
            t = p->prox;
            free(p);
        }
    }
    free(mac);
    return NULL;
}

bool isTurMacInitialized(struct turmac **mac){
    return mac != NULL ? true : false;
}

struct turmac* insnode(struct turmac *state, char char_lido, char char_subst, char dir, unsigned int est_dest, bool inic, bool fin){
    struct turmac *_new = (struct turmac*)malloc(sizeof(struct turmac));
    _new->prox = state;
    _new->caracter_lido = char_lido;
    _new->caracter_subst = char_subst;
    _new->direcao = dir;
    _new->estado_dest = est_dest;
    _new->inicial = inic;
    _new->final = fin;
    return _new;
}

struct turmac** insTran(struct turmac **Turmac, unsigned int state, char char_lido, char char_subst, char dir, unsigned int est_dest, bool inic, bool fin){
    Turmac[state] = insnode(Turmac[state], char_lido, char_subst, dir, est_dest, inic, fin);
    return Turmac;
}

void execturmac(struct turmac **Turmac, unsigned int est, std::string &str, unsigned int pos, bool &achei){
    typedef struct sp{
        struct turmac *p;
        unsigned int pos, est;
    }SP;
    Stack stc = init();
    SP *pil = (SP*)malloc(sizeof(SP)), *aux = NULL;
    pil->p = Turmac[est];
    pil->pos = pos;
    pil->est = est;
    do{
        while(pil != NULL && pil->p == NULL){
                free(pil);
                pil = (SP*)pop(&stc);
        }
        if(pil == NULL)
            break;
        if(pil->p->final == true){
            achei = true;
            free(pil);
            pil = NULL;
            break;
        }
        while(pil->p != NULL){
            if(pil->p->caracter_lido == '?' && pil->pos >= str.length()){
                if(pil->p->caracter_subst != '?'){
                    str+=pil->p->caracter_subst;
                    aux = (SP*)malloc(sizeof(SP));
                    aux->p = Turmac[pil->p->estado_dest];
                    aux->est = pil->p->estado_dest;
                    aux->pos = pil->pos;
                    pil->p->direcao == 'R' ? aux->pos++ : aux->pos--;
                    pil->p = pil->p->prox;
                    stc = push(stc, pil);
                    pil = aux;
                    aux = NULL;
                    break;
                }
            }else if(pil->pos < str.length()){
                if(pil->p->caracter_lido == str[pil->pos]){
                    str[pil->pos] = pil->p->caracter_subst;
                    aux = (SP*)malloc(sizeof(SP));
                    aux->p = Turmac[pil->p->estado_dest];
                    aux->est = pil->p->estado_dest;
                    aux->pos = pil->pos;
                    pil->p->direcao == 'R' ? aux->pos++ : aux->pos--;
                    pil->p = pil->p->prox;
                    stc = push(stc, pil);
                    pil = aux;
                    aux = NULL;
                    break;
                }
            }
            pil->p = pil->p->prox;
        }
    }while(!isEmpty(stc));
    stc = freeStack(stc);
    if(pil != NULL)
        free(pil);
}

bool execTurMac(struct turmac **Turmac, unsigned int num_est, std::string &str){
    bool OK = false;
    for(unsigned int i = 0; i < num_est; i++){
        if(Turmac[i]->inicial == true){
            execturmac(Turmac, i, str, 0, OK);
        }
    }
    return OK;
}
