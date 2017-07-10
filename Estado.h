#ifndef __ESTADO_H__
#define __ESTADO_H__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class Estado{
	private:
        char id_est;    //variable que almacena el identificar del estado
		char id_rep;
        int tipe_est;   //variable para saber si el estado es de aceptacion o no
        int num_trans;  //variable para saber si el nº de trans que tiene cada estado
		bool impreso;
		vector<char> transiciones; //vector que almacena las letras de las trancicones y sus numeros(estados)

        int id_conj;    //variable que almacena el identificar del conjunto
	public:
        Estado();       //constructor
       ~Estado();       //destructor
	//***funciones set***//con estos metodos escribimos una nueva propiedad del estado
		void set_id(char);
		void set_id_rep(char);
		void set_tipo(int);
		void set_num_trans(int);
		void set_trans(char);
		void set_id_conj(char);
		void set_impreso(bool);
	//***funciones get***//con estos metodos obtenemos cada propiedad de los estados que necesitemos
	    char get_id();
	    char get_id_rep();
		int get_tipo();
		int get_num_trans();
		char get_trans(int);
		char get_id_conj();
		bool get_impreso();

		void cambia_trans(int pos,char id);
};

#endif
