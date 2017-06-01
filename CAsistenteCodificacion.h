#ifndef CASISTENTECODIFICACION_H
#define CASISTENTECODIFICACION_H
#include <QWidget>
#include <QGridLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <vector>
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
    CLabel* LAplicar_;
    CLabel* LInicio_;
    CLabel* LDestino_;
    CLabel* LLetra_;
    vector<CCheckBox*>* cambiar_;
    vector<CCheckBox*>* aplicar_;
    vector<CLineEdit*>* inicios_;
    vector<CLineEdit*>* destinos_;
    vector<CLineEdit*>* letras_;

    QPushButton* aceptar_;
    QPushButton* cancelar_;

    bool aceptado_;
public:
    CAsistenteCodificacion(int, string, string, vector<int>* ini, vector<int>* fins, vector<char>* let, QWidget *parent = 0);

    int getNumNodos();
    string getNodoInicial();
    string getNodosFinales();

    CLabel* getLCambiar();
    CLabel* getLAplicar();
    CLabel* getLInicio();
    CLabel* getLDestino();
    CLabel* getLLetra();

    vector<CCheckBox*>* getCheckBoxCambiar();
    vector<CCheckBox*>* getCheckBoxAplicar();
    vector<CLineEdit*>* getInicios();
    vector<CLineEdit*>* getDestinos();
    vector<CLineEdit*>* getLetras();

    QPushButton* getAceptar();
    QPushButton* getCancelar();

    bool getAceptado();

    public slots:
    void slotCancelar();
    void slotAceptar();
};

#endif // CASISTENTECODIFICACION_H
