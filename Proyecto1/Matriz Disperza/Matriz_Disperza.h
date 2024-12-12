//
// Created by Marro on 08/12/2024.
//

#ifndef Matriz_Disperza_H
#define Matriz_Disperza_H

#include "Nodo.h"

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
    //------------------------------------------------------------------------------------------
    //otros metodos
    bool estavacia();

    Nodo *cabecerahorizontal(string valor);
    Nodo *cabeceravertical(string valor);


    Nodo *insertarCabeceraHorizontal(string valor);
    Nodo *insertarCabeceraVertical(string valor);

    void insertarvalor(string valor, string contra, string cabecera_horizontal, string cabecera_vertical);
    void insertarALfinal(Nodo *valor, Nodo *cabeceraHorizontal, Nodo *cabeceraVertical);
    void insertarAlFinalHorizontal(Nodo *valor, Nodo *cabeceraHorizontal);
    void insertarAlFinalVertical(Nodo *valor, Nodo *cabeceraVertical);
    void insertarAlMedioVertical(Nodo *valor, Nodo *VERTICAL);
    void insertarAlMedioHorizontal(Nodo *valor, Nodo *HORIZONTAL);

    Nodo *enCabeceraHorizontal(Nodo *NODE);
    Nodo *enCabeceraVertical(Nodo *NODE);

    bool masabajo(Nodo *cabeV, string cabecera_horizontal);
    bool masderecha(Nodo *cabeH, string cabecera_vertical);
    //para graficar y tener un mejor control de las cosas
    void graficarMatrizDisperza();

};
#endif //Matriz_Disperza_H
