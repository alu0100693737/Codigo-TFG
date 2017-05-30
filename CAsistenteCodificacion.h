#ifndef CASISTENTECODIFICACION_H
#define CASISTENTECODIFICACION_H
#include <QWidget>
#include <QGridLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <vector>
#include "CLabel.h"

class CAsistenteCodificacion : public QWidget {

private:
    //Texto de la GUI
    CLabel* LCambiar_;
    CLabel* LAplicar_;
    CLabel* LInicio_;
    CLabel* LDestino_;
    CLabel* LLetra_;
    vector<QCheckBox*>* cambiar_;
    vector<QCheckBox*>* aplicar_;
    vector<QLineEdit*>* inicios_;
    vector<QLineEdit*>* destinos_;
    vector<QLineEdit*>* letras_;

public:
    CAsistenteCodificacion(vector<int>* ini, vector<int>* fins, vector<char>* let, QWidget *parent = 0);

    CLabel* getLCambiar();
    CLabel* getLAplicar();
    CLabel* getLInicio();
    CLabel* getLDestino();
    CLabel* getLLetra();

    vector<QCheckBox*>* getCheckBoxCambiar();
    vector<QCheckBox*>* getCheckBoxAplicar();
    vector<QLineEdit*>* getInicios();
    vector<QLineEdit*>* getDestinos();
    vector<QLineEdit*>* getLetras();
};

#endif // CASISTENTECODIFICACION_H
