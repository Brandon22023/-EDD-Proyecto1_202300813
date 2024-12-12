//
// Created by Marro on 09/12/2024.
//
#include <fstream>
#include <iostream>
#include <string>
#include "Matriz Disperza/Matriz_Disperza.h"

using namespace std;

#include <float.h>

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


    Nodo *cabeceraHorizontal_ = nullptr;
    Nodo *cabeceraVertical_ = nullptr;

    Nodo *usuarioNuevo = new Nodo(valor);

    if (estavacia()) {
        //no es el mismo nodo asi que no hay problemas
        cabeceraHorizontal_= insertarCabeceraHorizontal(cabecera_horizontal);
        cabeceraVertical_ = insertarCabeceraVertical(cabecera_vertical);

        insertarALfinal(usuarioNuevo, cabeceraHorizontal_, cabeceraVertical_);

        return;
    }

    cabeceraHorizontal_ = cabecerahorizontal(cabecera_horizontal);
    cabeceraVertical_ = cabeceravertical(cabecera_vertical);

    if (cabeceraHorizontal_ == nullptr && cabeceraVertical_ == nullptr) {
        cabeceraHorizontal_ = insertarCabeceraHorizontal(cabecera_horizontal);
        cabeceraVertical_ = insertarCabeceraVertical(cabecera_vertical);

        insertarALfinal(usuarioNuevo, cabeceraHorizontal_, cabeceraVertical_);

        return;
    }


    if (cabeceraHorizontal_ == nullptr) {
        cabeceraHorizontal_ = insertarCabeceraHorizontal(cabecera_horizontal);

        insertarALfinal(usuarioNuevo, cabeceraHorizontal_, cabeceraVertical_);
        return;
    }

    if (cabeceraVertical_ == nullptr) {
        cabeceraVertical_ = insertarCabeceraVertical(cabecera_vertical);

        insertarALfinal(usuarioNuevo, cabeceraHorizontal_, cabeceraVertical_);

        return;

    }


    Nodo *auxiliarH = cabeceraHorizontal_->getAbajo();
    Nodo *usercabV;
    bool abajo;

    while (auxiliarH != nullptr) {
        usercabV = enCabeceraVertical(auxiliarH);
        abajo = masabajo(usercabV, cabecera_vertical);

        if (!abajo)break;

        auxiliarH = auxiliarH -> getAbajo();
    }

    if (abajo) {
        insertarAlFinalHorizontal(usuarioNuevo, cabeceraHorizontal_);
    }else {
        insertarAlMedioHorizontal(usuarioNuevo, auxiliarH);
    }

    Nodo *auxiliarV = cabeceraVertical_->getSiguiente();
    Nodo *usercabH;
    bool siguiente= false;

    while (auxiliarV != nullptr) {
        usercabH = enCabeceraHorizontal(auxiliarV);
        siguiente = masderecha(usercabH, cabecera_horizontal);

        if (!siguiente)break;

        auxiliarV = auxiliarV -> getSiguiente();
    }

    if (siguiente) {
        insertarAlFinalVertical(usuarioNuevo, cabeceraVertical_);
    }else{
        insertarAlMedioVertical(usuarioNuevo, auxiliarV);
    }
}

