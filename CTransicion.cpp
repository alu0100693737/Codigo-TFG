#include "CTransicion.h"

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include "CTransicion.h"

using namespace std;

void CTransicion::setTransicion( int origen, char caracter, int B){
    q = origen;
    c = caracter;
    next_q = B;
}

int  CTransicion::getEstado_siguiente(){
    return next_q;
}


char CTransicion::getCaracter(){
    return c;
}

void CTransicion::MostrarTransicion(){
    cout <<endl << "Inicio " << q << " con caracter " << c << " al estado " << next_q;
}
