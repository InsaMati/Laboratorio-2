#ifndef PROVEEDORES_H_INCLUDED
#define PROVEEDORES_H_INCLUDED

int BuscarProveedor(int);

class proveedor : public persona
{

private:

    int NumeroProve;
    bool estado;

public:

    bool CargarProveedor();
    bool GuardarProveedor();
    void MostrarProveedor();
    bool LeerDisco(int);
    int modificarEnDisco(int);

    // Getters y setters

    char *getnombre(){return nombre;}
    char *getapellido(){return apellido;}
    int getnumeroprove(){return NumeroProve;}
    bool getestado(){return estado;}
    void setnombre(char *n){strcpy(n,nombre);}
    void setapellido(char *p){strcpy(p,apellido);}
    void setnumeroprove(int n){NumeroProve = n;}
    void setestado(bool est){estado = est;}


};

bool proveedor::CargarProveedor()
{

    cout << "Datos Proveedor" << endl << endl;

    cout << "Numero de proveedor: ";
    cin >> NumeroProve;

    if(NumeroProve<0){

        system("cls");
        cout << "Numero de proveedor negativo." << endl << endl;

        return false;
    }

    int Buscar = BuscarProveedor(NumeroProve);

    if(Buscar!=-1)
    {

        system("cls");
        cout << "El numero de proveedor, ya existe." << endl;

        return false;

    }

    if(CargarPersona()==false){

        return false;

    }


    estado = true;

    return true;

}

bool proveedor::GuardarProveedor()
{

    FILE*p=fopen("proveedor.dat","ab");

    if (p==NULL)
    {
        cout << endl;
        cout << "Error al crear proveedor.dat" << endl << endl;
        return false;
    }

    fwrite(this,sizeof *this,1,p);
    fclose(p);

    return true;

}

void proveedor::MostrarProveedor()
{


    if(estado==true)
    {
        cout << "Numero Proveedor: " << NumeroProve << endl;
        cout << "DNI: " << dni << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Apellido: " << apellido << endl;
        cout << "Zona: " << zona << endl;

    }

}

bool proveedor::LeerDisco(int posicion)
{

    FILE*p = fopen("proveedor.dat","rb");

    if(p==NULL)
    {

        return false;
    }

    fseek(p,sizeof *this*posicion,0);

    bool leer = fread(this,sizeof *this,1,p);
    fclose(p);

    return leer;
}

