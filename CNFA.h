#ifndef CNFA_H
#define CNFA_H

#include "CEstado.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <set>

class CNFA{

      private:
            /**numero de estados del NFA*/
              int n_estados;
            /**estado inicial*/
              int estado_inic;
            /**nombre del archivo que contiene el NFA*/
              char archivo[50];
            /**array de estados*/
              CEstado* array_estados;
            /**alfabeto extraido del NFA*/
              set<char> alfabeto;

            /**estructura que guarda un nodo de un camino y el caracter con el que viniste al nodo*/
            typedef struct{
                int nodo_actual;
                int caracter;
            }Paso_;


      public:
             /**constructor de NFA*/
             CNFA();

             /**inicializa un NFA desde un fichero*/
             void leer();
             /**muestra el fichero con las especificaciones del automata*/
             void mostrar();
             /**identifica los estados de muerte del NFA*/
             void identificar();
             /**realiza una traza de las transiciones llevadas a cabo cuando se da como entrada una determinada cadena*/
             void analizar();
             /**funcion que analiza si el NFA de entrada es DFA*/
             void es_dfa();
};


#endif // CNFA_H
