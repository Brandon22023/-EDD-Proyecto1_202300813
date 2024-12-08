//
// Created by Marro on 07/12/2024.
//

#ifndef NODOSMATRIZDISPERZA_H
#define NODOSMATRIZDISPERZA_H



class NodosMatrizDisperza {
    // 6 apuntadores
    Node *siguiente;
    Node *previo;
    Node *arriba;
    Node *abajo;
    Node *atras;
    Node *adelante;

    Node() {
        this -> siguiente = nullptr;
        this -> previo = nullptr;
        this -> arriba = nullptr;
        this -> abajo = nullptr;
        this -> atras = nullptr;
        this -> adelante = nullptr;
    }

};



#endif //NODOSMATRIZDISPERZA_H
