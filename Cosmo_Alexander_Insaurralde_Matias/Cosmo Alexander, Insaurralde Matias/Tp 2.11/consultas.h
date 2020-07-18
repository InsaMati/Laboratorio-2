#ifndef CONSULTAS_H_INCLUDED
#define CONSULTAS_H_INCLUDED


//// Consulta Juegos

void MostrarPorGeneroJuego()
{

    juego obj;

    char clasificacion[20];

    int p = 0;

    int posicion = 0;
    int op;

    gotoxy(50,2);
    cout<< "<x> para mostrar todos los generos";
    gotoxy(50,4);
    cout << "Escribir en minuscula";
    gotoxy(50,6);
    cout << "Ingrese, genero de juego: ";
    cin >> clasificacion;

    system ("cls");

    obj.LeerJuego(0);

    while(obj.LeerJuego(posicion))
    {

        if(strcmp(clasificacion,"x")==0)
        {

            obj.MostrarJuego();
            cout << endl;
        }

        else
        {

            if(strcmp(obj.getclasificacion(),clasificacion)==0)
            {

                obj.MostrarJuego();
                p++;
                cout << endl;

            }
        }


        posicion++;
    }


}

void MostrarPorConsola()
{

    juego obj;

    char consola[20];

    int p = 0;
    int posicion = 0;
    int op;

    gotoxy(50,2);
    cout<< "<t> para mostrar todas las consolas";
    gotoxy(50,3);
    cout << "Escribir en minuscula";
    gotoxy(50,5);
    cout << "Ingrese, tipo de consola: ";
    cin >> consola;

    system ("cls");

    obj.LeerJuego(0);

    while(obj.LeerJuego(posicion))
    {

        if(strcmp(consola,"t")==0)
        {

            obj.MostrarJuego();
            cout << endl;
        }

        else
        {

            if(strcmp(obj.getconsola(),consola)==0)
            {

                obj.MostrarJuego();
                p++;
                cout << endl;

            }
        }


        posicion++;
    }


}

void MostrarPorPrecio()
{
    juego obj;

    int posicion = 0;
    int rango1,rango2;

    gotoxy(50,2);
    cout << "Ingrese, rango de precios: ";
    gotoxy(50,4);
    cout << "Menor Precio: ";
    cin >> rango1;
    gotoxy(50,5);
    cout << "Mayor precio: ";
    cin >> rango2;

    obj.LeerJuego(0);
    system ("cls");

    while(obj.LeerJuego(posicion))

    {

        if(obj.getprecio()>=rango1&&obj.getprecio()<=rango2)
        {

            obj.MostrarJuego();
            cout << endl;
        }


        posicion++;
    }

}


/////////

//// Consulta Empleados

void MostrarPorZona()
{

    empleado obj;

    char zona[20];
    int cont = 0;
    int opcion = 0;

    gotoxy(50,2);cout << "Zona que desea buscar: ";
    cin.ignore();
    cin.getline(zona,20);
    system ("cls");


    obj.LeerDisco(0);


    while(obj.LeerDisco(opcion))
    {

        if(strcmp(obj.getzona(),zona)==0)
        {

            cont++;
            cout << "Empleado: " << endl << endl;
            obj.MostrarEmpleado();
            cout << endl;

        }


        opcion++;
    }


}



void MostrarPorRangoIDEMPLEADO()
{

    empleado obj;

    int posicion = 0;
    int cont = 0;

    int rango1,rango2;

    gotoxy(50,2);cout << "Menor ID: ";
    cin >> rango2;

    gotoxy(50,3);cout << "Mayor ID: ";
    cin >> rango1;

    obj.LeerDisco(0);
    system ("cls");

    while(obj.LeerDisco(posicion))
    {

        if(obj.getidempleado()>=rango2 && obj.getidempleado()<=rango1)
        {

            if(cont==0)
            {

                cout << "Empleados de ID: " << rango2 <<"-"<< rango1 << endl << endl;
            }

            obj.MostrarEmpleado();
            cont++;

            cout << endl;

        }



        posicion++;
    }





}


/////////

//// Consulta Proveedores

void MostrarPorApellido()
{

    proveedor reg;

    char apellido [30];

    int posicion = 0;

    gotoxy(50,2);cout << "Ingrese apellido de proveedor a buscar: ";
    cin.ignore();
    cin.getline(apellido,30);
    system("cls");

    while(reg.LeerDisco(posicion))
    {

        if(strcmp(reg.getapellido(),apellido)==0)
        {

            reg.MostrarProveedor();
            cout<< endl;

        }

        posicion++;
    }


}

