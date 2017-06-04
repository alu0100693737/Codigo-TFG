#include "CPushButton.h"

CPushButton::CPushButton(QString text) : QPushButton(text){
    setStyleSheet("background-color: rgb(175, 187, 199); color: black; border-width: 1px; border-top: 1px solid white; border-left: 1px solid white; border-right: 1px solid grey; border-bottom: 1px solid grey; border-style: solid; border-radius: 5; padding: 3px; padding-left: 5px; padding-right: 5px; font: 16px; font-weight: bold;");
}
