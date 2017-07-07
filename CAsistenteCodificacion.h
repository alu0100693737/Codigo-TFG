///////////////////////////////////////////////////////////////////////////////
//CAsistenteCodificacion.h - Declaración de la clase CAsistenteCodificacion  //
//                                                                           //
//               Autor: Iván García Campos                                   //
//                                                                           //
//            Proyecto de Trabajo Fin de Grado.                              //
//                                                                           //
//               Fecha: 05/06/2017                                           //
///////////////////////////////////////////////////////////////////////////////


#ifndef CASISTENTECODIFICACION_H
#define CASISTENTECODIFICACION_H
#include <QWidget>
#include <QGridLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <vector>
#include <QSignalMapper>
#include <QFileDialog>
#include <QtWidgets>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPixmap>
#include <iostream>
#include "CPushButton.h"
#include "CLabel.h"
#include "CLineEdit.h"
#include "CCheckBox.h"
#include <algorithm>
using namespace std;
#define PATH_TEMPORAL "/home/ivan/Documentos/Codigo-TFG/codificaciones/temporal.txt"
/**
 * @brief
 * Clase asistente de la codificacion.
 * Utilizada al Procesar o Codificar una Imagen para confirmar que todo es correcto
 * antes de guardarlo en un fichero
 */
class CAsistenteCodificacion : public QWidget {
    Q_OBJECT
private:
    /// Numero de nodos del automata
    int numNodos_;
    /// Nodo inicial
    string nodoInicial_;
    /// Nodos finales del automata
    string nodosFinales_;

    /// Texto Cambiar
    CLabel* LCambiar_;
    /// Texto Borrar
    CLabel* LBorrar_;
    /// Texto Inicio
    CLabel* LInicio_;
    /// Texto Destino
    CLabel* LDestino_;
    /// Texto Letra
    CLabel* LLetra_;
    /// Texto Añadir
    QLabel* LAnadir_;

    /// Vector de CCheckbox para cambiar el orden de las transiciones
    vector<CCheckBox*>* cambiar_;
    /// Vector de CCheckbox para cambiar borrar la transicion que se desee
    vector<CCheckBox*>* borrar_;
    /// Vector de inicios de transiciones
    vector<CLineEdit*>* inicios_;
    /// Vector de destinos de transiciones
    vector<CLineEdit*>* destinos_;
    /// Vector de letras entre transiciones
    vector<CLineEdit*>* letras_;

    /// QLineEdit para añadir nuevas transiciones si se desea
    QLineEdit* anadir_;

    /// CPushButton para aceptar la codificacion del automata
    CPushButton* guardarComoFichero_;
    /// CPushButton para cancelar la codificacion del automata
    CPushButton* corregirAutomata_;
    CPushButton* cancelar_;
    /// CPushButton que ofrece ayuda sobre el funcionamiento del asistente
    CPushButton* help_;

public:
    /**
     * @brief
     * Constructor
     * @param nodos. Numero de nodos del automata
     * @param inicial. Nodo inicial del automata
     * @param finales. Nodos finales del automata
     * @param ini.     Conjunto de inicios de transiciones
     * @param fins     Conjunto de destinos de transiciones
     * @param let      Conjunto de letras entre transiciones
     * @param parent   Ventana padre
     */
    CAsistenteCodificacion(int nodos, string inicial, string finales, vector<int>* ini, vector<int>* fins, vector<char>* let, QWidget *parent = 0);

    /**
     * @brief
     * Metodo que devuelve el numero de nodos del automata
     * @return  int
     */
    int getNumNodos();
    /**
     * @brief
     * Metodo que devuelve el nodo inicial del automata
     * @return string
     */
    string getNodoInicial();
    /**
     * @brief
     * Metodo que devuelve los nodos finales del automata
     * @return string
     */
    string getNodosFinales();

    /**
     * @brief
     * Metodo que devuelve el CLabel con el texto 'Cambiar'
     * @return CLabel
     */
    CLabel* getLCambiar();
    /**
     * @brief
     * Metodo que devuelve el CLabel con el texto 'Borrar'
     * @return CLabel
     */
    CLabel* getLBorrar();
    /**
     * @brief
     * Metodo que devuelve el CLabel con el texto 'Inicio'
     * @return CLabel
     */
    CLabel* getLInicio();
    /**
     * @brief
     * Metodo que devuelve el CLabel con el texto 'Destino'
     * @return CLabel
     */
    CLabel* getLDestino();
    /**
     * @brief
     * Metodo que devuelve el CLabel con el texto 'Letra'
     * @return CLabel
     */
    CLabel* getLLetra();
    /**
     * @brief
     * Metodo que devuelve el CLabel con el texto 'Añadir'
     * @return CLabel
     */
    QLabel* getLAnadir();

    /**
     * @brief
     * Metodo que devuelve el vector de CCheckBox Cambiar
     * @return vector<CCheckBox*>*
     */
    vector<CCheckBox*>* getCheckBoxCambiar();
    /**
     * @brief
     * Metodo que devuelve el vector de CCheckBox Borrar
     * @return vector<CCheckBox*>*
     */
    vector<CCheckBox*>* getCheckBoxBorrar();
    /**
     * @brief
     * Metodo que devuelve el vector de CLineEdit Inicios
     * @return vector<CLineEdit*>*
     */
    vector<CLineEdit*>* getInicios();
    /**
     * @brief
     * Metodo que devuelve el vector de CLineEdit Destinos Cambiar
     * @return vector<CLineEdit*>*
     */
    vector<CLineEdit*>* getDestinos();
    /**
     * @brief
     * Metodo que devuelve el vector de CLineEdit Letras
     * @return vector<CLineEdit*>*
     */
    vector<CLineEdit*>* getLetras();

    /**
     * @brief
     * Metodo que devuelve el QLineEdit con los automatas a añadir. Estos se introducen por Ventana
     * @return QLineEdit
     */
    QLineEdit* getAnadir();

    /**
     * @brief
     * Metodo que devuelve el CPushButton Aceptar automata
     * @return CPushButton
     */
    CPushButton* getGuardarComoFichero();
    /**
     * @brief
     * Metodo que devuelve el CPushButton Cancelar automata
     * @return CPushButton
     */
    CPushButton* getCancelar();
    /**
     * @brief
     * Metodo que devuelve el CPushButton Corregir Automata sobre el asistente
     * @return CPushButton
     */
    CPushButton* getCorregirAutomata();

    void guardarAutomataTemporal();
    /**
     * @brief
     * Metodo que devuelve el CPushButton Ayuda sobre el asistente
     * @return CPushButton
     */
    CPushButton* getHelp();

    /**
     * @brief ventanaInfoCodificacion
     * Metodo que crea una ventana QWidget con la informacion resultado de la codificacion
     * @param text
     */
    void ventanaInfoCodificacion( string text);

public slots:
    /**
     * @brief
     * Metodo Slot que cierra el asistente sin codificar el automata
     */
    void slotCancelar();
    /**
     * @brief
     * Metodo Slot que Acepta el asistente guardandolo en un fichero
     */
    void slotGuardarComoFichero();
    /**
     * @brief
     * Metodo Slot que lanza la accion corregir automata
     */
    void slotCorregirAutomata();
    /**
     * @brief
     * Metodo Slot que lanza una ventana de ayuda
     */
    void slotHelp();
    /**
     * @brief
     * Metodo Slot que cambia los valores de inicio y destino de la fila correspondiente
     * si el valor del checkbox de esa linea esta marcado
     * @param i. Posicion
     */
    void slotCambiar(int i);
};

#endif // CASISTENTECODIFICACION_H
