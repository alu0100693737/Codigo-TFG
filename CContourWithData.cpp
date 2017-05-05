#include "CContourWithData.h"

ContourWithData::ContourWithData() { }

bool ContourWithData::checkIfContourIsValid() {
    if (fltArea < MIN_CONTOUR_AREA) return false;
    return true;
}

