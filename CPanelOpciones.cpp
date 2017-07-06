/////////////////////////////////////////////////////////////////
//CPanelOpciones.h - Implementacion de la clase CPanelOpciones //
//                                                             //
//               Autor: Iván García Campos                     //
//                                                             //
//            Proyecto de Trabajo Fin de Grado.                //
//                                                             //
//               Fecha: 05/06/2017                             //
/////////////////////////////////////////////////////////////////

#include "CPanelOpciones.h"

CPanelOpciones::CPanelOpciones() {
    ///Se carga el Layout del panel
    layout_ = new QGridLayout();
    setFixedHeight(120);
    //verde
    setStyleSheet("background-color: rgba(0, 107, 97, 0.9); border: 1px solid black");

    ///Agregamos a la ventana los datos
    setLayout(layout_);
    iniciarVistaDeteccion(0);
}

void CPanelOpciones::iniciarVistaDeteccion(int valor) {
    setFixedHeight(160);
    ///Se inicializan los QScrollBar
    cannyThresHold_ = new QScrollBar(Qt::Horizontal);
    accumulatorThresHold_ = new QScrollBar(Qt::Horizontal);
    hougLinesP_ = new QScrollBar(Qt::Horizontal);

    ///Aplicamos estilo fondo 'verde', rango de valores y valor por defecto a los QScrollBar

    getCannyThresHold()->setStyleSheet("background-color: rgba(126, 156, 232 ,  0.9);");
    getCannyThresHold()->setRange(10, 150);
    getCannyThresHold()->setValue(CANNYTHRESHOLD);

    getAccumulatorThresHold()->setStyleSheet("background-color: rgba(126, 156, 232 ,  0.9);");
    getAccumulatorThresHold()->setRange(10, 150);
    getAccumulatorThresHold()->setValue(ACCUMULATORTHRESHOLD);

    getHoughLinesP()->setStyleSheet("background-color: rgba(126, 156, 232,  0.9);");
    getHoughLinesP()->setRange(10, 150);
    getHoughLinesP()->setValue(HOUGHLINESP);

    lCannyThresHold_ = new CLabel(QString("CannyThresHold"), false);
    lAccumulatorThresHold_ = new CLabel(QString("AccumulatorThresHold"), false);
    lHoughLinesP_ = new CLabel(QString("HoughLinesP"), false);

    ///Se inicializan los CLabel con los valores de los QScrollBar
    valorCannyThresHold_ = new CLabel(QString::number(getCannyThresHold()->value()), false);
    valorAccumulatorThresHold_ = new CLabel(QString::number(getAccumulatorThresHold()->value()), false);
    valorHoughLinesP_ = new CLabel(QString::number(getHoughLinesP()->value()), false);
    setStyleSheet("background-color: rgba(0, 107, 97, 0.9); border: 1px solid black");
    // simplificarAutomata_ = new CPushButton("Simplificar Automata", true);
    // corregirFichero_ = new CPushButton("Corregir Fichero", true);

    if(!getLayout()->isEmpty()) {
        if(valor == 0){
            cout << "0 " << endl;
            getLayout()->removeWidget(getCargarImagenCorregir());
            getLayout()->removeWidget(getCargarImagenReferencia());
            getLayout()->removeWidget(getCargarFicheroCorregir());
            getLayout()->removeWidget(getCargarFicheroReferencia());

            delete getCargarImagenCorregir();
            delete getCargarImagenReferencia();
            delete getCargarFicheroCorregir();
            delete getCargarFicheroReferencia();
            for (int i = 0; i < getLayout()->count(); ++i) {
                QWidget *widget = getLayout()->itemAt(i)->widget();
                if (widget == getSimplificarFicheroReferencia()) {
                    getLayout()->removeWidget(getSimplificarFicheroReferencia());
                    delete getSimplificarFicheroReferencia();
                } else if (widget == getSimplificarFicheroCorregir()) {
                    getLayout()->removeWidget(getSimplificarFicheroCorregir());
                    delete getSimplificarFicheroCorregir();
                } else if (widget == getCorregirFichero()) {
                    getLayout()->removeWidget(getCorregirFichero());
                    delete getCorregirFichero();
                } else if (widget == getCargarImagenCorregir()) {
                    getLayout()->removeWidget(getCargarImagenCorregir());
                    delete getCargarImagenCorregir();
                }
            }
        } else if (valor == 1) {
            cout << "1" << endl;
            getLayout()->removeWidget(getCargarImagenCorregir());
            getLayout()->removeWidget(getCargarImagenReferencia());
            getLayout()->removeWidget(getCargarFicheroCorregir());
            getLayout()->removeWidget(getCargarFicheroReferencia());
            getLayout()->removeWidget(getAnalizarCadena());
            getLayout()->removeWidget(getSimplificarFicheroCorregir());

            delete getCargarImagenCorregir();
            delete getCargarImagenReferencia();
            delete getCargarFicheroCorregir();
            delete getCargarFicheroReferencia();
            delete getAnalizarCadena();
            delete getSimplificarFicheroCorregir();
            for (int i = 0; i < getLayout()->count(); ++i) {
                QWidget *widget = getLayout()->itemAt(i)->widget();
                if (widget == getSimplificarFicheroReferencia()) {
                    getLayout()->removeWidget(getSimplificarFicheroReferencia());
                    delete getSimplificarFicheroReferencia();
                } else if (widget == getSimplificarFicheroCorregir()) {
                    getLayout()->removeWidget(getSimplificarFicheroCorregir());
                    delete getSimplificarFicheroCorregir();
                } else if (widget == getCorregirFichero()) {
                    getLayout()->removeWidget(getCorregirFichero());
                    delete getCorregirFichero();
                }
            }
        } else if (valor == 2) {
            cout << " 2" << endl;

            getLayout()->removeWidget(getCargarImagenCorregir());
            getLayout()->removeWidget(getCargarImagenReferencia());
            getLayout()->removeWidget(getCargarFicheroCorregir());
            getLayout()->removeWidget(getCargarFicheroReferencia());
            getLayout()->removeWidget(getSimplificarFicheroReferencia());
            getLayout()->removeWidget(getAnalizarCadenaReferencia());

            delete getCargarImagenCorregir();
            delete getCargarImagenReferencia();
            delete getCargarFicheroCorregir();
            delete getCargarFicheroReferencia();
            delete getAnalizarCadenaReferencia();
            delete getSimplificarFicheroReferencia();

            for (int i = 0; i < getLayout()->count(); ++i) {
                QWidget *widget = getLayout()->itemAt(i)->widget();
                if (widget == getSimplificarFicheroReferencia()) {
                    getLayout()->removeWidget(getSimplificarFicheroReferencia());
                    delete getSimplificarFicheroReferencia();
                } else if (widget == getSimplificarFicheroCorregir()) {
                    getLayout()->removeWidget(getSimplificarFicheroCorregir());
                    delete getSimplificarFicheroCorregir();
                } else if (widget == getCorregirFichero()) {
                    getLayout()->removeWidget(getCorregirFichero());
                    delete getCorregirFichero();
                }
            }

        } else if (valor == 3) {
            cout << "3" << endl;
            getLayout()->removeWidget(getCargarImagenCorregir());
            getLayout()->removeWidget(getCargarImagenReferencia());
            getLayout()->removeWidget(getCargarFicheroCorregir());
            getLayout()->removeWidget(getCargarFicheroReferencia());
            getLayout()->removeWidget(getSimplificarFicheroReferencia());
            getLayout()->removeWidget(getAnalizarCadena());
            getLayout()->removeWidget(getAnalizarCadenaReferencia());
            getLayout()->removeWidget(getSimplificarFicheroCorregir());
            getLayout()->removeWidget(getCorregirFichero());

            delete getCargarImagenCorregir();
            delete getCargarImagenReferencia();
            delete getCargarFicheroCorregir();
            delete getCargarFicheroReferencia();
            delete getSimplificarFicheroReferencia();
            delete getAnalizarCadena();
            delete getAnalizarCadenaReferencia();
            delete getSimplificarFicheroCorregir();
            delete getCorregirFichero();

            for (int i = 0; i < getLayout()->count(); ++i) {
                QWidget *widget = getLayout()->itemAt(i)->widget();
                if (widget == getSimplificarFicheroReferencia()) {
                    getLayout()->removeWidget(getSimplificarFicheroReferencia());
                    delete getSimplificarFicheroReferencia();
                } else if (widget == getSimplificarFicheroCorregir()) {
                    getLayout()->removeWidget(getSimplificarFicheroCorregir());
                    delete getSimplificarFicheroCorregir();
                } else if (widget == getCorregirFichero()) {
                    cout << "Deberia borrar pero no borra " << endl;
                    getLayout()->removeWidget(getCorregirFichero());
                    delete getCorregirFichero();
                }
            }
        } else {
            cout << "Error, vista no valida en panel correccion" << endl;
        }
    }

    getLayout()->addWidget(getLCannyThresHold(),  0, 0, 1, 4);
    getLayout()->addWidget(getCannyThresHold(), 1, 0, 1, 3);
    getLayout()->addWidget(getValorCannyThresHold(), 1, 3, 1, 1);

    getLayout()->addWidget(getLAccumulatorThresHold(),  2, 0, 1, 4);
    getLayout()->addWidget(getAccumulatorThresHold(), 3, 0, 1, 3);
    getLayout()->addWidget(getValorAccumulatorThresHold(), 3, 3, 1, 1);

    getLayout()->addWidget(getLHoughLinesP(),  4, 0, 1, 4);
    getLayout()->addWidget(getHoughLinesP(), 5, 0, 1, 3);
    getLayout()->addWidget(getValorHoughLinesP(), 5, 3, 1, 1);
    setStyleSheet("background-color: rgba(0, 107, 97, 0.9); border: 1 px solid black");
}

