//
// Created by Marro on 13/12/2024.
//
#include "AVL/NodoAVL.h"

#include <set>

#include "Matriz Disperza/Nodo.h"

NodoAVL::NodoAVL(ElementoAVL elemento) : elemento(elemento) {
    this->factorEquilibrio = 0;
    this->izquierda = nullptr;
    this->derecha = nullptr;
}

//get
ElementoAVL &NodoAVL::getElemento() {
    return elemento;
}

int NodoAVL::getFactorEquilibrio() {
    return factorEquilibrio;
}

NodoAVL *&NodoAVL::getIzquierda() {
    return izquierda;
}

NodoAVL *&NodoAVL::getDerecha() {
    return derecha;
}
//set
void NodoAVL::setElemento(ElementoAVL elemento) {
    this->elemento = elemento;
}

void NodoAVL::setFactorEquilibrio(int factorEquilibrio) {
    this->factorEquilibrio = factorEquilibrio;
}
void NodoAVL::setIzquierda(NodoAVL *izquierda) {
    this->izquierda = izquierda;
}

void NodoAVL::setDerecha(NodoAVL *derecha) {
    this->derecha = derecha;
}