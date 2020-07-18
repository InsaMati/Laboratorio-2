#ifndef EMPLEADO_H_INCLUDED
#define EMPLEADO_H_INCLUDED

int BuscarIDempleado(int);


class PagoEmpleado{

private:

    int idempleado;
    float sueldo;
    fecha Pago;


public:

    bool CargarPago();
    bool LeerPago(int);
    void MostrarPago();
    bool GuardarPago();
    int getidempleado(){return idempleado;}

};

/////////////////////////////////////////

bool PagoEmpleado::CargarPago(){

    cout << "Id Empleado: ";
    cin >> idempleado;

    if(BuscarIDempleado(idempleado)==-3)
    {

        system("cls");

        cout << "No existe este id de empleado." << endl << endl;

        return false;
    }

    cout << "Importe a pagar: $";
    cin >> sueldo;

    if(sueldo<0){

        cout << "El sueldo es menor a 0." << endl << endl;

        return false;
    }

    cout << "Fecha de pago: " << endl;

    if(Pago.cargar()==0){

        system ("cls");

        cout << "Fecha invalida." << endl;

        return false;
    }



   return true;
}

/////////////////////////////////////////

bool PagoEmpleado::GuardarPago(){

FILE*p = fopen("PagoEmpleado.dat","ab");

if(p==NULL){cout << "Error al crear PagoEmpleado.dat";

return false;}

fwrite(this,sizeof*this,1,p);

fclose(p);

return true;

}

/////////////////////////////////////////

void PagoEmpleado::MostrarPago(){


    cout << "Id Empleado:" << idempleado << endl;
    cout << "Importe a pagar: $" << sueldo << endl;
    cout << "Fecha de pago: " << Pago.getdia() << "/" << Pago.getmes() << "/" << Pago.getanio() << endl;

}

/////////////////////////////////////////

bool PagoEmpleado::LeerPago(int posicion){

    FILE*p = fopen("PagoEmpleado.dat","rb");

    if(p==NULL){

    return false;

    }

    fseek(p,sizeof*this*posicion,0);

    bool leeme = fread(this,sizeof*this,1,p);

    fclose(p);

    return leeme;

}

/////////////////////////////////////////


class empleado : public persona{

private:

    int idempleado;
    fecha nacimiento;
    bool estado;

public:

    bool CargarEmpleado();
    bool GuardarEmpleado();
    void MostrarEmpleado();
    bool LeerDisco(int);
    int modificarEnDisco(int);

    //// Getters y Setters ////

    bool getestado(){return estado;}
    char *getnombre(){return nombre;}
    char *getapellido(){return apellido;}
    int getidempleado(){return idempleado;}
    void setnombre(char *n){strcpy(nombre,n);}
    void setapellido(char *a){strcpy(apellido,a);}
    void setzona(char *z){strcpy(zona,z);}
    void setgenero(char *g){strcpy(genero,g);}
    void setidempleado(int id){idempleado = id;}
    void setestado(bool est){estado = est;}
    fecha getfecha(){return nacimiento;}

};

/////////////////////////////////////////////

bool empleado::CargarEmpleado()
{
    cout << "ID Empleado: ";
    cin >> idempleado;

    if(idempleado<0){

        system("cls");
        cout << "Id empleado menor a 0." << endl << endl;

        return false;

    }

    if(BuscarIDempleado(idempleado)==-2)
    {

        cout << "Este id de empleado ya existe en el archivo." << endl << endl;

        return false;
    }


    if(CargarPersona()==false){

        return false;
    }

    cout << "Fecha de nacimiento" << endl;

    int f = nacimiento.cargar();

    if (f==0)
    {

        system ("cls");
        cout << "Fecha invalida." << endl;


        return false;
    }


    estado = true;

    return true;

}

/////////////////////////////////////////////

