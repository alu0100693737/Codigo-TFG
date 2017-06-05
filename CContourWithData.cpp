////////////////////////////////////////////////////////////////////////////
//   CContourWithData.h - Implementación de la clase CContourWithData     //
//                                                                        //
//               Autor: Iván García Campos                                //
//                                                                        //
//            Proyecto de Trabajo Fin de Grado.                           //
//                                                                        //
//               Fecha: 05/06/2017                                        //
////////////////////////////////////////////////////////////////////////////

#include "CContourWithData.h"

CContourWithData::CContourWithData() { }

CContourWithData::CContourWithData(const CContourWithData &copy) {
    ptContour = copy.ptContour;
    dimensionContorno = copy.dimensionContorno;
    fltArea = copy.fltArea;
}

bool CContourWithData::checkIfContourIsValid() {
    if (fltArea < MIN_CONTOUR_AREA) return false;
    return true;
}

void CContourWithData::mostrarContorno() {
    cout << "Contorno con dimension " << dimensionContorno << " en " << fltArea;
}