void Matriz_Disperza::insertarALfinal(Nodo *valor, Nodo *cabeceraHorizontal, Nodo *cabeceraVertical) {

    insertarAlFinalHorizontal(valor, cabeceraHorizontal);
    insertarAlFinalVertical(valor, cabeceraVertical);
}
Nodo *Matriz_Disperza::insertarCabeceraHorizontal(int valor) {
    Nodo *nuevacabecera = new Nodo(valor);

    if (this->getcabeceraHo() == nullptr) {
        this->setcabeceraHo(nuevacabecera);
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

    if (this->getcabecerave() == nullptr) {
        this->setcabecerave(nuevacabecera);
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

void Matriz_Disperza::insertarAlFinalHorizontal(Nodo *valor, Nodo *cabeceraHorizontal) {

    Nodo *auxiliar = cabeceraHorizontal;

    while (auxiliar->getAbajo() != nullptr) {
        auxiliar = auxiliar -> getAbajo();
    }

    auxiliar->setAbajo(valor);
    valor->setArriba(auxiliar);
}

void Matriz_Disperza::insertarAlFinalVertical(Nodo *valor, Nodo *cabeceraVertical) {

    Nodo *auxiliar = cabeceraVertical;

    while (auxiliar->getSiguiente() != nullptr) {
        auxiliar = auxiliar -> getSiguiente();
    }

    auxiliar->setSiguiente(valor);
    valor->setPrevio(auxiliar);



}
void Matriz_Disperza::insertarAlMedioHorizontal(Nodo *valor, Nodo *HORIZONTAL) {

    HORIZONTAL->getArriba()->setAbajo(valor);
    valor ->setAbajo(HORIZONTAL);
    valor->setArriba(HORIZONTAL->getArriba());
    HORIZONTAL->setArriba(valor);
}


void Matriz_Disperza::insertarAlMedioVertical(Nodo *valor, Nodo *VERTICAL) {
    VERTICAL->getPrevio()->setSiguiente(valor);
    valor ->setSiguiente(VERTICAL);
    valor->setPrevio(VERTICAL->getPrevio());
    VERTICAL->setPrevio(valor);
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

Nodo *Matriz_Disperza::cabeceravertical(int valor) {//busque empresas

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


Nodo *Matriz_Disperza::enCabeceraHorizontal(Nodo *NODE) {

    Nodo *auxiliar = NODE;

    while(auxiliar->getArriba() != nullptr) {
        auxiliar = auxiliar->getArriba();
    }

    return auxiliar;

}

Nodo *Matriz_Disperza::enCabeceraVertical(Nodo *NODE) {

    Nodo *auxiliar = NODE;

    while (auxiliar->getPrevio() != nullptr) {
        auxiliar = auxiliar->getPrevio();
    }

    return auxiliar;

}

bool Matriz_Disperza::masderecha(Nodo *cabeH, int cabecera_horizontal) {

    Nodo *auxiliar = cabeH;

    while (auxiliar  != nullptr) {

        if (auxiliar->getValor() == cabecera_horizontal) return true;
        auxiliar = auxiliar->getSiguiente();
    }

    return false; //si retona falso es porque no lo encontre y esta más a la izquierda

}

bool Matriz_Disperza::masabajo(Nodo *cabeV, int cabecera_vertical) {
    Nodo *auxiliar = cabeV;

    while (auxiliar != nullptr) {

        if (auxiliar->getValor() == cabecera_vertical) return true;
        auxiliar = auxiliar->getAbajo();
    }

    return false; //la cabecera esta mas arriba
}




bool Matriz_Disperza::estavacia() {
    return this->cabeceraHo == nullptr;
}








void Matriz_Disperza::graficarMatrizDisperza() {
    const string nombreArchivo = "Reporte_matriz_disperza.dot";
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para graficar." << endl;
        return;
    }

    archivo << "digraph G {\n";
    archivo << "    rankdir=LR;\n"; // Dirección de izquierda a derecha
    archivo << "    node [shape=box, fontcolor=black];\n"; // Definir el estilo de los nodos en blanco y negro

    // Subgráfico para las cabeceras horizontales (departamentos)
    archivo << "    { rank=same;\n"; // Asegura que todas las cabeceras horizontales estén en el mismo nivel
    Nodo* actualCabeceraHo = cabeceraHo;
    while (actualCabeceraHo != nullptr) {
        archivo << "    \"CabH_" << actualCabeceraHo->getValor()
                << "\" [label=\"Dept: " << actualCabeceraHo->getValor() << "\"];\n";
        actualCabeceraHo = actualCabeceraHo->getSiguiente();
    }
    archivo << "    }\n\n";

    // Subgráfico para las cabeceras verticales (empresas)
    Nodo* actualCabeceraVe = cabecerave;
    while (actualCabeceraVe != nullptr) {
        archivo << "    \"CabV_" << actualCabeceraVe->getValor()
                << "\" [label=\"Emp: " << actualCabeceraVe->getValor() << "\"];\n";
        actualCabeceraVe = actualCabeceraVe->getAbajo();
    }

    // Recorrido de la matriz y generación de nodos de usuario y conexiones
    actualCabeceraHo = cabeceraHo;
    while (actualCabeceraHo != nullptr) {
        Nodo* actual = actualCabeceraHo->getAbajo(); // Primer nodo en la columna actual

        while (actual != nullptr) {
            // Crear nodo de usuario
            archivo << "    \"Nodo_" << actual->getValor()
                    << "\" [label=\"Usuario: " << actual->getValor() << "\"];\n";

            // Conectar nodo con cabecera horizontal
            archivo << "    \"CabH_" << actualCabeceraHo->getValor() << "\" -> "
                    << "\"Nodo_" << actual->getValor() << "\" [dir=none];\n";

            // Conectar nodo con cabecera vertical
            Nodo* cabeceraVertical = cabecerave;
            while (cabeceraVertical != nullptr) {
                // Si el nodo está en la columna correspondiente de esta cabecera vertical
                if (actual->getValor() == cabeceraVertical->getValor()) {
                    archivo << "    \"CabV_" << cabeceraVertical->getValor() << "\" -> "
                            << "\"Nodo_" << actual->getValor() << "\" [dir=none];\n";
                    break; // Ya que la cabecera vertical correspondiente fue encontrada
                }
                cabeceraVertical = cabeceraVertical->getAbajo();
            }

            // Conexión con otros nodos (hacia la derecha)
            if (actual->getSiguiente() != nullptr) {
                archivo << "    \"Nodo_" << actual->getValor()
                        << "\" -> \"Nodo_" << actual->getSiguiente()->getValor() << "\" [dir=both];\n";
            }

            // Conexión con otros nodos (hacia abajo)
            if (actual->getAbajo() != nullptr) {
                archivo << "    \"Nodo_" << actual->getValor()
                        << "\" -> \"Nodo_" << actual->getAbajo()->getValor() << "\" [dir=both];\n";
            }

            actual = actual->getAbajo(); // Avanza al siguiente nodo en la columna
        }

        actualCabeceraHo = actualCabeceraHo->getSiguiente(); // Avanza a la siguiente cabecera horizontal
    }

    archivo << "}";
    archivo.close();

    cout << "Archivo DOT generado correctamente: " << nombreArchivo << endl;
}






//se crea un usuario
// el usuario tiene asociado un departamento y una empresa
// se deben buscar el depa y la empresa y si no existe crearlas.





