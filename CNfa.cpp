#include <iostream>
#include <iterator>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <string>
#include "CNfa.h"
#include <fstream>
#include <QString>
#include <QStringList>
using std::vector;
using std::set;
using std::string;

using namespace std;

void CNFA::ConstruirNFA(QString nombrefichero){
    QStringList list;
    list = nombrefichero.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    n_estados = list.at(0).toInt();
    cout << "Numero de nodos " << n_estados << endl;
    list.removeAt(0);
    inicial = list.at(0).toInt();
    cout << "Nodo inicial " << inicial << endl;
    list.removeAt(0);

    for(int i = 0; i < n_estados; i++) {
        if(list.size() > 0) {
            int id;
            int n;
            id = list.at(0).toInt();
            list.removeAt(0);
            n = list.at(0).toInt();
            list.removeAt(0);
            //nombrefichero >> id >> n;
            bool a;
            if (n == 0)
                a = false;
            else
                a = true;


            bool estado_muerte;

            if(a == true)
                estado_muerte = false;

            else
                estado_muerte = true;

            int n_trans;
            n_trans = list.at(0).toInt();
            cout << id << " " << a << " " << n_trans << " ";
            list.removeAt(0);

            CEstado estado;
            estado.setEstado(a, id, n_trans);

            for(int s =0; s < n_trans; s++) {
                char caracter;
                int destino;

                CTransicion transi;

                caracter = list.at(0).toStdString().at(0);
                list.removeAt(0);

                destino = list.at(0).toInt();
                list.removeAt(0);
                cout << caracter << " " << destino << " ";
                if((id != destino) && (a == false)){  // estado de muerte = destino y origen iguales y estado de NO aceptacion
                    estado_muerte = false;
                }

                transi.setTransicion( id, caracter, destino);
                estado.insertar_transicion(transi);
            }
            cout << endl;
            estado.set_muerte(estado_muerte);
            Q_.push_back(estado);
        } else { i = n_estados;}
    }

    while(Q_.size() < n_estados) {
        for(int i = 0; i < n_estados; i++) {
            bool encontrado = false;
            for(int l = 0; l < Q_.size(); l++) {
                if(Q_.at(l).get_id() == i)
                    encontrado = true;
            }
            if(encontrado == false) {
                CEstado estado;
                cout << i << " " << 0 << " " << 0 << endl;
                estado.setEstado(0, i, 0);
                estado.set_muerte(true);
                Q_.push_back(estado);
            }
        }
    }
    cout << "Adios " << endl;
}

string CNFA::AnalizarCadena(string &cadena){
    int t = -1;
    CEstado q = encontrarEstado(inicial);

    vector<CTransicion> caminos;

    bool aceptada = false;

    Analizar(q, cadena, t, caminos, aceptada);

    if(aceptada == true){
        return "\nDecision final: Cadena SI aceptada";
    }

    else{
        return "\nDecision final: Cadena NO aceptada";
    }
}

bool CNFA::Analizar(CEstado &q, string &cadena, int t, vector<CTransicion> &Caminos, bool &acepta){

    int a = t+1;
    if(q.existecamino(cadena[a]) || q.existecamino('~')){ //Saber si hay algun camino desde este estado con ese caracter o con caracter ~
        for(int i=0; i < q.get_n_trans(); i++){
            CTransicion trans = q.get_transicion(i);

            if(trans.getCaracter() == cadena[a]){
                CEstado siguiente = encontrarEstado(trans.getEstado_siguiente());
                Caminos.push_back(trans);

                if( a == cadena.length()-1){
                    if(siguiente.getAceptacion() == true){
                        MostrarCamino(Caminos);
                        cout << endl << "la cadena SI es aceptada";
                        acepta = true;
                        if(siguiente.existecamino('~')){
                            Analizar(siguiente, cadena, cadena.length()-1, Caminos, acepta);
                        }
                        Caminos.pop_back();
                    }

                    else{
                        MostrarCamino(Caminos);
                        cout << endl << "la cadena NO es aceptada";
                        if(siguiente.existecamino('~')){
                            Analizar(siguiente, cadena, cadena.length()-1, Caminos, acepta);
                        }
                        Caminos.pop_back();
                    }
                }

                else{
                    Analizar(siguiente, cadena, a, Caminos, acepta);
                    Caminos.pop_back();
                }
            }

            if(trans.getCaracter() == (int)'~'){
                CEstado siguiente = encontrarEstado(trans.getEstado_siguiente());
                Caminos.push_back(trans);

                if( a == cadena.length()){ // Sin -1 porque si es el ultimo valor, no coge el de la cadena y muestra el camino sin el valor, se supone en este caso que la los valores de la cadena ya se han recorrido
                    if(siguiente.getAceptacion() == true) {
                        MostrarCamino(Caminos);
                        cout << endl << "la cadena SI es aceptada";
                        acepta = true;
                        if(siguiente.existecamino('~')) {
                            Analizar(siguiente, cadena, cadena.length()-1, Caminos, acepta);
                        }
                        Caminos.pop_back();
                    }

                    else{
                        MostrarCamino(Caminos);
                        cout << endl << "la cadena NO es aceptada";
                        if(siguiente.existecamino('~')) {
                            Analizar(siguiente, cadena, cadena.length()-1, Caminos, acepta);
                        }
                        Caminos.pop_back();
                    }
                }

                else{
                    Analizar(siguiente, cadena, a-1, Caminos, acepta); // a-1 para que siga en la misma posicion del vector cadena
                    Caminos.pop_back();
                }
            }
        }
    }
    else { //NO hay camino para caracter de la cadena o con caracter ~
        MostrarCamino(Caminos);
        cout << endl << "No existe camino para determinar la cadena" << endl;
    }

    return acepta;
}