bool empleado::GuardarEmpleado()
{
    FILE*p = fopen("empleado.dat","ab");

    if(p==NULL)
    {

        cout << "Error al crear empleado.dat" << endl << endl;
        return false;
    }

    fwrite(this,sizeof *this,1,p);
    fclose(p);

}

/////////////////////////////////////////////

void empleado::MostrarEmpleado()
{


    if(estado==true)
    {

        cout << "Numero empleado: " << idempleado << endl;
        cout << "DNI: " << dni << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Apellido: " << apellido << endl;
        cout << "Genero: " << genero << endl;
        cout << "Zona: " << zona << endl;
        cout << "Fecha de nacimiento: " << nacimiento.getdia() << "/" << nacimiento.getmes() << "/" << nacimiento.getanio() << endl;


    }


}

/////////////////////////////////////////////

int empleado::modificarEnDisco(int posicion)
{

    FILE*p = fopen("empleado.dat","rb+");

    if(p==NULL)
    {

        cout << endl;
        cout << "Error." << endl;

        return -1;
    }

    fseek(p,sizeof*this*posicion,0);
    fwrite(this,sizeof*this,1,p);
    fclose(p);

}

/////////////////////////////////////////////

bool empleado::LeerDisco(int posicion)
{

    FILE*b = fopen ("empleado.dat","rb");

    if(b==NULL)
    {

        return false;
    }


    fseek(b,sizeof*this*posicion,0);
    bool leyo = fread(this,sizeof*this,1,b);
    fclose(b);

    return leyo;


}

/////////////////////////////////////////////

int ContarEmpleados();
void MostrarVectorEmpleado (empleado*,int);

/////////////////////////////////////////////

void cargar_vectorr(empleado vec[],int cant)
{
    FILE *p=fopen("empleado.dat","rb");
    if(p==NULL)
    {
        cout<< "Error al asignar memoria dinamica."<< endl;
        return;
    }
    fread(vec,sizeof (empleado),cant,p);
    fclose(p);
}

/////////////////////////////////////////////

void ordenar_nombre(empleado vec[],int cant)
{
    empleado jue;
    int aux;
    for(int i=0; i<cant-1; i++)
    {
        aux=i;
        for(int j=i+1; j<cant; j++)
        {
            if(strcmp(vec[j].getnombre(),vec[aux].getnombre())<0)
            {
                aux=j;
            }
        }
        jue=vec[i];
        vec[i]=vec[aux];
        vec[aux]=jue;
    }



}

//////////////////////////////////////////////////

void ordenar_por_nombre()
{
    empleado *vec;
    int cant;
    cant=ContarEmpleados();
    vec=new empleado[cant];
    if(vec==NULL)
    {
        cout<< "Error al asignar memoria dinamica."<< endl;
        return;
    }
    cargar_vectorr(vec,cant);
    ordenar_nombre(vec,cant);
    MostrarVectorEmpleado(vec,cant);

    delete(vec);

}

//////////////////////////////////////////////////

void MostrarEmpleados(){

    empleado *vec;
    int cant;
    cant=ContarEmpleados();
    vec=new empleado[cant];
    if(vec==NULL)
    {
        cout<< "Error al asignar memoria dinamica."<< endl;
        return;
    }
    cargar_vectorr(vec,cant);
    MostrarVectorEmpleado(vec,cant);

    delete(vec);


}



//////////////////////////////////////////////////

void ordenar_apellido(empleado vec[],int cant)
{
    empleado jue;
    int aux;
    for(int i=0; i<cant-1; i++)
    {
        aux=i;
        for(int j=i+1; j<cant; j++)
        {
            if(strcmp(vec[j].getapellido(),vec[aux].getapellido())<0)
            {
                aux=j;
            }
        }
        jue=vec[i];
        vec[i]=vec[aux];
        vec[aux]=jue;
    }


}

//////////////////////////////////////////////////

