#include <iostream>
#include <string>
#include <limits>

using namespace std;

class menu_sesion{
private:
    string user;
    string pass;
public:
    void Menu() {
        cout << "============================ Renta de Activos ============================" << endl;
        cout << "============================ Iniciar sesion ============================ " << endl;
        cout << "Ingrese una opcion" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Menu Administrador" << endl;
        cout << "elija una de las opciones mostradas" << endl;
        cin >> user;
        cout << "la opcion seleccionada fue " << user << "" << endl;
    }


};

class crear_usuario{
private:
    string opc;

public:
    void Menu_crear_usuario() {
        string nombre, contrasena, departamento, empresa;
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
        cout << "Nombre: " << nombre << ", Departamento: " << departamento << ", Empresa: " << empresa << endl;
    }
};

class Menu_Administrador{

public:
    void Menu() {
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
            cout << "|| 9. Salir" << endl;
            cout << "** Ingrese una opcion" << endl;
            cin >> opc;
            cout << "la opcion seleccionada fue " << opc << "" << endl;
            cout << " " << endl;

            switch(opc) {
                case 1:{
                    cout << "------------Has seleccionado la opcion de Registrar Usuario------------" << endl;
                    crear_usuario Creador_usuario1;
                    Creador_usuario1.Menu_crear_usuario();
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
                    cout << "opcion 9" << endl;
                    break;
                }

                default:
                    cout << "Opción no válida, intente de nuevo." << endl;
            }

        }while (opc !=9);

    }


};
int main() {
    //menu_sesion menu;
    //menu.Menu();

    Menu_Administrador menu_administrador;
    menu_administrador.Menu();
    //cout << "probando cosas" << endl;

    return 0;
}

