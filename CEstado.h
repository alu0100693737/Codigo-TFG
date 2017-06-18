#ifndef CESTADO_H
#define CESTADO_H

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class CEstado{

private:
    ///estado en el que te encuentras
    int estado_num;
    ///si es un estado de aceptacion
    bool acepta;
    ///numero de transiciones de ese estado
    int num_trans;
    ///array de simbolos que salen de ese estado
    char* simbolo;
    ///array de destinos de los respectivos simbolos
    int* destino;

public:
    /**constructor de estados*/
    CEstado();

    /**funcion a la que se le pasa el indice de cada estado*/
    void set_estado_num(int a);
    /**funcion que devuelve el indice de cada estado*/
    int get_estado_num();
    /**funcion a la que se le pasa si es un estado de aceptacion*/
    void set_estado(bool a_n);
    /**funcion que devuelve si es de aceptacion*/
    bool get_estado();
    /**funcion a la que se le pasa el numero de transiciones*/
    void set_num_transic(int tran);
    /**funcion que devuelve el numero de transiciones*/
    int get_num_transic();
    /**funcion a la que se le pasa todos los simbolos*/
    void set_simbolos(int i, char dato);
    /**funcion que devuelve los simbolos*/
    char get_simbolos(int i);
    /**funcion a la que se le pasa todos los destinos o estados siguientes*/
    void set_destino(int i,int dato);
    /**funcion que devuelve los destinos*/
    int get_destino(int i);

    void mostrar();

};



#endif // CESTADO_H
