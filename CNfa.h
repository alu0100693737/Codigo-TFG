
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>    // std::find
#include <QString>
using std::vector;
using std::set;
using std::string;
#include "CEstadoNFA.h"
#include "CTransicion.h"

#include <sstream>
using namespace std;
#define PATH_TEMPORALDFA "/home/ivan/Documentos/Codigo-TFG/codificaciones/temporalDFA.txt"

class CNFA{

private:
    vector<CEstado> Q_;
    int inicial;
    int n_estados;
    set<char> Alfabeto;
public:

    CEstado encontrarEstado(int q_id);
    void ConstruirNFA(QString nombrefichero);
    string MostrarEstadosMuerte();
    void MostrarNFA();
    bool Analizar(CEstado &q, string &cadena, int t, vector<CTransicion> &caminos, bool &acepta);
    string AnalizarCadena(string &cadena);
    void MostrarCamino(vector<CTransicion> &Camino);
    void CrearAlfabeto();
    string MostrarAlfabeto();
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
