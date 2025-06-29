//
// Created by Marro on 07/12/2024.
//

#ifndef NODO_H
#define NODO_H
#include <string>
using namespace std;


// Nodo con 6 apuntadores en una estructura dispersa
class Nodo {
private:

    string valor;    // Valor del nodo
    Nodo* siguiente;     // Apuntador al nodo siguiente
    Nodo* previo;        // Apuntador al nodo previo
    Nodo* arriba;        // Apuntador al nodo arriba
    Nodo* abajo;         // Apuntador al nodo abajo
    Nodo* atras;         // Apuntador al nodo atrás
    Nodo* adelante;      // Apuntador al nodo adelante

    //este es nodo extra para la contraseña del usuario
    Nodo* contra;      // Apuntador al nodo adelante

public:
    // Constructor

    explicit Nodo(string valor);

    // Get
    string getValor();
    Nodo* getSiguiente();
    Nodo* getPrevio();
    Nodo* getArriba();
    Nodo* getAbajo();
    Nodo* getAtras();
    Nodo* getadelante();
    Nodo* getcontra();

    // Set
    void setValor(string valor);
    void setSiguiente(Nodo* siguiente);
    void setPrevio(Nodo* previo);
    void setArriba(Nodo* arriba);
    void setAbajo(Nodo* abajo);
    void setAtras(Nodo* atras);
    void setadelante(Nodo* adelante);
    void setcontra(Nodo* adelante);
};

#endif // NODO_H