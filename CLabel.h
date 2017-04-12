#ifndef CLABEL_H
#define CLABEL_H
#include <QLabel>
#include <iostream>
using namespace std;

class CLabel : public QLabel {
private:
    QImage imagen_;
public:
    CLabel();
    CLabel(QString, bool);
    QImage getImagen();
    void setImagen(QString);
};

#endif // CLABEL_H
