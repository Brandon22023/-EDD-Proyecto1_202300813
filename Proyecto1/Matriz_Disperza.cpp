//
// Created by Marro on 09/12/2024.
//
#include "Matriz Disperza/Matriz_Disperza.h"

Matriz_Disperza::Matriz_Disperza() {
    this->cabeceraHo = nullptr;
    this->cabecerave = nullptr;

}

Nodo * Matriz_Disperza::getcabeceraHo() {
    return cabeceraHo;
}

Nodo * Matriz_Disperza::getcabecerave() {
    return cabecerave;
}

void Matriz_Disperza::setcabeceraHo(Nodo *cabeceraHo) {
    this->cabeceraHo = cabeceraHo;
}
void Matriz_Disperza::setcabecerave(Nodo *cabecerave) {
    this->cabecerave = cabecerave;
}

bool Matriz_Disperza::estavacia() {
    return this->cabeceraHo == nullptr && this->cabecerave == nullptr;
}

//se crea un usuario
// el usuario tiene asociado un departamento y una empresa
// se deben buscar el depa y la empresa y si no existe crearlas.





