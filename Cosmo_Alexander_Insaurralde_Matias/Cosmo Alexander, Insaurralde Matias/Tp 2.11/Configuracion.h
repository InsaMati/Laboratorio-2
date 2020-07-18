#ifndef CONFIGURACION_H_INCLUDED
#define CONFIGURACION_H_INCLUDED

bool BackUpJuegos()
{

    juego reg;

    FILE* p = fopen("juegos.dat","rb");
    FILE* c = fopen("juegos.bkp","ab");

    if(p==NULL || c==NULL)
    {
        cout << "No se pudo hacer el backup." << endl;
        return false;
    }

    while (fread(&reg,sizeof(juego),1,p)==1)
    {
        fwrite(&reg,sizeof(juego),1,c);

    }

    fclose(p);
    fclose(c);

    return true;


}

bool BackUpProveedores()
{

    proveedor reg;

    FILE*COPIAR = fopen("proveedor.dat","rb");
    FILE*ACA = fopen("proveedor.bkp","ab");

    if(COPIAR==NULL || ACA==NULL)
    {
        cout << endl;
        cout << "No se pudo hacer backup de proveedores." << endl << endl;
        return false;
    }

    while(fread(&reg,sizeof(proveedor),1,COPIAR)==1)
    {

        fwrite(&reg,sizeof(proveedor),1,ACA);


    }

    fclose(COPIAR);
    fclose(ACA);

    return true;


}

bool BackUpClientes()
{

    cliente reg;

    FILE*COPIAR = fopen("cliente.dat","rb");
    FILE*ACA = fopen("cliente.bkp","ab");

    if(COPIAR==NULL || ACA==NULL)
    {
        cout << endl;
        cout << "No se pudo hacer backup de clientes." << endl << endl;
        return false;
    }

    while(fread(&reg,sizeof(cliente),1,COPIAR)==1)
    {

        fwrite(&reg,sizeof(cliente),1,ACA);

    }

    fclose(COPIAR);
    fclose(ACA);

    return true;

}

bool BackUpEmpleados()
{
    empleado reg;

    FILE*COPIAR = fopen("empleado.dat","rb");
    FILE*ACA = fopen("empleado.bkp","ab");

    if(COPIAR==NULL || ACA==NULL)
    {
        cout << endl;
        cout << "No se pudo hacer backup de empleados." << endl << endl;
        return false;
    }

    while(fread(&reg,sizeof(empleado),1,COPIAR)==1)
    {

        fwrite(&reg,sizeof(empleado),1,ACA);

    }

    fclose(COPIAR);
    fclose(ACA);

    return true;




}

bool BackUpVentas()
{

    venta reg;

    FILE*COPIAR = fopen("venta.dat","rb");
    FILE*ACA = fopen("venta.bkp","ab");

    if(COPIAR==NULL || ACA==NULL)
    {
        cout << endl;
        cout << "No se pudo hacer backup de las ventas." << endl << endl;
        return false;
    }

    while(fread(&reg,sizeof(venta),1,COPIAR)==1)
    {

        fwrite(&reg,sizeof(venta),1,ACA);

    }

    fclose(COPIAR);
    fclose(ACA);

    return true;


}

void BackUpTodos()
{

    BackUpJuegos();
    BackUpEmpleados();
    BackUpProveedores();
    BackUpClientes();
    BackUpVentas();

    system ("cls");
    cout << "Backup completo." << endl;

}


