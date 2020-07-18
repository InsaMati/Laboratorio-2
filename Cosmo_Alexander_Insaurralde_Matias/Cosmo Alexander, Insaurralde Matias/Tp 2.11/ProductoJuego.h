#ifndef PRODUCTOJUEGO_H_INCLUDED
#define PRODUCTOJUEGO_H_INCLUDED

class ganancia{

    private:

        char consola[20];
        float porcentaje;


    public:

        bool CargarGanancia();
        void MostrarPorcentaje();
        int ModificarEnDisco(int);
        bool LeerGanancia(int);
        bool GuardarGanancia();
        char *getconsola(){return consola;}
        float getporcentaje(){return porcentaje;}
        void setconsola(char *c){strcpy(consola,c);}
        void setporcentaje(float p){porcentaje=p;}


};

///////////////////////////////////////////////////////////////////////////


bool BuscarCC(char *consola){

   ganancia obj;

   int posicion = 0;

   while(obj.LeerGanancia(posicion++)){

         if(strcmp(obj.getconsola(),consola)==0){

            return true;
         }

   }


return false;

}

///////////////////////////////////////////////////////////////////////////

bool ganancia::CargarGanancia(){


      char aux[20];

      cout << "Consola: ";
      cin.ignore();
      cin.getline(consola,20);

      strcpy(aux,consola);

      for(int x=0;x<20;x++){

        consola[x] = tolower(aux[x]);


      }


      if(BuscarCC(consola)==true){

        system("cls");

        cout << "Esta consola, ya existe en el archivo de ganancias." << endl;

        cout << "Use la opcion de modificar para cambiar de %" << endl << endl;


        return false;
      }

      cout << "Porcentaje de Ganancia: ";
      cin >> porcentaje;


}

///////////////////////////////////////////////////////////////////////////

bool ganancia::GuardarGanancia(){


   FILE* p = fopen("ganancia.dat","ab");
   if(p==NULL){return false;}

   fwrite(this,sizeof*this,1,p);
   fclose(p);

   return true;

}

///////////////////////////////////////////////////////////////////////////

void ganancia::MostrarPorcentaje(){

   cout << "Consola: " << consola << endl;
   cout << "Porcentaje de ganancia: " << porcentaje << endl;


}
///////////////////////////////////////////////////////////////////////////

int ContarGanancia(){

    int cantidad;

    FILE* p = fopen("ganancia.dat","ab");

    if(p==NULL){

        return -1;
    }

    fseek(p,0,2);

    cantidad = ftell(p);

    return cantidad/sizeof(ganancia);



}

void CargarGanancia(ganancia *v, int cantidad){

   FILE* p = fopen("ganancia.dat","rb");

   if(p==NULL){

    cout << "Error en CargarGanancia." << endl << endl;
   }

   fread(v,sizeof(ganancia),cantidad,p);

   fclose(p);

}

void MostrarGanancia(ganancia *v, int cant){




       gotoxy(8,0);printf("%c",201);
       gotoxy(42,0);printf("%c",187);

       gotoxy(8,1);printf("%c",186);
       gotoxy(42,1);printf("%c",186);

       gotoxy(8,2);printf("%c",204);
       gotoxy(42,2);printf("%c",185);

       for(int x=9;x<42;x++){

        gotoxy(x,2);printf("%c",205);
        gotoxy(x,0);printf("%c",205);
       }


       gotoxy(10,1);cout << "Consola";
       gotoxy(30,1);cout << "Porcentaje";



       for(int x=0;x<cant;x++){

        gotoxy(10,x+3);cout<< v[x].getconsola();
        gotoxy(33,x+3);cout << "% " << v[x].getporcentaje();


       }

       int j;

       for(int k=3; k<2+cant+2; k++)
    {

        j = k;

        gotoxy(8,k);
        printf("%c",186);

        gotoxy(42,k);
        printf("%c",186);

    }

    gotoxy(8,j);printf("%c",200);
    gotoxy(42,j);printf("%c",188);

    for(int x=9;x<42;x++){

    gotoxy(x,j);printf("%c",205);}




}



