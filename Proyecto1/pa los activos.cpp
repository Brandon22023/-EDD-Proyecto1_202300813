//
// Created by Marro on 15/12/2024.
//

#include <fstream>

#include <string>

#include "AVL/AVL.h"



using namespace std;

class NodoActivo {
public:
    ElementoAVL activo;  // Aquí almacenamos el activo
    NodoActivo* siguiente;

    NodoActivo(ElementoAVL& elem) : activo(elem), siguiente(nullptr) {}
};

class NodoUsuario {
public:
    string nombreUsuario;
    NodoActivo* cabezaActivos;  // Lista de activos de este usuario
    NodoUsuario* siguiente;

    NodoUsuario(string& nombre)
        : nombreUsuario(nombre), cabezaActivos(nullptr), siguiente(nullptr) {}
};

class ListaUsuariosAVL {
private:
    NodoUsuario* cabeza;

public:
    ListaUsuariosAVL() : cabeza(nullptr) {}

    // Devuelve el primer nodo de la lista de usuarios
    NodoUsuario* obtenerPrimero() {
        return cabeza;
    }

    // Busca un usuario por nombre
    NodoUsuario* buscarUsuario(const string& nombre) {
        NodoUsuario* actual = cabeza;
        while (actual != nullptr) {
            if (actual->nombreUsuario == nombre) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    // Busca un usuario por ID de uno de sus activos
    NodoUsuario* buscarUsuarioPorID(const int ID) {
        NodoUsuario* actual = cabeza;
        while (actual != nullptr) {
            NodoActivo* activo = actual->cabezaActivos;
            while (activo != nullptr) {
                if (activo->activo.getValor() == ID) {  // Suponiendo que ElementoAVL tiene un campo ID
                    return actual;
                }
                activo = activo->siguiente;
            }
            actual = actual->siguiente;
        }
        return nullptr;  // No se encontró el usuario con ese ID
    }

    // Agrega un nuevo usuario con su lista de activos
    void agregarUsuario(string& nombre) {
        if (buscarUsuario(nombre) == nullptr) {
            NodoUsuario* nuevo = new NodoUsuario(nombre);
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        }
    }

    // Agrega un activo a la lista de un usuario
    void agregarActivo(string& nombreUsuario, ElementoAVL& activo) {
        NodoUsuario* nodo = buscarUsuario(nombreUsuario);
        if (nodo != nullptr) {
            NodoActivo* nuevoActivo = new NodoActivo(activo);
            nuevoActivo->siguiente = nodo->cabezaActivos;
            nodo->cabezaActivos = nuevoActivo;
        } else {
            // Si no existe el usuario, creamos uno nuevo
            agregarUsuario(nombreUsuario);
            NodoUsuario* nodo = buscarUsuario(nombreUsuario);
            NodoActivo* nuevoActivo = new NodoActivo(activo);
            nuevoActivo->siguiente = nodo->cabezaActivos;
            nodo->cabezaActivos = nuevoActivo;
        }
    }

    bool actualizarEstadoActivo(const string& ID, bool nuevoEstado) {
        NodoUsuario* usuarioActual = cabeza;
        while (usuarioActual != nullptr) {
            NodoActivo* activoActual = usuarioActual->cabezaActivos;
            while (activoActual != nullptr) {
                if (activoActual->activo.getID() == ID) {  // Buscar activo por ID
                    activoActual->activo.setRentar(nuevoEstado);  // Actualizar estado
                    return true;  // Retornar éxito
                }
                activoActual = activoActual->siguiente;
            }
            usuarioActual = usuarioActual->siguiente;
        }
        return false;  // No se encontró el activo con el ID proporcionado
    }
    NodoActivo* buscarActivoPorID(const string& ID) {
        NodoUsuario* usuarioActual = cabeza; // Comenzamos con el primer usuario

        // Recorremos la lista de usuarios
        while (usuarioActual != nullptr) {
            NodoActivo* activoActual = usuarioActual->cabezaActivos; // Recorremos los activos del usuario

            // Recorremos la lista de activos del usuario
            while (activoActual != nullptr) {
                if (activoActual->activo.getID() == ID) {  // Si el ID del activo coincide con el proporcionado
                    return activoActual;  // Devolvemos el nodo que contiene el activo
                }
                activoActual = activoActual->siguiente;  // Avanzamos al siguiente activo
            }
            usuarioActual = usuarioActual->siguiente;  // Avanzamos al siguiente usuario
        }
        return nullptr;  // Si no se encuentra el activo con el ID, retornamos nullptr
    }

};