void ordenar_por_apellido()
{
    empleado *vec;
    int cant;
    cant=ContarEmpleados();
    vec=new empleado[cant];
    if(vec==NULL)
    {
        cout<< "Error al asignar memoria dinamica."<< endl;
        return;
    }
    cargar_vectorr(vec,cant);
    ordenar_apellido(vec,cant);
    MostrarVectorEmpleado(vec,cant);

    delete(vec);



}

///////////////////////////////////////////////////

void MostrarVectorEmpleado(empleado *vec,int cantidad){

    for(int x=0;x<cantidad;x++){

        if(vec[x].getestado()==true){

        gotoxy (5,1);
        cout << "ID";
        gotoxy (5,x+3);
        cout << vec[x].getidempleado();

        gotoxy(15,1);
        cout << "Dni";
        gotoxy(13,x+3);
        cout << vec[x].getdni();

        gotoxy(29,1);
        cout << "Nombre";
        gotoxy(25,x+3);
        cout<<vec[x].getnombre();

        gotoxy(49,1);
        cout<<"Apellido";
        gotoxy(45,x+3);
        cout<<vec[x].getapellido();

        gotoxy(68,1);
        cout<< "Genero";
        gotoxy(67,x+3);
        cout<< vec[x].getgenero();

        gotoxy(84,1);
        cout << "Zona";
        gotoxy(80,x+3);
        cout<< vec[x].getzona();

        gotoxy(99,1);
        cout << "Fecha Nacimiento";
        gotoxy(102,x+3);
        cout<< vec[x].getfecha().getdia() << "/" << vec[x].getfecha().getmes() << "/" << vec[x].getfecha().getanio();
                         }

    }


    //// No baja

    for(int x=2;x<118;x++){

        gotoxy(x,2);printf("%c",205);

    }

    gotoxy(2,2);printf("%c",204);

    gotoxy(118,2);printf("%c",185);

    gotoxy(96,2);printf("%c",206);

    //////////////////////////////////

    for(int x=3;x<118;x++){

        gotoxy(x,0);printf("%c",205);
    }

    gotoxy(2,0);printf("%c",201);
    gotoxy(2,1);printf("%c",186);

    gotoxy(10,0);printf("%c",203);
    gotoxy(10,1);printf("%c",186);

    gotoxy(22,0);printf("%c",203);
    gotoxy(22,1);printf("%c",186);

    gotoxy(43,0);printf("%c",203);
    gotoxy(43,1);printf("%c",186);

    gotoxy(64,0);printf("%c",203);
    gotoxy(64,1);printf("%c",186);

    gotoxy(78,0);printf("%c",203);
    gotoxy(78,1);printf("%c",186);

    gotoxy(96,0);printf("%c",203);
    gotoxy(96,1);printf("%c",186);

    gotoxy(118,0);printf("%c",187);
    gotoxy(118,1);printf("%c",186);


    /////////////////////////////////

    //// Si baja

    //// Izq Full

    int j;

    for(int k=3; k<2*cantidad+1; k++)
    {

        j = k;

        gotoxy(2,k);
        printf("%c",186);
    }


    gotoxy(2,j+1);printf("%c",200);
    gotoxy(118,j+1);printf("%c",188);

    for(int x=3;x<118;x++){

        gotoxy(x,j+1);printf("%c",205);
    }

    //// Derecha Full

 for(int k=3; k<2*cantidad+1; k++)
    {
        gotoxy(78,k);
        printf("%c",186);
    }

    gotoxy(78,2);printf("%c",206);


    ///////////////

    /// Dni/Nombre

    for(int k=3; k<2*cantidad+1; k++)
    {
        gotoxy(10,k);
        printf("%c",186);
    }

    gotoxy(10,2);printf("%c",206);

    /////////////

    /// Nombre/Apellido


    for(int k=3; k<2*cantidad+1; k++)
    {
        gotoxy(22,k);
        printf("%c",186);
    }

    gotoxy(22,2);printf("%c",206);

    /////////////

    /// Apellido/Genero


    for(int k=3; k<2*cantidad+1; k++)
    {
        gotoxy(43,k);
        printf("%c",186);
    }

    gotoxy(43,2);printf("%c",206);


    /////////////

    /// Genero/Zona

  for(int k=3; k<2*cantidad+1; k++)
    {
        gotoxy(64,k);
        printf("%c",186);
    }

    gotoxy(64,2);printf("%c",206);


    /////////////

        for(int k=3; k<2*cantidad+1; k++)
    {
        gotoxy(96,k);
        printf("%c",186);
    }


    //////////////

    for(int k=3; k<2*cantidad+1; k++)
    {
        gotoxy(118,k);
        printf("%c",186);
    }




    //////////////



    gotoxy(3,20);




}




