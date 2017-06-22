#include "CEstado.h"


#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include "CEstado.h"

using namespace std;

void CEstado::setEstado(bool a, int q, int n_trans){
    aceptacion = a;
    q_id = q;
    n_transiciones = n_trans;
}


void CEstado::MostrarNFA(){
    for (int i= 0; i < transiciones.size(); i++){
        transiciones[i].MostrarTransicion();
    }
}

void CEstado::set_aceptacion(bool p){
    aceptacion = p;
}


void CEstado::set_id(int i){
    q_id = i;
}

bool CEstado::getAceptacion(){
    return aceptacion;

}


int CEstado::get_id(){
    return q_id;
}

int CEstado::get_n_trans(){
    return n_transiciones;
}

bool CEstado::getMuerte(){
    return muerte;
}

void CEstado::insertar_transicion(CTransicion tran){
    transiciones.push_back(tran);
    posiblecamino.insert(tran.getCaracter());
}

CTransicion CEstado::get_transicion(int i){
    return transiciones[i];
}

void CEstado::set_muerte(bool p){
    muerte = p;
}

bool CEstado::existecamino(char variable){
    set <char> aux;
    aux.insert(variable);
    return includes(posiblecamino.begin(), posiblecamino.end(), aux.begin(), aux.end());
}

void CEstado::insertar_estado(int q_id){
    ConjuntoEstados.insert(q_id);
}

set<int> CEstado::RetornarConjunto(){
    return ConjuntoEstados;
}
