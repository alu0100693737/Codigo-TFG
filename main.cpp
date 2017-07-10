//
// Practica 4 :Simplificacion de un DFA
//
// Autor: Alberto Martínez Chincho
//
/*
#include "DFA_min.cpp"
#include "Estado.cpp"

int main(int argc, char *argv[]){

	// Menú del programa
    int opcion;
    DFA_MIN dfa;


    cout << " ***********************Menu************************ " << endl;
    cout << " *  1.- Leer el DFA                                * " << endl;
    cout << " *  2.- Mostrar el DFA                             * " << endl;
    cout << " *  3.- Identificar el estado de muerte            * " << endl;
    cout << " *  4.- Analizar una cadena                        * " << endl;
    cout << " *  5.- Simplificar DFA                            * " << endl;
    cout << " *  6.- Exportar DFA simplificado                  * " << endl;
    cout << " *  7.- Salir                                      * " << endl;
    cout << " *************************************************** " << endl;
    cout << "Eliga una opcion: ";
    cin >> opcion ;
    cout << endl;

    do {
      switch (opcion)  {
             case 1:
                  char nombre[20];
                  cout << "Introduzca el nombre del fichero: ";
                  cin >> nombre;
                  dfa.Leer_DFA(nombre);
                  cout << "\nPulse la funcion que desee que haga el programa: ";
                  cin >> opcion;
                  break;

             case 2:
                  dfa.Mostrar_DFA();
                  cout << "\nPulse la funcion que desee que haga el programa: ";
                  cin >> opcion;
                  cout<<endl;
                  break;


             case 3:
                  dfa.Ident_est_muerte();
                  cout << "\nPulse la funcion que desee que haga el programa: ";
                  cin >> opcion;
                  cout<<endl;
                  break;



             case 4:
			      dfa.Analizar_cadena();
                  cout << "\nPulse la funcion que desee que haga el programa: ";
                  cin >> opcion;
                  cout<<endl;
                  break;

             case 5:
             	//simplificarDFA
             	dfa.Divide_DFA();
             	dfa.Minimizar_DFA();
             	cout << "\nPulse la funcion que desee que haga el programa: ";
             	cin>>opcion;
             	cout<<endl;
             	break;

             case 6:
             	dfa.Exportar_DFA_min();
             	cout << "\nPulse la funcion que desee que haga el programa: ";
             	cin>>opcion;
             	cout<<endl;
             	break;

             case 7:
                  cout << "Saliendo del programa ... ";
                  cout <<"\n" <<endl;
                  break;

             default:
                 cout << "El numero introducido no esta en el menu" << endl;
                 cout <<"Introduzca un numero del menu: ";
                 cin >> opcion;
      }
    }while (opcion !=7);

  system ("PAUSE");

  return EXIT_SUCCESS;


}*/


