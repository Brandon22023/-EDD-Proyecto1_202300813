//
// Created by Marro on 08/12/2024.
//
#include "Matriz Disperza/Nodo.h"



Nodo::Nodo(int valor) {
    this->valor = valor;
    this->siguiente = nullptr;
    this->previo = nullptr;
    this->arriba = nullptr;
    this->abajo = nullptr;
    this->adelante = nullptr;
    this->atras = nullptr;
}

// Métodos *get*
int Nodo::getValor() {
    return valor;
}

Nodo* Nodo::getSiguiente() {
    return siguiente;
}

Nodo* Nodo::getPrevio() {
    return previo;
}

Nodo* Nodo::getArriba() {
    return arriba;
}

Nodo* Nodo::getAbajo() {
    return abajo;
}

Nodo* Nodo::getAtras() {
    return atras;
}

Nodo* Nodo::getAdelante() {
    return adelante;
}

// Métodos *set*
void Nodo::setValor(int valor) {
    this->valor = valor;
}

void Nodo::setSiguiente(Nodo* siguiente) {
    this->siguiente = siguiente;
}

void Nodo::setPrevio(Nodo* previo) {
    this->previo = previo;
}

void Nodo::setArriba(Nodo* arriba) {
    this->arriba = arriba;
}

void Nodo::setAbajo(Nodo* abajo) {
    this->abajo = abajo;
}

void Nodo::setAtras(Nodo* atras) {
    this->atras = atras;
}

void Nodo::setAdelante(Nodo* adelante) {
    this->adelante = adelante;
}




