cmake_minimum_required(VERSION 3.30)
project(Proyecto1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Proyecto1 main.cpp
        "Matriz Disperza/Nodo.h"
        Nodo.cpp
        "Matriz Disperza/Matriz_Disperza.h"
        Matriz_Disperza.cpp
        AVL/NodoAVL.h
        NodoAVL.cpp
        AVL/AVL.h
        AVL.cpp
        AVL/ELEMENTOAVL.h
        "pa los activos.cpp"
        "Lista Circular Doblemente enlazada.cpp"
)