void CPanelOpciones::iniciarVistaCorreccion(int valor) { //opciones
    setMinimumHeight(180);
    if(valor == 0)  {
        cout << "correccion 0" << endl;
        getLayout()->removeWidget(getCannyThresHold());
        getLayout()->removeWidget(getValorCannyThresHold());
        getLayout()->removeWidget(getLCannyThresHold());
        getLayout()->removeWidget(getAccumulatorThresHold());
        getLayout()->removeWidget(getValorAccumulatorThresHold());
        getLayout()->removeWidget(getLAccumulatorThresHold());
        getLayout()->removeWidget(getValorHoughLinesP());
        getLayout()->removeWidget(getHoughLinesP());
        getLayout()->removeWidget(getLHoughLinesP());

        delete getLCannyThresHold();
        delete getCannyThresHold();
        delete getValorCannyThresHold();
        delete getLAccumulatorThresHold();
        delete getAccumulatorThresHold();
        delete getValorAccumulatorThresHold();
        delete getLHoughLinesP();
        delete getHoughLinesP();
        delete getValorHoughLinesP();

        for (int i = 0; i < getLayout()->count(); ++i) {
            QWidget *widget = getLayout()->itemAt(i)->widget();

            if (widget == getAnalizarCadena()) {
                getLayout()->removeWidget(getAnalizarCadena());
                delete getAnalizarCadena();
            } else if (widget == getAnalizarCadenaReferencia()) {
                getLayout()->removeWidget((getAnalizarCadenaReferencia()));
                delete getAnalizarCadenaReferencia();
            } else if (widget == getSimplificarFicheroCorregir()) {
                getLayout()->removeWidget(getSimplificarFicheroCorregir());
                delete getSimplificarFicheroCorregir();
            } else if (widget == getCargarImagenCorregir()) {
                getLayout()->removeWidget(getCargarImagenCorregir());
                delete getCargarImagenCorregir();
            } else if (widget == getCargarFicheroCorregir()) {
                getLayout()->removeWidget(getCargarFicheroCorregir());
                delete getCargarFicheroCorregir();
            } else if (widget == getCorregirFichero()) {
                getLayout()->removeWidget(getCorregirFichero());
                delete getCorregirFichero();
            }
        }

        /// Valores para la codificacion 2 Botones
        cargarImagenCorregir_ = new CPushButton("Cargar imagen para \nsu corrección", true);
        cargarImagenReferencia_ = new CPushButton("Cargar imagen de \nreferencia", true);

        cargarFicheroCorregir_ = new CPushButton("Cargar fichero para \nsu corrección", true);
        cargarFicheroReferencia_ = new CPushButton("Cargar fichero de \nreferencia", true);
        getLayout()->addWidget(new CLabel("Panel 1", false), 0, 0, 1, 2);
        getLayout()->addWidget(new CLabel("Panel 2", false), 0, 2, 1, 2);
        getLayout()->addWidget(getCargarImagenCorregir(), 1, 0, 2, 2);
        getLayout()->addWidget(getCargarFicheroCorregir(), 3, 0, 2, 2);
        getLayout()->addWidget(getCargarImagenReferencia(), 1, 2, 2, 2);
        getLayout()->addWidget(getCargarFicheroReferencia(), 3, 2, 2, 2);
    } else if(valor == 1) {
        cout << "Correccion 1" << endl;
        for (int i = 0; i < getLayout()->count(); ++i) {
            QWidget *widget = getLayout()->itemAt(i)->widget();
            if (widget == getCannyThresHold()) {
                iniciarVistaCorreccion(0);
                break;
            } else if (widget == getAnalizarCadena()) {
                getLayout()->removeWidget(getAnalizarCadena());
                delete getAnalizarCadena();
            } else if (widget == getAnalizarCadenaReferencia()) {
                getLayout()->removeWidget((getAnalizarCadenaReferencia()));
                delete getAnalizarCadenaReferencia();
            } else if (widget == getSimplificarFicheroReferencia()) {
                getLayout()->removeWidget(getSimplificarFicheroReferencia());
                delete getSimplificarFicheroReferencia();
            } else if (widget == getCorregirFichero()) {
                getLayout()->removeWidget(getCorregirFichero());
                delete getCorregirFichero();
            }
        }

        analizarCadena_ = new CPushButton("Analizar cadena sobre el automata a corregir", false);
        simplificarAutomataCorregir_ = new CPushButton("Simplificar automata a corregir", false);

        getLayout()->removeWidget(getCargarImagenCorregir());
        getLayout()->removeWidget(getCargarFicheroCorregir());
        delete getCargarImagenCorregir();
        delete getCargarFicheroCorregir();

        cargarImagenCorregir_ = new CPushButton("Cargar Imagen para su correccion", false);
        cargarFicheroCorregir_ = new CPushButton("Cargar fichero para su correccion", false);

        getLayout()->addWidget(getCargarImagenCorregir(), 1, 0, 1, 2);
        getLayout()->addWidget(getCargarFicheroCorregir(), 2, 0, 1, 2);
        getLayout()->addWidget(getAnalizarCadena(), 3, 0, 1, 2);
        getLayout()->addWidget(getSimplificarFicheroCorregir(), 4, 0, 1, 2);
    } else if (valor == 2) {
        cout << "Correccion 2" << endl;
        for (int i = 0; i < getLayout()->count(); ++i) {
            QWidget *widget = getLayout()->itemAt(i)->widget();
            if (widget == getCannyThresHold()) {
                cout << "Borrando scrollbars " << endl;
                getLayout()->removeWidget(getCannyThresHold());
                getLayout()->removeWidget(getValorCannyThresHold());
                getLayout()->removeWidget(getLCannyThresHold());
                getLayout()->removeWidget(getAccumulatorThresHold());
                getLayout()->removeWidget(getValorAccumulatorThresHold());
                getLayout()->removeWidget(getLAccumulatorThresHold());
                getLayout()->removeWidget(getValorHoughLinesP());
                getLayout()->removeWidget(getHoughLinesP());
                getLayout()->removeWidget(getLHoughLinesP());

                delete getLCannyThresHold();
                delete getCannyThresHold();
                delete getValorCannyThresHold();
                delete getLAccumulatorThresHold();
                delete getAccumulatorThresHold();
                delete getValorAccumulatorThresHold();
                delete getLHoughLinesP();
                delete getHoughLinesP();
                delete getValorHoughLinesP();

                cargarImagenCorregir_ = new CPushButton("Cargar imagen para \nsu corrección", true);
                cargarImagenReferencia_ = new CPushButton("Cargar imagen de \nreferencia", true);

                cargarFicheroCorregir_ = new CPushButton("Cargar fichero para \nsu corrección", true);
                cargarFicheroReferencia_ = new CPushButton("Cargar fichero de \nreferencia", true);
                getLayout()->addWidget(new CLabel("Panel 1", false), 0, 0, 1, 2);
                getLayout()->addWidget(new CLabel("Panel 2", false), 0, 2, 1, 2);
                getLayout()->addWidget(getCargarImagenCorregir(), 1, 0, 2, 2);
                getLayout()->addWidget(getCargarFicheroCorregir(), 3, 0, 2, 2);
                getLayout()->addWidget(getCargarImagenReferencia(), 1, 2, 2, 2);
                getLayout()->addWidget(getCargarFicheroReferencia(), 3, 2, 2, 2);

            }
            else if (widget == getSimplificarFicheroReferencia()) {
                getLayout()->removeWidget(getSimplificarFicheroReferencia());
                delete getSimplificarFicheroReferencia();
            } else if (widget == getCorregirFichero()) {
                getLayout()->removeWidget(getCorregirFichero());
                delete getCorregirFichero();
            } else if(widget == getSimplificarFicheroCorregir()) {
                getLayout()->removeWidget(getSimplificarFicheroCorregir());
                delete getSimplificarFicheroCorregir();
            } else if (widget == getCorregirFichero()) {
                getLayout()->removeWidget(getCorregirFichero());
                delete getCorregirFichero();
            } else if (widget == getAnalizarCadenaReferencia()) {
                getLayout()->removeWidget((getAnalizarCadenaReferencia()));
                delete getAnalizarCadenaReferencia();
            }
        }

        simplificarAutomataReferencia_ = new CPushButton("Simplificar autómata de referencia", false);
        getLayout()->removeWidget(getCargarImagenReferencia());
        getLayout()->removeWidget((getCargarFicheroReferencia()));
        delete getCargarImagenReferencia();
        delete getCargarFicheroReferencia();

        cargarImagenReferencia_ = new CPushButton("Cargar Imagen de referencia", false);
        cargarFicheroReferencia_ = new CPushButton("Cargar fichero de referencia", false);
        analizarCadenaReferencia_ = new CPushButton("Analizar cadena sobre automata de referencia", false);

        getLayout()->addWidget(new CLabel("Panel 1", false), 0, 0, 1, 2);
        getLayout()->addWidget(getCargarImagenCorregir(), 1, 0, 2, 2);
        getLayout()->addWidget(getCargarFicheroCorregir(), 3, 0, 2, 2);

        getLayout()->addWidget(new CLabel("Panel 2", false), 0, 2, 1, 2);
        getLayout()->addWidget(getCargarImagenReferencia(), 1, 2, 1, 2);
        getLayout()->addWidget(getCargarFicheroReferencia(), 2, 2, 1, 2);
        getLayout()->addWidget(getAnalizarCadenaReferencia(), 3, 2, 1, 2);
        getLayout()->addWidget(getSimplificarFicheroReferencia(), 4, 2, 1, 2);
    } else if(valor == 3) {
        cout << "Correcion 3" << endl;

        for (int i = 0; i < getLayout()->count(); ++i) {
            QWidget *widget = getLayout()->itemAt(i)->widget();
            if (widget == getCannyThresHold()) {
                getLayout()->removeWidget(getCannyThresHold());
                getLayout()->removeWidget(getValorCannyThresHold());
                getLayout()->removeWidget(getLCannyThresHold());
                getLayout()->removeWidget(getAccumulatorThresHold());
                getLayout()->removeWidget(getValorAccumulatorThresHold());
                getLayout()->removeWidget(getLAccumulatorThresHold());
                getLayout()->removeWidget(getValorHoughLinesP());
                getLayout()->removeWidget(getHoughLinesP());
                getLayout()->removeWidget(getLHoughLinesP());

                delete getLCannyThresHold();
                delete getCannyThresHold();
                delete getValorCannyThresHold();
                delete getLAccumulatorThresHold();
                delete getAccumulatorThresHold();
                delete getValorAccumulatorThresHold();
                delete getLHoughLinesP();
                delete getHoughLinesP();
                delete getValorHoughLinesP();
            }
            else if (widget == getSimplificarFicheroReferencia()) {
                getLayout()->removeWidget(getSimplificarFicheroReferencia());
                delete getSimplificarFicheroReferencia();
            }else if (widget == getAnalizarCadena()) {
                getLayout()->removeWidget(getAnalizarCadena());
                delete getAnalizarCadena();
            } else if (widget == getAnalizarCadenaReferencia()) {
                getLayout()->removeWidget((getAnalizarCadenaReferencia()));
                delete getAnalizarCadenaReferencia();
            } else if (widget == getSimplificarFicheroCorregir()) {
                getLayout()->removeWidget(getSimplificarFicheroCorregir());
                delete getSimplificarFicheroCorregir();
            } else if (widget == getCorregirFichero()) {
                getLayout()->removeWidget(getCorregirFichero());
                delete getCorregirFichero();
            }
        }

        analizarCadena_ = new CPushButton("Analizar cadena sobre el automata a corregir", false);
        analizarCadenaReferencia_ =  new CPushButton("Analizar cadena sobre automata de referencia", false);
        simplificarAutomataCorregir_ = new CPushButton("Simplificar automata a corregir", false);

        getLayout()->removeWidget(getCargarImagenCorregir());
        getLayout()->removeWidget(getCargarFicheroCorregir());

        delete getCargarImagenCorregir();
        delete getCargarFicheroCorregir();

        getLayout()->removeWidget(getCargarImagenReferencia());
        getLayout()->removeWidget((getCargarFicheroReferencia()));
        delete getCargarImagenReferencia();
        delete getCargarFicheroReferencia();

        cargarImagenCorregir_ = new CPushButton("Cargar Imagen para su correccion", false);
        cargarFicheroCorregir_ = new CPushButton("Cargar fichero para su correccion", false);

        cargarImagenReferencia_ = new CPushButton("Cargar Imagen de referencia", false);
        cargarFicheroReferencia_ = new CPushButton("Cargar fichero de referencia", false);

        simplificarAutomataReferencia_ = new CPushButton("Simplificar autómata de referencia", false);

        getLayout()->addWidget(new CLabel("Panel 1", false), 0, 0, 1, 2);
        getLayout()->addWidget(getCargarImagenCorregir(), 1, 0, 1, 2);
        getLayout()->addWidget(getCargarFicheroCorregir(), 2, 0, 1, 2);
        getLayout()->addWidget(getAnalizarCadena(), 3, 0, 1, 2);
        getLayout()->addWidget(getSimplificarFicheroCorregir(), 4, 0, 1, 2);

        getLayout()->addWidget(new CLabel("Panel 2", false), 0, 2, 1, 2);
        getLayout()->addWidget(getCargarImagenReferencia(), 1, 2, 1, 2);
        getLayout()->addWidget(getCargarFicheroReferencia(), 2, 2, 1, 2);
        getLayout()->addWidget(getAnalizarCadenaReferencia(), 3, 2, 1, 2);
        getLayout()->addWidget(getSimplificarFicheroReferencia(), 4, 2, 1, 2);

        corregirFichero_ = new CPushButton("Comprobar equivalencia", true);
        getCorregirFichero()->setStyleSheet("background-color: rgb(154, 238, 127);"
                                            "color: black; border-width: 1px;"
                                            "border-top: 1px solid white;"
                                            "border-left: 1px solid white;"
                                            "border-right: 1px solid grey;"
                                            "border-bottom: 1px solid grey;"
                                            "border-style: solid; "
                                            "border-radius: 5;"
                                            "padding: 2px;"
                                            "padding-left: 5px;"
                                            "padding-right: 5px;"
                                            "font: 16px;"
                                            "font-weight: bold;");

        getLayout()->addWidget(getCorregirFichero(), 5, 0, 1, 4);
    }
}