int proveedor::modificarEnDisco(int posicion)
{

    FILE*p = fopen("proveedor.dat","rb+");

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

//////////////////////////////////////////////////////

///// Prototipos ABML

void ListarProveedores();
int BajaProveedor();
void BuscarPorNumero();


////////////

int BuscarProveedor(int NumeroProve)
{

    proveedor obj;

    int contador = 0;

    FILE*p = fopen ("proveedor.dat","rb");

    if (p==NULL)
    {

    }

    while(fread(&obj,sizeof(proveedor),1,p)==1)

    {

        if(NumeroProve==obj.getnumeroprove() && obj.getestado()==true)
        {

            return contador;

        }


        contador++;
    }


    return -1;

}

////////////

void ListarProveedores()
{

    proveedor obj;

    FILE*p = fopen("proveedor.dat","rb");

    if(p==NULL)
    {
        cout << endl;
        cout << "Error al abrir proveedor.dat en modo lectura." << endl << endl;
    }

    while(fread(&obj,sizeof(proveedor),1,p)==1)
    {

        obj.MostrarProveedor();
        cout << endl;

    }


    fclose(p);


}

////////////

void BuscarPorNumero()
{
    proveedor obj;

    int numero;
    int x = 0;

    cout << "Ingrese, un numero de proveedor: ";
    cin >> numero;

    system ("cls");

    FILE*p = fopen("proveedor.dat","rb");

    while(fread(&obj,sizeof(proveedor),1,p)==1)
    {

        if(numero==obj.getnumeroprove() && obj.getestado() == true)
        {

            obj.MostrarProveedor();
            x++;
        }


    }

    if(x==0)
    {

        cout << "El Numero de proveedor es invalido, no existe en el archivo." << endl << endl;
    }


    fclose(p);
}

////////////

int BajaProveedor()
{
    proveedor obj;

    int numero;
    int posicion = 0;
    char opc;

    cout << "Ingrese, el numero del proveedor que desee dar de baja: ";
    cin >> numero;

    obj.LeerDisco(0);
    system ("cls");

    while(obj.LeerDisco(posicion)==1)
    {
        if(obj.getnumeroprove()==numero)
        {

            cout << "Proveedor encontrado en el archivo." << endl << endl;

            obj.MostrarProveedor();
            cout << endl;

            cout << "Esta seguro que desea dar de baja a este proveedor? S/N" << endl << endl;
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

//////////////////////////////////////////////////////


int ContarProveedores()
{

    int cantidad;

    FILE*p = fopen("proveedor.dat","rb");

    if(p==NULL)
    {

        cout << "Error" << endl;
    }

    fseek (p,0,2);

    cantidad = ftell(p);

    return cantidad/sizeof(proveedor);

}

/////////////////////////////////////////////////////

void CargarPro(proveedor *vec, int cantidad){

    FILE*p = fopen("proveedor.dat","rb");

    if(p==NULL){cout << "Error" << endl << endl;}

    fread(vec,sizeof(proveedor),cantidad,p);
    fclose(p);

}


/////////////////////////////////////////////////////

void MostrarVectorProveedores(proveedor *vec,int cantidad){

    for(int x=0;x<cantidad;x++){


        if(vec[x].getestado()==true){

        gotoxy (4,1);
        cout << "Numero";
        gotoxy (5,x+3);
        cout << vec[x].getnumeroprove();

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

        gotoxy(69,1);
        cout<< "Genero";
        gotoxy(67,x+3);
        cout<< vec[x].getgenero();

        gotoxy(85,1);
        cout << "Zona";
        gotoxy(80,x+3);
        cout<< vec[x].getzona();}


    }


    //// No baja

    for(int x=2;x<96;x++){

        gotoxy(x,2);printf("%c",205);

    }

    for(int x=3;x<96;x++){

        gotoxy(x,0);printf("%c",205);
    }


    /////////////////////

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


    ////////////////////


    gotoxy(2,0);printf("%c",201);
    gotoxy(2,1);printf("%c",186);
    gotoxy(2,2);printf("%c",204);

    gotoxy(96,0);printf("%c",187);
    gotoxy(96,1);printf("%c",186);
    gotoxy(96,2);printf("%c",185);

    int j;

    //// Si baja

    //// Izq Full

    for(int k=3; k<2*cantidad+1; k++)
    {
        j = k;

        gotoxy(2,k);
        printf("%c",186);
    }

    gotoxy(2,j+1);printf("%c",200);
    gotoxy(96,j+1);printf("%c",188);

    for(int x=3;x<96;x++){

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

    gotoxy(3,20);


}


/////////////////////////////////////////////////////

void PorNumeroProve(proveedor *vec,int cantidad){


     proveedor obj;

     int auxiliar;

     for(int x=0;x<cantidad-1;x++){

        auxiliar = x;

        for(int p=x+1;p<cantidad;p++){

            if(vec[p].getnumeroprove()<vec[auxiliar].getnumeroprove()){

                auxiliar = p;

            }

        }

        obj = vec[x];
        vec[x]=vec[auxiliar];
        vec[auxiliar]= obj;

     }


}



/////////////////////////////////////////////////////

void PorApellido(proveedor *vec,int cantidad){

    proveedor obj;

     int auxiliar;

     for(int x=0;x<cantidad-1;x++){

        auxiliar = x;

        for(int p=x+1;p<cantidad;p++){

            if(strcmp(vec[p].getapellido(),vec[auxiliar].getapellido())<0){

                auxiliar = p;

            }

        }

        obj = vec[x];
        vec[x]=vec[auxiliar];
        vec[auxiliar]= obj;

     }


}

/////////////////////////////////////////////////////

void MostrarProveedores(){

   proveedor *vec;

   int cantidad = ContarProveedores();

   vec = new proveedor[cantidad];

   if(vec==NULL){

    cout << "No se pudo asignar, la memoria." << endl << endl;
   }

   CargarPro(vec,cantidad);
   MostrarVectorProveedores(vec,cantidad);

   delete(vec);

}

/////////////////////////////////////////////////////

void MostrarPorApe(){

   proveedor *vec;

   int cantidad = ContarProveedores();

   vec = new proveedor[cantidad];

   if(vec==NULL){

    cout << "No se pudo asignar, la memoria." << endl << endl;
   }

   CargarPro(vec,cantidad);
   PorApellido(vec,cantidad);
   MostrarVectorProveedores(vec,cantidad);

   delete(vec);

}

/////////////////////////////////////////////////////

void MostrarPorId(){

   proveedor *vec;

   int cantidad = ContarProveedores();

   vec = new proveedor[cantidad];

   if(vec==NULL){

    cout << "No se pudo asignar, la memoria." << endl << endl;
   }

   CargarPro(vec,cantidad);
   PorNumeroProve(vec,cantidad);
   MostrarVectorProveedores(vec,cantidad);

   delete(vec);

}


/////////////////////////////////////////////////////


int MenuMostrarProveedores()
{

    int OpcionSelec;

    while (true)
    {

        Datos();
        Bordes ();

        gotoxy(75,9);
        cout << "MENU MOSTRAR";
        gotoxy(53,9);
        cout << "*******************";
        gotoxy(92,9);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Mostrar sin ordenamiento";
        gotoxy(53,13);
        cout << "<2> Por Numero Proveedor";
        gotoxy(53,14);
        cout << "<3> Por Apellido";
        gotoxy(53,15);
        cout << "<0> Volver al Menu Principal";
        gotoxy(75,18);
        cout << "xxxxxxxxxxxxxx";
        gotoxy(53,18);
        cout << "*******************";
        gotoxy(92,18);
        cout << "*******************";

        gotoxy(40,23);
        cout << "\tOPCION: [ ]\b\b";
        cin >> OpcionSelec;
        system ("cls");

        switch (OpcionSelec)
        {

        case 1:

            MostrarProveedores();
            system ("pause");
            system ("cls");
            break;

        case 2:
            MostrarPorId();
            system ("pause");
            system ("cls");
            break;

        case 3:
            MostrarPorApe();
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


/////////////////////////////////////////////////////

int MenuProveedores()
{
    proveedor b;

    int OpcionSelec;

    while (true)
    {

        Datos();
        Bordes ();

        gotoxy(75,10);
        cout << "MENU PROVEEDOR";
        gotoxy(53,10);
        cout << "*******************";
        gotoxy(92,10);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Cargar Proveedor";
        gotoxy(53,13);
        cout << "<2> Mostrar Proveedores";
        gotoxy(53,14);
        cout << "<3> Buscar Proveedor";
        gotoxy(53,15);
        cout << "<4> Baja Proveedor";
        gotoxy(53,16);
        cout << "<0> Volver al Menu Principal";
        gotoxy(75,18);
        cout << "xxxxxxxxxxxxxx";
        gotoxy(53,18);
        cout << "*******************";
        gotoxy(92,18);
        cout << "*******************";

        gotoxy(40,23);
        cout << "\tOPCION: [ ]\b\b";
        cin >> OpcionSelec;
        system ("cls");

        switch (OpcionSelec)
        {

        case 1:

        if(b.CargarProveedor()==true){

            if(b.GuardarProveedor()==true){

                system ("cls");
                cout << "Se ha guardado correctamente, el proveedor." << endl << endl;
            }
        }

            system ("pause");
            system ("cls");
            break;

        case 2:
            MenuMostrarProveedores();
            system ("cls");
            break;

        case 3:
            BuscarPorNumero();
            system ("pause");
            system ("cls");
            break;

        case 4:
            BajaProveedor();
            system ("pause");
            system ("cls");
            break;

        case 5:
            break;

        case 6:
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

//////////////////////////////////////////////////////////////////////////


#endif // PROVEEDORES_H_INCLUDED
