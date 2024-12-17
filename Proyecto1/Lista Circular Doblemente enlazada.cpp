//
// Created by Marro on 16/12/2024.
//

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// Nodo de la lista circular doblemente enlazada
class NodoTransaccion {
public:
    string idTransaccion;      // ID único de la transacción
    string idActivo;           // ID del activo rentado
    string usuario;            // Usuario que realizó la renta
    string departamento;       // Departamento del usuario
    string empresa;            // Empresa del usuario
    string fecha;              // Fecha de la transacción
    int tiempoRentar;          // Tiempo de renta (en días)

    NodoTransaccion* siguiente;
    NodoTransaccion* anterior;

    NodoTransaccion(string idTransaccion, string idActivo, string usuario,
                     string departamento, string empresa, string fecha, int tiempoRentar)
        : idTransaccion(idTransaccion), idActivo(idActivo), usuario(usuario),
          departamento(departamento), empresa(empresa), fecha(fecha), tiempoRentar(tiempoRentar) {
        siguiente = anterior = nullptr;
    }
};

// Lista Circular Doblemente Enlazada
class ListaCircularDoble {
private:
    NodoTransaccion* cabeza;

public:
    ListaCircularDoble() {
        cabeza = nullptr;
    }

    // Método para agregar una nueva transacción
    void agregarTransaccion(string idTransaccion, string idActivo, string usuario,
                             string departamento, string empresa, string fecha, int tiempoRentar) {
        NodoTransaccion* nuevo = new NodoTransaccion(idTransaccion, idActivo, usuario,
                                                     departamento, empresa, fecha, tiempoRentar);
        if (cabeza == nullptr) {
            // Si la lista está vacía, el primer nodo es el mismo en cabeza y cola
            cabeza = nuevo;
            cabeza->siguiente = cabeza;
            cabeza->anterior = cabeza;
        } else {
            // Insertar el nodo al final de la lista
            NodoTransaccion* ultimo = cabeza->anterior;
            ultimo->siguiente = nuevo;
            nuevo->anterior = ultimo;
            nuevo->siguiente = cabeza;
            cabeza->anterior = nuevo;
        }
    }

    // Mostrar las transacciones
    void mostrarTransacciones() {
        if (cabeza == nullptr) {
            cout << "No hay transacciones." << endl;
            return;
        }

        NodoTransaccion* actual = cabeza;
        do {
            cout << "ID Transacción: " << actual->idTransaccion << endl;
            cout << "ID Activo: " << actual->idActivo << endl;
            cout << "Usuario: " << actual->usuario << endl;
            cout << "Departamento: " << actual->departamento << endl;
            cout << "Empresa: " << actual->empresa << endl;
            cout << "Fecha: " << actual->fecha << endl;
            cout << "Tiempo de Renta (días): " << actual->tiempoRentar << endl;
            cout << "--------------------------" << endl;
            actual = actual->siguiente;
        } while (actual != cabeza);
    }

    // Método para eliminar una transacción por su ID
    void eliminarTransaccion(string idTransaccion) {
        if (cabeza == nullptr) {
            cout << "No hay transacciones para eliminar." << endl;
            return;
        }

        NodoTransaccion* actual = cabeza;
        do {
            if (actual->idTransaccion == idTransaccion) {
                if (actual == cabeza && actual->siguiente == cabeza) {
                    // Si es el único nodo en la lista
                    delete actual;
                    cabeza = nullptr;
                    return;
                }

                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;

                // Sí estamos eliminando el primer nodo (cabeza)
                if (actual == cabeza) {
                    cabeza = actual->siguiente;
                }

                delete actual;
                cout << "Transacción " << idTransaccion << " eliminada." << endl;
                return;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);

        cout << "Transacción no encontrada." << endl;
    }
    void graficarTransacciones() {
        if (cabeza == nullptr) {
            cout << "No hay transacciones para graficar." << endl;
            return;
        }

        string nombreArchivoDOT = "reporte_transacciones.dot";
        string nombreArchivoSVG = "reporte_transacciones.svg";

        ofstream archivo(nombreArchivoDOT); // Crear el archivo .dot
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo para escribir." << endl;
            return;
        }

        // Inicia el archivo DOT
        archivo << "digraph G {\n";
        archivo << "    node [shape=box, color=black, style=filled, fillcolor=gray, fontcolor=white];\n";
        archivo << "    graph [splines=polyline, nodesep=0.5];\n";
        archivo << "    rankdir=LR;\n";
        archivo << "    label=\"Transacciones\";\n";
        archivo << "    labelloc=\"t\";\n";
        archivo << "    fontsize=20;\n";
        archivo << "    fontcolor=red;\n";

        NodoTransaccion* actual = cabeza;
        int contador = 0;

        // Generar nodos con saltos de línea en sus etiquetas
        do {
            archivo << "    nodo" << contador << " [label=\""
                    << "ID: " << actual->idTransaccion << "\\n"
                    << "Activo: " << actual->idActivo << "\\n"
                    << "Usuario: " << actual->usuario << "\\n"
                    << "Depto/Emp: " << actual->departamento << " / " << actual->empresa << "\\n"
                    << "Fecha: " << actual->fecha << "\\n"
                    << "Tiempo: " << actual->tiempoRentar << " días\"];\n";
            actual = actual->siguiente;
            contador++;
        } while (actual != cabeza);

        // Generar conexiones entre nodos (siguiente y anterior)
        for (int i = 0; i < contador; i++) {
            int siguiente = (i + 1) % contador; // Nodo siguiente circularmente
            int anterior = (i - 1 + contador) % contador; // Nodo anterior circularmente

            archivo << "    nodo" << i << " -> nodo" << siguiente << " [color=orange];\n";
            archivo << "    nodo" << i << " -> nodo" << anterior << " [color=orange, dir=back];\n";
        }

        archivo << "}\n";
        archivo.close();

        // Generar el archivo SVG usando Graphviz
        string comandoDot = "dot -Tsvg " + nombreArchivoDOT + " -o " + nombreArchivoSVG;
        int resultadoDot = system(comandoDot.c_str());

        if (resultadoDot == 0) {
            cout << "Archivo SVG generado exitosamente: " << nombreArchivoSVG << endl;

            // Abrir el archivo SVG en el navegador predeterminado
            string comandoAbrir = "start " + nombreArchivoSVG; // Para Windows
            system(comandoAbrir.c_str());
        } else {
            cout << "Error al generar el archivo SVG." << endl;
        }
    }