int MenuBackUp()
{

    int OpcionSelec;
    int s;

    while (true)
    {

        time_t tiempo;

        struct tm *tmPtr;

        tiempo = time(NULL);
        tmPtr = localtime(&tiempo);

        gotoxy (3,2);
        cout << "DATOS SISTEMA";
        gotoxy (3,3);
        cout << "-----------------------------------------------------------------------";
        gotoxy (3,4);
        cout << "FECHA: ";
        cout << tmPtr->tm_mday << "/" << tmPtr->tm_mon+1 << "/" << tmPtr->tm_year+1900 <<" ";
        gotoxy (3,6);
        cout << "HORA: ";
        cout << tmPtr->tm_hour <<":" << tmPtr->tm_min<< ":" << tmPtr->tm_sec << "\n\n";

        gotoxy (62,6);
        cout << "IDIOMA: ESP";

        gotoxy (3,7);
        cout << "-----------------------------------------------------------------------";

        Bordes ();

        gotoxy(33,9);
        cout << "MENU BACKUP";
        gotoxy(12,9);
        cout << "*******************";
        gotoxy(47,9);
        cout << "*******************";
        gotoxy(13,11);
        cout << "<1> Juegos";
        gotoxy(13,12);
        cout << "<2> Proveedores";
        gotoxy(13,13);
        cout << "<3> Clientes";
        gotoxy(13,14);
        cout << "<4> Empleados";
        gotoxy(13,15);
        cout << "<5> Ventas";
        gotoxy(13,16);
        cout << "<6> Todos los archivos";
        gotoxy(13,17);
        cout << "<0> Volver al Menu Principal";
        gotoxy(32,19);
        cout << "xxxxxxxxxxxxxx";
        gotoxy(12,19);
        cout << "*******************";
        gotoxy(47,19);
        cout << "*******************";

        gotoxy(0,22);
        cout << "\tOPCION: [ ]\b\b";
        cin >> OpcionSelec;
        system ("cls");

        switch (OpcionSelec)
        {

        case 1:
            if(BackUpJuegos()==true)
            {

                cout << "Backup Completo." << endl << endl;
            }
            system ("pause");
            system ("cls");
            break;

        case 2:
            if(BackUpProveedores()==true)
            {
                cout << "Backup Completo." << endl << endl;
            }
            system ("pause");
            system ("cls");
            break;

        case 3:
            if(BackUpClientes()==true)
            {
                cout << "Backup Completo." << endl << endl;
            }
            system ("pause");
            system ("cls");
            break;

        case 4:
            if(BackUpEmpleados()==true)
            {
                cout << "Backup Completo." << endl << endl;
            }
            system ("pause");
            system ("cls");
            break;

        case 5:
            if(BackUpVentas()==true)
            {
                cout << "Backup Completo." << endl << endl;
            }
            system ("pause");
            system ("cls");
            break;

        case 6:
            BackUpTodos();
            system ("pause");
            system ("cls");
            break;

        default:

            gotoxy (20,0);
            cout << "Opcion incorrecta, ingrese una opcion valida . . .";

            gotoxy (22,2);
            system ("pause");
            system ("cls");
            break;

        case 0:

            return 0;

            break;


        }



    }




}



bool RestJuegos()
{
    juego reg;

    FILE*copiar = fopen("juegos.bkp","rb");
    FILE*aca = fopen("juegos.dat","wb");

    if(copiar==NULL || aca==NULL)
    {
        cout << endl;
        cout << "No se pudo hacer la restauracion." << endl;
        return false;
    }

    while(fread(&reg,sizeof(juego),1,copiar)==1)
    {

        fwrite(&reg,sizeof(juego),1,aca);

    }

    fclose(copiar);
    fclose(aca);

    return true;

}


bool RestProveedores()
{

    proveedor reg;

    FILE*copiar = fopen("proveedor.bkp","rb");
    FILE*aca = fopen("proveedor.dat","wb");

    if(copiar==NULL || aca==NULL)
    {
        cout << endl;
        cout << "No se pudo hacer la restauracion." << endl;
        return false;
    }

    while(fread(&reg,sizeof(proveedor),1,copiar)==1)
    {

        fwrite(&reg,sizeof(proveedor),1,aca);

    }

    fclose(copiar);
    fclose(aca);

    return true;


}



bool RestEmpleados()
{

    empleado reg;

    FILE*copiar = fopen("empleado.bkp","rb");
    FILE*aca = fopen("empleado.dat","wb");

    if(copiar==NULL || aca==NULL)
    {
        cout << endl;
        cout << "No se pudo hacer la restauracion." << endl;
        return false;
    }

    while(fread(&reg,sizeof(empleado),1,copiar)==1)
    {

        fwrite(&reg,sizeof(empleado),1,aca);

    }

    fclose(copiar);
    fclose(aca);

    return true;



}

bool RestClientes()
{

    cliente reg;

    FILE*copiar = fopen("cliente.bkp","rb");
    FILE*aca = fopen("cliente.dat","wb");

    if(copiar==NULL || aca==NULL)
    {
        cout << endl;
        cout << "No se pudo hacer la restauracion." << endl;
        return false;
    }

    while(fread(&reg,sizeof(cliente),1,copiar)==1)
    {

        fwrite(&reg,sizeof(cliente),1,aca);

    }

    fclose(copiar);
    fclose(aca);

    return true;

}

