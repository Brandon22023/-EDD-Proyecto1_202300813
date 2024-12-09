//
// Created by Marro on 07/12/2024.
//

#ifndef NODO_H
#define NODO_H



// Nodo con 6 apuntadores en una estructura dispersa
class Nodo {
private:
    int valor;           // Valor del nodo
    Nodo* siguiente;     // Apuntador al nodo siguiente
    Nodo* previo;        // Apuntador al nodo previo
    Nodo* arriba;        // Apuntador al nodo arriba
    Nodo* abajo;         // Apuntador al nodo abajo
    Nodo* atras;         // Apuntador al nodo atrás
    Nodo* adelante;      // Apuntador al nodo adelante

public:
    // Constructor

    explicit Nodo(int valor);

    // Get
    int getValor();
    Nodo* getSiguiente();
    Nodo* getPrevio();
    Nodo* getArriba();
    Nodo* getAbajo();
    Nodo* getAtras();
    Nodo* getAdelante();

    // Set
    void setValor(int valor);
    void setSiguiente(Nodo* siguiente);
    void setPrevio(Nodo* previo);
    void setArriba(Nodo* arriba);
    void setAbajo(Nodo* abajo);
    void setAtras(Nodo* atras);
    void setAdelante(Nodo* adelante);
};

#endif // NODO_H
