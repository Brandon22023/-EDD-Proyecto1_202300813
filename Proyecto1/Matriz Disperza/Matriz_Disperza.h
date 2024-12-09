//
// Created by Marro on 08/12/2024.
//

#ifndef Matriz_Disperza_H
#define Matriz_Disperza_H

#include "Matriz Disperza/Nodo.h"

class Matriz_Disperza {

private:
    Nodo *cabeceraHo;
    Nodo *cabecerave;

public:
    Matriz_Disperza();

    //get
    Nodo *getcabeceraHo();
    Nodo *getcabecerave();

    //set
    void setcabeceraHo(Nodo *cabeceraHo);
    void setcabecerave(Nodo *cabecerave);

    //otros metodos
    bool estavacia();

    Nodo *cabecerahorizontal(int valor);
    Nodo *cabececarvertical(int valor);

    void insertarvalor(int valor);






};



#endif //Matriz_Disperza_H
