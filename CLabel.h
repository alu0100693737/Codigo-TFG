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
    CLabel(QString text);
    QImage getImagen();
    void setImagen(const QImage);
};

#endif // CLABEL_H
