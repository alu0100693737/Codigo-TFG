#include "CDfa.h"

CDFA::CDFA() {
    transiciones_ = new vector<CEstado>();
    finales_ = new vector<int>();
    leerFichero();
}

void CDFA::detectarEstadosMuerte() {
    cout << "\nEstados de muerte:" << endl;
    std::vector<int>::iterator it;
    for(int i = 0; i < getNumNodos(); i++) {
        bool encontrado = false;
        for(int j = 0; j < getTransiciones()->size(); j++) {
            if(getTransiciones()->at(j).getInicio() == i) {
                encontrado = true;
                break;
            }
        }
        if(encontrado == false ) {
            cout << " el Nodo " << i << " es un estado de Muerte " << endl;
        }
    }
}

void CDFA::analizarCadena() {
    cout << "Introduzca una cadena " << endl;
    string cadena;
    cin >> cadena;
    cout << "\nCadena de entrada: " << cadena << endl;
    const char *cstr = cadena.c_str();
    int estadoActual = getEstadoInicial();
    int contador = 0; //posicion de la cadena

   // vector<Point>* posiblesCandidatos = new vector<Point>();

    cout << "Estado actual\tEntrada\tSiguiente estado" << endl;
    for(int i = 0; i < strlen(cstr); i++) {
        for(int j = 0; j < getTransiciones()->size(); j++) {
            if(getTransiciones()->at(j).getInicio() == estadoActual) {
                if(getTransiciones()->at(j).getLetraTransicion() == cstr[contador]) {
                    //Poner en candidatos
                    cout << estadoActual << "\t" <<  getTransiciones()->at(j).getLetraTransicion() << "\t";
                    contador++;
                    estadoActual = getTransiciones()->at(j).getDestino();
                    cout << estadoActual << endl;
                    //Es una transicion vacia
                } else if (getTransiciones()->at(j).getLetraTransicion() == '~') {

                }
            }
        }
    }
    //si en este momento nos encontramos en un nodo final HACER
    if(contador < strlen(cstr)) {
        cout << "\nCADENA NO ACEPTADA \n";
    } else {
        bool aceptado = false;
        for(int i  =0; i < getFinales()->size(); i++) {
            if(getFinales()->at(i) == estadoActual)
                aceptado = true;
        }
        if(aceptado == true)
            cout << "\nCADENA ACEPTADA \n";
        else
            cout << "\nCADENA NO ACEPTADA \n";
    }
}

void CDFA::esDFA() {
    cout << "Recuerde que las transiciones vacias se codifican como ~ " << endl;
    bool nfa = false;
    for(int i = 0; i < getTransiciones()->size(); i++) {
        if((getTransiciones()->at(i)).getLetraTransicion() == '~') {
            nfa = true;
            break;
        }
    }
    if(nfa == true)
        cout << "Es un NFA " << endl;
    else
        cout << "Es un DFA " << endl;
}

void CDFA::leerFichero() {
    /*cout << "Introduzca el nombre del fichero " << endl;
            string aux;
            cin >> aux;*/

    std::ifstream fe ("prueba.txt.txt.txt", std::ifstream::in);
    fe >> numNodos_;
    fe >> estadoInicial_;
    string linea;
    getline(fe, linea);
    while (!fe.eof()) {     // Mientras se haya podido leer algo
        getline(fe, linea);
        QString str = QString::fromStdString(linea);
        cout << str.toStdString() << endl;
        QStringList list = str.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        if(list.size() >= 3) {
            int inicial = list[0].toInt();

            if(list[1].toInt()) {
                getFinales()->push_back(inicial);
            }

            int numTransiciones = list[2].toInt();

            if(numTransiciones > 0) {
                for(int i = 0; i < numTransiciones; i++) {
                    char letra = list[3 + (2*i)].at( 0 ).toLatin1();
                    int destino = list[4 + (2*i)].toInt();
                    getTransiciones()->push_back(CEstado(inicial, destino, letra));
                    getTransiciones()->at(getTransiciones()->size() - 1).mostrar();
                }
            }
        } else {
            cout << list.size() << endl;
            cout << linea << endl;
            cout << "Fichero mal estructurado" << endl;
            break;
        }
    }
    fe.close();
    mostrarDFA();
}

vector<CEstado>* CDFA::getTransiciones() {
    return transiciones_;
}

void CDFA::setTransiciones(vector<CEstado>* copia) {
    transiciones_ = copia;
}

vector<int>* CDFA::getFinales() {
    return finales_;
}

int CDFA::getEstadoInicial() {
    return estadoInicial_;
}

int CDFA::getNumNodos() {
    return numNodos_;
}

void CDFA::mostrarDFA() {
    cout << "Estado inicial " << getEstadoInicial() << endl;
    cout << "Num de nodos " << getNumNodos() << endl;
    cout << "Nodos finales " << endl;
    for(int i = 0; i < getFinales()->size(); i++) {
        cout << getFinales()->at(i) << " ";
    }
    cout << endl;
    mostrarEstadosFinales();
    mostrarTransiciones();
}

void CDFA::mostrarTransiciones() {
    cout << " TRANSICIONES " << endl;
    for(int i = 0; i < getTransiciones()->size(); i++) {
        getTransiciones()->at(i).mostrar();
    }
}

void CDFA::mostrarEstadosFinales() {
    cout << "ESTADOS FINALES " << endl;
    cout << "{";
    for(int i = 0; i < (getFinales()->size() - 1); i++) {
        cout << getFinales()->at(i) << ", ";
    }
    cout << getFinales()->at(getFinales()->size() - 1) << "}" << endl;
}
