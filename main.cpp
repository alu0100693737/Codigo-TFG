#include "CNFA.h"
#include <stdio.h>
#include <cstdio>
#include <iostream>


main() {
     /**opcion seleccionada*/
     int opc;
     CDFA* A = new CDFA();

     do{
        cout << endl << "Elija una opcion" << endl;
        cout << endl << "0.Salir\n1.Leer NFA\n2.Mostrar NFA\n3.Identificar estados de muerte\n4.Es DFA?\n5.Analizar cadena" << endl; //mostrar menu
        cout << endl << "OPCION: ";

        cin >> opc;

        switch (opc){

            case 0: break;
            case 1: A->leer(); break;
            case 2: A->mostrar(); break;
            case 3: A->identificar(); break;
            case 4: A->es_dfa(); break;
            case 5: A->analizar(); break;
            default: cout << endl << "OPCION INCORRECTA" << endl;
        }

     }while(opc!=0);

}

