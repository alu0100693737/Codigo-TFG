///////////////////////////////////////////////////////////////
//          Principal.cpp - Programa principal               //
//                                                           //
//               Autor: Iván García Campos                   //
//                                                           //
//            Proyecto de Trabajo Fin de Grado.              //
//                                                           //
//               Fecha: 05/06/2017                           //
///////////////////////////////////////////////////////////////

#include "CAplicacion.h"
int main(int argc, char *argv[]) {
    QApplication app(argc,argv);

    CAplicacion window;
    window.show();
    cout << "Version: " << CV_MAJOR_VERSION << endl;

    /*
    // LINEA DE COMANDOS   EJECUTAR : ./NFA  .....nfa  .....dfa     input    Ó   ./NFA 0 0 0 si no quieres argumentos

    int errorapertura1;
    CNFA nfa1;
    CNFA dfa1;

    nfa1.ConstruirNFA("prueba.txt", errorapertura1);
    nfa1.CrearAlfabeto();
    dfa1.ConstruirNFA("prueba.txt", errorapertura1);
    dfa1.CrearAlfabeto();

    nfa1.MostrarNFA();
    dfa1.MostrarNFA();

    ifstream fich;
    fich.open("RESULTADO.txt");
    if(fich.is_open()){

        string cadena;
        string nfa_aceptada;
        string dfa_aceptada;

        cout << endl << endl << "-- CADENA --         -- NFA --        -- DFA --" << endl;
        cout <<"------------------------------------------------" << endl;

        while(! fich.eof()){
            fich >> cadena;
            if(nfa1.AnalizarCadena2(cadena) == true){
                nfa_aceptada = "SI";
            }
            else{

                nfa_aceptada = "NO";
            }

            if(dfa1.AnalizarCadena2(cadena) == true){
                dfa_aceptada = "SI";
            }

            else{

                dfa_aceptada = "NO";
            }
            cout << cadena << "              " << nfa_aceptada << "        " << dfa_aceptada << endl;
        }
    }
    ///////////////////////////

    int opcion = -1;
    int errorapertura = 0;
    int posibilidad_exportar_dfa=0;
    vector<CEstado> Orden;

    CNFA nfa;
    while(opcion != 7){
        cout << endl << "		MENÚ" << endl << endl;
        cout << endl << "	1. Leer NFA";
        cout << endl << "	2. Mostrar NFA";
        cout << endl << "	3. Identificar estados de muerte";
        cout << endl << "	4. Analizar Cadena";
        cout << endl << "	5. Convertir a DFA";
        cout << endl << "	6. Exportar DFA a fichero";
        cout << endl << "	7. Salir" << endl;

        if( errorapertura == 2){
            cout << endl << endl << "					NFA cargado" << endl;
        }

        else{
            cout << endl << endl << "					NFA NO cargado" << endl;
        }

        cout << endl << "Introducir opción : ";
        cin >> opcion;

        switch(opcion){
        case 1:{
            cout << endl << "Introduzca el nombre del fichero con extensión .nfa :   ";
            string fichero;
            cin >> fichero;

            nfa.ConstruirNFA(fichero, errorapertura);
            if(errorapertura == 2){
                cout << endl << "Fichero " << fichero << " leído correctamente" << endl;
            }

            if(errorapertura == 1){
                cout << endl << "¡¡ ERROR !! El fichero no se ha podido abrir" << endl;
            }
            nfa.CrearAlfabeto();
            break;
        }

        case 2:{
            if((errorapertura == 0) || (errorapertura == 1)){
                cout << endl << "El fichero .nfa todavía no se ha cargado" << endl;
            }

            if( errorapertura == 2){
                cout << endl << "--> Mostar NFA" << endl;
                nfa.MostrarNFA();
                cout << endl << endl;
            }

            break;
        }

        case 3: {
            if((errorapertura == 0) || (errorapertura == 1)){
                cout << endl << "El fichero .nfa todavía no se ha cargado" << endl;
            }

            if( errorapertura == 2){
                cout << endl << "--> Estados de Muerte" << endl;
                nfa.MostrarEstadosMuerte();
                cout << endl << endl;
            }
            break;
        }

        case 4: {
            if((errorapertura == 0) || (errorapertura == 1)){
                cout << endl << "El fichero .nfa todavía no se ha cargado" << endl;
            }

            if( errorapertura == 2){
                cout << endl << "--> Analizar Cadena" << endl;
                cin.ignore();
                string cadena;
                cout << endl << "Introduzca una cadena" << endl;
                getline(cin, cadena );
                nfa.AnalizarCadena(cadena);
                cout << endl << endl;
            }
            break;
        }

        case 5: {
            if((errorapertura == 0) || (errorapertura == 1)){
                cout << endl << "El fichero .nfa todavía no se ha cargado" << endl;
            }

            if( errorapertura == 2){
                cout << endl << "--> Convertir a DFA" << endl;
                Orden = nfa.ConverttoDFA();
                cout << endl << endl;
                posibilidad_exportar_dfa = 1;
            }
            break;
        }

        case 6:{
            if( posibilidad_exportar_dfa == 0){
                cout << endl << "No se puede exportar ya que todavía no se ha realizado la transformación de NFA a DFA" << endl;
            }

            if(posibilidad_exportar_dfa == 1){
                nfa.Exportar(Orden);

                cout << endl << "Conversion a DFA exportada a fichero DFA.dfa " << endl ;
            }
            break;
        }

        case 7: {
            cout << endl << endl << "    . . . Cerrando NFA" << endl << endl;
            break;
        }
        }
    }*/
    return app.exec();
}
