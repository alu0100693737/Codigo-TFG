#include "CEstado.h"

CEstado::CEstado(int inicial, int destino, char letra) {
    inicio_ = inicial;
    destino_ = destino;
    letraTransicion_ = letra;
}

int CEstado::getInicio() {
    return inicio_;
}

int CEstado::getDestino() {
    return destino_;
}

char CEstado::getLetraTransicion() {
    return letraTransicion_;
}

void CEstado::mostrar() {
    cout << "Inicio " << getInicio() << " destino: " << getDestino() << " letra " << getLetraTransicion() << endl;
}