void CNFA::MostrarCamino(vector<CTransicion> &Camino) {
    cout << endl << endl << " Camino: " << endl;

    for(int i=0; i < Camino.size(); i++){
        Camino[i].MostrarTransicion();
    }
    cout << endl;
}

CEstado CNFA::encontrarEstado(int q_id) {
    for(int i=0; i < Q_.size(); i++){
        if(Q_[i].get_id() == q_id){
            return Q_[i];
        }
    }
}

string CNFA::MostrarEstadosMuerte() {
    string aux;
    for(int i=0; i < Q_.size(); i++){
        if(Q_[i].getMuerte() ){
            aux += "El estado ";
            stringstream strs;
              strs << Q_[i].get_id();
              aux += strs.str();

            aux += " es un estado de muerte \n";
        }
    }
    return aux;
}

void CNFA::MostrarNFA() {
    cout << endl << "	NFA" << endl;
    for(int i= 0; i < Q_.size(); i++){
        Q_[i].MostrarNFA();
    }
    MostrarAlfabeto();
}

void CNFA::CrearAlfabeto() {
    CTransicion auxiliar;
    for(int i=0; i < Q_.size(); i++) {
        for(int j=0; j < Q_[i].get_n_trans(); j++) {
            auxiliar = Q_[i].get_transicion(j);
            if(auxiliar.getCaracter() != '~'){
                Alfabeto.insert(auxiliar.getCaracter());
            }
        }
    }
}

string CNFA::MostrarAlfabeto() {
    string aux;
    aux.append("\n Alfabeto \n");
    aux.append("{ ");
    for (set<char>::iterator it = Alfabeto.begin(); it != Alfabeto.end(); it++) {
        aux += *it;
                aux.append(" ");
    }
    aux.append("} ");
    return aux;
}

void CNFA::epsilonClosure(CEstado &q, CEstado &A) {

    A.insertar_estado(q.get_id());

    if(q.existecamino('~')) {
        for(int i =0; i < q.get_n_trans(); i++) {
            CTransicion aux;
            aux = q.get_transicion(i);

            if(aux.getCaracter() == '~') {
                CEstado auxiliar = encontrarEstado(aux.getEstado_siguiente());
                epsilonClosure(auxiliar, A);
            }
        }
    }
}


void CNFA::epsilonClosure(CEstado &A) {
    set<int> auxiliar = A.RetornarConjunto();

    for(set<int>::iterator i = auxiliar.begin(); i != auxiliar.end(); i++) {
        int aux = *i;
        CEstado auxx = encontrarEstado(aux);
        epsilonClosure(auxx, A);
    }
}

CEstado CNFA::move(set<int> &A, char simbolo) {
    CEstado NuevoEstado;
    for(set<int>::iterator a = A.begin(); a != A.end(); a++) {
        int i = *a;
        CEstado auxiliar = encontrarEstado(i);

        if( auxiliar.existecamino(simbolo)) {
            for(int j=0; j < auxiliar.get_n_trans(); j++) {
                CTransicion aux;
                aux = auxiliar.get_transicion(j);
                if(aux.getCaracter() == simbolo){
                    NuevoEstado.insertar_estado(aux.getEstado_siguiente());
                }
            }
        }
    }

    epsilonClosure(NuevoEstado);
    return NuevoEstado;
}

