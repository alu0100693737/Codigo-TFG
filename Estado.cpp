//
//
// Practica 5: Simplificacion de un DFA
//
//  Autor: Alberto Martínez Chincho
//
//

#include "Estado.h"
Estado::Estado(){
};

Estado::~Estado(){
};
/*******Funciones set*******/
void Estado::set_id(char x){			//introducimos un nuevo estado
	id_est = x;
}

void Estado::set_id_rep(char x){			//introducimos un nuevo estado
	id_rep = x;
}

void Estado::set_tipo(int x){			//introducimos si el nuevo estado es de aceptacion o no
	tipe_est = x;
}

void Estado::set_num_trans(int x){		//introducimos el numero de transicion del nuevo estado
	num_trans = x;
}

void Estado::set_trans(char sig){		//introducimos en el vector las transiciones y con que simbolos lo hace
	transiciones.push_back(sig);
}

void Estado::set_id_conj(char x){		//introducimos el identificador del conjunto al que pertenece el estado
	id_conj = x;
}
void Estado::set_impreso(bool x){
	impreso = x;
}


/*******Funciones get*******/
char Estado::get_id(){			//nos devuelve el identificardor del estado en el que estemos
	return id_est;
}
char Estado::get_id_rep(){			//nos devuelve el identificardor del estado en el que estemos
	return id_rep;
}
int Estado::get_tipo(){			//nos devuelve si el estado en el que estamos es de aceptacion o no
	return tipe_est;
}

int Estado::get_num_trans(){	//nos devuelve el numero de transiciones de nuestro NFA
	return num_trans;
}

char Estado::get_trans(int i){	//nos devuelve al valor de la transicion en la que estamos
	return transiciones[i];
}

char Estado::get_id_conj(){			//nos devuelve el identificardor del conjunto al que pertenece el estado
	return id_conj;
}
bool Estado::get_impreso(){
	return impreso;
}
/* FIN DE SETTER Y GETTER */
void Estado::cambia_trans(int pos,char id){
	transiciones[pos] = id;
}
