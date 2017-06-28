#ifndef CESTADO_H
#define CESTADO_H



#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include "CTransicion.h"
#include <algorithm>
#include <set>
using namespace std;

using std::vector;
class CEstado{

private:
    bool aceptacion;
    int q_id;
    bool muerte;
    int n_transiciones;
    vector <CTransicion> transiciones;
    set <char> posiblecamino; //Conjunto de caracteres, para determinar si habría un camino posible.
    set <int> ConjuntoEstados;
public:
    void setEstado(bool a, int q, int n_trans);
    bool getAceptacion();
    int get_id();
    void set_id(int i);
    bool getMuerte();
    void MostrarNFA();
    void insertar_transicion(CTransicion tran);
    CTransicion get_transicion(int i);
    int get_n_trans();
    void set_muerte(bool p);
    void set_aceptacion(bool p);
    bool existecamino(char variable);
    void insertar_estado(int q_id);
    set<int> RetornarConjunto();
};

#endif // CESTADO_H
