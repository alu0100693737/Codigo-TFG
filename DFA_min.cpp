#include "DFA_min.h"

DFA_MIN::DFA_MIN() {
    cont_id_conj = 3;
    cont_acep = 0;
};

DFA_MIN::~DFA_MIN() {
};

void DFA_MIN::Leer_DFA(char nombre[]) {
    char ident;
	int tipe; 			//Varaibles para almacenar los datos del fichero
	int num_trans;
	char trans;

	ifstream textfile;
	textfile.open (nombre);
    if (textfile.is_open()) {
		textfile >> num_est >> est_ini; //leemos el numero de estados y el estado inicial de nuestro nfa(fichero)
		V = new Estado[num_est]; //espacio de memoria para el vector que tendra los estados y sus propiedades
			for(int i=0; i<num_est; i++){ //ahora recorremos cada estado
				textfile >> ident >> tipe >> num_trans; //leemos las propiedades de cada estado hasta la columna 3
				V[i].set_id(ident);
				V[i].set_impreso(true);
				V[i].set_tipo(tipe);			//almacenamos las propiedades en nuestro vector
				/*NUEVO*/
                if(tipe==1) {
                    cont_acep++;
                    V[i].set_id_conj('1');
                } else {
                    V[i].set_id_conj('2');
				}
				/*NUEVO*/
				V[i].set_num_trans(num_trans);
                for(int j=0; j<V[i].get_num_trans()*2; j++) { //recorremos el vector segun el numero de transicion y le ponemos el doble porque tendremos la transicion y el estado
					textfile >> trans; //leemos las transiciones de cada estado
					V[i].set_trans(trans); //almacenamos las transiciones en el vector
				}
			}
	}
}

void DFA_MIN::Exportar_DFA_min() {
	ofstream textfile;
    textfile.open (PATH_TEMPORALDFA);
	if (textfile.is_open()){
		textfile << num_est << endl << est_ini << endl;
		for(int i=0; i<num_est; i++){
			textfile << V[i].get_id()<< " " << V[i].get_tipo() << " " << V[i].get_num_trans() << " ";
			for(int j=0; j<V[i].get_num_trans()*2; j++){
				textfile << V[i].get_trans(j) << " ";
			}
			textfile << endl;
		}
	}
}

int DFA_MIN::long_cadena (char *cadena) {
    int j=0;
    while (cadena[j] != '\0') {j++;}
    return j;
}

int DFA_MIN::Contador_ID(int id) {
    int cont=0;
    for(int i=0; i<num_est; i++) {
        if(id == V[i].get_id_conj() ) {
            cont++;
        }
    }
    return cont;
}
bool DFA_MIN::Comprobar_Trans(int id_conj, char id_trans, int n_trans) {
    bool coincide = true;
    for(int i = 0; i < num_est; i++){
        if(id_conj == V[i].get_id_conj() && id_trans != V[i].get_trans(n_trans * 2)){
            coincide = false;
        }
    }
    return coincide;
}


char DFA_MIN::BuscarEstado(char est) {
    for(int i = 0; i < cont_acep; i++) {
        if(acep[i].get_id() == est) {
            return '1';
        }
    }
    return '2';
}

void DFA_MIN::Cambia_Estado(char id, char rep){
    for(int i = 0; i < num_est; i++){
        if(V[i].get_id() == id){
            V[i].set_impreso(false);
            V[i].set_id_rep(rep);
        }
    }
}

void DFA_MIN::Cambia_Conjunto(Estado *vec, int tam,char id, char tra, char conj){
    for(int i=0; i<tam; i++){
        if(vec[i].get_id() == id){
                vec[i].cambia_trans(tra,conj);
        }
    }
}

