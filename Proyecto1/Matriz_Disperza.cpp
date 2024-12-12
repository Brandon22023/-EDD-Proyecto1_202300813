//
// Created by Marro on 09/12/2024.
//
#include <fstream>
#include <iostream>
#include <string>
#include "Matriz Disperza/Matriz_Disperza.h"

using namespace std;
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
void Matriz_Disperza::insertarvalor(string valor, string contra, string cabecera_horizontal, string cabecera_vertical) {


    Nodo *cabeceraHorizontal_ = nullptr;
    Nodo *cabeceraVertical_ = nullptr;


    Nodo *usuarioNuevo = new Nodo(valor);
    Nodo *contraNodo = new Nodo(contra);  // Nodo para la contraseña
    usuarioNuevo->setcontra(contraNodo);

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
Nodo *Matriz_Disperza::insertarCabeceraHorizontal(string valor) {
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

Nodo *Matriz_Disperza::insertarCabeceraVertical(string valor) {
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
Nodo *Matriz_Disperza::cabecerahorizontal(string valor) {//busque pais

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

Nodo *Matriz_Disperza::cabeceravertical(string valor) {//busque empresas

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

bool Matriz_Disperza::masderecha(Nodo *cabeH, string cabecera_horizontal) {

    Nodo *auxiliar = cabeH;

    while (auxiliar  != nullptr) {

        if (auxiliar->getValor() == cabecera_horizontal) return true;
        auxiliar = auxiliar->getSiguiente();
    }

    return false; //si retona falso es porque no lo encontré y esta más a la izquierda

}
bool Matriz_Disperza::masabajo(Nodo *cabeV, string cabecera_vertical) {
    Nodo *auxiliar = cabeV;

    while (auxiliar != nullptr) {

        if (auxiliar->getValor() == cabecera_vertical) return true;
        auxiliar = auxiliar->getAbajo();
    }

    return false; //la cabecera está más arriba
}

bool Matriz_Disperza::estavacia() {
    return this->cabeceraHo == nullptr;
}


//para buscar a los usuarios existentes
Nodo *Matriz_Disperza::buscarUsuario(string valor) {
    Nodo *cabeceraHorizontal = getcabeceraHo();
    Nodo *cabeceraVertical = getcabecerave();

    while (cabeceraHorizontal != nullptr) {
        Nodo* auxiliar = cabeceraHorizontal->getAbajo();
        while (auxiliar != nullptr) {
            if (auxiliar->getValor() == valor) {
                return auxiliar;
            }
            auxiliar = auxiliar->getAbajo();
        }
        cabeceraHorizontal = cabeceraHorizontal->getSiguiente();
    }

    while (cabeceraVertical != nullptr) {
        Nodo* auxiliar = cabeceraVertical->getSiguiente();
        while (auxiliar != nullptr) {
            if (auxiliar->getValor() == valor) {
                return auxiliar;
            }
            auxiliar = auxiliar->getSiguiente();
        }
        cabeceraVertical = cabeceraVertical->getAbajo();
    }

    return nullptr; // Si no hay usuario en la matriz

}

void Matriz_Disperza::insertarAdelante(Nodo *nuevoUsuario, Nodo *usuarioExistente) {
    Nodo* adelante = usuarioExistente->getadelante();
    usuarioExistente->setadelante(nuevoUsuario);
    nuevoUsuario->setAtras(usuarioExistente);
    if (adelante != nullptr) {
        nuevoUsuario->setadelante(adelante);
        adelante->setAtras(nuevoUsuario);
    }
}

void Matriz_Disperza::insertarAtras(Nodo *nuevoUsuario, Nodo *usuarioExistente) {
    Nodo* atras = usuarioExistente->getAtras();
    usuarioExistente->setAtras(nuevoUsuario);
    nuevoUsuario->setadelante(usuarioExistente);

    if (atras != nullptr) {
        nuevoUsuario->setAtras(atras);
        atras->setadelante(nuevoUsuario);
    }
}


void Matriz_Disperza::graficarMatrizDisperza() {
    const std::string nombreArchivo = "Reporte_matriz_disperza.dot";
    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    archivo << "digraph MatrizDispersa {\n";
    archivo << "    rankdir=TB;\n";
    archivo << "    node [shape=box];\n";

    // Graficar cabeceras horizontales (cabeceraHo)
    Nodo* cabeceraH = cabeceraHo;
    while (cabeceraH != nullptr) {
        archivo << "    \"" << cabeceraH->getValor() << "\" [label=\"cabho: " << cabeceraH->getValor() << "\", style=filled, color=lightblue];\n";
        cabeceraH = cabeceraH->getSiguiente();
    }

    // Graficar cabeceras verticales (cabecerave)
    Nodo* cabeceraV = cabecerave;
    while (cabeceraV != nullptr) {
        archivo << "    \"" << cabeceraV->getValor() << "\" [label=\"cabve: " << cabeceraV->getValor() << "\", style=filled, color=lightgreen];\n";
        cabeceraV = cabeceraV->getAbajo();
    }

    // Conexiones entre cabeceras horizontales (cabeceraHo)
    cabeceraH = cabeceraHo;
    while (cabeceraH != nullptr && cabeceraH->getSiguiente() != nullptr) {
        archivo << "    \"" << cabeceraH->getValor() << "\" -> \"" << cabeceraH->getSiguiente()->getValor() << "\" [dir=both];\n";
        cabeceraH = cabeceraH->getSiguiente();
    }

    // Conexiones entre cabeceras verticales (cabecerave)
    cabeceraV = cabecerave;
    while (cabeceraV != nullptr && cabeceraV->getAbajo() != nullptr) {
        archivo << "    \"" << cabeceraV->getValor() << "\" -> \"" << cabeceraV->getAbajo()->getValor() << "\" [dir=both];\n";
        cabeceraV = cabeceraV->getAbajo();
    }

    // Recorrer nodos en la matriz dispersa desde la perspectiva de cada cabecera horizontal
    cabeceraH = cabeceraHo;
    while (cabeceraH != nullptr) {
        Nodo* nodoActual = cabeceraH->getAbajo();
        while (nodoActual != nullptr) {
            archivo << "    \"" << nodoActual->getValor() << "\" [label=\"valor: " << nodoActual->getValor() << "\", style=filled, color=yellow];\n";

            // Conexión al siguiente nodo en la fila
            if (nodoActual->getSiguiente() != nullptr) {
                archivo << "    \"" << nodoActual->getValor() << "\" -> \"" << nodoActual->getSiguiente()->getValor() << "\" [dir=both];\n";
            }

            // Conexión al nodo debajo en la columna
            if (nodoActual->getAbajo() != nullptr) {
                archivo << "    \"" << nodoActual->getValor() << "\" -> \"" << nodoActual->getAbajo()->getValor() << "\" [dir=both];\n";
            }

            nodoActual = nodoActual->getAbajo();
        }
        cabeceraH = cabeceraH->getSiguiente();
    }

    // Recorrer nodos en la matriz dispersa desde la perspectiva de cada cabecera vertical
    cabeceraV = cabecerave;
    while (cabeceraV != nullptr) {
        Nodo* nodoActual = cabeceraV->getSiguiente();
        while (nodoActual != nullptr) {
            // Ya están definidos los nodos y conexiones en el recorrido horizontal
            nodoActual = nodoActual->getSiguiente();
        }
        cabeceraV = cabeceraV->getAbajo();
    }

    archivo << "}";
    archivo.close();

    std::cout << "Archivo DOT generado: " << nombreArchivo << std::endl;
}


















