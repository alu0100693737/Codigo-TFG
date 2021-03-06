﻿//////////////////////////////////////////////////////////////////////////////////
//CAsistenteCodificacion.h - Implementacion de la clase CAsistenteCodificacion  //
//                                                                              //
//               Autor: Iván García Campos                                      //
//                                                                              //
//            Proyecto de Trabajo Fin de Grado.                                 //
//                                                                              //
//               Fecha: 05/06/2017                                              //
//////////////////////////////////////////////////////////////////////////////////

#include "CAsistenteCodificacion.h"
#include "opencv2/opencv.hpp"   //WINDOW_AUTOSIZE, windows
using namespace std;
using namespace cv;
//sudo setxkbmap -layout 'es,es' -model pc105
CAsistenteCodificacion::CAsistenteCodificacion(int nodos, string inicial, string finales, vector<int>* ini, vector<int>* fins, vector<char>* let, QWidget *parent) {
    numNodos_ = nodos;
    nodoInicial_ = inicial;
    nodosFinales_ = finales;

    LCambiar_ = new CLabel("Cambiar Sentido", true);
    LBorrar_ = new CLabel("Eliminar Transicion", true);
    LInicio_ = new CLabel("Inicios",true);
    LDestino_ = new CLabel("Destinos", true);
    LLetra_ = new CLabel("Transicion", true);
    LAnadir_ = new CLabel("Añadir nueva transicion: ", true);

    cambiar_ = new vector<CCheckBox*>();
    borrar_ = new vector<CCheckBox*>();
    inicios_= new vector<CLineEdit*>();
    destinos_ = new vector<CLineEdit*>();
    letras_ = new vector<CLineEdit*>();

    anadir_ = new QLineEdit();
    getAnadir()->setPlaceholderText("Formato: 2 3 b ; 4 5 ~ ;");

    guardarComoFichero_ = new CPushButton("Guardar como fichero", false);
    cancelar_ = new CPushButton("Cancelar", false);
    help_ = new CPushButton("Help", false);
    corregirAutomata_ = new CPushButton("Corregir automata", false);

    this->setStyleSheet("background-color: rgba(220, 220, 220, 1);");
    QGridLayout *layout = new QGridLayout();

    this->setLayout (layout);

    layout->addWidget(getLCambiar(), 0, 0, 1, 1, Qt::AlignHCenter);
    layout->addWidget(getLBorrar(), 0, 1, 1, 1);
    layout->addWidget(getLInicio(), 0, 2, 1, 1);
    layout->addWidget(getLDestino(), 0, 3, 1, 1);
    layout->addWidget(getLLetra(), 0, 4, 1, 1);

    for(int i = 0; i < ini->size(); i++) {
        getCheckBoxCambiar()->push_back(new CCheckBox());
        getCheckBoxBorrar()->push_back(new CCheckBox());

        getInicios()->push_back(new CLineEdit(QString::number(ini->at(i))));
        getDestinos()->push_back(new CLineEdit(QString::number(fins->at(i))));
        getLetras()->push_back(new CLineEdit(QString(let->at(i))));
    }

    for(int i = 0; i < ini->size(); i++) {
        layout->addWidget(getCheckBoxCambiar()->at(i), i + 1, 0, 1, 2);
        layout->addWidget(getCheckBoxBorrar()->at(i), i + 1, 1, 1, 1);
        layout->addWidget(getInicios()->at(i),  i + 1, 2, 1, 1);
        layout->addWidget(getDestinos()->at(i), i + 1, 3, 1, 1);
        layout->addWidget(getLetras()->at(i),  i + 1, 4, 1, 1);
    }

    //Linea horizontal
    QFrame* lineD = new QFrame;
    lineD->setFrameShape(QFrame::HLine);
    layout->addWidget(lineD, ini->size() + 1, 0, 1, 5);

    layout->addWidget(getLAnadir(), ini->size() + 2, 0, 1, 2);
    layout->addWidget(getAnadir(), ini->size() + 2, 2, 1, 3);
    layout->addWidget(new QLabel(), ini->size() + 3, 0, 1, 5);

    QHBoxLayout* layout1 = new QHBoxLayout();
    layout1->addWidget(getCancelar()); layout1->addWidget(getGuardarComoFichero()); layout1->addWidget(getCorregirAutomata());
    layout1->addWidget(getHelp());
    layout1->setSpacing(10);
    layout->addLayout(layout1, ini->size() + 3, 0, 2, 5);

    connect(getCancelar(), SIGNAL(clicked()), this, SLOT(slotCancelar()));
    connect(getGuardarComoFichero(), SIGNAL(clicked()), this, SLOT(slotGuardarComoFichero()));
    connect(getCorregirAutomata(), SIGNAL(clicked()), this, SLOT(slotCorregirAutomata()));
    connect(getHelp(), SIGNAL(clicked()), this, SLOT(slotHelp()));

    //Necesario para poder saber que CCheckBox se esta cliked()
    QSignalMapper* signalMapper = new QSignalMapper(this);
    for(int i = 0; i < getCheckBoxCambiar()->size(); i++) {
        connect(getCheckBoxCambiar()->at(i), SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(getCheckBoxCambiar()->at(i), i);
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(slotCambiar(int)));

    this->setFixedSize(this->width(), this->height());
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

vector<CCheckBox*>* CAsistenteCodificacion::getCheckBoxBorrar() {
    return borrar_;
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

CLabel* CAsistenteCodificacion::getLBorrar() {
    return LBorrar_;
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

QLabel* CAsistenteCodificacion::getLAnadir() {
    return LAnadir_;
}

QLineEdit* CAsistenteCodificacion::getAnadir() {
    return anadir_;
}

CPushButton* CAsistenteCodificacion::getGuardarComoFichero() {
    return guardarComoFichero_;
}

CPushButton* CAsistenteCodificacion::getCorregirAutomata() {
    return corregirAutomata_;
}

CPushButton* CAsistenteCodificacion::getCancelar() {
    return cancelar_;
}

CPushButton* CAsistenteCodificacion::getHelp() {
    return help_;
}

void CAsistenteCodificacion::slotCancelar() {
    ofstream fs(PATH_TEMPORAL);
    this->close();
}

void CAsistenteCodificacion::slotGuardarComoFichero() {
    ///Abre una ventana para guardar la codificacion en un fichero
    setStyleSheet("background-color: white;");
    QFileDialog dialogFile(this, tr("Guardar Codificacion"));
    dialogFile.setDefaultSuffix(".txt");

    const QStringList documentsLocations = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    dialogFile.setDirectory(documentsLocations.last());

    QString filename = dialogFile.getSaveFileName(
                this,
                tr("Save File"),
                "",
                tr("Documents (*.txt)") );

    if( !filename.isNull() ) {
        if(!filename.endsWith(".txt")) {
            filename.append(".txt");
        }
        vector<int> marcados;
        // spliteamos nodos finales
        QString str;
        QStringList list;

        str = QString::fromStdString(getNodosFinales());
        list = str.split(QRegExp("\\s+"));
        //Si se quieren añadir transiciones nuevas
        if(getAnadir()->text() != "") {
            QStringList list1 = getAnadir()->text().split(QRegExp("\\s+"), QString::SkipEmptyParts);
            cout << "size " << list1.size() << endl;
            if((list1.size() % 4 == 0) && (list1.size() > 0)){
                for(int i = 0; i < list1.size(); i++) {
                    if(list1[i] == ";") {
                        list1.removeAt(i);
                        i--;
                        cout << "borrando ;" << endl;
                    } else
                        cout << list1[i].toLocal8Bit().constData() << endl;
                }
                for(int i = 0; i < list1.size(); i++) {
                    getInicios()->push_back(new CLineEdit(list1[i]));
                    i++;
                    getDestinos()->push_back(new CLineEdit(list1[i]));
                    i++;
                    getLetras()->push_back(new CLineEdit(list1[i]));
                }
            } else {
                QMessageBox mensaje;
                mensaje.setText("El campo añadir nueva transición tiene un formato incorrecto.\n Ej: 1 2 b ; 4 2 c ;");
                mensaje.setIcon(QMessageBox::Information);
                mensaje.exec();

            }
        }

        ofstream fs(filename.toStdString());
        fs << getNumNodos() << endl;
        fs << getNodoInicial() << endl;
        //fs << getNodosFinales() << endl;
        for(int i = 0; i < getInicios()->size(); i++) {
            if((getCheckBoxBorrar()->size() <= i) || (!getCheckBoxBorrar()->at(i)->isChecked())){
                std::vector<int>::iterator it;
                it = std::find (marcados.begin(), marcados.end(), i);
                if (it == marcados.end()) {
                    fs << getInicios()->at(i)->text().toStdString() << " ";
                    //Considerando si es estado final o no
                    if(list.contains(getInicios()->at(i)->text()))
                        fs << 1 << " ";
                    else
                        fs << 0 << " ";

                    //Utilizado para saber el numero de transiciones de ese nodo
                    QString text1;
                    text1.append(QString::fromStdString(getLetras()->at(i)->text().toStdString()) + " " + QString::fromStdString(getDestinos()->at(i)->text().toStdString()) + " ");
                    vector<QString> textos;
                    textos.push_back(text1);
                    //fs << getDestinos()->at(i)->text().toStdString() << " " << getLetras()->at(i)->text().toStdString() << " ";
                    for(int j = i + 1; j < getInicios()->size(); j++) {
                        if(getInicios()->at(i)->text() == getInicios()->at(j)->text()) {
                            QString text2;
                            text2.append(QString::fromStdString(getLetras()->at(j)->text().toStdString()) + " " + QString::fromStdString(getDestinos()->at(j)->text().toStdString()) + " ");
                            textos.push_back(text2);
                            //fs << getDestinos()->at(j)->text().toStdString() << " " << getLetras()->at(j)->text().toStdString() << " ";
                            marcados.push_back(j);
                        }
                    }
                    fs << textos.size() << " ";
                    for(int k = 0; k < textos.size(); k++) {
                        fs << textos.at(k).toStdString();
                    }
                    fs << endl;
                }
            }
        }

        //Caso puntual, nodo final sin transiciones
        QString finales(QString::fromStdString(getNodosFinales()));
        QStringList list1 = finales.split(QRegExp("\\s+"), QString::SkipEmptyParts);

        for(int i = 0; i < list1.size(); i++) {
            cout << "Lista: " << list1.at(i).toStdString() << endl;
            if(std::find(getInicios()->begin(), getInicios()->end(), new CLineEdit(QString(list1.at(i)))) == getInicios()->end()) {
                cout << "El nodo final no tiene transiciones, se agrega manualmente" << endl;
                fs << list1.at(i).toStdString() << " 1 0" << endl;
            }
        }


        fs.close();

        string text;
        string line;
        ifstream myfile (filename.toStdString());
        if (myfile.is_open()) {
            while (getline(myfile,line)) {
                text += line;
                text += "\n";
                cout << line << endl;
            }
            myfile.close();
        }
        ///Crea una nueva ventana con la codificacion deseada por si se desea consultar
        ventanaInfoCodificacion(text);
        setStyleSheet("background-color: rgba(220, 220, 220, 1);");
    }   else
        setStyleSheet("background-color: rgba(220, 220, 220, 1);");

}

void CAsistenteCodificacion::slotCorregirAutomata() {
    guardarAutomataTemporal();
    this->close();
}

void CAsistenteCodificacion::guardarAutomataTemporal() {

    vector<int> marcados;
    // spliteamos nodos finales
    QString str;
    QStringList list;

    str = QString::fromStdString(getNodosFinales());
    list = str.split(QRegExp("\\s+"));
    //Si se quieren añadir transiciones nuevas
    if(getAnadir()->text() != "") {
        QStringList list1 = getAnadir()->text().split(QRegExp("\\s+"), QString::SkipEmptyParts);
        cout << "size " << list1.size() << endl;
        if((list1.size() % 4 == 0) && (list1.size() > 0)){
            for(int i = 0; i < list1.size(); i++) {
                if(list1[i] == ";") {
                    list1.removeAt(i);
                    i--;
                    cout << "borrando ;" << endl;
                } else
                    cout << list1[i].toLocal8Bit().constData() << endl;
            }
            for(int i = 0; i < list1.size(); i++) {
                getInicios()->push_back(new CLineEdit(list1[i]));
                i++;
                getDestinos()->push_back(new CLineEdit(list1[i]));
                i++;
                getLetras()->push_back(new CLineEdit(list1[i]));
            }
        } else {
            QMessageBox mensaje;
            mensaje.setText("El campo añadir nueva transición tiene un formato incorrecto.\n Ej: 1 2 b ; 4 2 c ;");
            mensaje.setIcon(QMessageBox::Information);
            mensaje.exec();

        }
    }

    ofstream fs(PATH_TEMPORAL);
    fs << getNumNodos() << endl;
    fs << getNodoInicial() << endl;
    //fs << getNodosFinales() << endl;
    for(int i = 0; i < getInicios()->size(); i++) {
        if((getCheckBoxBorrar()->size() <= i) || (!getCheckBoxBorrar()->at(i)->isChecked())){
            std::vector<int>::iterator it;
            it = std::find (marcados.begin(), marcados.end(), i);
            if (it == marcados.end()) {
                fs << getInicios()->at(i)->text().toStdString() << " ";
                //Considerando si es estado final o no
                if(list.contains(getInicios()->at(i)->text()))
                    fs << 1 << " ";
                else
                    fs << 0 << " ";

                //Utilizado para saber el numero de transiciones de ese nodo
                QString text1;
                text1.append(QString::fromStdString(getLetras()->at(i)->text().toStdString()) + " " + QString::fromStdString(getDestinos()->at(i)->text().toStdString()) + " ");
                vector<QString> textos;
                textos.push_back(text1);
                //fs << getDestinos()->at(i)->text().toStdString() << " " << getLetras()->at(i)->text().toStdString() << " ";
                for(int j = i + 1; j < getInicios()->size(); j++) {
                    if(getInicios()->at(i)->text() == getInicios()->at(j)->text()) {
                        QString text2;
                        text2.append(QString::fromStdString(getLetras()->at(j)->text().toStdString()) + " " + QString::fromStdString(getDestinos()->at(j)->text().toStdString()) + " ");
                        textos.push_back(text2);
                        //fs << getDestinos()->at(j)->text().toStdString() << " " << getLetras()->at(j)->text().toStdString() << " ";
                        marcados.push_back(j);
                    }
                }
                fs << textos.size() << " ";
                for(int k = 0; k < textos.size(); k++) {
                    fs << textos.at(k).toStdString();
                }
                fs << endl;
            }
        }
    }

    //Caso puntual, nodo final sin transiciones
    QString finales(QString::fromStdString(getNodosFinales()));
    QStringList list1 = finales.split(QRegExp("\\s+"), QString::SkipEmptyParts);

    for(int i = 0; i < list1.size(); i++) {
        cout << "Lista: " << list1.at(i).toStdString() << endl;
        if(std::find(getInicios()->begin(), getInicios()->end(), new CLineEdit(QString(list1.at(i)))) == getInicios()->end()) {
            cout << "El nodo final no tiene transiciones, se agrega manualmente" << endl;
            fs << list1.at(i).toStdString() << " 1 0" << endl;
        }
    }

    fs.close();
}

void CAsistenteCodificacion::slotHelp() {

    ///Crea una ventana que tenga la imagen infoAsistente con informacion relevante
    QWidget* window = new QWidget(); QHBoxLayout* a = new QHBoxLayout();
    QLabel* aux = new QLabel(); QImage myImage;

    myImage.load("/home/ivan/Documentos/Codigo-TFG/images/infoAsistente.png");
    aux->setPixmap(QPixmap::fromImage(myImage));
    a->addWidget(aux);

    window->setLayout(a);
    window->setStyleSheet("background-color: black;");
    window->setWindowTitle("Ayuda del asistente");
    this->setFixedSize(this->width(), this->height());
    window->show();
}

void CAsistenteCodificacion::slotCambiar(int i) {
    QString aux = getInicios()->at(i)->text();
    getInicios()->at(i)->setText(getDestinos()->at(i)->text());
    getDestinos()->at(i)->setText(aux);
    //cout << "heys" << endl;
}

void CAsistenteCodificacion::ventanaInfoCodificacion(string text) {
    ///Aplica un estilo y carga
    QWidget* window = new QWidget(); QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom);
    QLabel* label = new QLabel();
    label->setText(QString::fromStdString(text));
    QFont f( "Arial", 14, QFont::Bold);
    label->setFont( f);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    window->setStyleSheet("color: white; background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c); border-width: 1px;"
                          "border-color: #339;"
                          "border-style: solid;"
                          "border-radius: 7;"
                          "padding: 3px;"
                          "margin-left: 20px;"
                          "margin-right: 20px;"
                          "padding-left: 5px;"
                          "padding-right: 5px;");

    window->setLayout(layout);
    window->setWindowTitle("Codificacion");
    window->setMinimumSize(240, 180);
    window->setFixedWidth(240);
    window->setStyleSheet("background-color: white");

    window->show();
}
