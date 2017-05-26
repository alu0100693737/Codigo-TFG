#ifndef CPANELOPCIONES_H
#define CPANELOPCIONES_H
#include <QWidget>
#include <QScrollBar>
#include <QHBoxLayout>
#include "CLabel.h"


class CPanelOpciones : public QWidget {
private:
    QScrollBar* cannyThresHold_; //circulos 30
    QScrollBar* accumulatorThresHold_; //circulos 42
    QScrollBar* hougLinesP_; //80

    CLabel* valorCannyThresHold_;
    CLabel* valorAccumulatorThresHold_;
    CLabel* valorHoughLinesP_;

public:
    CPanelOpciones();
    QScrollBar* getCannyThresHold();
    QScrollBar* getAccumulatorThresHold();
    QScrollBar* getHoughLinesP();

    CLabel* getValorCannyThresHold();
    CLabel* getValorAccumulatorThresHold();
    CLabel* getValorHoughLinesP();
};

#endif // CPANELOPCIONES_H