void MostrarPorNombre()
{

    proveedor reg;

    char nombre [30];

    int posicion = 0;

    gotoxy(50,2);cout << "Ingrese Nombre de proveedor a buscar: ";
    cin.ignore();
    cin.getline(nombre,30);
    system("cls");

    while(reg.LeerDisco(posicion))
    {

        if(strcmp(reg.getnombre(),nombre)==0)
        {

            reg.MostrarProveedor();
            cout<< endl;

        }

        posicion++;
    }



}

void MostrarPorRangoNumeroProveedor()
{

    proveedor reg;

    int posicion = 0;
    int rango1, rango2;

    gotoxy(50,2);cout << "Rango de proveedor que desea buscar: " << endl;
    gotoxy(50,4);cout << "Menor rango: ";
    cin >> rango1;

    gotoxy(50,5);cout << "Mayor rango: ";
    cin >> rango2;

    system("cls");

    while(reg.LeerDisco(posicion))
    {

        if(reg.getnumeroprove()>=rango1 && reg.getnumeroprove()<=rango2)
        {

            reg.MostrarProveedor();
            cout << endl;
        }


        posicion++;
    }



}

//////////////////////////////////////////////////////

//// Consulta Ventas

bool VentaPorEmpleado(){

    venta obj;
    int idempleado;
    int posicion = 0;

    gotoxy(50,2);cout << "ID Empleado: ";
    cin >> idempleado;
    system("cls");

    if(BuscarIDempleado(idempleado)==-3){

        system("cls");
        cout << "No existe este id de empleado." << endl << endl;
        return false;
    }



    while(obj.LeerVenta(posicion++)){

            if(idempleado==obj.getidempleado()){

                  obj.MostrarVenta();
                 cout << endl;

            }

    }


}

//////////////////////////////////////////////////////

bool VentaPorCliente(){

    venta obj;
    int idcliente;
    int posicion = 0;

    gotoxy(50,2);cout << "ID Cliente: ";
    cin >> idcliente;

    if(BuscarCliente(idcliente)==-1){

        system("cls");
        cout << "No existe este id de cliente." << endl << endl;
        return false;
    }

    system("cls");

    while(obj.LeerVenta(posicion++)){

            if(idcliente==obj.getidcliente()){

                obj.MostrarVenta();
                cout << endl;

            }

    }




}


//////////////////////////////////////////////////////

int MenuConsultasJuegos()
{

    int OpcionSelec;

    while (true)
    {

        Datos();

        Bordes ();

        gotoxy(75,10);
        cout << "CONSULTA JUEGOS";
        gotoxy(92,10);
        cout << "*******************";
        gotoxy(53,10);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Por Genero";
        gotoxy(53,13);
        cout << "<2> Por Consola";
        gotoxy(53,14);
        cout << "<3> Por Rango Precio";;
        gotoxy(53,16);
        cout << "<0> Volver al Menu Principal";
        gotoxy(75,19);
        cout << "xxxxxxxxxxxxxx";
        gotoxy(92,19);
        cout << "*******************";
        gotoxy(53,19);
        cout << "*******************";

        gotoxy(40,23);
        cout << "\tOPCION: [ ]\b\b";
        cin >> OpcionSelec;
        system ("cls");

        switch (OpcionSelec)
        {

        case 1:
            MostrarPorGeneroJuego();
            system ("pause");
            system ("cls");
            break;

        case 2:
            MostrarPorConsola();
            system ("pause");
            system ("cls");
            break;

        case 3:
            MostrarPorPrecio();
            system ("pause");
            system ("cls");
            break;


        default:

            gotoxy (50,1);
            cout << "Opcion incorrecta, ingrese una opcion valida . . .";

            gotoxy (50,3);
            system ("pause");
            system ("cls");
            break;

        case 0:

            return 0;

            break;


        }



    }





}


int MenuConsultasProveedores()
{

    int OpcionSelec;

    while (true)
    {

        Datos();

        Bordes ();

        gotoxy(75,10);
        cout << "CONSULTA PROVEE";
        gotoxy(53,10);
        cout << "*******************";
        gotoxy(92,10);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Por Rango ID";
        gotoxy(53,13);
        cout << "<2> Por Nombre";
        gotoxy(53,14);
        cout << "<3> Por Apellido";
        gotoxy(53,16);
        cout << "<0> Volver al Menu Principal";
        gotoxy(75,19);
        cout << "xxxxxxxxxxxxxx";
        gotoxy(92,19);
        cout << "*******************";
        gotoxy(53,19);
        cout << "*******************";

        gotoxy(40,23);
        cout << "\tOPCION: [ ]\b\b";
        cin >> OpcionSelec;
        system ("cls");

        switch (OpcionSelec)
        {

        case 1:
            MostrarPorRangoNumeroProveedor();
            system ("pause");
            system ("cls");
            break;

        case 2:
            MostrarPorNombre();
            system ("pause");
            system ("cls");
            break;

        case 3:
            MostrarPorApellido();
            system ("pause");
            system ("cls");
            break;


        default:

            gotoxy (50,1);
            cout << "Opcion incorrecta, ingrese una opcion valida . . .";

            gotoxy (50,3);
            system ("pause");
            system ("cls");
            break;

        case 0:

            return 0;

            break;


        }



    }




}


