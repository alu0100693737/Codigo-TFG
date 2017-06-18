#include "CNFA.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

CNFA::CNFA():								//constructor del NFA
             n_estados(0),
             estado_inic(0),
             array_estados(NULL)
             {

            array_estados = new CEstado[n_estados];		//crea los estados del NFA
             }


void CNFA::leer(){				//funcion que lee un NFA desde un fichero

     cout << "Introduzca el nombre del fichero: ";
     cin >> archivo;

    ifstream in;

    char entrada;
    int q, w, j, s;
    char e;
    bool p;
    in.open(archivo);
    if(in.good()){							//si no hubo error de apertura
        in >> n_estados >> estado_inic;
        array_estados = new CEstado[n_estados];
        cout << n_estados << " " << estado_inic << endl;
        for (int i=0; i<n_estados; i++){
            in >> q >> p >> w;
            array_estados[i].set_estado_num(q);
            array_estados[i].set_estado(p);
            array_estados[i].set_num_transic(w);
            for (int m=0; m<w; m++){
                in >> e >> j;
                alfabeto.insert(e);
                array_estados[i].set_simbolos(m,e);
                array_estados[i].set_destino(m,j);
                array_estados[i].mostrar();
            }

            cout << "HOLA" << endl;
        }

        if (!in.eof()){
            cout << "Error :Fichero mal estructurado "<<endl; //si no se ha llegado al final, el fichero esta mal definido
        }
    }else
        cout << endl << "FALLO AL ABRIR EL ARCHIVO" << endl;

    in.close();

}

void CNFA::mostrar(){					//funcion que muestra la definicion del NFA como se ve en el fichero
    if(n_estados == 0)
        cout << "\nCargue primero un DFA" << endl;
    else{
        cout << endl << "FICHERO " << archivo << endl;

        cout << "\nAlfabeto = {";
        set<char>::iterator i = alfabeto.begin();
        while(i != alfabeto.end())
            cout << " " << *i++ << ",";
        cout << "}" << endl;

        cout << endl << n_estados << endl;
        cout << estado_inic << endl;

        for (int i=0; i<n_estados; i++){
            cout << array_estados[i].get_estado_num() << " ";
            cout << array_estados[i].get_estado() << " ";
            cout << array_estados[i].get_num_transic() << " ";
            if(array_estados[i].get_num_transic() == 0) cout << "	<--- No tiene transiciones";
            else{
                 for (int m=0; m<array_estados[i].get_num_transic(); m++){
                    cout << array_estados[i].get_simbolos(m) << " ";
                    cout << array_estados[i].get_destino(m) << " ";
                 }
            }
            cout << endl;
        }
    }

}

void CNFA::identificar(){			//funcion que identifica los estados de muerte del NFA
    if(n_estados == 0)
        cout << "\nCargue primero un DFA" << endl;
    else{
        int muertes = 0;
        for(int i = 0; i < n_estados; i++){
            if(array_estados[i].get_num_transic() == 0){
                muertes++;
                cout << endl << "EL ESTADO " << i << " ES DE MUERTE" << endl;
            }
            else{
                for(int j = 0; j < array_estados[i].get_num_transic(); j++){
                    if(array_estados[i].get_destino(j) != array_estados[i].get_estado_num())
                        break;
                    else{
                        if(j == array_estados[i].get_num_transic()-1){
                            muertes++;
                            cout << endl << "EL ESTADO " << i << " ES DE MUERTE" << endl;
                        }
                    }
                }
            }
        }
        cout << endl << endl << "TIENE " << muertes << " ESTADO(S) DE MUERTE" << endl;
    }
}

