//
// Created by Marro on 13/12/2024.
//

#include "AVL/AVL.h"

AVL::AVL() {
    this->raiz = nullptr;
}

NodoAVL* AVL::getRaiz() {
    return raiz;
}

void AVL::setRaiz(NodoAVL *raiz) {
    this->raiz = raiz;
}

//--------------------------------------------

void AVL::insertar(int valor) {
    NodoAVL *nodo = new NodoAVL(valor);

    insertar(nodo, this->raiz);
}


void AVL::insertar(NodoAVL *valor, NodoAVL *&raiz) {

}






