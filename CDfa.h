#ifndef CDFA_H
#define CDFA_H
#include <iostream>
#include <fstream>
#include "CEstado.h"
#include <vector>
#include <QString>
#include <QStringList>
using namespace std;
// inicio final letra
class CDFA {
    int estadoInicial_;
    int numNodos_;
    vector<int>* finales_;
    vector<CEstado>* transiciones_;
    void leerFichero();
public:
    CDFA();

    void detectarEstadosMuerte();
    void analizarCadena();

    vector<CEstado>* getTransiciones();
    void setTransiciones(vector<CEstado>* copia);
    vector<int>* getFinales();

    int getEstadoInicial();
    int getNumNodos();

    void mostrarDFA();
    void mostrarTransiciones();
    void mostrarEstadosFinales();
};

#endif // CDFA_H
