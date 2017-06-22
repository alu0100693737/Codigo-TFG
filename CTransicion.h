#ifndef CTRANSICION_H
#define CTRANSICION_H

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <stdio.h>
#include <string.h>

class CTransicion{
private:
    int q;
    char c;
    int next_q;


public:
    void setTransicion( int q, char c, int next_q);
    int  getEstado_origen();
    int  getEstado_siguiente();
    char getCaracter();
    void MostrarTransicion();
};

#endif // CTRANSICION_H