bool RestVentas()
{

    venta reg;

    FILE*copiar = fopen("venta.bkp","rb");
    FILE*aca = fopen("venta.dat","wb");

    if(copiar==NULL || aca==NULL)
    {
        cout << endl;
        cout << "No se pudo hacer la restauracion." << endl;
        return false;
    }

    while(fread(&reg,sizeof(venta),1,copiar)==1)
    {

        fwrite(&reg,sizeof(venta),1,aca);

    }

    fclose(copiar);
    fclose(aca);

    return true;



}

void RestTodos()
{
    RestJuegos();
    RestProveedores();
    RestEmpleados();
    RestClientes();
    RestVentas();

}

int MenuRestauracion()
{

    int OpcionSelec;

    while (true)
    {

        time_t tiempo;

        struct tm *tmPtr;

        tiempo = time(NULL);
        tmPtr = localtime(&tiempo);

        gotoxy (3,2);
        cout << "DATOS SISTEMA";
        gotoxy (3,3);
        cout << "-----------------------------------------------------------------------";
        gotoxy (3,4);
        cout << "FECHA: ";
        cout << tmPtr->tm_mday << "/" << tmPtr->tm_mon+1 << "/" << tmPtr->tm_year+1900 <<" ";
        gotoxy (3,6);
        cout << "HORA: ";
        cout << tmPtr->tm_hour <<":" << tmPtr->tm_min<< ":" << tmPtr->tm_sec << "\n\n";

        gotoxy (62,6);
        cout << "IDIOMA: ESP";

        gotoxy (3,7);
        cout << "-----------------------------------------------------------------------";

        Bordes ();


        gotoxy(33,9);
        cout << "MENU REST";
        gotoxy(12,9);
        cout << "*******************";
        gotoxy(47,9);
        cout << "*******************";
        gotoxy(13,11);
        cout << "<1> Juegos";
        gotoxy(13,12);
        cout << "<2> Proveedores";
        gotoxy(13,13);
        cout << "<3> Clientes";
        gotoxy(13,14);
        cout << "<4> Empleados";
        gotoxy(13,15);
        cout << "<5> Ventas";
        gotoxy(13,16);
        cout << "<6> Todos los archivos";
        gotoxy(13,17);
        cout << "<0> Volver al Menu Principal";
        gotoxy(32,19);
        cout << "xxxxxxxxxxxxxx";
        gotoxy(12,19);
        cout << "*******************";
        gotoxy(47,19);
        cout << "*******************";

        gotoxy(0,23);
        cout << "\tOPCION: [ ]\b\b";
        cin >> OpcionSelec;
        system ("cls");

        switch (OpcionSelec)
        {

        case 1:
            if(RestJuegos()==true)
            {
                cout << "Restauracion completa." << endl;
            }
            system("pause");
            system ("cls");
            break;

        case 2:
            if(RestProveedores()==true)
            {
                cout << "Restauracion completa." << endl;
            }
            system("pause");
            system ("cls");
            break;

        case 3:
            if(RestEmpleados()==true)
            {
                cout << "Restauracion completa." << endl;
            }
            system ("pause");
            system ("cls");
            break;

        case 4:
            if(RestEmpleados()==true)
            {
                cout << "Restauracion completa." << endl;
            }
            system ("pause");
            system ("cls");
            break;

        case 5:
            if(RestVentas()==true)
            {
                cout << "Restauracion completa." << endl;
            }
            system("pause");
            system("cls");
            break;

        case 6:
            RestTodos();
            system("pause");
            system("cls");
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


int MenuConfiguracion()
{


    int OpcionSelec;

    while (true)
    {

        Datos();

        Bordes ();

        gotoxy(75,9);
        cout << "CONFIGURACION";
        gotoxy(92,9);
        cout << "*******************";
        gotoxy(53,9);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Realizar BackUp";
        gotoxy(53,14);
        cout << "<2> Restaurar BackUp";
        gotoxy(53,16);
        cout << "<0> Volver al Menu Principal";
        gotoxy(75,18);
        cout << "xxxxxxxxxxxxxx";
        gotoxy(53,18);
        cout << "*******************";
        gotoxy(92,18);
        cout << "*******************";

        gotoxy(40,22);
        cout << "\tOPCION: [ ]\b\b";
        cin >> OpcionSelec;
        system ("cls");

        switch (OpcionSelec)
        {

        case 1:


            MenuBackUp();
            system ("cls");
            break;

        case 2:
            MenuRestauracion();
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



#endif // CONFIGURACION_H_INCLUDED