    // Método para ordenar transacciones de manera ascendente
    void ordenarAscendente() {
        if (cabeza == nullptr || cabeza->siguiente == cabeza) {
            cout << "No hay suficientes transacciones para ordenar." << endl;
            return;
        }

        bool swapped;
        NodoTransaccion* actual;
        NodoTransaccion* ultimo = nullptr;

        do {
            swapped = false;
            actual = cabeza;

            // Recorre la lista comparando elementos adyacentes
            do {
                NodoTransaccion* siguiente = actual->siguiente;
                if (siguiente != cabeza && actual->idTransaccion.compare(siguiente->idTransaccion) > 0) {
                    // Intercambia los valores de los nodos
                    swapNodos(actual, siguiente);
                    swapped = true;
                }
                actual = actual->siguiente;
            } while (actual->siguiente != cabeza && actual->siguiente != ultimo);

            ultimo = actual; // Marca el último nodo ya ordenado
        } while (swapped);

        cout << "Transacciones ordenadas de manera ascendente." << endl;
    }

    // Método para ordenar transacciones de manera descendente
    void ordenarDescendente() {
        if (cabeza == nullptr || cabeza->siguiente == cabeza) {
            cout << "No hay suficientes transacciones para ordenar." << endl;
            return;
        }

        bool swapped;
        NodoTransaccion* actual;
        NodoTransaccion* ultimo = nullptr;

        do {
            swapped = false;
            actual = cabeza;

            // Recorre la lista comparando elementos adyacentes
            do {
                NodoTransaccion* siguiente = actual->siguiente;
                if (siguiente != cabeza && actual->idTransaccion.compare(siguiente->idTransaccion) < 0) {
                    // Intercambia los valores de los nodos
                    swapNodos(actual, siguiente);
                    swapped = true;
                }
                actual = actual->siguiente;
            } while (actual->siguiente != cabeza && actual->siguiente != ultimo);

            ultimo = actual; // Marca el último nodo ya ordenado
        } while (swapped);

        cout << "Transacciones ordenadas de manera descendente." << endl;
    }

    // Método auxiliar para intercambiar los valores de dos nodos
    void swapNodos(NodoTransaccion* a, NodoTransaccion* b) {
        // Intercambia toda la información del nodo, no las conexiones
        swap(a->idTransaccion, b->idTransaccion);
        swap(a->idActivo, b->idActivo);
        swap(a->usuario, b->usuario);
        swap(a->departamento, b->departamento);
        swap(a->empresa, b->empresa);
        swap(a->fecha, b->fecha);
        swap(a->tiempoRentar, b->tiempoRentar);
    }
    // Mostrar los idActivo de las transacciones asociadas a un usuario
    void mostrarActivosPorUsuario(string usuarioActual) {
        if (cabeza == nullptr) {
            cout << "No hay transacciones." << endl;
            return;
        }

        NodoTransaccion* actual = cabeza;
        bool encontrados = false;
        do {
            if (actual->usuario == usuarioActual) {
                cout << "ID: " << actual->idActivo << endl;
                encontrados = true;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);

        if (!encontrados) {
            cout << "No se encontraron activos para el usuario " << usuarioActual << "." << endl;
        }
    }
};


