#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED


////////////////////////////////////////////////////////////

class Error{

 private:
     char codigo[5];
     int cantidad;

 public:

    bool Leer(int);
    bool Guardar();
    char *getcodigo(){return codigo;}
    int getcantidad(){return cantidad;}
    void setcodigo(char *c){strcpy(codigo,c);}
    void setcantidad(int cant){cantidad = cant;}

};

////////////////////////////////////////////////////////////


bool Error::Guardar(){

  FILE*p = fopen ("Error.dat","ab");

  if(p==NULL){return false;}

  fwrite(this,sizeof*this,1,p);

  fclose(p);

  return true;

}

////////////////////////////////////////////////////////////

bool Error::Leer(int posicion){

FILE*p = fopen ("Error.dat","rb");

  if(p==NULL){return false;}

  fseek(p,sizeof*this*posicion,0);

  bool leeme = fread(this,sizeof*this,1,p);

  fclose(p);

  return leeme;
}
////////////////////////////////////////////////////////////

class detalle_venta{

private:

    int idventa;
    char codigojuego[5];
    int cantidad;
    float importe;
    bool estado = true;


public:

    bool CargarDetalleVenta(int);
    bool LeerDetalleVenta(int);
    void MostrarDetalleVenta();
    bool GuardarDetalleVenta();

    /// Getters

    int getidventa(){return idventa;}
    char *getcodigojuego(){return codigojuego;}
    int getcantidad(){return cantidad;}
    float getimporte(){return importe;}

    /// Setters

    void setidventa(int id){idventa = id;}
    void setcodigojuego(char* cod){strcpy(codigojuego,cod);}
    void setcantidad(int cant){cantidad = cant;}
    void setimporte(float p ){importe = p;}
    void setestado(bool b){estado = b;}
    int ModificarEnDisco(int);

};


///////////////////////////////////////////////////////////

int buscar_cantidad_stock(char *cod,int cant){
juego ju;
FILE *p=fopen("juegos.dat","rb");
if(p==NULL){
    cout<< "error."<< endl;
    return -1;
}
while(fread(&ju,sizeof (juego),1,p)){
    if(strcmp(ju.getcodigo(),cod)==0){
        if(ju.getstock()>=cant){
            return 1;
        }
    }
}
fclose(p);
return -1;
}

///////////////////////////////////////////////////////////

void VentaRestarStock(int cantidad, char *cod){

    juego obj;

    int posicion = 0;
    float m;

    while(obj.LeerJuego(posicion)){

        if(strcmp(obj.getcodigo(),cod)==0){

            obj.setstock(obj.getstock()-cantidad);
            obj.modificarendisco(posicion);


        }

    posicion++;

    }

}

///////////////////////////////////////////////////////

void SumarStockError(char *codigo,int cantidad){

    juego ekko;

    int posicion = 0;

    while(ekko.LeerJuego(posicion)){

        if(strcmp(ekko.getcodigo(),codigo)==0){

            ekko.setstock(ekko.getstock()+cantidad);
            ekko.modificarendisco(posicion);


        }

        posicion++;

    }


}

///////////////////////////////////////////////////////

void ErrorDeVenta(){

    Error obj;

    int posicion = 0;

    while(obj.Leer(posicion++)){

            SumarStockError(obj.getcodigo(),obj.getcantidad());

    }

    FILE*p = fopen("Error.dat","wb");

}

////////////////////////////////////////////////////////////

