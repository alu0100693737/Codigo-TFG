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
public:
    CPanelOpciones();
    QScrollBar* getCannyThresHold();
    QScrollBar* getAccumulatorThresHold();
    QScrollBar* getHoughLinesP();
};

#endif // CPANELOPCIONES_H
