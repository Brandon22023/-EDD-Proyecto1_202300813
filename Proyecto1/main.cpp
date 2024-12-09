#include <iostream>
#include <string>
#include <limits>

using namespace std;


class Menus{
public:
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
            cout << "Has iniciado sesion como Usuario..." << endl;
            cout << "" << endl;
            Menu_usuario();
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
                    cout << "opcion 2" << endl;
                    break;
                }

                case 3:{
                    cout << "opcion 3" << endl;
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

        cout << "Usuario creado exitosamente con los datos: " << endl;
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
                case 1:{
                    cout << "============================ Agregar Activo ============================" << endl;
                    cout << ">> Ingrese Nombre:" << endl;
                    cout << ">> Ingrese Descripcion:" << endl;
                    break;
                }
                case 2:{
                    cout << "============================ Eliminar Activo ============================" << endl;
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
};




int main() {
    Menus t_menus;
    t_menus.Menu_sesion();


    //cout << "probando cosas" << endl;

    return 0;
}

