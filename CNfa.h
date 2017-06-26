
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <string>
#include <QString>
using std::vector;
using std::set;
using std::string;
#include "CEstado.h"
#include "CTransicion.h"

#include <sstream>


class CNFA{

private:
    vector<CEstado> Q_;
    int inicial;
    int n_estados;
    set<char> Alfabeto;
public:

    CEstado EncontrarEstado(int q_id);
    void ConstruirNFA(QString nombrefichero);
    void MostrarEstadosMuerte();
    void MostrarNFA();
    bool Analizar(CEstado &q, string &cadena, int t, vector<CTransicion> &caminos, bool &acepta);
    void AnalizarCadena(string &cadena);
    bool Analizar2(CEstado &q, string &cadena, int t, vector<CTransicion> &caminos, bool &acepta);
    bool AnalizarCadena2(string &cadena);
    void MostrarCamino(vector<CTransicion> &Camino);
    void CrearAlfabeto();
    void MostrarAlfabeto();
    void epsilonClosure(CEstado &q, CEstado &A);
    void epsilonClosure(CEstado &A);
    CEstado move(set<int> &A, char simbolo);
    int Encontrarpos(CEstado &A, vector<CEstado> &Orden);
    bool Existe(CEstado &A, vector<CEstado> &Orden);
    vector<CEstado> ConverttoDFA();
    bool igualdad(set<int> &A, set<int> &B);
    void aceptacion_id(vector<CEstado> &Orden);
    void Exportar(vector<CEstado> &Orden);
};