bool DinamicaGanancia(){

     ganancia *v;

     int t = ContarGanancia();

     v = new ganancia [t];

     if(v==NULL){

        cout << "No se pudo asignar memoria de manera dinamica en la funcion DinamicaGanancia." << endl << endl;

        return false;
     }

     CargarGanancia(v,t);
     MostrarGanancia(v,t);

     gotoxy(5,10);




}


///////////////////////////////////////////////////////////////////////////

bool ganancia::LeerGanancia(int posicion){

  FILE* p = fopen ("ganancia.dat","rb");

  if(p==NULL){return false;}

  fseek(p,sizeof*this*posicion,0);

  bool leeme = fread(this,sizeof*this,1,p);

  fclose(p);

  return leeme;

}

///////////////////////////////////////////////////////////////////////////

int ganancia::ModificarEnDisco(int posicion)
{

    FILE*p = fopen("ganancia.dat","rb+");

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


///////////////////////////////////////////////////////////////////////////

int BuscarCodigoJuego(char*);

class juego
{

private:
    char nombre[30];
    char consola[20];
    char clasificacion[20];
    char codigo[5];
    int stock;
    float precio;
    bool estado;

public:

    bool CargarJuego();
    bool GrabarJuego(int);
    bool LeerJuego(int);
    void MostrarJuego();
    int modificarendisco(int);

    /// Getters y setters

    char *getcodigo (){return codigo;}
    char *getnombre (){return nombre;}
    char *getclasificacion(){return clasificacion;}
    char *getconsola (){return consola;}
    int getstock(){return stock;}
    float getprecio(){return precio;}
    bool getestado(){return estado;}
    void setcodigo (char *c){strcpy(codigo,c);}
    void setnombre (char *n){strcpy(nombre,n);}
    void setclasificacion (char *clas){strcpy(clasificacion,clas);}
    void setconsola (char *cons){strcpy(consola,cons);}
    void setstock (int s){stock = s;}
    void setprecio (float p){precio = p;}
    void setestado (bool b){estado = b;}

};

//////////////////////////////////////////////////////////////////////////

bool juego::CargarJuego()
{

    char aux[20];

    cout << "Codigo: ";
    cin >> codigo;

    int posicion = BuscarCodigoJuego(codigo);

    if(posicion!=-1)
    {

        system ("cls");

        cout << "Codigo Repetido." << endl;

        return false;

    }

    cout << "Nombre: ";
    cin.ignore();
    cin.getline(nombre,30);


    cout << "Consola: ";
    cin.getline(consola,20);


      strcpy(aux,consola);

      for(int x=0;x<20;x++){

        consola[x] = tolower(aux[x]);


      }

    cout << "Genero: ";
    cin.getline(clasificacion,20);

    cout << "Stock: ";
    cin >> stock;

    if(stock<0)
    {
        system ("cls");

        cout << "Stock menor a 0." << endl;


        return false;
    }

    cout << "Precio: $";
    cin >> precio;
    if(precio<0)
    {
        system ("cls");

        cout << "Precio menor a 0." << endl;

        return false;
    }

    estado = true;

    return true;
}

///////////////////////////////////////////////////////

bool juego::GrabarJuego(int posicion=0){

    /// Si no se le envia ninguna posicion, lo graba normalmente.

    FILE*p;

    if(posicion==0)
    {

        p = fopen("juegos.dat","ab");
        if(p==NULL)
        {
            cout << endl;
            cout << "Error al crear juegos.dat." << endl <<endl;
            return false;
        }

        fwrite(this,sizeof *this,1,p);
        fclose(p);

    }

    /// En caso de que reciba una posicion, busca el juego ya existente y lo graba para modificaciones/eliminacion etc.

    else
    {

        p = fopen ("juegos.dat","rb+");
        if(p==NULL)
        {

            cout << endl;
            cout << "Error al abrir juegos.dat. para modificacion" << endl <<endl;
            return false;

        }

        fseek (p,sizeof*this*posicion,0);

    }

    fwrite (this, sizeof *this,1,p);
    fclose(p);

    return true;


}

int ContarJuegos();


///////////////////////////////////////////////////////

void juego::MostrarJuego(){



    if(estado==true)
    {

        cout << "Codigo: " << codigo << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Consola: " << consola << endl;
        cout << "Clasificacion: " << clasificacion << endl;
        cout << "Stock: " << stock << endl;
        cout << "Precio: $" << precio << endl;
    }

}

///////////////////////////////////////////////////////


bool juego::LeerJuego(int posicion)
{

    FILE*b = fopen ("juegos.dat","rb");

    if(b==NULL)
    {

        return false;
    }

    fseek(b,sizeof*this*posicion,0);
    bool leyo = fread(this,sizeof *this,1,b);
    fclose(b);

    return leyo;



}

///////////////////////////////////////////////////////

int juego::modificarendisco(int posicion)
{

    FILE*p = fopen("juegos.dat","rb+");

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

//////////////////////////////////////////////////////////////////////////

/// Prototipos Funciones ABML

int BajaJuego();
int ModificacionJuego();
void ListarJuegos();
int BuscarCodigoJuego(char*);
void AsignacionVector();
void CargarVector();
int menu_stock();
void MostrarVectorCargado(class juego *v,int cantidad);
void ordenar_preciomenor(juego vec[],int cant);
int menu_precio();

////////////////////////////////////////////////////////////

void ordenar_juegos_stock(juego vecj[],int cant)
{
    juego jue;
    int aux;
    for(int i=0; i<cant-1; i++)
    {
        aux=i;
        for(int j=i+1; j<cant; j++)
        {
            if(vecj[j].getstock()<vecj[aux].getstock())
            {
                aux=j;
            }
        }
        jue=vecj[i];
        vecj[i]=vecj[aux];
        vecj[aux]=jue;
    }

}

////////////////////////////////////

void cargar_vector(juego vecj[],int cant)
{
    FILE *p=fopen("juegos.dat","rb");
    if(p==NULL)
    {
        cout<< "Error al asignar memoria dinamica."<< endl;
        return;

    }

    fread(vecj,sizeof (juego),cant,p);
    fclose(p);
}

////////////////////////////////////

void MostrarJuegos(){

    juego *vecj;
    int cant;
    cant=ContarJuegos();
    vecj=new juego[cant];

    if(vecj==NULL)
    {
        cout<< "Error al asignar memoria dinamica."<< endl;
        return;
    }

    cargar_vector(vecj,cant);
    MostrarVectorCargado(vecj,cant);
    delete(vecj);

}



////////////////////////////////////

void listar_juegos_ordenados()
{
    juego *vecj;
    int cant;
    cant=ContarJuegos();
    vecj=new juego[cant];
    if(vecj==NULL)
    {
        cout<< "Error al asignar memoria dinamica."<< endl;
        return;
    }
    cargar_vector(vecj,cant);
    ordenar_juegos_stock(vecj,cant);
    MostrarVectorCargado(vecj,cant);
    delete(vecj);
}

////////////////////////////////////

void ordenar(juego vec[],int cant)
{
    juego jue;
    int aux;
    for(int i=0; i<cant-1; i++)
    {
        aux=i;
        for(int j=i+1; j<cant; j++)
        {
            if(strcmp(vec[j].getconsola(),vec[aux].getconsola())<0)
            {
                aux=j;
            }
        }
        jue=vec[i];
        vec[i]=vec[aux];
        vec[aux]=jue;
    }

}

////////////////////////////////////

void ordenar_por_consolas()
{
    juego *vec;
    int cant;
    cant=ContarJuegos();
    vec=new juego[cant];
    if(vec==NULL)
    {
        cout<< "Error al asignar memoria dinamica."<< endl;
        return;
    }
    cargar_vector(vec,cant);
    ordenar(vec,cant);
    MostrarVectorCargado(vec,cant);
    delete(vec);
}

////////////////////////////////////

void ordenar_preciomayor(juego vec[],int cant)
{
    juego jue;
    int aux;
    for(int i=0; i<cant-1; i++)
    {
        aux=i;
        for(int j=i+1; j<cant; j++)
        {
            if(vec[j].getprecio()>vec[aux].getprecio())
            {
                aux=j;
            }
        }
        jue=vec[i];
        vec[i]=vec[aux];
        vec[aux]=jue;
    }



}

////////////////////////////////////

void ordenar_por_precio_mayor()
{
    juego *vec;
    int cant;
    cant=ContarJuegos();
    vec=new juego[cant];
    if(vec==NULL)
    {
        cout<< "Error al asignar memoria dinamica."<< endl;
        return;
    }
    cargar_vector(vec,cant);
    ordenar_preciomayor(vec,cant);
    MostrarVectorCargado(vec,cant);
    delete(vec);
}

////////////////////////////////////

void ordenar_por_precio_menor()
{
    juego *vec;
    int cant;
    cant=ContarJuegos();
    vec=new juego[cant];
    if(vec==NULL)
    {
        cout<< "Error al asignar memoria dinamica."<< endl;
        return;
    }
    cargar_vector(vec,cant);
    ordenar_preciomenor(vec,cant);
    MostrarVectorCargado(vec,cant);
    delete(vec);
}

////////////////////////////////////

void ordenar_preciomenor(juego vec[],int cant)
{
    juego jue;
    int aux;
    for(int i=0; i<cant-1; i++)
    {
        aux=i;
        for(int j=i+1; j<cant; j++)
        {
            if(vec[j].getprecio()<vec[aux].getprecio())
            {
                aux=j;
            }
        }
        jue=vec[i];
        vec[i]=vec[aux];
        vec[aux]=jue;
    }
}

////////////////////////////////////

void ordenar_juego(juego vec[],int cant)
{
    juego jue;
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

////////////////////////////////////

void ordenar_por_nombre_juego()
{
    juego *vec;
    int cant;
    cant=ContarJuegos();
    vec=new juego[cant];
    if(vec==NULL)
    {
        cout<< "Error al asignar memoria dinamica."<< endl;
        return;
    }
    cargar_vector(vec,cant);
    ordenar_juego(vec,cant);
    MostrarVectorCargado(vec,cant);
    delete(vec);
}


////////////////////////////////////////////////////////////

int BuscarCodigoJuego(char *cod)
{
    juego gp;
    int pos=0;

    while(gp.LeerJuego(pos))
    {

        if(strcmp(cod, gp.getcodigo())==0)
        {
           if(gp.getestado()==true){
            return pos;
           }
        }

        pos++;
    }

    return -1 ;

}

int BajaJuego()
{
    juego obj;

    char codigo[5];
    int posicion = 0;
    char opc;

    cout << "Ingrese, el codigo del juego que desee dar de baja: ";
    cin >> codigo;

    obj.LeerJuego(0);
    system ("cls");

    while(obj.LeerJuego(posicion)==1)
    {
        if(strcmp(obj.getcodigo(),codigo)==0)
        {

            cout << "Juego encontrado en el archivo." << endl << endl;

            obj.MostrarJuego();
            cout << endl;

            cout << "Esta seguro que desea dar de baja a este Juego? S/N" << endl << endl;
            cout << "OPCION: [ ]\b\b";
            cin >> opc;

            switch (opc)
            {

            case 's':
            case 'S':

                obj.setestado(false);
                obj.modificarendisco(posicion);

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

void ListarJuegos()
{

    juego gp;

    int posicion = 0;

    while(gp.LeerJuego(posicion++)==true)
    {

        gp.MostrarJuego();
        cout << endl;

    }

}


int ModificacionJuego()
{

    juego obj;

    char codigo[5];
    float imp;
    int posicion = 0;
    char opc;

    cout << "Ingrese, codigo de juego a modificar: ";
    cin >> codigo;

    obj.LeerJuego(0);
    system ("cls");

    while(obj.LeerJuego(posicion)==1)
    {
        if(strcmp(obj.getcodigo(),codigo)==0)
        {

            cout << "Juego encontrado en el archivo." << endl << endl;

            obj.MostrarJuego();
            cout << endl;

            cout << "Esta seguro que desea dar de modificar este juego? S/N" << endl << endl;
            cout << "OPCION: [ ]\b\b";
            cin >> opc;

            switch (opc)
            {

            case 's':
            case 'S':

                system ("cls");

                cout << "Ingrese, nuevo importe: ";
                cin >> imp;

                obj.setprecio(imp);
                obj.modificarendisco(posicion);

                system ("cls");

                cout << "Modificado correctamente" << endl;


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

int ContarJuegos()
{

    int cantidad;

    FILE*p = fopen("juegos.dat","rb");

    if(p==NULL)
    {

        cout << "Error" << endl;
    }

    fseek (p,0,2);

    cantidad = ftell(p);

    return cantidad/sizeof(juego);

}

////////////////////////////////////////////////

int ModificarCantidad(int cantidad, char *codigo)
{

    juego obj;

    int posicion = 0;
    int p = 0;
    int total = 0;

    obj.LeerJuego(0);

    while(obj.LeerJuego(posicion)==1)
    {
        if(strcmp(obj.getcodigo(),codigo)==0)
        {

            p = obj.getstock();
            total = p + cantidad;
            obj.setstock(total);
            obj.modificarendisco(posicion);


        }
        posicion++;
    }



}

/////////////////////////////////////////////////////////////////////////////////

void OrdenarPorStockDeMayorAMenor(class juego *v,int cant)
{

    int maximo,x,p, auxiliar;

    juego obj;

    for(int x=0; x<cant-1; x++)
    {

        auxiliar = x;

        for(int p=x+1; p<cant; p++)
        {

            if(v[p].getstock()>v[auxiliar].getstock())
            {

                auxiliar = p ;
            }

        }

        obj = v[x];
        v[x]= v[auxiliar];
        v[auxiliar]=obj;

    }

}


///////////////////////////////////////

void MostrarVectorCargado(class juego*v, int cantidad)
{

    for(int x=0; x<cantidad; x++)
    {

        if(v[x].getestado()==true){

        gotoxy (4,2);
        cout << "Codigo";
        gotoxy (5,x+4);
        cout << v[x].getcodigo();

        gotoxy(13,2);
        cout << "Precio";
        gotoxy(13,x+4);
        cout<< "$" << v[x].getprecio();

        gotoxy(29,2);
        cout << "Nombre";
        gotoxy(25,x+4);
        cout << v[x].getnombre();

        gotoxy(47,2);
        cout<<"Clasificacion";
        gotoxy(45,x+4);
        cout<<v[x].getclasificacion();

        gotoxy(68,2);
        cout<< "Stock";
        gotoxy(67,x+4);
        cout<< v[x].getstock();

        gotoxy(84,2);
        cout << "Consola";
        gotoxy(80,x+4);
        cout<<v[x].getconsola();
        }


    }




    //// Primera Linea

    for (int x=2;x<96;x++){
        gotoxy(x,1);printf("%c",205);

    }


    //// No baja

    for(int x=3;x<96;x++){

        gotoxy(x,3);printf("%c",205);

    }



    /// Bordes

    gotoxy(2,3);printf("%c",204);
    gotoxy(2,2);printf("%c",186);
    gotoxy(2,1);printf("%c",201);

    gotoxy(96,3);printf("%c",185);
    gotoxy(96,2);printf("%c",186);
    gotoxy(96,1);printf("%c",187);

    //// Si baja

    //// Izq Full

    int j;

    for(int k=4; k<2+cantidad+3; k++)
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

 for(int k=4; k<2+cantidad+3; k++)
    {

        gotoxy(78,k);
        printf("%c",186);
    }

    gotoxy(78,1);printf("%c",203);
    gotoxy(78,2);printf("%c",186);
    gotoxy(78,3);printf("%c",206);

    ///////////////

    /// Dni/Nombre

    for(int k=3; k<2+cantidad+3; k++)
    {
        gotoxy(11,k);
        printf("%c",186);
    }

    gotoxy(11,1);printf("%c",203);
    gotoxy(11,2);printf("%c",186);
    gotoxy(11,3);printf("%c",206);

    /////////////

    /// Nombre/Apellido

    for(int k=3; k<2+cantidad+3; k++)
    {
        gotoxy(22,k);
        printf("%c",186);
    }

    gotoxy(22,1);printf("%c",203);
    gotoxy(22,2);printf("%c",186);
    gotoxy(22,3);printf("%c",206);


    /////////////

    /// Apellido/Genero


    for(int k=3; k<2+cantidad+3; k++)
    {
        gotoxy(43,k);
        printf("%c",186);
    }


    gotoxy(43,1);printf("%c",203);
    gotoxy(43,2);printf("%c",186);
    gotoxy(43,3);printf("%c",206);



    /////////////

    /// Genero/Zona

  for(int k=3; k<2+cantidad+3; k++)
    {
        gotoxy(64,k);
        printf("%c",186);
    }


    gotoxy(64,1);printf("%c",203);
    gotoxy(64,2);printf("%c",186);
    gotoxy(64,3);printf("%c",206);


    /////////////

 for(int k=4; k<2+cantidad+3; k++)
    {
        gotoxy(96,k);
        printf("%c",186);
    }



/////////////////////////

 gotoxy(0,20);

}

///////////////////////////////////////

void CargarVector(class juego *v,int cant)
{

    FILE* p = fopen ("juegos.dat","rb");
    if(p==NULL)
    {
        cout << "Error." << endl;
    }

    fread(v,sizeof(juego),cant,p);
    fclose(p);

}

///////////////////////////////////////


void AsignacionVector(int opcion)
{

    juego *v;

    int cantidad = ContarJuegos();

    v = new juego[cantidad];

    if(v==NULL)
    {
        cout << endl;
        cout << "No se pudo asignar memoria." << endl << endl;
    }

    CargarVector (v,cantidad);
    OrdenarPorStockDeMayorAMenor(v,cantidad);
    MostrarVectorCargado(v,cantidad);

    delete v;


}

///////////////////////////////////////////////////////////////////////////

bool ModificarGanancia(){


   ganancia obj;

   char cons [20];
   float porcentaje;
   int posicion = 0;

   gotoxy(50,2);cout << "Ingresar, consola a modificar: ";
   cin.ignore();
   cin.getline(cons,20);

   while(obj.LeerGanancia(posicion)){

        if(strcmp(obj.getconsola(),cons)==0){


            system("cls");
            gotoxy(50,2);cout << "Nuevo porcentaje de ganancia de " << cons << ": ";
            cin >> porcentaje;

            obj.setporcentaje(porcentaje);
            obj.ModificarEnDisco(posicion);

            return true;

        }

    posicion++;

   }



 return false;

}

///////////////////////////////////////////////////////////////////////////

void ListarGanancia(){

   ganancia obj;

   int posicion = 0;

   while(obj.LeerGanancia(posicion++)){

       obj.MostrarPorcentaje();
       cout << endl;


   }


}




/////////////////////////////////////////////////////////////////////////////////

int MenuMostrar()
{

    int OpcionSelec;
    int s;

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
        gotoxy(53,11);
        cout << "<1> Mostrar sin ordenamiento";
        gotoxy(53,12);
        cout << "<2> Por Stock";
        gotoxy(53,13);
        cout << "<3> Por Precio";
        gotoxy(53,14);
        cout << "<4> alfabeticamente por Consola";
        gotoxy(53,15);
        cout << "<5> Ordenado Alfabeticamente por nombre de juego";
        gotoxy(53,17);
        cout << "<0> Volver al Menu Principal";
        gotoxy(75,19);
        cout << "xxxxxxxxxxxxxx";
        gotoxy(53,19);
        cout << "*******************";
        gotoxy(92,19);
        cout << "*******************";

        gotoxy(53,23);
        cout << "\tOPCION: [ ]\b\b";
        cin >> OpcionSelec;
        system ("cls");

        switch (OpcionSelec)
        {

        case 1:

            MostrarJuegos();
            system ("pause");
            system ("cls");
            break;

        case 2:
            menu_stock();
            system ("cls");
            break;

        case 3:

            menu_precio();
            system ("cls");
            break;

        case 4:
            ordenar_por_consolas();
            system ("pause");
            system ("cls");
            break;


        case 5:
            ordenar_por_nombre_juego();
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


//////////////////////////////////////////////////////////////////////////

int MenuProductos ()
{

    juego b;
    mercaderia a;
    ganancia c;

    int OpcionSelec;

    while (true)
    {

        Datos();
        Bordes ();

        gotoxy(75,10);
        cout << "MENU PRODUCTOS";
        gotoxy(53,10);
        cout << "*******************";
        gotoxy(92,10);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Cargar Producto";
        gotoxy(53,13);
        cout << "<2> Mostrar Producto";
        gotoxy(53,14);
        cout << "<3> Modificar Precio";
        gotoxy(53,15);
        cout << "<4> Eliminar Producto";
        gotoxy(53,16);
        cout << "<5> Ingreso Juegos proveedores";
        gotoxy(92,12);
        cout << "<6> Mostrar ingreso proveedores";
        gotoxy(92,13);
        cout << "<7> Porcentaje Ganancia";
        gotoxy(92,14);
        cout << "<8> Modificar Porcentaje G";
         gotoxy(92,15);
        cout << "<9> Listar Porcentaje G";
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

            if(b.CargarJuego()==true)
            {

                if(b.GrabarJuego()==true)
                {

                    system ("cls");
                    cout << "Se ha guardado correctamente." << endl << endl;
                }


            }


            system ("pause");
            system ("cls");
            break;

        case 2:
            MenuMostrar();
            system ("cls");
            break;

        case 3:
            ModificacionJuego();
            system ("pause");
            system ("cls");
            break;

        case 4:
            BajaJuego();
            system ("pause");
            system ("cls");
            break;

        case 5:

            if(a.CargarIngreso()==true){

                    if(a.GuardarIngreso()==true){

                        system ("cls");

                        cout << "Se ha guardado correctamente." << endl << endl;
                    }


            }


            system ("pause");
            system ("cls");

            break;

        case 6:


            MostrarMercaderiaPorAnio();
            system("pause");
            system("cls");

            break;

        case 7:

            if(c.CargarGanancia()==true){

                if(c.GuardarGanancia()==true){

                    system("cls");
                    cout << "Se ha guardado correctamente." << endl << endl;
                }
            }

            system("pause");
            system("cls");
            break;

        case 8:

            if(ModificarGanancia()==true){

                system("cls");

                cout << "Se ha modificado correctamente, la ganancia." << endl << endl;

            }


            system("pause");
            system("cls");

            break;

        case 9:

            DinamicaGanancia();
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

//////////////////////////////////////////////////////////////
int menu_stock()
{
    int OpcionSelec;
    int s;

    while (true)
    {
        Datos();
        Bordes ();

        gotoxy(75,9);
        cout << "MENU STOCK";
        gotoxy(53,9);
        cout << "*******************";
        gotoxy(92,9);
        cout << "*******************";
        gotoxy(53,11);
        cout << "<1> por stock de mayor a menor";
        gotoxy(53,12);
        cout << "<2> Por stock de menor a mayor";
        gotoxy(53,13);
        cout << "<0> Volver al Menu Principal";
        gotoxy(74,19);
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
            AsignacionVector(OpcionSelec);
            system ("pause");
            system ("cls");
            break;

        case 2:
            listar_juegos_ordenados();
            system ("pause");
            system ("cls");
            break;

        case 0:
            return 0;
            break;

        default:

            gotoxy (50,1);
            cout << "Opcion incorrecta, ingrese una opcion valida . . .";

            gotoxy (50,3);
            system ("pause");
            system ("cls");
            break;



        }



    }






}
int menu_precio()
{
    int OpcionSelec;
    int s;

    while (true)
    {
        Datos();
        Bordes ();

        gotoxy(75,9);
        cout << "MENU PRECIOS";
        gotoxy(53,9);
        cout << "*******************";
        gotoxy(92,9);
        cout << "*******************";
        gotoxy(53,11);
        cout << "<1> Por precio de mayor a menor";
        gotoxy(53,12);
        cout << "<2> Por precio de menor a mayor";
        gotoxy(53,13);
        cout << "<0> Volver al Menu Principal";
        gotoxy(74,19);
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
            ordenar_por_precio_mayor();
            system ("pause");
            system ("cls");
            break;

        case 2:
            ordenar_por_precio_menor();
            system ("pause");
            system ("cls");
            break;

        case 0:
            return 0;
            system ("cls");
            break;

        default:

            gotoxy (50,1);
            cout << "Opcion incorrecta, ingrese una opcion valida . . .";

            gotoxy (50,3);
            system ("pause");
            system ("cls");
            break;



        }



    }







}

////////////////////////////////////////////////////////////


#endif // PRODUCTOJUEGO_H_INCLUDED
