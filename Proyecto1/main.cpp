#include <fstream>
#include <iostream>
#include <string>

#include "AVL/AVL.h"
#include "Matriz Disperza/Matriz_Disperza.h"
#include <cstdlib> // Para system()
#include <random>
#include <ctime>
#include "AVL/ELEMENTOAVL.h"
#include "pa los activos.cpp"

using namespace std;
AVL*arbolAVL = new AVL();
ListaUsuariosAVL listaUsuarios;//no encontre otra opcion para guardar los activos de los usuarios
class Menus{
public:
    Matriz_Disperza matriz;
    string usuarioActual;  // Variable para almacenar el usuario actual

    void Menu_sesion() {
        int opc=0;

        do {
            cout << "============================ Renta de Activos ============================" << endl;
            cout << "============================ 1. Iniciar sesion ============================ " << endl;
            cout << "============================ 2. Salir del programa ============================ " << endl;
            cout << "Ingrese una opcion" << endl;
            cin >> opc;

            switch(opc) {
                case 1:{
                    login();
                    break;
                }
                case 2:{
                    cout << "Has seleccionado la opcion de Salir del programa" << endl;
                    exit(0);
                }
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
            }

        }while (opc !=2);

    }
    void login() {
        string nombre, contrasena, departamento, empresa;
        cout << "============================ Renta de Activos ============================" << endl;
        cout << "============================       Login      ============================ " << endl;
        cout << "Ingrese el nombre del usuario: ";
        cin >> nombre;

        cout << "Ingrese la contraseña: ";
        cin >> contrasena;

        cout << "Ingrese el departamento: ";
        cin >> departamento;

        cout << "Ingrese la empresa: ";
        cin >> empresa;

        if (contrasena == "admin" and nombre == "admin" and departamento == "admin" and empresa == "admin") {
            cout << "Has iniciado sesion como Administrador..." << endl;
            cout << "" << endl;
            Menu_administrador();

        }else {
            Nodo *cabeceraHorizontal = matriz.getcabeceraHo();
            while (cabeceraHorizontal != nullptr) { // mientras la cabecera horizontal no este vacia
                Nodo *usuarioNodo = cabeceraHorizontal->getAbajo(); // Primer nodo en la columna de esta cabecera horizontal
                while (usuarioNodo != nullptr) { // Recorremos la columna actual
                    if (usuarioNodo->getValor() == nombre &&
                        usuarioNodo->getcontra() != nullptr &&
                        usuarioNodo->getcontra()->getValor() == contrasena) {
                        cout << "Has iniciado sesion como Usuario..." << endl;
                        usuarioActual = nombre;  // Guardamos el nombre del usuario autenticado
                        cout << "" << endl;
                        Menu_usuario();//metodo de usuario
                        return;
                        }
                    usuarioNodo = usuarioNodo->getAbajo(); // Siguiente nodo en la columna
                }
                cabeceraHorizontal = cabeceraHorizontal->getSiguiente(); // Siguiente cabecera horizontal
            }
            cout << "Error: Los datos son erroneos." << endl;
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
                    cout << "opcion 5" << endl;
                    break;
                }

                case 6:{
                    cout << "opcion 6" << endl;
                    break;
                }

                case 7:{
                    cout << "opcion 7" << endl;
                    break;
                }

                case 8:{
                    cout << "opcion 8" << endl;
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

        cout << "Ingrese la contraseña: ";
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


                        ElementoAVL elemento1(IDACII, nameActivo, Descripcion, tiempoRenta, usuarioActual);
                        // Agregar el activo a la lista de activos del usuario
                        listaUsuarios.agregarActivo(usuarioActual, elemento1);
                    } catch (const std::exception &e) {
                        cout << "Ocurrió un error: " << e.what() << endl;
                    } catch (...) {
                        cout << "Ocurrió un error inesperado." << endl;
                    }

                    break;
                }
                case 2: {
                    cout << "============================ Eliminar Activo ============================" << endl;

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
                            cout << "ID: " << activoActual->activo.getValor()
                                 << ", Nombre: " << activoActual->activo.getNombreActivo()
                                 << ", Descripción: " << activoActual->activo.getDescripcion()
                                 << ", Tiempo de Renta: " << activoActual->activo.getTiempoRentar() << " días"
                                 << endl;
                            activoActual = activoActual->siguiente;
                        }
                    }

                    break;
                }

                case 3:{
                    cout << "============================ Modificar Activo ============================" << endl;
                    cout << ">> Ingrese ID de Activo a Modificar: :" << endl;
                    break;
                }

                case 4:{
                    cout << "============================ Catalogo Activos   ============================" << endl;
                    cout << "" << endl;
                    cout << "" << endl;
                    do{
                        cout << ">> 1. Rentar Activo" << endl;
                        cout << ">> 2. Regresar a Menu" << endl;
                        cout << ">> Ingrese una opcion" << endl;
                        cin >> opcion2;
                        if (opcion2 == 1) {
                            cout << ">> Ingrese ID de Activo a Rentar: :" << endl;
                            cout << ">> Ingrese dias a rentar:" << endl;
                        } else if (opcion2 == 2) {
                            Menu_usuario();

                        }else {
                            cout << "Opcion no valida" << endl;
                        }
                    }while(opcion2 != 2);

                    break;

                }

                case 5:{
                    cout << "============================ Activos Rentados   ============================" << endl;
                    cout << "" << endl;
                    cout << "" << endl;
                    do{
                        cout << ">> 1. Registrar Devolucon" << endl;
                        cout << ">> 2. Regresar a Menu" << endl;
                        cout << ">> Ingrese una opcion" << endl;
                        cin >> opcion2;
                        if (opcion2 == 1) {
                            cout << ">> Ingrese ID de Activo a Devolver: :" << endl;

                        } else if (opcion2 == 2) {
                            Menu_usuario();

                        }else {
                            cout << "Opcion no valida" << endl;
                        }
                    }while(opcion2 != 2);

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
};



int main() {
    Menus t_menus;
    //cout<<"el codigo generado es: " << t_menus.ID_RANDOM()<<endl;
    t_menus.Menu_sesion();
    //Matriz_Disperza *matriz = new Matriz_Disperza();
    //matriz->insertarvalor("juan","kiche","contaduria");
    //matriz->insertarvalor("Diego","Palin","arquitecto");
    //matriz->insertarvalor(8, 1, 0);
    //matriz->insertarvalor(10, 2, 1);
    //matriz->insertarvalor(15, 1, 1);
    //matriz->graficarMatrizDisperza();

    /*AVL*arbolAVL = new AVL();
    arbolAVL->insertar(10);
    arbolAVL->insertar(5);
    arbolAVL->insertar(4);
    arbolAVL->insertar(1);
    arbolAVL->insertar(3);
    arbolAVL->insertar(0);
    arbolAVL->insertar(6);
    arbolAVL->insertar(12);
    arbolAVL->insertar(14);
    arbolAVL->insertar(11);*/

    /*arbolAVL->hakai(10);
    arbolAVL->hakai(3);
    arbolAVL->hakai(12);
    arbolAVL->hakai(6);*/








    //string path = "/Users/Marro/Documents/yon/VACACIONES DICIEMBRE 2024/LAB ESTRUCTURA DE DATOS/-EDD-Proyecto1_202300813/Proyecto1/";
    //string path = "";





    //cout << "probando cosas" << endl;
    return 0;
}