int MenuConsultasEmpleados()
{


    int OpcionSelec;

    while (true)
    {

        Datos();
        Bordes ();

        gotoxy(75,10);
        cout << "  EMPLEADOS";
        gotoxy(53,10);
        cout << "*******************";
        gotoxy(92,10);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Por Zona";
        gotoxy(53,14);
        cout << "<2> Por Rango ID Empleado";
        gotoxy(53,16);
        cout << "<0> Volver al Menu Principal";
        gotoxy(75,19);
        cout << "xxxxxxxxxxxxxx";
        gotoxy(53,19);
        cout << "*******************";
        gotoxy(92,19);
        cout << "*******************";

        gotoxy(40,23);
        cout << "\tOPCION: [ ]\b\b";
        cin >> OpcionSelec;
        system ("cls");

        switch (OpcionSelec)
        {

        case 1:
            MostrarPorZona();
            system ("pause");
            system ("cls");
            break;

        case 2:
            MostrarPorRangoIDEMPLEADO();
            system ("pause");
            system ("cls");
            break;

        default:

            gotoxy (50,1);
            cout << "Opcion incorrecta, ingrese una opcion valida . . .";

            gotoxy (50,3);
            system ("pause");
            system ("cls");
            break;

        case 0:

            return 0;

            break;


        }



    }


}


int MenuConsultasVentas()
{


    int OpcionSelec;

    while (true)
    {

        Datos();

        Bordes ();

        gotoxy(75,10);
        cout << "    VENTAS";
        gotoxy(53,10);
        cout << "*******************";
        gotoxy(92,10);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Por Empleado";
        gotoxy(53,14);
        cout << "<2> Por Cliente";
        gotoxy(53,16);
        cout << "<0> Volver al Menu Principal";
        gotoxy(75,19);
        cout << "xxxxxxxxxxxxxx";
        gotoxy(53,19);
        cout << "*******************";
        gotoxy(92,19);
        cout << "*******************";

        gotoxy(40,23);
        cout << "\tOPCION: [ ]\b\b";
        cin >> OpcionSelec;
        system ("cls");

        switch (OpcionSelec)
        {

        case 1:
            VentaPorEmpleado();
            system ("pause");
            system ("cls");
            break;

        case 2:
            VentaPorCliente();
            system("pause");
            system ("cls");
            break;



        default:

            gotoxy (50,1);
            cout << "Opcion incorrecta, ingrese una opcion valida . . .";

            gotoxy (50,3);
            system ("pause");
            system ("cls");
            break;

        case 0:

            return 0;

            break;


        }



    }
}








int MenuConsultas()
{

    int OpcionSelec;

    while (true)
    {

        Datos();

        Bordes ();

        gotoxy(75,10);
        cout << "MENU CONSULTAS";
        gotoxy(53,10);
        cout << "*******************";
        gotoxy(92,10);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Juegos";
        gotoxy(53,13);
        cout << "<2> Empleados";
        gotoxy(53,14);
        cout << "<3> Proveedores";
        gotoxy(53,15);
        cout << "<4> Ventas";
        gotoxy(53,16);
        cout << "<0> Volver al Menu Principal";
        gotoxy(75,19);
        cout << "xxxxxxxxxxxxxx";
        gotoxy(53,19);
        cout << "*******************";
        gotoxy(92,19);
        cout << "*******************";
        gotoxy(40,23);
        cout << "\tOPCION: [ ]\b\b";
        cin >> OpcionSelec;
        system ("cls");

        switch (OpcionSelec)
        {

        case 1:
            MenuConsultasJuegos();
            system ("cls");
            break;

        case 2:
            MenuConsultasEmpleados();
            system ("cls");
            break;

        case 3:
            MenuConsultasProveedores();
            system ("cls");
            break;

        case 4:
            MenuConsultasVentas();
            system ("cls");
            break;


        default:

            gotoxy (50,1);
            cout << "Opcion incorrecta, ingrese una opcion valida . . .";

            gotoxy (50,3);
            system ("pause");
            system ("cls");
            break;

        case 0:

            return 0;

            break;


        }



    }




}



#endif // CONSULTAS_H_INCLUDED
