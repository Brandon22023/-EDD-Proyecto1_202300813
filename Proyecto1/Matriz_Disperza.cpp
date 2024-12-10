//
// Created by Marro on 09/12/2024.
//
#include "Matriz Disperza/Matriz_Disperza.h"

Matriz_Disperza::Matriz_Disperza() {
    this->cabeceraHo = nullptr;
    this->cabecerave = nullptr;

}

Nodo* Matriz_Disperza::getcabeceraHo() {
    return cabeceraHo;
}

Nodo* Matriz_Disperza::getcabecerave() {
    return cabecerave;
}

void Matriz_Disperza::setcabeceraHo(Nodo *cabeceraHo) {
    this->cabeceraHo = cabeceraHo;
}
void Matriz_Disperza::setcabecerave(Nodo *cabecerave) {
    this->cabecerave = cabecerave;
}
//------------------------------------------------------


void Matriz_Disperza::insertarvalor(int valor, int cabecera_horizontal, int cabecera_vertical) {

    if (estavacia()) {
        //no es el mismo nodo asi que no hay problemas
        Nodo *cabeceraHorizontal = insertarCabeceraHorizontal(cabecera_horizontal);
        Nodo *cabeceraVertical = insertarCabeceraVertical(cabecera_vertical);

        insertarALfinal(valor, cabeceraHorizontal, cabeceraVertical);
    }


}

void Matriz_Disperza::insertarALfinal(int valor, Nodo *cabeceraHorizontal, Nodo *cabeceraVertical) {
    Nodo *usuarioNuevo = new Nodo(valor);

    Nodo *auxiliarHorizontal = cabeceraHorizontal;
    Nodo *auxiliarvertical = cabeceraVertical;


    while (auxiliarHorizontal->getAbajo() != nullptr) {
        auxiliarHorizontal = auxiliarHorizontal->getAbajo();
    }

    auxiliarHorizontal -> setAbajo(usuarioNuevo);
    usuarioNuevo -> setArriba(auxiliarHorizontal);

    while (auxiliarvertical->getSiguiente() != nullptr) {
        auxiliarvertical = auxiliarvertical->getSiguiente();
    }

    auxiliarvertical -> setSiguiente(usuarioNuevo);
    usuarioNuevo -> setPrevio(auxiliarvertical);
}






Nodo *Matriz_Disperza::insertarCabeceraHorizontal(int valor) {
    Nodo *nuevacabecera = new Nodo(valor);

    if (getcabeceraHo() == nullptr) {
        setcabeceraHo(nuevacabecera);
        return nuevacabecera;
    }


    Nodo *auxiliar = getcabeceraHo();
    //recorrer hasta el final
    while (auxiliar->getSiguiente() != nullptr) {
        auxiliar = auxiliar -> getSiguiente();
    }


    auxiliar->setSiguiente(nuevacabecera);
    nuevacabecera->setPrevio(auxiliar);

    return nuevacabecera;
}

Nodo *Matriz_Disperza::insertarCabeceraVertical(int valor) {
    Nodo *nuevacabecera = new Nodo(valor);

    if (getcabecerave() == nullptr) {
        setcabecerave(nuevacabecera);
        return nuevacabecera;
    }


    Nodo *auxiliar = getcabecerave();
    //recorrer hasta el final
    while (auxiliar->getAbajo() != nullptr) {
        auxiliar = auxiliar -> getAbajo();
    }


    auxiliar->setAbajo(nuevacabecera);
    nuevacabecera->setArriba(auxiliar);

    return nuevacabecera;



}

//buscar si existe o no existe la cabecera
Nodo *Matriz_Disperza::cabecerahorizontal(int valor) {//busque pais

    if (estavacia()) {//se verifica si la matriz esta vacia
        return nullptr;
    }
    Nodo *auxiliar = getcabeceraHo();

    while (auxiliar->getSiguiente() != nullptr) {
        if (auxiliar->getValor() == valor) return auxiliar;
        auxiliar = auxiliar->getSiguiente();
    }
    return nullptr;
}//retorna todo el contenido de la cabecera, en si es recorreer la matriz

Nodo *Matriz_Disperza::cabececarvertical(int valor) {//busque empresas

    if (estavacia()) {
        return nullptr;
    }

    Nodo *auxiliar = getcabecerave();

    while (auxiliar!=nullptr) {
        if (auxiliar->getValor() == valor)return auxiliar;

        auxiliar = auxiliar->getAbajo();
    }
    return nullptr;




}


bool Matriz_Disperza::estavacia() {
    return this->cabeceraHo == nullptr;
}

//se crea un usuario
// el usuario tiene asociado un departamento y una empresa
// se deben buscar el depa y la empresa y si no existe crearlas.





