//
// Created by Marro on 14/12/2024.
//

#ifndef ELEMENTOAVL_H
#define ELEMENTOAVL_H
#include <string>
using namespace std;
class ElementoAVL {
private:
    long long valor;           // Entero original
    string nombreActivo;
    string descripcion; // String adicional
    int tiempoRentar;
    string user;
    string ID;

public:
    ElementoAVL(long long valor, string nombreActivo="", string descripcion = "", int tiempoRentar= 0, string user = "", string ID="") {
        this->valor = valor;
        this->nombreActivo = nombreActivo;
        this->descripcion = descripcion;
        this->tiempoRentar = tiempoRentar;
        this->user = user;
        this->ID = ID;
    }

    // Getters
    long long getValor() {
        return valor;
    }

    string &getDescripcion(){
        return descripcion;
    }
    string getNombreActivo(){
        return nombreActivo;
    }
    int getTiempoRentar(){
        return tiempoRentar;
    }
    string getUser(){
        return user;
    }
    string getID(){
        return ID;
    }

    // Setters
    void setValor(long long valor) {
        this->valor = valor;
    }

    void setnombreActivo(string &nombreActivo) {
        this->nombreActivo = nombreActivo;
    }

    void setDescripcion(string &descripcion) {
        this->descripcion = descripcion;
    }

    void setTiempoRentar(int tiempoRentar) {
        this->tiempoRentar = tiempoRentar;
    }

    void setUser(string &user) {
        this->user = user;
    }

    void setID(string &ID) {
        this->ID = ID;
    }
};

#endif //ELEMENTOAVL_H