void CNFA::analizar(){			//funcion que analiza una cadena introducida por el usuario y muestra los caminos posibles
    if(n_estados == 0)
        cout << "\nCargue primero un DFA" << endl;
    else{
        string cadena;

        cout << endl << "Introduzca una cadena para analizar: ";
        cin >> cadena;
        cout << endl << endl <<"Cadena de entrada: " << cadena << endl;


        typedef vector<Paso_> camino;

        vector<camino> acabados;
        queue<camino> pendientes;

        vector<Paso_> aux;
        Paso_ dummy;
        dummy.nodo_actual = estado_inic;
        dummy.caracter = 0;
        aux.push_back(dummy);
        pendientes.push(aux);

        while(!pendientes.empty()){
            for(int i = 0; i < pendientes.front().size(); i++)
                cout << pendientes.front()[i].nodo_actual << " ";
            cout << endl;
            aux = pendientes.front();
            pendientes.pop();
            int mayor = 0;		//elemento de la cadena por la que voy
            for(int j = 0; j < aux.size(); j++)
                if(mayor < aux[j].caracter)
                    mayor = aux[j].caracter;

            bool fin = true;
            for(int i = 0; i < array_estados[aux.back().nodo_actual].get_num_transic(); i++){
                if(array_estados[aux.back().nodo_actual].get_simbolos(i) == '~'){
                    fin = false;
                    vector<Paso_> aux2 = aux;
                    Paso_ dummy;
                    dummy.nodo_actual = array_estados[aux.back().nodo_actual].get_destino(i);
                    dummy.caracter = 0;
                    aux2.push_back(dummy);
                    pendientes.push(aux2);
                }
                if(array_estados[aux.back().nodo_actual].get_simbolos(i) == cadena[mayor]){
                    fin = false;
                    vector<Paso_> aux2 = aux;
                    Paso_ dummy;
                    dummy.nodo_actual = array_estados[aux.back().nodo_actual].get_destino(i);
                    dummy.caracter = mayor+1;
                    aux2.push_back(dummy);
                    pendientes.push(aux2);
                }
            }
            if(fin == true)
                acabados.push_back(aux);
        }
        for(int i = 0; i < acabados.size(); i++){
            for(int j = 0; j < acabados[i].size(); j++){
                cout << " ";
                if(acabados[i][j].caracter != 0)
                    cout << cadena[acabados[i][j].caracter-1];
                else
                    cout << "~";
                cout << ";" << acabados[i][j].nodo_actual;
            }
            cout << endl;
        }

        /////AQUI SE MUESTRAN LOS DIFERENTES CAMINOS
        bool aceptada = false;

        for(int i = 0; i < acabados.size(); i++){
            int cont_cadena = 0;
            cout << "\nCamino " << i+1 << ":" << endl;
            cout << "Estado actual		Entrada		Siguiente estado" << endl;
            cout << acabados[i][0].nodo_actual << "			";
            for(int j = 0; j < acabados[i].size()-1; j++){
                if(acabados[i][j+1].caracter == 0)
                    cout << "\u03B5  		";
                else{
                    cont_cadena++;
                    cout << cadena[acabados[i][j+1].caracter-1] << "  		";
                }
                cout << acabados[i][j+1].nodo_actual << endl;
                //if(cont_cadena == )
                cout << acabados[i][j+1].nodo_actual << "			";

            }
            cout << "\nCadena de entrada ";
            if((array_estados[acabados[i].back().nodo_actual].get_estado() == true) && (cont_cadena == cadena.size())){
                cout << "ACEPTADA";
                aceptada = true;
            }
            else cout << "NO ACEPTADA";
            cout << endl;
        }
        cout << "\n\nDecision final:\nCadena de entrada ";
        if(aceptada == true) cout << "ACEPTADA\n";
        else cout << "NO ACEPTADA\n";
        cout << endl;
    }
}

void CNFA::es_dfa(){
    if(n_estados == 0)
        cout << "\nCargue primero un DFA" << endl;
    else{
        bool acierto = true;
        set<char> aux;

        for(int i = 0; i < n_estados; i++){
            if(array_estados[i].get_num_transic() == alfabeto.size()){
                aux = alfabeto;
                for(int j = 0; j < array_estados[i].get_num_transic(); j++){
                    if(aux.count(array_estados[i].get_simbolos(j)))
                        aux.erase(array_estados[i].get_simbolos(j));
                    else{
                        acierto = false;
                        break;
                    }
                }
            }
            else{
                acierto = false;
                break;
            }
        }
        if(acierto == true) cout << "\nSi";
        else cout << "\nNo";
        cout << " es un dfa." << endl;
    }
}
