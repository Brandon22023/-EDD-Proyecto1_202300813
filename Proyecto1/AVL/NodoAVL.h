//
// Created by Marro on 13/12/2024.
//

#ifndef NODOAVL_H
#define NODOAVL_H

class NodoAVL {
private:
    int valor;
    int factorEquilibrio;
    NodoAVL *izquierda;
    NodoAVL *derecha;


public:
    explicit NodoAVL(int valor);

    //get
    int getValor();
    int getFactorEquilibrio();
    NodoAVL* getIzquierda();
    NodoAVL* getDerecha();

    //set
    void setValor(int valor);
    void setFactorEquilibrio(int factorEquilibrio);
    void setIzquierda(NodoAVL *izquierda);
    void setDerecha(NodoAVL *derecha);

};








#endif //NODOAVL_H
