#ifndef CLABEL_H
#define CLABEL_H
#include <QLabel>
#include <iostream>
using namespace std;

class CLabel : public QLabel {
public:
    CLabel();
    CLabel(QString, bool);
};

#endif // CLABEL_H
