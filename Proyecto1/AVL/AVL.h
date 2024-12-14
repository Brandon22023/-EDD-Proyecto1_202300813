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
    void hakai(int valor, NodoAVL* &raiz);
    int alturaMaxima(NodoAVL *nodo);
    int factorDeEquilibrio(NodoAVL *nodo);
    void rotacionDerecha(NodoAVL* &NODO);
    void rotacionIzquierda(NodoAVL* &NODO);
    void rotacionDerechaIzquierda(NodoAVL* &NODO);
    void rotacionIzquierdaDerecha(NodoAVL* &NODO);
    NodoAVL *andateDerecha(NodoAVL* &NODO);
    std::string imprimir(NodoAVL *raiz, int &count);




public:
    AVL();

    //get
    NodoAVL *getRaiz();
    //set
    void setRaiz(NodoAVL *raiz);


    //otros metodos
    bool esHoja(NodoAVL *nodo);
    void insertar(int valor);
    void hakai(int valor);


    std::string imprimir();








};



#endif //AVL_H