int CNFA::Encontrarpos(CEstado &A, vector<CEstado> &Orden) {
    set<int> aux1 = A.RetornarConjunto();

    for(int i=0; i < Orden.size(); i++) {
        set<int> aux2 = Orden[i].RetornarConjunto();
        if(igualdad(aux1, aux2) == true) {
            return i;
        }
    }
}

void CNFA::aceptacion_id(vector<CEstado> &Orden) {
    for(int y=0; y < Orden.size(); y++) {
        Orden[y].set_id(y);
        Orden[y].set_aceptacion(false);
    }

    for(int i=0; i < n_estados; i++){
        if(Q_[i].getAceptacion() == true) {
            int aux = Q_[i].get_id();
            set<int> aux1;
            aux1.insert(aux);

            for(int j=0; j < Orden.size(); j++) {
                set<int> aux2 = Orden[j].RetornarConjunto();

                if( includes(aux2.begin(), aux2.end(), aux1.begin(), aux1.end())) {
                    Orden[j].set_aceptacion(true);
                }
            }
        }
    }
}

bool CNFA::Existe(CEstado &A, vector<CEstado> &Orden) {
    bool aux = false;
    set<int> aux1 = A.RetornarConjunto();

    for(int i=0; i < Orden.size(); i++){
        set<int> aux2 = Orden[i].RetornarConjunto();
        if(igualdad(aux1, aux2) == true) {
            aux = true;
        }
    }
    return aux;
}

vector<CEstado> CNFA::ConverttoDFA() {
    cout << "Entre " << endl;
    vector<CTransicion> transiciones;
    vector<CEstado> Orden;
    vector<CEstado> Cola;

    CEstado A;
    CEstado auxiliar = encontrarEstado(inicial);
    epsilonClosure(auxiliar, A);

    Orden.push_back(A);
    Cola.push_back(A);

    while(! Cola.empty()) {
        CEstado aux = Cola[0];
        vector<CEstado>::iterator pop = Cola.begin();
        Cola.erase(pop);

        set<int> conjuntoauxiliar = aux.RetornarConjunto();

        for(set<char>::iterator i = Alfabeto.begin(); i != Alfabeto.end(); i++) {
            char simb = *i;

            CEstado aux1 = move(conjuntoauxiliar, simb);

            if((! Existe(aux1, Cola)) && (!Existe(aux1, Orden))) {
                Cola.push_back(aux1);
                Orden.push_back(aux1);
            }

            CTransicion auxtrans;

            int origen = Encontrarpos(aux, Orden);
            int destino = Encontrarpos(aux1, Orden);

            auxtrans.setTransicion(origen, simb, destino);
            Orden[origen].insertar_transicion(auxtrans);
        }
    }

    aceptacion_id(Orden);

    cout << endl << endl << "NFA TO DFA" << endl << endl;

    cout << "orden size " << Orden.size() << endl;
    for(int u=0; u < Orden.size(); u++){
        Orden[u].MostrarNFA();
    }

    set<int> auzz;

    cout << endl << endl;

    for(int t=0; t < Orden.size(); t++){
        auzz = Orden[t].RetornarConjunto();

        cout << endl << "El estado " << Orden[t].get_id() << " contiene los estados : " << endl;

        cout << "{";
        for(set<int>::iterator r = auzz.begin(); r != auzz.end(); r++){
            cout << *r << "  ";
        }
        cout << "}";
    }
    return Orden;
}

bool CNFA::igualdad(set<int> &A, set<int> &B){
    if( (includes(B.begin(), B.end(), A.begin(), A.end())) && (includes(A.begin(), A.end(), B.begin(), B.end()) )){
        return true;
    }
    else{
        return false;
    }
}


void CNFA::Exportar(vector<CEstado> &Orden){
    int t;

    ofstream fout(PATH_TEMPORALDFA);
    fout << Orden.size() << endl;
    fout << 0 << endl;

    for(int x=0; x < Orden.size(); x++){
        if(Orden[x].getAceptacion() == true){
            t = 1;
        }

        else {
            t=0;
        }
        fout << Orden[x].get_id() << " " << t << " " << Alfabeto.size();

        for(int p=0; p < Alfabeto.size(); p++){
            CTransicion auxiliar = Orden[x].get_transicion(p);
            fout << " " << auxiliar.getCaracter() << " " << auxiliar.getEstado_siguiente();
        }
        fout << endl;
    }
    fout.close();
}

