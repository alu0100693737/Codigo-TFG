#include "CAsistenteCodificacion.h"
#include "opencv2/opencv.hpp"   //WINDOW_AUTOSIZE, windows
using namespace std;
using namespace cv;
//sudo setxkbmap -layout 'es,es' -model pc105
CAsistenteCodificacion::CAsistenteCodificacion(int nodos, string inicial, string finales, vector<int>* ini, vector<int>* fins, vector<char>* let, QWidget *parent) {

    numNodos_ = nodos;
    nodoInicial_ = inicial;
    nodosFinales_ = finales;

    LCambiar_ = new CLabel("Cambiar", true);
    LAplicar_ = new CLabel("Aplicar", false);
    LInicio_ = new CLabel("Inicios",true);
    LDestino_ = new CLabel("Destinos", true);
    LLetra_ = new CLabel("Transicion", true);

    cambiar_ = new vector<CCheckBox*>();
    aplicar_ = new vector<CCheckBox*>();
    inicios_= new vector<CLineEdit*>();
    destinos_ = new vector<CLineEdit*>();
    letras_ = new vector<CLineEdit*>();

    aceptar_ = new QPushButton("Codificar");
    cancelar_ = new QPushButton("Cancelar");

    setStyleSheet("background-color: rgba(255, 255, 130, 1);  border-style: outset; border-width: 2px; border-color: beige;");
    QGridLayout *layout = new QGridLayout();
    this->setLayout (layout);

    layout->addWidget(getLCambiar(), 0, 0, 1, 2);
    //layout->addWidget(getLAplicar(), 0, 1, 1, 1);
    layout->addWidget(getLInicio(), 0, 2, 1, 1);
    layout->addWidget(getLDestino(), 0, 3, 1, 1);
    layout->addWidget(getLLetra(), 0, 4, 1, 1);

    for(int i = 0; i < ini->size(); i++) {

        getCheckBoxCambiar()->push_back(new CCheckBox());
        //getCheckBoxAplicar()->push_back(new QCheckBox());

        getInicios()->push_back(new CLineEdit(QString::number(ini->at(i))));
        //cout << ini->at(i) << " " << fins->at(i) << endl;
        getDestinos()->push_back(new CLineEdit(QString::number(fins->at(i))));
        getLetras()->push_back(new CLineEdit(QString(let->at(i))));
    }

    for(int i = 0; i < ini->size(); i++) {
        layout->addWidget(getCheckBoxCambiar()->at(i), i + 1, 0, 1, 2);
        //layout->addWidget(getCheckBoxAplicar()->at(i), i + 1, 1, 1, 1);

        layout->addWidget(getInicios()->at(i),  i + 1, 2, 1, 1);
        layout->addWidget(getDestinos()->at(i), i + 1, 3, 1, 1);
        layout->addWidget(getLetras()->at(i),  i + 1, 4, 1, 1);
    }

    layout->addWidget(getCancelar(), ini->size() + 4, 2, 1, 1);
    layout->addWidget(getAceptar(), ini->size() + 4, 3, 1, 1);

    connect(getCancelar(), SIGNAL(clicked()), this, SLOT(slotCancelar()));
    connect(getAceptar(), SIGNAL(clicked()), this, SLOT(slotAceptar()));

    for(int i = 0; i < getCheckBoxCambiar()->size(); i++)
        connect(getCheckBoxCambiar()->at(i), SIGNAL(clicked()), this, SLOT(slotCambiar()));
    //setMinimumSize(400, 200);
    setWindowTitle("Asistente para la codificación");

}

int CAsistenteCodificacion::getNumNodos() {
    return numNodos_;
}

string CAsistenteCodificacion::getNodoInicial() {
    return nodoInicial_;
}

string CAsistenteCodificacion::getNodosFinales() {
    return nodosFinales_;
}

vector<CCheckBox*>* CAsistenteCodificacion::getCheckBoxCambiar() {
    return cambiar_;
}

vector<CCheckBox*>* CAsistenteCodificacion::getCheckBoxAplicar() {
    return aplicar_;
}

vector<CLineEdit*>* CAsistenteCodificacion::getInicios() {
    return inicios_;
}

vector<CLineEdit*>* CAsistenteCodificacion::getDestinos() {
    return destinos_;
}

vector<CLineEdit*>* CAsistenteCodificacion::getLetras() {
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

QPushButton* CAsistenteCodificacion::getAceptar() {
    return aceptar_;
}

QPushButton* CAsistenteCodificacion::getCancelar() {
    return cancelar_;
}

void CAsistenteCodificacion::slotCancelar() {
    this->close();
}

void CAsistenteCodificacion::slotAceptar() {
    ofstream fs("/home/ivan/Documentos/Codigo-TFG/codificaciones/codificacion.txt");
    fs << getNumNodos() << endl;
    fs << getNodoInicial() << endl;
    fs << getNodosFinales() << endl;
    for(int i = 0; i < getInicios()->size(); i++)
        fs << getInicios()->at(i)->text().toStdString() << " " << getDestinos()->at(i)->text().toStdString() << " " << getLetras()->at(i)->text().toStdString() << endl;
    fs.close();
    slotCancelar();
}

void CAsistenteCodificacion::slotCambiar() {
    int i = 0;
    QString aux = getInicios()->at(i)->text();
    getInicios()->at(i)->text() = getDestinos()->at(i)->text();
    getDestinos()->at(i)->text() = aux;
    cout << "heys" << endl;
}
