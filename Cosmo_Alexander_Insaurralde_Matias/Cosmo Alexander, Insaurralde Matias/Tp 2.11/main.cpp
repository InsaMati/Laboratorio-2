#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <windows.h>
#include <ctime>
#include <conio.h>

/*

   Cosas para hacer

   *Intentar Hacer un Menu con flecha.
   *Averiguar como exportar a pdf.
   *Terminar Facturacion.

*/

using namespace std;

/// Define

#define ABAJO 'i'
#define ARRIBA 'k'
#define ENTER 13
#define ESCAPE_KEY 27

/// Prototipos

void gotoxy (int, int);
void Integrantes();
bool LeerOpcion(int);
void Bordes ();
void Datos();
int menu_principal ();

/// Bibliotecas

#include "fecha.h"
#include "persona.h"
#include "empleado.h"
#include "mercaderia.h"'
#include "ProductoJuego.h"
#include "Proveedores.h"
#include "Clientes.h"
#include "venta.h"
#include "Configuracion.h"
#include "consultas.h"
#include "informe.h"

/// Para ubicar el texto o cualquier cosa.

void gotoxy(int x,int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

void EsconderCursor(){

     HANDLE hCon;

     hCon = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_CURSOR_INFO cci;


     cci.dwSize = 2;
     cci.bVisible = false;

     SetConsoleCursorInfo(hCon,&cci);

}

void Integrantes ()
{

    system ("cls");
    gotoxy(66,2);
    cout << "UNIVERSIDAD DE TECNOLOGIA NACIONAL";
    gotoxy(60,4);
    cout << "Integrantes: Insaurralde Matias, Alexander Cosmo.";
    gotoxy (68,6);
    cout << "Gestion Negocio de Videojuegos.";

}

//////////////////////////////////////////////////////////////////////////

void Datos(){

        time_t tiempo;

        struct tm *tmPtr;

        tiempo = time(NULL);
        tmPtr = localtime(&tiempo);

        gotoxy (46,2);
        cout << "DATOS SISTEMA";
        gotoxy (46,3);
        cout << "-------------------------------------------------------------------------";
        gotoxy (46,4);
        cout << "FECHA: ";
        cout << tmPtr->tm_mday << "/" << tmPtr->tm_mon+1 << "/" << tmPtr->tm_year+1900 <<" ";
        gotoxy (46,6);
        cout << "HORA: ";
        cout << tmPtr->tm_hour <<":" << tmPtr->tm_min<< ":" << tmPtr->tm_sec << "\n\n";

        gotoxy (108,6);
        cout << "IDIOMA: ESP";

        gotoxy (46,7);
        cout << "-------------------------------------------------------------------------";



}

//////////////////////////////////////////////////////////////////////////

void Bordes()
{

    for(int x=45;x<121;x++){

        gotoxy(x,8);printf("%c",205);
    }

    gotoxy(44,8);printf("%c",201);
    gotoxy(120,8);printf("%c",187);

    for(int x=9;x<21;x++){

    gotoxy(44,x);printf("%c",186);
    gotoxy(120,x);printf("%c",186);


    }

    gotoxy(44,21);printf("%c",200);
    gotoxy(120,21);printf("%c",188);

    for(int x=45;x<120;x++){

        gotoxy(x,21);printf("%c",205);
    }




}

//////////////////////////////////////////////////////////////////////////

int menu_principal ()
{
    int OpcionSelec;

    char op;
    system ("color 0B");

    while (true)
    {

        Integrantes();
        Bordes ();
        gotoxy(75,10);
        cout << "MENU PRINCIPAL";
        gotoxy(53,10);
        cout << "*******************";
        gotoxy(92,10);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Productos";
        gotoxy(53,13);
        cout << "<2> Proveedores";
        gotoxy(53,14);
        cout << "<3> Empleados";
        gotoxy(53,15);
        cout << "<4> Clientes";
        gotoxy(53,16);
        cout << "<5> Informes";
        gotoxy(92,12);
        cout << "<6> Consultas";
        gotoxy(92,13);
        cout << "<7> Ventas";
        gotoxy(92,14);
        cout << "<8> Configuracion";
        gotoxy(53,18);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
        cout << "<0> Salir del Programa";
        gotoxy(45,23);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
        cout << "\tOPCION: [ ]\b\b";
        cin >> OpcionSelec;


        system ("cls");
        system ("color 0B");
        switch (OpcionSelec)
        {
        case 1:
            MenuProductos();
            system ("cls");
            break;

        case 2:
            MenuProveedores();
            system ("cls");
            break;

        case 3:
            MenuEmpleado();
            system ("cls");
            break;

        case 4:
            MenuCliente();
            system ("cls");
            break;

        case 5:
            MenuInformes();
            system ("cls");
            break;

        case 6:
            MenuConsultas();
            system ("cls");
            break;

        case 7:
            MenuVentas();
            system("cls");
            break;

        case 8:
            MenuConfiguracion();
            system ("cls");
            break;


        default:

            gotoxy (50,1);
            cout << "Opcion incorrecta, ingrese una opcion valida . . .";

            gotoxy (50,3);
            system ("pause");
            system ("cls");
            break;

        case 0 :

            gotoxy (50,1);
            cout << "Esta seguro que desea salir del programa? (S/N)";
            cout << endl;
            gotoxy (50,3);
            cout << "OPCION:[ ]\b\b";
            cin >> op;

            switch (op)
            {
            case 'S':
            case 's':
                system ("cls");
                return 0;
                break;

            case 'N':
            case 'n':
                break;

            default:
                gotoxy (12,0);
                system ("cls");
                cout << "Opcion incorrecta.\n\n";
                system ("pause");
                system ("cls");
                break;

            }

            break;


        }



    }

}

/////////////////////////////////////////////////////////////////////////

int main()
{
    system("mode 650");
    system ("color FB");
    menu_principal();

}
