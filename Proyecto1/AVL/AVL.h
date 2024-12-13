//
// Created by Marro on 13/12/2024.
//

#ifndef AVL_H
#define AVL_H

#include "NodoAVL.h"

class AVL {
private:
    NodoAVL *raiz;
    void insertar(NodoAVL *valor, NodoAVL* &raiz);
    int alturaMaxima(NodoAVL *nodo);
    int factorDeEquilibrio(NodoAVL *nodo);
public:
    AVL();

    //get
    NodoAVL *getRaiz();
    //set
    void setRaiz(NodoAVL *raiz);

    //otros metodos

    void insertar(int valor);








};



#endif //AVL_H
