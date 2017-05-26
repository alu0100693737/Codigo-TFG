#include "CPanelOpciones.h"

CPanelOpciones::CPanelOpciones() {

    QGridLayout *layout = new QGridLayout();

    cannyThresHold_ = new QScrollBar(Qt::Horizontal);
    accumulatorThresHold_ = new QScrollBar(Qt::Horizontal);
    hougLinesP_ = new QScrollBar(Qt::Horizontal);

    getCannyThresHold()->setRange(2, 200);
    getCannyThresHold()->setValue(30);

    getAccumulatorThresHold()->setRange(2, 100);
    getAccumulatorThresHold()->setValue(42);

    getHoughLinesP()->setRange(2, 200);
    getHoughLinesP()->setValue(80);

    layout->addWidget(new CLabel(QString("CannyThresHold"), true),  0, 0, 1, 2);
    layout->addWidget(getCannyThresHold(), 1, 0, 1, 1);
    layout->addWidget(new CLabel(QString::number(getCannyThresHold()->value()), false), 1, 1, 1, 1);
    layout->addWidget(getAccumulatorThresHold(), 2, 0, 1, 1);
    layout->addWidget(new CLabel(QString::number(getAccumulatorThresHold()->value()), false), 2, 1, 1, 1);
    layout->addWidget(getHoughLinesP(), 3, 0, 1, 1);
    layout->addWidget(new CLabel(QString::number(getHoughLinesP()->value()), false), 3, 1, 1, 1);



    layout->addWidget(new CLabel(QString::number(cannyThresHold_->value()), false), 0, 1, 1, 1);

    setLayout(layout);
   //this->addAction(cannyThresHold_);
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
