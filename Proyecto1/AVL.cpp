//
// Created by Marro on 13/12/2024.
//
#include <iostream>
#include "AVL/AVL.h"
#include "AVL/ELEMENTOAVL.h"
#include "pa los activos.cpp"
#include <string>


using namespace std;



using namespace std;
AVL::AVL() {
    this->raiz = nullptr;
}

NodoAVL* AVL::getRaiz() {
    return raiz;
}

void AVL::setRaiz(NodoAVL *raiz) {
    this->raiz = raiz;
}

//--------------------------------------------

void AVL::insertar(ElementoAVL elemento) {
    NodoAVL* nodo = new NodoAVL(elemento);
    insertar(nodo, this->raiz);
}


void AVL::insertar(NodoAVL *valor, NodoAVL *&raiz) {

    if (raiz== nullptr) {
        raiz = valor;
        raiz->setFactorEquilibrio(factorDeEquilibrio(raiz));
        return;
    }
    if (valor->getElemento().getValor() < raiz->getElemento().getValor()) {
        insertar(valor, raiz->getIzquierda());
    }else {
        insertar(valor, raiz->getDerecha());
    }
    raiz->setFactorEquilibrio(factorDeEquilibrio(raiz));

    if (raiz->getFactorEquilibrio() < -1) {
        if (raiz->getIzquierda()->getFactorEquilibrio() > 0) {
            rotacionIzquierdaDerecha(raiz);

            return;

        }
        rotacionDerecha(raiz);
        return;
    }

    if (raiz->getFactorEquilibrio() > 1) {
        if (raiz->getDerecha()->getFactorEquilibrio() < 0) {
            rotacionDerechaIzquierda(raiz);
            return;
        }
        rotacionIzquierda(raiz);

    }
}

void AVL::hakai(long long valor) {
    hakai(valor, this->raiz);
}

void AVL::hakai(long long valor, NodoAVL *&raiz) {

    if (raiz == nullptr) {
        cout<<"El valor: " + to_string(valor) + " no se encuentra en el arbol" <<endl;
        return;
    }
    if (valor == raiz->getElemento().getValor()) {

        //primer caso "ser hoja"
        if (esHoja(raiz)) {
            raiz = nullptr;
            return;
        }
        //segundo caso "no ser hoja"

        if (raiz->getIzquierda() == nullptr) {
            raiz = raiz->getDerecha();
            return;
        }

        //otro caso
        if (raiz->getDerecha() == nullptr) {
            raiz = raiz->getIzquierda();
            return;
        }

        //tercer caso cuando ninguno es nulo, es buscar a la derecha del hijo izquierda
        NodoAVL *NODODERECHA = andateDerecha(raiz->getIzquierda());
        raiz->getElemento().setValor(NODODERECHA->getElemento().getValor());
        hakai(NODODERECHA->getElemento().getValor(), raiz->getIzquierda());

        valor = raiz->getElemento().getValor();

    }
    if (valor < raiz ->getElemento().getValor()) {
        hakai(valor, raiz->getIzquierda());

    }
    if (valor > raiz ->getElemento().getValor()) {
        hakai(valor, raiz->getDerecha());

    }

    raiz->setFactorEquilibrio(factorDeEquilibrio(raiz));

    if (raiz->getFactorEquilibrio() < -1) {
        if (raiz->getIzquierda()->getFactorEquilibrio() > 0) {
            rotacionIzquierdaDerecha(raiz);
            return;

        }
        rotacionDerecha(raiz);
        return;
    }

    if (raiz->getFactorEquilibrio() > 1) {
        if (raiz->getDerecha()->getFactorEquilibrio() < 0) {
            rotacionDerechaIzquierda(raiz);
            return;
        }
        rotacionIzquierda(raiz);
        return;

    }



}


