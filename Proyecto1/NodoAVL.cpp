//
// Created by Marro on 13/12/2024.
//
#include "AVL/NodoAVL.h"

#include <set>

#include "Matriz Disperza/Nodo.h"

NodoAVL::NodoAVL(int valor) {
    this->valor = valor;
    this->factorEquilibrio = 0;
    this->izquierda = nullptr;
    this->derecha = nullptr;
}
//get
int NodoAVL::getValor() {
    return valor;
}

int NodoAVL::getFactorEquilibrio() {
    return factorEquilibrio;
}

NodoAVL *NodoAVL::getIzquierda() {
    return izquierda;
}

NodoAVL *NodoAVL::getDerecha() {
    return derecha;
}
//set
void NodoAVL::setValor(int valor) {
    this->valor = valor;
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