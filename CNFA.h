#include "CEstado.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <set>
#include <queue>

class CDFA{

    private:
        int n_estados;
        int estado_inic;
        char archivo[50];
        CEstado* array_estados;

        /**alfabeto extraido del NFA*/
                      set<char> alfabeto;

                      /**estructura que guarda un nodo de un camino y el caracter con el que viniste al nodo*/
                              typedef struct{
                                  int nodo_actual;
                                  int caracter;
                              }Paso_;
    public:
        CDFA();

        void leer();		//inicializa un DFA desde un fichero
        void mostrar();
        void identificar();	//identifica los estados de muerte del DFA
        void analizar();	//realiza una traza de las transiciones llevadas a cabo cuando se da como entrada una determinada cadena.
        /**funcion que analiza si el NFA de entrada es DFA*/
                void es_dfa();
};