void DFA_MIN::Transforma_Conj(Estado *vec, int tam){

    char a;
    int k;
    for(int i=0; i<tam; i++){
        k=1;
        for(int j=1;j<=vec[i].get_num_trans();j++){

            a = BuscarEstado(vec[i].get_trans(k));
            vec[i].cambia_trans(k,a);
            k=k+2;


        }
    }

}
void DFA_MIN::Min_VEc(Estado *vec, int tam, int x){
    int l,k,kk,ll,c=-1;

    for(int i=0; i<tam-1; i++){
        k=1;
        l=1;
        while(k<=vec[i].get_num_trans()){
            for(int j=0; j<tam; j++){
                if(i!=j){
                    if(vec[i].get_id_conj() == vec[j].get_id_conj() && vec[i].get_trans(l) != vec[j].get_trans(l)){
                        char ch = '0' + cont_id_conj;
                        vec[j].set_id_conj(ch);

                        /* LO NUEVO */
                        for(int y=0;y<num_est;y++){
                            kk=1;
                            ll=1;
                            while(kk<=V[y].get_num_trans()){
                                if(V[y].get_trans(ll) == vec[j].get_id()){
                                    Cambia_Conjunto(vec, tam,V[y].get_id(), ll,vec[j].get_id_conj());
                                }
                                kk++;
                                ll=ll+2;
                            }
                        }
                        c=j;
                    }
                }
            }
            k++;
            if(c!=-1){
                //cout << "Con el simbolo '" << vec[c].get_trans(l-1) << "':" << endl;
                //Imprime_DFA(x);
                x++;
                c=-1;
            }
            l=l+2;
        }
        cont_id_conj++;
    }


}
int DFA_MIN::Oculta_Estados(Estado *vec, int tam, int res){
    // Quitar aquellos nodos que han quedado agrupados. ESpecial para cuando el nodo es el final.
    for(int i=0; i<tam-1; i++){
        for(int j=i+1; j<tam; j++){
            if(vec[i].get_id_conj() == vec[j].get_id_conj()){
                Cambia_Estado(vec[j].get_id(),vec[i].get_id());
                res++;
                //Buscar el id_est de j en v y ponerlo a false para que no se tenga en cuenta.
                //Una vez tengamos los false en v hacemos un borrado moviendoa la izquierda
            }
        }
    }
    return res;
}
void DFA_MIN::Check_Trans(){
    //si se agrupa hay que quitar las transiciones que habian al nodo que se elimina. Se coloca el representativo del conjunto

    int l,k=1;
    for(int i=0; i<num_est; i++){
        if(V[i].get_impreso() == false){
            for(int j=0; j<num_est; j++){
                k=1;
                l=1;
                while(k<=V[i].get_num_trans()){
                    if(V[j].get_trans(l) == V[i].get_id()){
                        V[j].cambia_trans(l,V[i].get_id_rep());
                    }
                    k++;
                    l=l+2;
                }
            }
        }
    }

}
//Especial para cuando  hay un nodo en medio que no debe tenerse en cuenta.
void DFA_MIN::Borrar_Estados(){

    for(int i=0; i<num_est; i++){
        if(V[i].get_impreso() == false){
            for(int j=i+1; j<num_est; j++){
                V[j-1]=V[j];
            }
        }
    }

}
void DFA_MIN::Minimizar_DFA(){
    int x=0;
    Transforma_Conj(acep, cont_acep);
    Transforma_Conj(noacep, num_est-cont_acep);
    //imprime2();
    //Imprime_DFA(x);
    x++;

    int l,k,kk,ll,c=-1;

    Min_VEc(acep, cont_acep, x);
    Min_VEc(noacep, num_est-cont_acep, x);

    //imprime2();
    int res=0;
    int tam2=num_est-cont_acep;

    res = Oculta_Estados(acep, cont_acep, res);
    res = Oculta_Estados(noacep, tam2, res);

    Check_Trans();
    Borrar_Estados();

    num_est = num_est-res;


};

void DFA_MIN::Divide_DFA(){
    int i_acep=0,i_noacep=0;

    acep = new Estado[cont_acep];
    noacep = new Estado[num_est-cont_acep];

    //Separamos en aceptacion y no aceptacion.
    for(int i=0; i<num_est; i++){
        if(V[i].get_tipo()==1){
            acep[i_acep]=V[i];
            acep[i_acep].set_impreso(false);
            i_acep++;
        }else{
            noacep[i_noacep]=V[i];
            noacep[i_noacep].set_impreso(false);
            i_noacep++;
        }
    }
};
