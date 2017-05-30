#include "CAsistenteCodificacion.h"
#include "opencv2/opencv.hpp"   //WINDOW_AUTOSIZE, windows
using namespace std;
using namespace cv;

CAsistenteCodificacion::CAsistenteCodificacion(vector<int>* ini, vector<int>* fins, vector<char>* let, QWidget *parent) {

    LCambiar_ = new CLabel("Cambiar", false);
    LAplicar_ = new CLabel("Aplicar", false);
    LInicio_ = new CLabel("Inicios",false);
    LDestino_ = new CLabel("Destinos", false);
    LLetra_ = new CLabel("Transicion", false);

    cambiar_ = new vector<QCheckBox*>();
    aplicar_ = new vector<QCheckBox*>();
    inicios_= new vector<QLineEdit*>();
    destinos_ = new vector<QLineEdit*>();
    letras_ = new vector<QLineEdit*>();


    QGridLayout *layout = new QGridLayout();
    this->setLayout (layout);

    layout->addWidget(getLCambiar(), 0, 0, 1, 1);
    layout->addWidget(getLAplicar(), 0, 1, 1, 1);
    layout->addWidget(getLInicio(), 0, 2, 1, 1);
    layout->addWidget(getLDestino(), 0, 3, 1, 1);
    layout->addWidget(getLLetra(), 0, 4, 1, 1);

    for(int i = 0; i < ini->size(); i++) {
        getCheckBoxCambiar()->push_back(new QCheckBox());
        getCheckBoxAplicar()->push_back(new QCheckBox());
        getInicios()->push_back(new QLineEdit(QString(ini->at(i))));
        getDestinos()->push_back(new QLineEdit(QString(fins->at(i))));
        getLetras()->push_back(new QLineEdit(QString(let->at(i))));
    }

    for(int i = 0; i < ini->size(); i++) {
        layout->addWidget(getCheckBoxCambiar()->at(i), i + 1, 0, 1, 1);
        layout->addWidget(getCheckBoxAplicar()->at(i), i + 1, 1, 1, 1);
        cout << getInicios()->at(i)->text().toStdString() << endl;
        layout->addWidget(getInicios()->at(i),  i + 1, 2, 1, 1);
        layout->addWidget(getDestinos()->at(i), i + 1, 3, 1, 1);
        layout->addWidget(getLetras()->at(i),  i + 1, 4, 1, 1);
    }

     show();

    //setMinimumSize(400, 200);
    setWindowTitle("Asistente para la codificación");

}


vector<QCheckBox*>* CAsistenteCodificacion::getCheckBoxCambiar() {
    return cambiar_;
}

vector<QCheckBox*>* CAsistenteCodificacion::getCheckBoxAplicar() {
    return aplicar_;
}

vector<QLineEdit*>* CAsistenteCodificacion::getInicios() {
    return inicios_;
}

vector<QLineEdit*>* CAsistenteCodificacion::getDestinos() {
    return destinos_;
}

vector<QLineEdit*>* CAsistenteCodificacion::getLetras() {
    return letras_;
}

CLabel* CAsistenteCodificacion::getLCambiar() {
    return LCambiar_;
}

CLabel* CAsistenteCodificacion::getLAplicar() {
    return LAplicar_;
}

CLabel* CAsistenteCodificacion::getLInicio() {
    return LInicio_;
}

CLabel* CAsistenteCodificacion::getLDestino() {
    return LDestino_;
}

CLabel* CAsistenteCodificacion::getLLetra() {
    return LLetra_;
}

