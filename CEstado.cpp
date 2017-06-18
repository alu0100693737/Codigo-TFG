#include "CEstado.h"

#include <stdio.h>
#include <iostream>

CEstado::CEstado(){
    estado_num = 0;
    acepta = true;
    num_trans = 0;
}


void CEstado::set_estado_num(int a) {
    estado_num = a;
}

int CEstado::get_estado_num() {
    return estado_num;
}

void CEstado::set_estado(bool a_n){
    acepta = a_n;
}

bool CEstado::get_estado() {
    return acepta;
}

void CEstado::set_num_transic(int tran) {
    num_trans = tran;
    simbolo = new char[num_trans];
    destino = new int [num_trans];
}

int CEstado::get_num_transic(){
    return num_trans;
}

void CEstado::set_simbolos(int i, char dato){
    simbolo[i]=dato;
}

char CEstado::get_simbolos(int i){
    return simbolo[i];
}

void CEstado::set_destino(int i,int dato){
    destino[i]=dato;
}

int CEstado::get_destino(int i){
    return destino[i];
}

void CEstado::mostrar() {
    cout << "Estado " << estado_num << " aceptacion " << acepta << endl;
    cout << "Tiene " << num_trans << endl;
    for(int i = 0; i < strlen(simbolo); i++) {
        cout << "Simbolo " << simbolo[i] << " Destino " << destino[i] << endl;
    }
}