///////////////////////////////////////////////////


////////ABML EMPLEADO////////////////////


void ListarEmpleado();
int BajaEmpleado();
int ModificacionEmpleado();
int BuscarDNIEmpleado(int);
void ListarPorID();


int BuscarIDempleado(int id)
{

    empleado obj;

    int posicion = 0;

    FILE* p = fopen("empleado.dat","rb");

    if(p==NULL)
    {

        return -1;
    }

    while(obj.LeerDisco(posicion))
    {

        if(id==obj.getidempleado() && obj.getestado() == true)
        {


            return -2;
        }


        posicion++;
    }


    fclose(p);
    return -3;

}

//////////////////////////////////////////////////

int BuscarDNIEmpleado(int dni)
{

    empleado obj;

    int posicion = 0;

    FILE* p = fopen("empleado.dat","rb");

    if(p==NULL)
    {

        return -1;
    }

    while(obj.LeerDisco(posicion))
    {


        if(dni==obj.getdni()&& obj.getestado() == true)
        {


            return posicion;
        }


        posicion++;
    }


    fclose(p);
    return -1;

}

//////////////////////////////////////////////////

void ListarEmpleado()
{

    empleado gp;

    int posicion = 0;

    while(gp.LeerDisco(posicion++)==true)
    {

        gp.MostrarEmpleado();
        cout << endl;

    }



}

//////////////////////////////////////////////////

int BajaEmpleado()
{

    empleado obj;


    int id;
    int posicion = 0;
    char opc;

    cout << "Ingrese, el ID del Empleado que desee dar de baja: ";
    cin >> id;

    obj.LeerDisco(0);
    system ("cls");

    while(obj.LeerDisco(posicion)==1)
    {
        if(obj.getidempleado()==id)
        {

            cout << "Empleado encontrado en el archivo." << endl << endl;

            obj.MostrarEmpleado();
            cout << endl;

            cout << "Esta seguro que desea dar de baja a este Juego? S/N" << endl << endl;
            cout << "OPCION: [ ]\b\b";
            cin >> opc;

            switch (opc)
            {

            case 's':
            case 'S':

                obj.setestado(false);
                obj.modificarEnDisco(posicion);

                system ("cls");
                cout << "Dado de baja." << endl << endl;
                return 1;
                break;

            case 'n':
            case 'N':
                return 0;
                break;
            }
        }
        posicion++;
    }




}

//////////////////////////////////////////////////

void ListarPorID()
{

    empleado obj;

    int id;

    cout << "Ingrese, numero de ID: ";
    cin >> id;

    system("cls");

    int posicion = 0;

    while(obj.LeerDisco(posicion++))
    {



            if(obj.getidempleado()==id && obj.getestado() == true)
            {

                cout << "Empleado encontrado en el archivo" << endl << endl;
                obj.MostrarEmpleado();
                cout << endl;



            }


    }

}

//////////////////////////////////////////////////

