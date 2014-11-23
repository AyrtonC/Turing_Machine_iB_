//
//  main.cpp
//  Máquina de Turing iB
//
//  Created by Ayrton Cavalieri on 21/11/2014.
//  Copyright (c) 2014 AyrtonC. All rights reserved.
//

#include <iostream>

#include "TurMac.h"

TurMac creatTrans(TurMac mac, unsigned int tam){
    char op, dir;
    bool init = false, final, inicial;
    unsigned int tran;
    char read, subst;
    for(unsigned int i = 0; i < tam; i++){
        inicial = false;
        final = false;
        cout << "Preencher informações sobre o estado " << i+1 << ":" <<endl;
        if(init == false){
            cout << "É inicial? (S - SIM / N - NÃO)" << endl;
            cin >> op;
            if(op == 's' || op == 'S'){
                inicial = true;
                init = true;
            }
        }
        cout << "É final? (S - SIM / N - NÃO)" << endl;
        cin >> op;
        if(op == 's' || op == 'S'){
            final = true;
        }
        cout << "Deseja inserir transições? (S - SIM / N - NÃO)" << endl;
        cin >> op;
        if(op == 'n' || op == 'N'){
            cout << "Digite a direção de deslocamento da fita (R = Direita / L = Esquerda):\n";
            cin >> dir;
            if(dir == 'l' || dir == 'L'){
                dir = 'L';
            }else{
                dir = 'R';
            }
            mac = insTran(mac, i, '\0', '\0', dir, -1, inicial, final);
            break;
        }
        do{
            cout << "Digite o caracter a ser lido (? - Branco):" << endl;
            cin >> read;
            cout << "Digite o caracter de substituição:" << endl;
            cin >> subst;
            cout << "Digite o destino:" << endl;
            cin >> tran;
            tran--;
            cout << "Digite a direção de deslocamento da fita (R = Direita / L = Esquerda):" << endl;
            cin >> dir;
            if(dir == 'l' || dir == 'L'){
                dir = 'L';
            }else{
                dir = 'R';
            }
            mac = insTran(mac, i, read, subst, dir, tran, inicial, final);
            cout << "Deseja inserir outra transição? (S - SIM / N - NÃO)" << endl;
            cin >> op;
        }while(op != 'n' && op != 'N');
    }
    return mac;
}

int main(int argc, const char * argv[]) {
    TurMac mac;
    unsigned int tam;
    string chain;
    bool test;
    
    system("clear");
    cout << "SIMULADOR DE MÁQUINA DE TURING NÃO-DETERMINÍSTICA.\nDigite o nome do arquivo onde está a M.T., caso não exista, uma nova máquina será criada e será salva com o nome do arquivo passado:\n";
    getline(cin, chain);
    if(chain.find(".mt") == string::npos)
        chain += ".mt";
    mac = openTurMac(chain, tam);
    if(!isTurMacInitialized(mac)){
        cout << "Digite a quantidade de estados:" << endl;
        cin >> tam;
        mac = initTurMac(tam);
        if(!isTurMacInitialized(mac)){
            cout << "HEAP ERROR!!!" << endl;
            return 1;
        }
        mac = creatTrans(mac, tam);
        saveTurMac(chain, mac, tam);
    }
    do{
        cout << "Digite a cadeia para teste:" << endl;
        cin >> chain;
        if(chain != "exit"){
            test = execTurMac(mac, tam, chain);
            if(test == true){
                cout << "Cadeia aceita!" << endl;
            }else{
                cout << "Cadeia recusada!\n";
            }
            cout << "Cadeia após processamento:\n" << chain << endl;
        }
    }while(chain != "exit");
    system("clear");
    return 0;
}

