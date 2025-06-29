//
// Created by Marro on 13/12/2024.
//

#ifndef NODOAVL_H
#define NODOAVL_H
#include "ELEMENTOAVL.h"

class NodoAVL {
private:
    ElementoAVL elemento;
    int factorEquilibrio;
    NodoAVL *izquierda;
    NodoAVL *derecha;


public:
    explicit NodoAVL(ElementoAVL elemento);

    //get
    ElementoAVL &getElemento();
    int getFactorEquilibrio();
    NodoAVL*& getIzquierda();
    NodoAVL*& getDerecha();

    //set
    void setElemento(ElementoAVL elemento);
    void setFactorEquilibrio(int factorEquilibrio);
    void setIzquierda(NodoAVL *izquierda);
    void setDerecha(NodoAVL *derecha);

};

#endif //NODOAVL_H
