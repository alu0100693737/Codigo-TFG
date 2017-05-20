#include "CContourWithData.h"

ContourWithData::ContourWithData() { }

ContourWithData::ContourWithData(const ContourWithData &copy) {
    ptContour = copy.ptContour;
    dimensionContorno = copy.dimensionContorno;
    fltArea = copy.fltArea;
}

bool ContourWithData::checkIfContourIsValid() {
    if (fltArea < MIN_CONTOUR_AREA) return false;
    return true;
}

void ContourWithData::mostrarContorno() {
    cout << "Contorno con dimension " << dimensionContorno << " en " << fltArea;
}
