#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "AVL/AVL.h"
#include "Matriz Disperza/Matriz_Disperza.h"
#include <cstdlib> // Para system()
#include <random>
#include <ctime>
#include "AVL/ELEMENTOAVL.h"
#include "pa los activos.cpp"
#include "Lista Circular Doblemente enlazada.cpp"

using namespace std;
AVL*arbolAVL = new AVL();
ListaUsuariosAVL listaUsuarios;//no encontre otra opcion para guardar los activos de los usuarios
ListaCircularDoble listaTransacciones;//pa transacciones

class Menus{
public:
    Matriz_Disperza matriz;
    string usuarioActual;//para autenticar el usuario
    string Empresa_global; //recordar quitarlo solo son pruebas
    string departamento_global;

    void Menu_sesion() {
        int opc=0;

        do {
            try {
                cout << "============================ Renta de Activos ============================" << endl;
                cout << "============================ 1. Iniciar sesion ============================ " << endl;
                cout << "============================ 2. Salir del programa ============================ " << endl;
                cout << "Ingrese una opcion: ";

                // Habilitar excepciones en cin
                cin.exceptions(ios::failbit | ios::badbit);

                cin >> opc;

                // Validación de opción fuera de rango
                if (opc < 1 || opc > 2) {
                    throw out_of_range("Opcion fuera de rango. Intente de nuevo.");
                }

                switch (opc) {
                    case 1: {
                        login();
                        break;
                    }
                    case 2: {
                        cout << "Has seleccionado la opcion de Salir del programa." << endl;
                        cout << "Saliendo..." << endl;
                        exit(0);
                        return; // Salida limpia
                    }
                    default: ;
                }

            } catch (const exception &e) {
                cout << "Ocurrió un error: " << e.what() << endl;
            } catch (...) {
                cout << "Ocurrió un error inesperado." << endl;
            }
        } while (true);

    }
    void login() {

        try {
            string nombre, contrasena, departamento, empresa;
            cout << "============================ Renta de Activos ============================\n";
            cout << "============================       Login      ============================ \n";
            cout << "Ingrese el nombre del usuario: ";
            cin.ignore(); // Para limpiar el buffer antes de getline si se usan espacios
            getline(cin, nombre);

            cout << "Ingrese la contrasena: ";
            getline(cin, contrasena);

            cout << "Ingrese el departamento: ";
            getline(cin, departamento);
            departamento_global = departamento;

            cout << "Ingrese la empresa: ";
            getline(cin, empresa);
            Empresa_global = empresa;

            if (contrasena == "admin" && nombre == "admin" && departamento == "admin" && empresa == "admin") {
                cout << "Has iniciado sesion como Administrador..." << endl;
                Menu_administrador();
            } else {
                Nodo* cabeceraHorizontal = matriz.getcabeceraHo();
                bool usuarioEncontrado = false;

                while (cabeceraHorizontal != nullptr) { // mientras la cabecera horizontal no este vacia
                    Nodo* usuarioNodo = cabeceraHorizontal->getAbajo(); // Primer nodo en la columna de esta cabecera horizontal
                    while (usuarioNodo != nullptr) { // Recorremos la columna actual
                        if (usuarioNodo->getValor() == nombre &&
                            usuarioNodo->getcontra() != nullptr &&
                            usuarioNodo->getcontra()->getValor() == contrasena) {
                            cout << "Has iniciado sesion como Usuario..." << endl;
                            usuarioActual = nombre;  // Guardamos el nombre del usuario autenticado
                            Menu_usuario();
                            usuarioEncontrado = true;
                            return;
                        }
                        usuarioNodo = usuarioNodo->getAbajo(); // Siguiente nodo en la columna
                    }
                    cabeceraHorizontal = cabeceraHorizontal->getSiguiente(); // Siguiente cabecera horizontal
                }

                if (!usuarioEncontrado) {
                    throw runtime_error("Error: Los datos son erroneos.");
                }
            }
        } catch (const exception &e) {
            cout << "Ocurrió un error: " << e.what() << endl;
        } catch (...) {
            cout << "Ocurrió un error inesperado." << endl;
        }
    }
    void Menu_administrador() {
        int opc= 0;

        do {
            cout << "============================ Menu Administrador ============================" << endl;
            cout << "|| 1. Registrar Usuario" << endl;
            cout << "|| 2. Reporte de Matriz Dispersa" << endl;
            cout << "|| 3. Reporte Activos Disponibles de un Departamento" << endl;
            cout << "|| 4. Reporte Activos Disponibles de una Empresa" << endl;
            cout << "|| 5. Reporte Transacciones" << endl;
            cout << "|| 6. Reporte Activos de un Usuario" << endl;
            cout << "|| 7. Activos rentados por un Usuario" << endl;
            cout << "|| 8. Ordenar Transacciones" << endl;
            cout << "|| 9. cerrar sesion" << endl;
            cout << "** Ingrese una opcion" << endl;
            cin >> opc;
            cout << "la opcion seleccionada fue " << opc << "" << endl;
            cout << " " << endl;

            switch(opc) {
                case 1:{
                    cout << "------------Has seleccionado la opcion de Registrar Usuario------------" << endl;
                    registrar_usuario();
                    break;
                }
                case 2:{
                    matriz.graficarMatrizDisperza();
                    break;
                }

                case 3:{
                    paraimprimir();
                    break;
                }

                case 4:{
                    cout << "opcion 4" << endl;
                    break;
                }

                case 5:{
                    cout << "Haciendo el reporte... espere por favor..." << endl;
                    listaTransacciones.graficarTransacciones();
                    break;
                }

                case 6: {

                    try {
                        // Crear un nuevo árbol AVL (reinicia los haciendo nuevo arbol vacio)
                        if (arbolAVL != nullptr) {
                            delete arbolAVL; // Liberar memoria del árbol anterior
                        }
                        arbolAVL = new AVL(); // Crear nuevo árbol vacío
                        string Usuario_buscar_ahora;
                        cout << "Reporte Activos de un Usuario" << endl;
                        cout << "Ingrese el nombre del usuario: ";
                        cin >> Usuario_buscar_ahora;
                        cout << "Buscando al usuario...generando arbol...." << endl;
                        NodoUsuario* usuario = listaUsuarios.buscarUsuario(Usuario_buscar_ahora);

                        // Verificar si el usuario existe
                        if (usuario != nullptr) {
                            // Recorrer la lista de activos del usuario
                            NodoActivo* activoActual = usuario->cabezaActivos;
                            while (activoActual != nullptr) {
                                ElementoAVL elemento1(activoActual->activo.getValor(), activoActual->activo.getNombreActivo(), activoActual->activo.getDescripcion(), activoActual->activo.getTiempoRentar(), usuarioActual, activoActual->activo.getID(), activoActual->activo.getRentar());
                                arbolAVL->insertar(elemento1);

                                activoActual = activoActual->siguiente; // Avanzar al siguiente activo
                            }
                        } else {
                            cout << "Usuario no encontrado." << endl;
                        }
                        paraimprimir();

                    }catch (const exception &e) {
                        cout << "Ocurrió un error: " << e.what() << endl;
                    } catch (...) {
                        cout << "Ocurrió un error inesperado." << endl;
                    }
                    break;
                }

                case 7:{
                    cout << "opcion 7" << endl;
                    break;
                }

                case 8: {
                    int opcionOrdenar = 0;
                    cout << "------------------------------------Ordenar Transacciones----------------------------------" << endl;
                    cout << "Elija la manera en la cual quiere ordenar las transacciones:" << endl;
                    cout << "1. Ascendente" << endl;
                    cout << "2. Descendente" << endl;

                    // Validación de entrada
                    while (true) {
                        cout << "Ingrese su opción (1 o 2): ";
                        if (!(cin >> opcionOrdenar)) {
                            cerr << "Error: Entrada inválida. Por favor ingrese un número." << endl;
                            cin.clear(); // Limpiar el estado de error de cin
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer
                        } else if (opcionOrdenar < 1 || opcionOrdenar > 2) {
                            cerr << "Error: Opción fuera de rango. Elija 1 o 2." << endl;
                        } else {
                            break; // Entrada válida
                        }
                    }

                    // Procesar la opción elegida
                    if (opcionOrdenar == 1) {
                        cout << "Ordenando las transacciones en orden Ascendente..." << endl;
                        listaTransacciones.ordenarAscendente();
                        listaTransacciones.graficarTransacciones();
                        // Aquí llama a la función de ordenar Ascendente
                    } else if (opcionOrdenar == 2) {
                        cout << "Ordenando las transacciones en orden Descendente..." << endl;
                        listaTransacciones.ordenarDescendente();
                        listaTransacciones.graficarTransacciones();
                        // Aquí llama a la función de ordenar Descendente
                    }
                    break;
                }

                case 9:{
                    cout << "saliendo del modo aministrador...regresando al inicio del programa..." << endl;
                    cout << " " << endl;
                    Menu_sesion();
                    break;
                }

                default:
                    cout << "Opción no válida, intente de nuevo." << endl;
            }

        }while (opc !=9);

    }
    void registrar_usuario() {
        string nombre, contrasena, departamento, empresa;
        cout << "============================ Administrador ============================" << endl;
        cout << "============================ Crear Usuario ============================ " << endl;
        cout << "Ingrese el nombre del usuario: ";
        cin >> nombre;

        cout << "Ingrese la contrasena: ";
        cin >> contrasena;

        cout << "Ingrese el departamento: ";
        cin >> departamento;

        cout << "Ingrese la empresa: ";
        cin >> empresa;

        // Verificar si el usuario ya existe con los mismos datos (nombre, departamento, empresa)
        Nodo* usuarioExistente = matriz.buscarUsuario(nombre, departamento, empresa);

        if (usuarioExistente != nullptr) {
            char opcion;
            cout << "El usuario ya existe. ¿Desea registrar al nuevo usuario adelante o atrás del usuario existente?" << endl;
            cout << "Ingrese 'a' para registrarlo adelante  o 'f' para registrarlo atrás: ";
            cin >> opcion;

            // Crear el nuevo nodo de usuario y su contraseña
            Nodo *usuarioNuevo = new Nodo(nombre);
            Nodo *contraNodo = new Nodo(contrasena);
            usuarioNuevo->setcontra(contraNodo);

            if (opcion == 'a') {
                // Insertar el nuevo usuario adelante
                matriz.insertarAdelante(usuarioNuevo, usuarioExistente);
            } else if (opcion == 'f') {
                // Insertar el nuevo usuario atrás
                matriz.insertarAtras(usuarioNuevo, usuarioExistente);
            } else {
                cout << "Opción no válida. El usuario no se registrará." << endl;
            }
        } else {
            // Si el usuario no existe, proceder con el registro normal
            matriz.insertarvalor(nombre, contrasena, departamento, empresa);
            cout << "Usuario creado exitosamente " << endl;
        }
    }
    void Menu_usuario() {
        int opcion= 0;
        int opcion2= 0;

        do {
            cout << "============================ Nombre de Usuario ============================" << endl;
            cout << "|| 1. Agregar Activo" << endl;
            cout << "|| 2. Eliminar Activo" << endl;
            cout << "|| 3. Modificar Activo" << endl;
            cout << "|| 4. Rentar Activo" << endl;
            cout << "|| 5. Activos Rentados" << endl;
            cout << "|| 6. Mis Activos Rentados" << endl;
            cout << "|| 7. Cerrar sesion" << endl;
            cout << "** Ingrese una opcion" << endl;
            cin >> opcion;
            cout << "la opcion seleccionada fue " << opcion << "" << endl;
            cout << " " << endl;

            switch(opcion) {
                case 1: {
                    try {
                        bool rentar=false;
                        string ID, nameActivo, Descripcion;
                        long long IDACII;
                        int tiempoRenta;

                        // Generar IDs
                        ID = ID_RANDOM();
                        IDACII = ID_RANDOMACII(ID);

                        // Solicitar datos al usuario
                        cout << "============================ Agregar Activo ============================" << endl;
                        cout << ">> Ingrese Nombre:" << endl;
                        cin.ignore(); // Para limpiar el buffer antes de getline si se usan espacios
                        getline(cin, nameActivo);

                        cout << ">> Ingrese Descripcion:" << endl;
                        getline(cin, Descripcion);

                        cout << ">> Ingrese el tiempo de Renta:" << endl;
                        cin >> tiempoRenta;

                        // Mostrar datos
                        cout << "ID del Activo: " << ID << ", su IDACII es: " << IDACII
                             << ", su Nombre es: " << nameActivo
                             << ", su Descripcion es: " << Descripcion
                             << ", su Tiempo de Renta (dias): " << tiempoRenta << ", su Usuario es: " << usuarioActual << endl;


                        ElementoAVL elemento1(IDACII, nameActivo, Descripcion, tiempoRenta, usuarioActual, ID, rentar);
                        // Agregar el activo a la lista de activos del usuario
                        listaUsuarios.agregarActivo(usuarioActual, elemento1);
                    } catch (const exception &e) {
                        cout << "Ocurrio un error: " << e.what() << endl;
                    } catch (...) {
                        cout << "Ocurrio un error inesperado." << endl;
                    }

                    break;
                }
                case 2: {

                    cout << "============================ Eliminar Activo ============================" << endl;

                    try {
                        long long ID_ELIMINAR_;
                        string ID_letrasNumeros;

                        // Crear un nuevo árbol AVL (reinicia los haciendo nuevo arbol vacio)
                        if (arbolAVL != nullptr) {
                            delete arbolAVL; // Liberar memoria del árbol anterior
                        }
                        arbolAVL = new AVL(); // Crear nuevo árbol vacío

                        // Primero, buscamos al usuario actual en la lista de usuarios
                        NodoUsuario* usuario = listaUsuarios.buscarUsuario(usuarioActual);

                        if (usuario == nullptr) {
                            cout << "No se ha encontrado al usuario " << usuarioActual << "." << endl;
                            break;  // Si no se encuentra el usuario, no hay activos que mostrar
                        }

                        // Si el usuario tiene activos, los mostramos
                        NodoActivo* activoActual = usuario->cabezaActivos;

                        if (activoActual == nullptr) {
                            cout << "No hay activos registrados para el usuario " << usuarioActual << "." << endl;
                        } else {
                            cout << "Estos son los activos del usuario " << usuarioActual << ":" << endl;

                            while (activoActual != nullptr) {
                                // Mostrar los detalles de cada activo
                                cout << "ID: " << activoActual->activo.getID()
                                     << ", Nombre: " << activoActual->activo.getNombreActivo()
                                     << ", Descripcion: " << activoActual->activo.getDescripcion()
                                     << ", Tiempo de Renta: " << activoActual->activo.getTiempoRentar() << " dias"
                                     << endl;
                                ElementoAVL elemento1(activoActual->activo.getValor(), activoActual->activo.getNombreActivo(), activoActual->activo.getDescripcion(), activoActual->activo.getTiempoRentar(), usuarioActual, activoActual->activo.getID(), activoActual->activo.getRentar());
                                arbolAVL->insertar(elemento1);
                                activoActual = activoActual->siguiente;
                            }
                        }
                        paraimprimir();

                        // Solicitar el ID del activo a eliminar
                        cout << "Ingrese el ID del activo a eliminar: ";

                        cin>>ID_letrasNumeros;
                        ID_ELIMINAR_ = ID_RANDOMACII(ID_letrasNumeros);

                        // Buscamos el activo por ID antes de eliminarlo
                        NodoUsuario* usuarioEliminar = listaUsuarios.buscarUsuario(usuarioActual);
                        if (usuarioEliminar != nullptr) {
                            NodoActivo* activoEliminar = usuarioEliminar->cabezaActivos;
                            bool encontrado = false;

                            while (activoEliminar != nullptr) {
                                if (activoEliminar->activo.getValor() == ID_ELIMINAR_) {
                                    // Imprimir los detalles del activo a eliminar
                                    cout << "Detalles del activo a eliminar:" << endl;
                                    cout << "ID: " << activoEliminar->activo.getID()
                                         << ", Nombre: " << activoEliminar->activo.getNombreActivo()
                                         << ", Descripcion: " << activoEliminar->activo.getDescripcion()
                                         << ", Tiempo de Renta: " << activoEliminar->activo.getTiempoRentar() << " dias"
                                         << endl;
                                    encontrado = true;
                                    break;
                                }
                                activoEliminar = activoEliminar->siguiente;
                            }

                            if (!encontrado) {
                                cout << "No se encontro un activo con el ID proporcionado." << endl;
                                break;
                            }
                        } else {
                            cout << "Usuario no encontrado." << endl;
                            break;
                        }


                        arbolAVL->hakai(ID_ELIMINAR_);
                        paraimprimir();
                        stringstream buffer;
                        streambuf* oldCoutBuffer = cout.rdbuf(buffer.rdbuf()); // Redirigir cout

                        // Recorrer el árbol AVL para capturar los valores en buffer
                        arbolAVL->recorrerInorden();

                        cout.rdbuf(oldCoutBuffer); // Restaurar cout a su estado original

                        // Leer la salida capturada del stringstream y comparar con la lista de usuarios
                        string linea;

                        NodoUsuario* nodoUsuario = listaUsuarios.obtenerPrimero(); // Método que obtiene la cabeza de la lista

                        while (nodoUsuario != nullptr) {
                            NodoActivo* activo = nodoUsuario->cabezaActivos;
                            NodoActivo* previo = nullptr;

                            while (activo != nullptr) {
                                bool encontrado = false;

                                // Leer el stringstream línea por línea y buscar el ID
                                buffer.clear();
                                buffer.seekg(0, ios::beg); // Reiniciar el stream para leer desde el inicio

                                while (getline(buffer, linea)) {
                                    if (linea.find("ID:") != string::npos) {
                                        string idCapturado;
                                        stringstream(linea.substr(4)) >> idCapturado;

                                        if (idCapturado == activo->activo.getID()) {
                                            encontrado = true;
                                            break;
                                        }
                                    }
                                }

                                if (!encontrado) {
                                    // Eliminar el activo si su ID no está en los ID
                                    if (previo == nullptr) {
                                        nodoUsuario->cabezaActivos = activo->siguiente;
                                    } else {
                                        previo->siguiente = activo->siguiente;
                                    }
                                    delete activo;
                                    activo = (previo == nullptr) ? nodoUsuario->cabezaActivos : previo->siguiente;
                                } else {
                                    previo = activo;
                                    activo = activo->siguiente;
                                }
                            }

                            nodoUsuario = nodoUsuario->siguiente;
                        }


                    }catch (const exception &e) {
                        cout << "Ocurrio un error: " << e.what() << endl;
                    } catch (...) {
                        cout << "Ocurrio un error inesperado." << endl;
                    }
                    break;
                }
                case 3:{
                    try {

                        string ID_letrasNum, descripcion_nueva;
                        long long ID_buscador;

                        cout << "============================ Modificar Activo ============================" << endl;
                        //-----crearnuevo arbol
                        // Crear un nuevo árbol AVL (reiniciar valores)
                        if (arbolAVL != nullptr) {
                            delete arbolAVL; // Liberar memoria del árbol anterior
                        }
                        arbolAVL = new AVL(); // Crear un nuevo árbol vacío

                        //------crearnuevo arbol

                        // Primero, buscamos al usuario actual en la lista de usuarios
                        NodoUsuario* usuario = listaUsuarios.buscarUsuario(usuarioActual);

                        if (usuario == nullptr) {
                            cout << "No se ha encontrado al usuario " << usuarioActual << "." << endl;
                            break;  // Si no se encuentra el usuario, no hay activos que mostrar
                        }

                        // Si el usuario tiene activos, los mostramos
                        NodoActivo* activoActual = usuario->cabezaActivos;

                        if (activoActual == nullptr) {
                            cout << "No hay activos registrados para el usuario " << usuarioActual << "." << endl;
                        } else {
                            while (activoActual != nullptr) {
                                // Mostrar los detalles de cada activo
                                cout << "ID: " << activoActual->activo.getID()
                                     << ", Nombre: " << activoActual->activo.getNombreActivo()
                                     << ", Descripcion: " << activoActual->activo.getDescripcion()
                                     << ", Tiempo de Renta: " << activoActual->activo.getTiempoRentar() << " dias"
                                     << endl;
                                ElementoAVL elemento1(activoActual->activo.getValor(), activoActual->activo.getNombreActivo(), activoActual->activo.getDescripcion(), activoActual->activo.getTiempoRentar(), usuarioActual, activoActual->activo.getID(), activoActual->activo.getRentar());
                                arbolAVL->insertar(elemento1);
                                activoActual = activoActual->siguiente;
                            }
                        }
                        //---------------------------------------------------------------------------
                        cout << ">> Ingrese ID de Activo a Modificar: :" << endl;
                        cin >> ID_letrasNum;
                        ID_buscador = ID_RANDOMACII(ID_letrasNum);
                        cout << ">> Ingrese la nueva descripcion: :" << endl;
                        cin.ignore(); // Para limpiar el buffer antes de getline si se usan espacios
                        getline(cin, descripcion_nueva);

                        NodoAVL* nodoModificado = arbolAVL->buscarYModificarDescripcion(ID_buscador, descripcion_nueva);

                        if (nodoModificado != nullptr) {
                            cout << "Activo Modificado:" << endl;
                            cout << "ID: " << nodoModificado->getElemento().getID() << endl;
                            cout << "Nombre: " << nodoModificado->getElemento().getNombreActivo() << endl;
                            cout << "Descripcion actualizada: " << nodoModificado->getElemento().getDescripcion() << endl;
                            cout << "Tiempo de Renta: " << nodoModificado->getElemento().getTiempoRentar() << " dias" << endl;

                            // Ahora actualizamos la descripción en la lista de usuarios
                            NodoActivo* activoLista = usuario->cabezaActivos;
                            bool encontrado = false;

                            while (activoLista != nullptr) {
                                if (activoLista->activo.getID() == ID_letrasNum) {
                                    // Si encontramos el activo, actualizamos la descripción en la lista de usuarios
                                    activoLista->activo.setDescripcion(nodoModificado->getElemento().getDescripcion());
                                    encontrado = true;
                                    break;
                                }
                                activoLista = activoLista->siguiente;
                            }

                            if (!encontrado) {
                                cout << "No se encontro el activo en la lista de usuarios." << endl;
                            }

                        } else {
                            cout << "No se encontro un nodo con el ID proporcionado en el arbol AVL." << endl;
                        }

                    }catch (const exception &e) {
                        cout << "Ocurrio un error: " << e.what() << endl;
                    } catch (...) {
                        cout << "Ocurrio un error inesperado." << endl;
                    }

                    break;
                }
                case 4:{
                    try {
                        string ID_letrasNum_, usuario_nuevo;
                        long long ID_rentar;
                        string name= usuarioActual;
                        string ID_NOSE;



                        cout << "============================ Catalogo Activos ============================" << endl;
                        //-----crearnuevo arbol
                        // Crear un nuevo árbol AVL (reiniciar valores)
                        if (arbolAVL != nullptr) {
                            delete arbolAVL; // Liberar memoria del árbol anterior
                        }
                        arbolAVL = new AVL(); // Crear un nuevo árbol vacío

                        //------crearnuevo arbol

                        // Imprimir todos los activos de todos los usuarios
                        NodoUsuario* usuarioActual = listaUsuarios.obtenerPrimero();
                        if (usuarioActual == nullptr) {
                            cout << "No hay usuarios registrados." << endl;
                        } else {
                            cout << "Activos disponibles para rentar:" << endl;
                            while (usuarioActual != nullptr) {
                                NodoActivo* activoActual = usuarioActual->cabezaActivos;

                                if (activoActual == nullptr) {
                                    cout << "El usuario " << usuarioActual->nombreUsuario << " no tiene activos." << endl;
                                } else {
                                    while (activoActual != nullptr) {
                                        // Verificar si el activo no está rentado
                                        if (!activoActual->activo.getRentar()) {
                                            // Mostrar los detalles de cada activo que no esté rentado
                                            cout << "ID: " << activoActual->activo.getID()
                                                 << ", Nombre: " << activoActual->activo.getNombreActivo()
                                                 << ", Descripcion: " << activoActual->activo.getDescripcion()
                                                 << ", Tiempo de Renta: " << activoActual->activo.getTiempoRentar() << " dias"
                                                 << endl;
                                            ElementoAVL elemento1(activoActual->activo.getValor(), activoActual->activo.getNombreActivo(), activoActual->activo.getDescripcion(), activoActual->activo.getTiempoRentar(), activoActual->activo.getUser(), activoActual->activo.getID(), activoActual->activo.getRentar());
                                            arbolAVL->insertar(elemento1);
                                        }
                                        activoActual = activoActual->siguiente;
                                    }
                                }

                                usuarioActual = usuarioActual->siguiente;
                            }
                        }

                        // Continuar con la opción para rentar un activo
                        int opcion_2;
                        do {
                            cout << ">> 1. Rentar Activo" << endl;
                            cout << ">> 2. Regresar a Menu" << endl;
                            cout << ">> Ingrese una opcion" << endl;
                            cin >> opcion_2;

                            if (opcion_2 == 1) {
                                cout << ">> Ingrese ID de Activo a Rentar: :" << endl;
                                cin >> ID_letrasNum_;
                                ID_rentar= ID_RANDOMACII(ID_letrasNum_);
                                NodoAVL* nodorentar = arbolAVL->buscarporID(ID_rentar);

                                if (nodorentar != nullptr) {
                                    cout << "Activo a Rentar: " << endl;
                                    cout << "ID: " << nodorentar->getElemento().getID()
                                         << ", Nombre: " << nodorentar->getElemento().getNombreActivo()
                                         << ", Descripcion: " << nodorentar->getElemento().getDescripcion()
                                         << ", Tiempo de Renta: " << nodorentar->getElemento().getTiempoRentar() << " dias"
                                         << endl;

                                    ID_NOSE= nodorentar->getElemento().getID();
                                }

                                cout << ">> Ingrese dias a rentar:" << endl;
                                int diasRenta;
                                cin >> diasRenta;
                                // Actualizar el estado del activo
                                bool actualizado = listaUsuarios.actualizarEstadoActivo(ID_letrasNum_, true);
                                if (actualizado) {
                                    cout << "El activo con ID " << ID_letrasNum_ << " fue rentado exitosamente." << endl;
                                } else {
                                    cout << "No se pudo actualizar el estado del activo. Por favor, verifica el ID." << endl;
                                }

                                string empresa= "";
                                string departamento= "";
                                string ID_transacciones = ID_RANDOM();
                                string Fecha_actual = obtenerFechaActual();
                                listaTransacciones.agregarTransaccion(ID_transacciones,
                                                                      ID_NOSE, name,
                                                                      departamento_global, Empresa_global, Fecha_actual, diasRenta);


                            } else if (opcion_2 == 2) {
                                Menu_usuario();
                            } else {
                                cout << "Opcion no valida" << endl;
                            }
                        } while (opcion_2 != 2);

                    } catch (const exception &e) {
                        cout << "Ocurrió un error: " << e.what() << endl;
                    } catch (...) {
                        cout << "Ocurrió un error inesperado." << endl;
                    }

                    break;

                }
                case 5:{
                    int elegir;
                    string ID_E;
                    cout << "============================ Activos Rentados ============================" << endl;

                    // Redirigir cout para capturar la salida de mostrarActivosPorUsuario
                    stringstream buffer;
                    streambuf* oldCoutBuffer = cout.rdbuf(buffer.rdbuf()); // Redirigir cout

                    // Llamar a la función que muestra los activos por usuario
                    listaTransacciones.mostrarActivosPorUsuario(usuarioActual);

                    // Restaurar cout a su estado original
                    cout.rdbuf(oldCoutBuffer);

                    // Leer la salida capturada del stringstream
                    string linea;
                    NodoUsuario* nodoUsuario = listaUsuarios.obtenerPrimero(); // Método que obtiene la cabeza de la lista

                    // Recorremos la lista de usuarios
                    while (nodoUsuario != nullptr) {
                        NodoActivo* activo = nodoUsuario->cabezaActivos;
                        NodoActivo* previo = nullptr;

                        // Recorremos los activos del usuario
                        while (activo != nullptr) {
                            bool encontrado = false;

                            // Reiniciar el stringstream para leer desde el inicio
                            buffer.clear();
                            buffer.seekg(0, ios::beg);

                            // Leer línea por línea de la salida capturada
                            while (getline(buffer, linea)) {
                                if (linea.find("ID:") != string::npos) {
                                    string idCapturado;
                                    stringstream(linea.substr(4)) >> idCapturado;  // Capturamos el ID después de "ID:"

                                    if (idCapturado == activo->activo.getID()) {
                                        encontrado = true;
                                        break;
                                    }
                                }
                            }

                            if (encontrado) {
                                // Si se encuentra el ID, buscar el activo en la lista usando el ID
                                NodoActivo* activoEncontrado = listaUsuarios.buscarActivoPorID(activo->activo.getID());

                                if (activoEncontrado != nullptr) {
                                    // Imprimir la información del activo encontrado
                                    cout << "Activo encontrado: " << endl;
                                    cout << "ID: " << activoEncontrado->activo.getID() << endl;
                                    cout << "Nombre: " << activoEncontrado->activo.getNombreActivo() << endl;
                                    cout << "Descripcion: " << activoEncontrado->activo.getDescripcion() << endl;
                                    cout << "Tiempo de renta: " << activoEncontrado->activo.getTiempoRentar() << " dias" << endl;
                                    cout << "Usuario: " << activoEncontrado->activo.getUser() << endl;
                                    cout << "Estado de renta: " << (activoEncontrado->activo.getRentar() ? "Rentado" : "Disponible") << endl;
                                }
                            }
                            activo = activo->siguiente;


                        }

                        nodoUsuario = nodoUsuario->siguiente;
                    }



                    cout << "" << endl;

                    do {
                        try {
                            cout << ">> 1. Registrar Devolucion" << endl;
                            cout << ">> 2. Regresar a Menu" << endl;
                            cout << ">> Ingrese una opcion: ";
                            cin >> elegir;

                            // Verificamos si la entrada fue válida (si fue otra opcion que no sea numero)
                            if (cin.fail()) {
                                throw invalid_argument("Opción no válida. Por favor ingrese un número.");
                            }

                            if (elegir == 1) {
                                cout << ">> Ingrese ID de Activo a Devolver: "<<endl;
                                cin >> ID_E;
                                // Actualizar el estado del activo
                                bool actualizado = listaUsuarios.actualizarEstadoActivo(ID_E, false);
                                if (actualizado) {
                                    cout << "El activo con ID " << ID_E << " fue devuelto exitosamente." << endl;
                                } else {
                                    cout << "No se pudo actualizar el estado del activo. Por favor, verifica el ID." << endl;
                                }
                            } else if (elegir == 2) {
                                Menu_usuario();
                            } else {
                                throw invalid_argument("Opción no válida. Por favor ingrese 1 o 2.");
                            }

                        } catch (const exception &e) {
                            cout << "Ocurrió un error: " << e.what() << endl;
                        } catch (...) {
                            cout << "Ocurrió un error inesperado." << endl;
                        }

                    } while (elegir != 2); // Termina cuando se selecciona regresar al menú

                    break;
                }

                case 6:{
                    cout << "============================ Mis Activos Rentados   ============================" << endl;
                    cout << "" << endl;
                    cout << "" << endl;
                    do{
                        cout << ">> Ingresar 1 para regresar al Menu" << endl;
                        cin >> opcion2;
                        if (opcion2 == 1) {
                            cout << ">> Regresando al menu... por favor espere esto puede demorar unos minutos..." << endl;
                            Menu_usuario();
                            cout <<""<< endl;

                        }else {
                            cout << "Opcion no valida" << endl;
                        }
                    }while(opcion2 != 1);

                    break;
                }

                case 7: {
                    cout << "saliendo del menu de usuario...regresando al inicio del programa..." << endl;
                    cout << " " << endl;
                    Menu_sesion();
                    break;
                }

                default:
                    cout << "Opción no válida, intente de nuevo." << endl;
            }

        }while (opcion !=7);

    }
    string ID_RANDOM(int longitud = 15) {
        string codigo;
        mt19937 generador(static_cast<unsigned>(std::time(nullptr)));//se genera dichas semillas
        uniform_int_distribution<> tipoCaracter(0, 2);//se determina el tipo de carácter a generar, 1: letra mayúscula, 2: dígito
        uniform_int_distribution<> letrasMinusculas('a', 'z'); //se generan las letras minúsculas
        uniform_int_distribution<> letrasMayusculas('A', 'Z'); //se generan las letras mayusculas
        uniform_int_distribution<> digitos('0', '9');//se genera numeros
        for (int i = 0; i < longitud; ++i) {
            // Elegimos el tipo de carácter
            int tipo = tipoCaracter(generador);

            // Variable para almacenar el carácter generado
            char nuevoCaracter;
            if (tipo == 0) {
                // Generar una letra minúscula
                nuevoCaracter = static_cast<char>(letrasMinusculas(generador));
            } else if (tipo == 1) {
                // Generar una letra mayúscula
                nuevoCaracter = static_cast<char>(letrasMayusculas(generador));
            } else {
                // Generar un dígito
                nuevoCaracter = static_cast<char>(digitos(generador));
            }
            // Añadimos el carácter generado al string final
            codigo += nuevoCaracter;

        }

        //cout << "Codigo ASCII: " << codigosAscii << endl;
        // Devolvemos el código generado
        return codigo;
    }
    // Función para convertir un ID (string) en un único número entero que representa todos los códigos ASCII concatenados
    long long ID_RANDOMACII(const string& codigo) {
        long long codigosAscii = 0;  // Usamos long para manejar números grandes

        for (char caracter : codigo) {
            // Convertimos cada carácter a su código ASCII y lo añadimos a la variable codigosAscii
            codigosAscii = codigosAscii * 1000 + static_cast<int>(caracter);  // *1000 para evitar que se solapen los números

            // Esto asegura que no haya solapamiento entre los valores ASCII de los caracteres
        }

        return codigosAscii;
    }


    void paraimprimir() {
        ofstream file("arbolAVL.dot");

        if (!file) {
            cout << "Error al crear el archivo" << endl;
        }

        file <<arbolAVL->imprimir();
        file.close();

        string command = "dot -Tsvg arbolAVL.dot -o arbolAVL.svg";

        system(command.c_str());

        command = "start arbolAVL.svg";
        system(command.c_str());
    }

    string obtenerFechaActual() {
        string FechaActual;
        time_t t = time(nullptr);  // Obtener el tiempo actual
        tm* now = localtime(&t);   // Convertir el tiempo a una estructura tm

        // Concatenar los valores para formar la fecha en formato dd/mm/yyyy
        FechaActual = to_string(now->tm_mday) + '/' +
                      to_string(now->tm_mon + 1) + '/' +
                      to_string(now->tm_year + 1900);
        return FechaActual;
    }
};
int main() {
    Menus t_menus;
    t_menus.Menu_sesion();
    return 0;
}























