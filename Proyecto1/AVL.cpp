//
// Created by Marro on 13/12/2024.
//
#include <iostream>
#include "AVL/AVL.h"

#include <string>

using namespace std;

#include "Matriz Disperza/Nodo.h"

using namespace std;
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

    if (raiz== nullptr) {
        raiz = valor;
        raiz->setFactorEquilibrio(factorDeEquilibrio(raiz));

        return;
    }
    if (valor->getValor() < raiz->getValor()) {
        insertar(valor, raiz->getIzquierda());
    }else {
        insertar(valor, raiz->getDerecha());
    }
    raiz->setFactorEquilibrio(factorDeEquilibrio(raiz));

    if (raiz->getFactorEquilibrio() < -1) {
        if (raiz->getIzquierda()->getFactorEquilibrio() > 0) {
            rotacionDerechaIzquierda(raiz);

            return;

        }
        rotacionIzquierda(raiz);
        return;
    }

    if (raiz->getFactorEquilibrio() > 1) {
        if (raiz->getDerecha()->getFactorEquilibrio() < 0) {
            rotacionIzquierdaDerecha(raiz);
            return;
        }
        rotacionDerecha(raiz);

    }
}
void AVL::rotacionIzquierda(NodoAVL *&NODO) {

    NodoAVL *auxiliar = NODO->getIzquierda();

    NODO->getIzquierda() = auxiliar->getDerecha();
    auxiliar->getDerecha() = NODO;
    NODO = auxiliar;

    NODO->setFactorEquilibrio(factorDeEquilibrio(NODO));
    NODO->getIzquierda()->setFactorEquilibrio(factorDeEquilibrio(NODO->getIzquierda()));
    NODO->getDerecha()->setFactorEquilibrio(factorDeEquilibrio(NODO->getDerecha()));
}
void AVL::rotacionDerecha(NodoAVL *&NODO) {

    NodoAVL *auxiliar = NODO->getDerecha();

    NODO->getDerecha() = auxiliar->getIzquierda();
    auxiliar->getIzquierda() = NODO;
    NODO = auxiliar;

    NODO->setFactorEquilibrio(factorDeEquilibrio(NODO));
    NODO->getIzquierda()->setFactorEquilibrio(factorDeEquilibrio(NODO->getIzquierda()));
    NODO->getDerecha()->setFactorEquilibrio(factorDeEquilibrio(NODO->getDerecha()));

}
void AVL::rotacionIzquierdaDerecha(NodoAVL *&NODO) {
    rotacionIzquierda(NODO->getDerecha());
    rotacionDerecha(NODO);

}

void AVL::rotacionDerechaIzquierda(NodoAVL *&NODO) {
    rotacionDerecha(NODO->getIzquierda());
    rotacionIzquierda(NODO);

}


int AVL::alturaMaxima(NodoAVL *nodo) {

    if (nodo == nullptr)return 0;

    int hijoIzquierdo= alturaMaxima(nodo->getIzquierda());
    int hijoDerecho=alturaMaxima(nodo->getDerecha());


    return hijoIzquierdo > hijoDerecho ? hijoIzquierdo + 1 : hijoDerecho +1;
}

int AVL::factorDeEquilibrio(NodoAVL *nodo) {
    return alturaMaxima(nodo->getDerecha())-alturaMaxima(nodo->getIzquierda());
}

bool AVL::esHoja(NodoAVL *nodo) {
    return nodo->getIzquierda() == nullptr && nodo->getDerecha() == nullptr;
}

std::string AVL::imprimir() {
    int count = -1;
    std::string dot = "digraph G {\n\tnode [shape = circle];\n\t" ;

    dot += imprimir(this->raiz, count);

    dot += "\n}";

    return dot;

}

std::string AVL::imprimir(NodoAVL *raiz, int &count) {
    count++;

    int correntCount = count;

    string dot = "n" + to_string(correntCount) + "[label=\"" + to_string(raiz->getValor()) + "\"];\n\t";

    if (esHoja(raiz)) {
        return dot;
    }

    if (raiz->getIzquierda() != nullptr) {
        int nextNodo = count + 1;
        dot += "n" + to_string(correntCount) + " -> n" + to_string(nextNodo) + ";\n\t" + imprimir(raiz->getIzquierda(), count);
    }

    if (raiz->getDerecha() != nullptr) {
        int nextNodo = count + 1;
        dot += "n" + to_string(correntCount) + " -> n" + to_string(nextNodo) + ";\n\t" + imprimir(raiz->getDerecha(), count);
    }

    return dot;



}


































