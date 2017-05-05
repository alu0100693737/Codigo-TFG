#ifndef CDETECTARTRANSICIONES_H
#define CDETECTARTRANSICIONES_H

#include "CContourWithData.h"

#include<iostream>
#include<sstream>
using namespace std;

const int RESIZED_IMAGE_WIDTH = 20;
const int RESIZED_IMAGE_HEIGHT = 30;

class CDetectarTransiciones
{

public:
    CDetectarTransiciones();
    bool ejecutar();
};

#endif // CDETECTARTRANSICIONES_H
