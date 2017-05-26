#include "CPanelOpciones.h"

CPanelOpciones::CPanelOpciones() {

    QGridLayout *layout = new QGridLayout();
    cannyThresHold_ = new QScrollBar(Qt::Horizontal);
    accumulatorThresHold_ = new QScrollBar(Qt::Horizontal);
    hougLinesP_ = new QScrollBar(Qt::Horizontal);

    getCannyThresHold()->setStyleSheet("background-color: rgba(232, 255, 141, 0.9);");
    getCannyThresHold()->setRange(2, 200);
    getCannyThresHold()->setValue(30);

    getAccumulatorThresHold()->setStyleSheet("background-color: rgba(232, 255, 141, 0.9);");
    getAccumulatorThresHold()->setRange(2, 200);
    getAccumulatorThresHold()->setValue(42);

    getHoughLinesP()->setStyleSheet("background-color: rgba(232, 255, 141, 0.9);");
    getHoughLinesP()->setRange(2, 200);
    getHoughLinesP()->setValue(80);

    layout->addWidget(new CLabel(QString("CannyThresHold"), false),  0, 0, 1, 4);
    layout->addWidget(getCannyThresHold(), 1, 0, 1, 3);
    layout->addWidget(new CLabel(QString::number(getCannyThresHold()->value()), false), 1, 3, 1, 1);

    layout->addWidget(new CLabel(QString("AcummulatorThresHold"), false),  2, 0, 1, 4);
    layout->addWidget(getAccumulatorThresHold(), 3, 0, 1, 3);
    layout->addWidget(new CLabel(QString::number(getAccumulatorThresHold()->value()), false), 3, 3, 1, 1);

    layout->addWidget(new CLabel(QString("HoughLinesP"), false),  4, 0, 1, 4);
    layout->addWidget(getHoughLinesP(), 5, 0, 1, 3);
    layout->addWidget(new CLabel(QString::number(getHoughLinesP()->value()), false), 5, 3, 1, 1);

    setLayout(layout);
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