int detalle_venta::ModificarEnDisco(int posicion)
{

    FILE*p = fopen("detalleventa.dat","rb+");

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

///////////////////////////////////////////////////////////

void CambiarEstado(int idventa){

   detalle_venta obj;

   int posicion = 0;

   while(obj.LeerDetalleVenta(posicion)){

        if(idventa==obj.getidventa()){

            obj.setestado(false);
            obj.ModificarEnDisco(posicion);

        }

        posicion++;


   }


}

//////////////////////////////////////////////////////

float RetornarPorcentaje(char *consola){

   ganancia obj;

   int posicion = 0;

   while(obj.LeerGanancia(posicion++)){

         if(strcmp(obj.getconsola(),consola)==0){


            return obj.getporcentaje();

         }

   }


   return 15;

}

//////////////////////////////////////////////////////

float BuscarConsola(char *codigojuego){

  juego obj;

  int posicion = 0;

  while(obj.LeerJuego(posicion++)){

       if(obj.getestado()==true){

       if(strcmp(obj.getcodigo(),codigojuego)==0){

            return RetornarPorcentaje(obj.getconsola());

       }

       }


  }



}


//////////////////////////////////////////////////////

float RetornarPrecio(char *codigojuego){

  juego obj;

  int posicion = 0;

  while(obj.LeerJuego(posicion++)){

       if(obj.getestado()==true){

       if(strcmp(obj.getcodigo(),codigojuego)==0){


            return obj.getprecio();

       }

       }


  }


}



//////////////////////////////////////////////////////

bool detalle_venta::CargarDetalleVenta(int id){


    float p,j;
    float PorUnidad;

    Error obj;

    char opcion;

    while(true){

    idventa = id;

        int f = -1;

        while(f==-1){

            cout << "Codigo: ";
            cin >> codigojuego;

            f = BuscarCodigoJuego(codigojuego);

            if(f==-1){

                cout << endl;
                cout << "El codigo de juego, no existe en el archivo juegos.dat" << endl << endl;
                system("pause");
                system("cls");
            }

        }

        j = BuscarConsola(codigojuego);

        p = RetornarPrecio(codigojuego);

        PorUnidad = j * p / 100 + p;

    ////////////////////////////////////////

        cantidad = -1;

        while(cantidad<0){

        cout << "Cantidad: ";
        cin >> cantidad;

        if(cantidad<0){

            cout << endl;
            cout << "La cantidad ingresada es menor a 0." << endl << endl;
            system("pause");
            system("cls");

             }



        }


    ///////////////////////////////////

    if(buscar_cantidad_stock(codigojuego,cantidad)==-1){


    system("cls");
    cout << "La cantidad solicitada, no se encuentra disponible.... --- STOCK INSUFICIENTE ----." << endl << endl;
    ErrorDeVenta();
    CambiarEstado(idventa);
    return false;}

    else{

    obj.setcodigo(codigojuego);
    obj.setcantidad(cantidad);
    obj.Guardar();
    VentaRestarStock(cantidad,codigojuego);
    }

    ////////////////////////////////////

    importe = PorUnidad * cantidad;

    cout << endl;

    cout << "Por Unidad: $" << PorUnidad << endl;
    cout << "Importe: $" << importe << endl << endl;


    cout << "¿Desea ingresar mas productos? (S/N)" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    setidventa(idventa);
    setcodigojuego(codigojuego);
    setimporte(importe);
    setcantidad(cantidad);
    GuardarDetalleVenta();

    switch(opcion){

    case 'S':
    case 's':

        system("cls");

    break;

    case 'n':
    case 'N':

        return true;

    break;

    default:

        system("cls");
        cout << "Opcion incorrecta." << endl << endl;

        break;



    }

    }

  return true;

}

////////////////////////////////////////////////////////////

bool detalle_venta::GuardarDetalleVenta(){

FILE*p = fopen("detalleventa.dat","ab");

if(p==NULL){

    cout << "Error en la creacion del archivo, detalleventa.dat" << endl << endl;

    return false;
}

fwrite(this,sizeof*this,1,p);

fclose(p);

return true;

}

////////////////////////////////////////////////////////////

void detalle_venta::MostrarDetalleVenta(){


if(estado==true){
cout << "Codigo juego: " << codigojuego << endl;
cout << "Importe: $" << importe << endl;
cout << "Cantidad: " << cantidad << endl;}

}

////////////////////////////////////////////////////////////

bool detalle_venta::LeerDetalleVenta(int posicion){

    FILE*p = fopen ("detalleventa.dat","rb");

    if(p==NULL){


        cout << "Error al abrir detalleventa.dat en modo lectura." << endl << endl;

        return false;
    }

    fseek(p,sizeof*this*posicion,0);

    bool leeme = fread(this,sizeof*this,1,p);

   fclose(p);

   return leeme;

}

////////////////////////////////////////////////////////////

void ListarDetalle(int idventa){

   detalle_venta obj;

   int posicion = 0;

   while(obj.LeerDetalleVenta(posicion++)){

    if(idventa==obj.getidventa()){

        obj.MostrarDetalleVenta();
        cout << endl;
    }

   }



}

////////////////////////////////////////////////////////////

class venta{

private:

    int idventa;
    int idempleado;
    int idcliente;
    fecha DeVenta;
    int FormaDePago;

public:

    bool CargarVenta();
    bool GuardarVenta();
    bool LeerVenta(int);
    void MostrarVenta();

    ///////////

    int getidventa(){return idventa;}
    int getidempleado(){return idempleado;}
    int getidcliente(){return idcliente;}
    fecha getfechaventa(){return DeVenta;}
    int  getFormaDePago(){return FormaDePago;}

};


////////////////////////////////////////////////////////////

int BuscarMaxId(){

   venta obj;

   int idventa = 0;
   int posicion = 0;

   while(obj.LeerVenta(posicion++)){


    if(obj.getidventa()>idventa){

        idventa = obj.getidventa();

    }
}

return idventa +1;

}

void retornar_empleado(int id){
empleado obj;
FILE *p=fopen("empleado.dat","rb");
if(p==NULL){
    cout<< "error.";
    return;
    }
while(fread(&obj,sizeof(empleado),1,p)){

        if(obj.getidempleado()==id){
        obj.MostrarEmpleado();
        fclose(p);

        }


    }
fclose(p);
}

void retornar_cliente(int id){
cliente obj;
FILE *p=fopen("cliente.dat","rb");
if(p==NULL){
    cout<< "error.";
    return;
    }
while(fread(&obj,sizeof(cliente),1,p)){

        if(obj.getidcliente()==id){
        obj.MostrarCliente();
        fclose(p);
        }
}
fclose(p);
}

///////////////////////////////////////////////////////////

bool venta::CargarVenta(){
   empleado emp;
   cliente cli;
   juego ju;
   detalle_venta obj;
   int c=0;
   char opc;

    idventa = BuscarMaxId();

    cout << "Id Venta: " << idventa << endl << endl;

    cout << "Id Empleado: ";
    cin >> idempleado;

    if(BuscarIDempleado(idempleado)==-3){

        system("cls");
        cout << "No existe este id de empleado." << endl << endl;
        return false;
    }
    retornar_empleado(idempleado);
    cout<< "es el empleado que desea para esta venta? "<< endl;
    cout<< "s)si     n)no"<<endl;
    cin>> opc;
    switch(opc){
case 's':
    system("cls");
    break;
    case 'S':
        system("cls");
    break;
    case 'n':
        cout<< "venta cancelada."<< endl;
        return false;
    break;
    case 'N':
        cout<< "venta cancelada."<< endl;
        return false;
    break;
}

    cout << "Id Cliente: ";
    cin >> idcliente;

    if(BuscarCliente(idcliente)==-1){

        system("cls");

        cout << "No existe este id de cliente." << endl << endl;

        return false;

    }
retornar_cliente(idcliente);
   cout<< "es el cliente que desea para esta venta? "<< endl;
    cout<< "s)si     n)no"<<endl;
    cin>> opc;
    switch(opc){
case 's':
    system("cls");
    break;
    case 'S':
        system("cls");
    break;
    case 'n':
        cout<< "venta cancelada."<< endl;
        return false;
    break;
    case 'N':
        cout<< "venta cancelada."<< endl;
        return false;
    break;
}
    system("cls");

    cout << "Forma De Pago: " << endl;
    cout << "<1> Debito <2> Efectivo <3> Credito" << endl << endl;
    cout << "Opcion: ";
    cin >> FormaDePago;

    if(FormaDePago<1 || FormaDePago >3){
        cout<< "Forma de pago invalida, por favor verifique los datos que ingreso."<< endl;
        return false;
    }

    system("cls");

    cout << "Fecha de venta: " << endl << endl;
    if(DeVenta.cargar()==0){

            system("cls");

            cout << "Fecha invalida." << endl;

             return false;

    }

    system("cls");

    if(obj.CargarDetalleVenta(idventa)==false){

        return false;
    }


   return true;
}


///////////////////////////////////////////////////////////

bool venta::GuardarVenta(){

    FILE*p = fopen("venta.dat","ab");

    if(p==NULL){

        cout << "Error al crear venta.dat" << endl << endl;

        return false;
    }

    fwrite(this,sizeof*this,1,p);

    fclose(p);

    return true;

}

///////////////////////////////////////////////////////////

bool venta::LeerVenta(int posicion){

    FILE*p = fopen("venta.dat","rb");

    if(p==NULL){


        return false;
    }

    fseek(p,sizeof*this*posicion,0);

    bool leeme = fread(this,sizeof*this,1,p);

    fclose(p);

    return leeme;

}

///////////////////////////////////////////////////////////

void venta::MostrarVenta(){

    cout << "Id venta: " << idventa << endl;
    cout << "Id Empleado: " << idempleado << endl;
    cout << "Id Cliente: " << idcliente << endl;
    cout << "Forma de Pago: " << FormaDePago << endl;
    cout << "Fecha de venta: " << DeVenta.getdia() << "/" << DeVenta.getmes() << "/" << DeVenta.getanio() << endl << endl;

    ListarDetalle(idventa);

    cout << "-------------------------------------------------------";


}

///////////////////////////////////////////////////////////

void ListarVenta(){

  venta obj;

  int posicion = 0;

  int anio;


  cout << "Ingrese anio: ";
  cin >> anio;
  system("cls");

  cout << "-------------------------------------------------------" << endl;

  while(obj.LeerVenta(posicion++)){

  if(obj.getfechaventa().getanio()==anio){


    obj.MostrarVenta();
    cout << endl;}

  }

}

////////////////////////////////////////////////////////////

bool VerificarIdVenta(int id){

   venta obj;
   int posicion = 0;

   while(obj.LeerVenta(posicion++)){

    if(obj.getidventa()==id){

        return true;
    }

   }


return false;

}

////////////////////////////////////////////////////////////

int ContarVentas(){

   int c;

   FILE* p = fopen ("venta.dat","rb");

   if(p==NULL){

      cout << "Error." << endl << endl;
   }

   fseek(p,0,2);

   c = ftell(p);

   return c/sizeof(venta);

}

///////////////

void CargarVectorVenta(venta *v, int cantidad){

    FILE* p = fopen ("venta.dat","rb");

    if(p==NULL){
        cout << "Error." << endl << endl;
    }

    fread(v,sizeof(venta),cantidad,p);
    fclose(p);

}

///////////////

int BuscarIdVenta(venta *v,int cantidad,int id){

    for(int x=0;x<cantidad;x++){

            if(v[x].getidventa()==id){

                return x;
            }

    }

}

///////////////

void MostrarVectorVenta(venta *v,int cantidad){

    for(int x=0;x<cantidad;x++){

       cout << v[x].getidventa() << endl;
       cout << v[x].getidcliente() << endl;


    }


}

///////////////

void DinamicaDetalleVenta(int);
void BordesFactura(venta*,int,detalle_venta*,int,int);



int ContarDetalles(){

    int cantidad;

    FILE*p = fopen ("detalleventa.dat","rb");

    if(p==NULL){return -1;}

    fseek(p,0,2);

    cantidad = ftell(p);

    fclose(p);

    return cantidad/sizeof(detalle_venta);

}

void CargarDetalle(detalle_venta *v, int total){

    FILE*p = fopen ("detalleventa.dat","rb");

    if(p==NULL){cout << "No se pudo abrir detalleventa.dat en la funcion CargarDetalle." << endl << endl;}

    fread(v,sizeof(detalle_venta),total,p);

    fclose(p);


}

////////////

void EsconderCursor();

void Imprimiendo(){


    float porce = 0;

    gotoxy(10,1);cout << "Buscando Factura: ";

    /// Como cambiar solo esta linea de color
    /// system ("color 2");
    /// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),VARIABLE);
    /// TextColor();

    gotoxy(10,2);cout << "Cargando: %";

    EsconderCursor();

    for(int x=0;x<10;x++){


        Sleep(120);
        gotoxy(30,1);cout << "*";
        Sleep(120);
        gotoxy(30,1);cout << " ";
        gotoxy(31,1);cout << " *";
        Sleep(120);
        gotoxy(32,1);cout << "  *";
        Sleep(120);
        gotoxy(33,1);cout << "   *";
        Sleep(120);
        gotoxy(34,1);cout << "    *";
        Sleep(120);
        gotoxy(35,1);cout << "     ";

        porce+=10;

        gotoxy(21,2);cout<<porce;



    }
    system("cls");



}

///////////

bool DinamicaVenta(){

    venta *v;

    int id;

    int r;

    int cantidad = ContarVentas();

    v = new venta [cantidad];

    if(v==NULL){

        cout << "No se pudo asignar memoria dinamicamente en vector vecta." << endl << endl;
    }

    CargarVectorVenta(v,cantidad);

    gotoxy(10,1);cout << "Id Venta: ";
    cin >> id;

    system("cls");

    Imprimiendo();

    if(VerificarIdVenta(id)==false){
        system("cls");
        gotoxy(10,1);cout << "Factura no encontrada.";
        gotoxy(10,3);cout << "Error 404.";
        gotoxy(10,5);

        return false;
    }

    r = BuscarIdVenta(v,cantidad,id);
    ///MostrarVectorVenta(v,cantidad);

    ///////////////////////////////////////

    detalle_venta *ve;

    int cant = ContarDetalles();

    ve = new detalle_venta [cant];

    if(ve==NULL){

        cout << "No se pudo asignar memoria de manera dinamica." << endl << endl;
    }

    CargarDetalle(ve,cant);

    BordesFactura(v,r,ve,cant,id);

}


///////////////////////////////////////////////////////////

string RetornarNombreCliente(int id){

    cliente obj;

    int posicion = 0;

    while(obj.LeerDisco(posicion++)){

            if(obj.getidcliente()==id){

                return obj.getnombre();
            }

    }

}

string RetornarApellidoCliente(int id){


    cliente obj;

    int posicion = 0;

    while(obj.LeerDisco(posicion++)){

            if(obj.getidcliente()==id){

                return obj.getapellido();
            }

    }



}

string RetornarDireccion(int id){

     cliente obj;

    int posicion = 0;

    while(obj.LeerDisco(posicion++)){

            if(obj.getidcliente()==id){

                return obj.getdireccion();
            }

    }



}

string RetornarZona(int id){


       cliente obj;

    int posicion = 0;

    while(obj.LeerDisco(posicion++)){

            if(obj.getidcliente()==id){

                return obj.getzona();
            }

    }



}

int RetornarDni(int id){

    cliente obj;

    int posicion = 0;

    while(obj.LeerDisco(posicion++)){

            if(obj.getidcliente()==id){

                return obj.getdni();
            }

    }


}

void AgregarVencimiento(int *f){

    if(f[1]==12){

        f[1]==1;
        f[2]+=1;

    }

    else{

    f[1]+=1;}

}

///////

string RetornarNombreJuego (char *c){

    juego obj;

    int posicion = 0;

    while(obj.LeerJuego(posicion++)){

        if(strcmp(obj.getcodigo(),c)==0){

            return obj.getnombre();

        }

    }

}

///////////////////////////////////////////////////////////

void BordesFactura(venta *v,int pos,detalle_venta *detalle,int TotalDetalles,int iden){

    /////////////////////////////////

    ///// Variables

    /// Id para mostrar
    int id;
    /// Dia, mes, año
    int d,m,a;
    /// Fec guarda dia, mes y año
    int fec[3]={0};
    /// Acumula el importe de los juegos.
    float total = 0;

    //// Encabezado

    gotoxy(1,0);printf("%c",201);
    gotoxy(90,0);printf("%c",187);

    for(int x=2;x<90;x++){
        gotoxy(x,0);printf("%c",205);
    }

    gotoxy(1,1);printf("%c",186);
    gotoxy(90,1);printf("%c",186);

    gotoxy(1,2);printf("%c",204);
    gotoxy(90,2);printf("%c",185);

    for(int j=2;j<90;j++){

    gotoxy(j,2);printf("%c",205);

    }

    gotoxy(3,1);cout << "Tipo: FACTURA A";


    gotoxy(73,1);cout << "Remito: 000000"<< v[pos].getidventa();

    d =  v[pos].getfechaventa().getdia();
    m = v[pos].getfechaventa().getmes();
    a = v[pos].getfechaventa().getanio();

    fec[0]=d;
    fec[1]=m;
    fec[2]=a;

    gotoxy(53,1);cout << "Fecha: " << d << "/" << m << "/" << a;

    ////////////////////////////////////

    //// Cliente

    for(int w=3;w<30;w++){

            gotoxy(1,w);printf("%c",186);
            gotoxy(90,w);printf("%c",186);

    }

    for(int h=2;h<90;h++){

        gotoxy(h,30);printf("%c",205);

    }

    gotoxy(1,30);printf("%c",200);

    gotoxy(90,30);printf("%c",188);



    gotoxy(3,3);cout << "Datos del Cliente: ";

    id = v[pos].getidcliente();

    gotoxy(3,5);cout << id;
    gotoxy(7,5);cout <<  RetornarApellidoCliente(id) << " " << RetornarNombreCliente(id);
    gotoxy(3,7);cout << RetornarDireccion(id);
    gotoxy(20,7);cout << RetornarZona(id);

    gotoxy(66,5);cout << "Cuilt: 27-" << RetornarDni(id) << "-20";

    AgregarVencimiento(fec);

    gotoxy(66,7);cout << "Vencimiento: " << fec[0] << "/" << fec[1] << "/" << fec[2];

    for(int x=2;x<90;x++){

        gotoxy(x,8);printf("%c",205);
    }

    ////////////////////////////////////

    for(int x=0;x<TotalDetalles;x++){

            //// en la posicion de Y, va bajando dependiendo de la posicion del for con X
            //// Intentar arreglar los espacios en blanco.

    if(detalle[x].getidventa()==iden){

    gotoxy(3,9);cout << "Codigo";
    gotoxy(3,11+x);cout<< detalle[x].getcodigojuego();

    gotoxy(12,9);cout << "Descripcion";

    gotoxy(12,11+x);cout << RetornarNombreJuego(detalle[x].getcodigojuego());

    gotoxy(34,9);cout<< "Cantidad";
    gotoxy(36,11+x);cout<< detalle[x].getcantidad();

    gotoxy(48,9);cout<< "Precio";
    gotoxy(48,11+x);cout<< "$" << detalle[x].getimporte()/detalle[x].getcantidad();

    total+=detalle[x].getimporte();

    gotoxy(66,9);cout<< "Importe";
    gotoxy(66,11+x);cout<< "$"<<detalle[x].getimporte();

    gotoxy(58,9);cout<< "Desc";
    gotoxy(58,11+x);cout<< "0000";

    }

    }

    gotoxy(80,9);cout<< "Total";
    gotoxy(80,29);cout<< "$" << total;




    //// Bordes Codigo

    for(int x=2;x<90;x++){

        gotoxy(x,10);printf("%c",196);
    }

    //// Entre Codigo/Descripcion.

    for(int x=9;x<30;x++){

        gotoxy(10,x);printf("%c",179);
    }

    //// Entre Descrpcion/Cantidad

    for(int x=9;x<30;x++){

        gotoxy(32,x);printf("%c",179);
    }

    //// Entre Cantidad/Precio

    for(int x=9;x<30;x++){

        gotoxy(45,x);printf("%c",179);
    }

    //// Entre Precio/Desc

    for(int x=9;x<30;x++){

        gotoxy(56,x);printf("%c",179);
    }

    //// Entre Desc/Importe

    for(int x=9;x<30;x++){

        gotoxy(64,x);printf("%c",179);
    }

    ////

    for(int x=9;x<30;x++){

        gotoxy(78,x);printf("%c",179);
    }

    gotoxy(1,43);


}


///////////////////////////////////////////////////////////

int MenuVentas()
{
    venta obj;

    int OpcionSelec;

    while (true)
    {

        Datos();
        Bordes ();

        gotoxy(77,9);
        cout << "MENU VENTA";
        gotoxy(92,9);
        cout << "*******************";
        gotoxy(53,9);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Cargar Venta";
        gotoxy(53,13);
        cout << "<2> Listar Ventas";
        gotoxy(53,14);
        cout << "<3> Factura (Prueba)";
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

        switch(OpcionSelec){

    case 1:

        if(obj.CargarVenta()==true){

            if(obj.GuardarVenta()==true){

                system("cls");
                cout << "Se ha guardado correctamente, la venta." << endl << endl;
            }

        }

        system("pause");
        system("cls");
        break;

    case 2:

        ListarVenta();
        system("pause");
        system("cls");
        break;

    case 3:
        DinamicaVenta();
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




#endif // VENTA_H_INCLUDED