int ModificacionEmpleado()
{

    empleado obj;

    char zona[20];
    int posicion = 0;
    char opcion;
    int idempleado;

    cout << "ID EMPLEADO: ";
    cin >> idempleado;
    system ("cls");

    obj.LeerDisco(0);

    while(obj.LeerDisco(posicion)==1)
    {

        if(obj.getidempleado()==idempleado)
        {
            cout << "EMPLEADO: " << endl << endl;
            obj.MostrarEmpleado();
            cout << endl;
            cout << "Quiere modificar a este empleado? (S/N)" << endl << endl;
            cout << "OPCION [ ]\b\b";
            cin >> opcion;
            system ("cls");

            switch (opcion)
            {

            case 's':
            case 'S':

                cout << "Nueva zona: ";
                cin.ignore();
                cin.getline(zona,20);

                obj.setzona(zona);
                obj.modificarEnDisco(posicion);

                system ("cls");
                cout << "Modificacion completada." << endl << endl;
                return 1;
                break;

            case 'n':
            case 'N':
                return 0;
                break;
            }



        }


        posicion++;
    }

}

//////////////////////////////////////////////////

int ContarEmpleados()
{

    int cantidad;

    FILE*p = fopen("empleado.dat","rb");

    if(p==NULL)
    {

        cout << "Error" << endl;
    }

    fseek (p,0,2);

    cantidad = ftell(p);

    return cantidad/sizeof(empleado);

}

//////////////////////////////////////////

void ListarPagos(){

    PagoEmpleado pp;

    int posicion = 0;

    while(pp.LeerPago(posicion++)){

        pp.MostrarPago();
        cout << endl;

    }


}

//////////////////////////////////////////



int MenuMostrarEmpleado()
{
    int OpcionSelec;

    while (true)
    {

        Datos();
        Bordes ();

        gotoxy(75,10);
        cout << "MENU MOSTRAR";
        gotoxy(53,10);
        cout << "*******************";
        gotoxy(92,10);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Mostrar por defecto";
        gotoxy(53,13);
        cout << "<2> Mostrar alfabeticamente por nombre";
        gotoxy(53,14);
        cout << "<3> Mostrar alfabeticamente por apellido";
        gotoxy(53,17);
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
            MostrarEmpleados();
            system ("pause");
            system ("cls");
            break;

        case 2:
            ordenar_por_nombre();
            system("pause");
            system ("cls");
            break;

        case 3:
            ordenar_por_apellido();
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

//////////////////////////////////////////


int MenuEmpleado()
{
    empleado obj;
    PagoEmpleado ob;

    int OpcionSelec;

    while (true)
    {

        Datos();
        Bordes ();

        gotoxy(75,10);
        cout << "MENU EMPLEADO";
        gotoxy(53,10);
        cout << "*******************";
        gotoxy(92,10);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Cargar Empleado";
        gotoxy(53,13);
        cout << "<2> Mostrar Empleado";
        gotoxy(53,14);
        cout << "<3> Modificar Zona";
        gotoxy(53,15);
        cout << "<4> Buscar Empleado por ID";
        gotoxy(53,16);
        cout << "<5> Baja Empleado";
        gotoxy(92,12);
        cout << "<6> Pago Empleado";
        gotoxy(92,13);
        cout << "<7> Mostrar Pagos";
        gotoxy(53,17);
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

            if(obj.CargarEmpleado()==true)
            {

                if(obj.GuardarEmpleado()==true)
                {

                    cout << "Se ha guardado correctamente, el empleado en el archivo." << endl << endl;
                }

            }


            system ("pause");
            system ("cls");
            break;

        case 2:
            MenuMostrarEmpleado();
            system ("cls");
            break;

        case 3:

            ModificacionEmpleado();
            system ("pause");
            system ("cls");
            break;

        case 4:

            ListarPorID();
            system ("pause");
            system ("cls");
            break;

        case 5:
            BajaEmpleado();
            system ("pause");
            system ("cls");
            break;

        case 6:

            if(ob.CargarPago()==true){

                if(ob.GuardarPago()==true){

                    cout << "Se ha guardado el pago." << endl << endl;


                }

            }

            system("pause");
            system("cls");
            break;

        case 7:
            ListarPagos();
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



#endif // EMPLEADO_H_INCLUDED