void AVL::rotacionDerecha(NodoAVL *&NODO) {

    NodoAVL *auxiliar = NODO->getIzquierda();

    NODO->getIzquierda() = auxiliar->getDerecha();
    auxiliar->getDerecha() = NODO;
    NODO = auxiliar;

    NODO->setFactorEquilibrio(factorDeEquilibrio(NODO));
    NODO->getDerecha()->setFactorEquilibrio(factorDeEquilibrio(NODO->getDerecha()));

    if (NODO->getIzquierda() == nullptr) return;
    NODO->getIzquierda()->setFactorEquilibrio(factorDeEquilibrio(NODO->getIzquierda()));

}
void AVL::rotacionIzquierda(NodoAVL *&NODO) {

    NodoAVL *auxiliar = NODO->getDerecha();

    NODO->getDerecha() = auxiliar->getIzquierda();
    auxiliar->getIzquierda() = NODO;
    NODO = auxiliar;

    NODO->setFactorEquilibrio(factorDeEquilibrio(NODO));
    NODO->getIzquierda()->setFactorEquilibrio(factorDeEquilibrio(NODO->getIzquierda()));

    if (NODO->getDerecha() == nullptr) return;
    NODO->getDerecha()->setFactorEquilibrio(factorDeEquilibrio(NODO->getDerecha()));

}
void AVL::rotacionDerechaIzquierda(NodoAVL *&NODO) {
    rotacionDerecha(NODO->getDerecha());
    rotacionIzquierda(NODO);

}

void AVL::rotacionIzquierdaDerecha(NodoAVL *&NODO) {
    rotacionIzquierda(NODO->getIzquierda());
    rotacionDerecha(NODO);

}

NodoAVL *AVL::andateDerecha(NodoAVL *&NODO) {
    if (NODO->getDerecha() == nullptr) {
        return NODO;
    }
    return andateDerecha(NODO->getDerecha());
}




int AVL::alturaMaxima(NodoAVL *nodo) {

    if (nodo == nullptr)return 0;

    int hijoIzquierdo= alturaMaxima(nodo->getIzquierda());
    int hijoDerecho=alturaMaxima(nodo->getDerecha());


    return hijoIzquierdo > hijoDerecho ? hijoIzquierdo + 1 : hijoDerecho +1;
}

int AVL::factorDeEquilibrio(NodoAVL *nodo) {
    return alturaMaxima(nodo->getDerecha())-alturaMaxima(nodo->getIzquierda());
}

bool AVL::esHoja(NodoAVL *nodo) {
    return nodo->getIzquierda() == nullptr && nodo->getDerecha() == nullptr;
}
//---------------------------------
//recorrr dichoa AVL
// Método para recorrer el árbol en orden (inorden)



void AVL::recorrerInorden(NodoAVL *nodo) {
    if (nodo == nullptr) {
        return;
    }

    // Primero recorremos el subárbol izquierdo
    recorrerInorden(nodo->getIzquierda());

    // Luego procesamos el nodo raíz
    cout << "ID: "<<nodo->getElemento().getID() << " "<< endl;
    cout <<"nombreActivo: "<< nodo->getElemento().getNombreActivo() << " "<< endl;
    cout << "descripcion del activo:  "<<nodo->getElemento().getDescripcion()<< " "<< endl;
    cout <<"tiempo: "<< nodo->getElemento().getTiempoRentar()<< " "<< endl;
    cout <<"usuario: "<<nodo->getElemento().getUser() << " "<<endl;
    // Finalmente recorremos el subárbol derecho
    recorrerInorden(nodo->getDerecha());
}

// Método público que llama a la versión recursiva
void AVL::recorrerInorden() {
    recorrerInorden(this->raiz);
}


//-----------------------------------------
std::string AVL::imprimir() {
    int count = -1;
    std::string dot = "digraph G {\n\tnode [shape = circle];\n\t" ;

    dot += imprimir(this->raiz, count);

    dot += "\n}";

    return dot;

}
//--------------------------------------------------
std::string AVL::imprimir(NodoAVL *raiz, int &count) {
    count++;

    int correntCount = count;

    string dot = "n" + to_string(correntCount) + "[label=\"" + raiz->getElemento().getNombreActivo() + "\"];\n\t";

    if (esHoja(raiz)) {
        return dot;
    }

    if (raiz->getIzquierda() != nullptr) {
        int nextNodo = count + 1;
        dot += "n" + to_string(correntCount) + " -> n" + to_string(nextNodo) + ";\n\t" + imprimir(raiz->getIzquierda(), count);
    }

    if (raiz->getDerecha() != nullptr) {
        int nextNodo = count + 1;
        dot += "n" + to_string(correntCount) + " -> n" + to_string(nextNodo) + ";\n\t" + imprimir(raiz->getDerecha(), count);
    }

    return dot;
}


































