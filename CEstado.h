#ifndef CESTADO_H
#define CESTADO_H
#include <iostream>
using namespace std;

class CEstado {
private:
    int inicio_;
    int destino_;
    char letraTransicion_;
public:
    CEstado(int inicial, int final, char letra);
    int getInicio();
    int getDestino();
    char getLetraTransicion();
    void mostrar();
};

#endif // CESTADO_H
