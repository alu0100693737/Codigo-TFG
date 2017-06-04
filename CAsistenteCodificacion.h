#ifndef CASISTENTECODIFICACION_H
#define CASISTENTECODIFICACION_H
#include <QWidget>
#include <QGridLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <vector>
#include <QSignalMapper>
#include <QGroupBox>
#include <QHBoxLayout>
#include "CPushButton.h"
#include "CLabel.h"
#include "CLineEdit.h"
#include "CCheckBox.h"

class CAsistenteCodificacion : public QWidget {
    Q_OBJECT
private:
    int numNodos_;
    string nodoInicial_;
    string nodosFinales_;

    //Texto de la GUI
    CLabel* LCambiar_;
    CLabel* LBorrar_;
    CLabel* LInicio_;
    CLabel* LDestino_;
    CLabel* LLetra_;
    QLabel* LAnadir_;

    vector<CCheckBox*>* cambiar_;
    vector<CCheckBox*>* borrar_;
    vector<CLineEdit*>* inicios_;
    vector<CLineEdit*>* destinos_;
    vector<CLineEdit*>* letras_;

    QLineEdit* anadir_;

    CPushButton* aceptar_;
    CPushButton* cancelar_;
    CPushButton* help_;

public:
    CAsistenteCodificacion(int, string, string, vector<int>* ini, vector<int>* fins, vector<char>* let, QWidget *parent = 0);

    int getNumNodos();
    string getNodoInicial();
    string getNodosFinales();

    CLabel* getLCambiar();
    CLabel* getLBorrar();
    CLabel* getLInicio();
    CLabel* getLDestino();
    CLabel* getLLetra();
    QLabel* getLAnadir();

    vector<CCheckBox*>* getCheckBoxCambiar();
    vector<CCheckBox*>* getCheckBoxBorrar();
    vector<CLineEdit*>* getInicios();
    vector<CLineEdit*>* getDestinos();
    vector<CLineEdit*>* getLetras();

    QLineEdit* getAnadir();

    CPushButton* getAceptar();
    CPushButton* getCancelar();
    CPushButton* getHelp();

public slots:
    void slotCancelar();
    void slotAceptar();
    void slotHelp();
    void slotCambiar(int i);
};

#endif // CASISTENTECODIFICACION_H
