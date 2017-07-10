
#ifndef __DFA_H__
#define __DFA_H__

#include "Estado.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <set>
#define PATH_TEMPORALDFA "/home/ivan/Documentos/Codigo-TFG/codificaciones/temporalDFA.txt"

class DFA_MIN {

	 private:
        Estado *V;      //vector donde se almacena la letra y su transicion
        int num_est;    //variable para almacenar el numero de estados
        int est_ini;    //variable para almacenar el numero del estado inicial

        int cont_id_conj;
		Estado *acep;
		Estado *noacep;
		int cont_acep;

	 public:
        DFA_MIN();
       ~DFA_MIN();
        void Leer_DFA(char nombre[]);//lee el fichero
        void Exportar_DFA_min();//metodo para una vez obtenido el DFA minimizado presentamos la minimizacion en un fichero
        int long_cadena(char *);//metodo que nos devuelve la longuitud de la cadena que introduce el usuario
        void Minimizar_DFA(); //metodo que nos realiza las llamadas para hacer por partes la minimizacion de estados
        void Divide_DFA(); //para dividir el DFA en dos conjuntos de aceptacion y no aceptacion
        int Contador_ID(int id); //contador id para saber en que conjunto estamos
        bool Comprobar_Trans(int id_conj, char id_trans, int n_trans); //comprobamos las transiciones de los estados entre diferentes conjuntos
        char BuscarEstado(char est); //metodo para buscar el estado 
        void Cambia_Estado(char id, char rep);//para cambiar el estado de transicion en casp 
        void Cambia_Conjunto(Estado *vec, int tam,char id, char tra, char conj);
        void Transforma_Conj(Estado *vec, int tam); //para separar el conjunto en caso de que se tenga que hacer
        void Min_VEc(Estado *vec, int tam, int x);
        int Oculta_Estados(Estado *vec, int tam, int res); //para quitar el estado o estados que sobran cuando el nodo(estado) es el ultimo
        void Check_Trans();//para cambiar las transiciones del nodo que se elimina
        void Borrar_Estados(); //para quitar el estado o estados que sobran cuando el nodo(estado) no es el ultimo
};

#endif