QGridLayout* CPanelOpciones::getLayout() {
    return layout_;
}

QScrollBar* CPanelOpciones::getCannyThresHold() {
    return cannyThresHold_;
}

QScrollBar* CPanelOpciones::getAccumulatorThresHold() {
    return accumulatorThresHold_;
}

QScrollBar* CPanelOpciones::getHoughLinesP() {
    return hougLinesP_;
}

CLabel* CPanelOpciones::getLCannyThresHold() {
    return lCannyThresHold_;
}

CLabel* CPanelOpciones::getLAccumulatorThresHold() {
    return lAccumulatorThresHold_;
}

CLabel* CPanelOpciones::getLHoughLinesP() {
    return lHoughLinesP_;
}

CLabel* CPanelOpciones::getValorCannyThresHold() {
    return valorCannyThresHold_;
}

CLabel* CPanelOpciones::getValorAccumulatorThresHold() {
    return valorAccumulatorThresHold_;
}

CLabel* CPanelOpciones::getValorHoughLinesP() {
    return valorHoughLinesP_;
}

CPushButton* CPanelOpciones::getCargarImagenCorregir() {
    return cargarImagenCorregir_;
}

CPushButton* CPanelOpciones::getCargarFicheroCorregir() {
    return cargarFicheroCorregir_;
}

CPushButton* CPanelOpciones::getCargarImagenReferencia() {
    return cargarImagenReferencia_;
}

CPushButton* CPanelOpciones::getCargarFicheroReferencia() {
    return cargarFicheroReferencia_;
}

CPushButton* CPanelOpciones::getAnalizarCadena() {
    return analizarCadena_;
}

CPushButton* CPanelOpciones::getAnalizarCadenaReferencia() {
    return analizarCadenaReferencia_;
}

CPushButton* CPanelOpciones::getSimplificarFicheroCorregir() {
    return simplificarAutomataCorregir_;
}

CPushButton* CPanelOpciones::getSimplificarFicheroReferencia() {
    return simplificarAutomataReferencia_;
}

CPushButton* CPanelOpciones::getCorregirFichero() {
    return corregirFichero_;
}
