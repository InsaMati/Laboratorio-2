#ifndef MERCADERIA_H_INCLUDED
#define MERCADERIA_H_INCLUDED

void ListarDetalleMerca(int);

int BuscarCodigoJuego(char*);
int BuscarProveedor(int);
int BuscarCliente(int);
int ModificarCantidad(int,char*);
int ModificarProveedor(int,int);
int BuscarIDMercaderia();

class DetalleMercaderia
{

private:

    int idmercaderia;
    float importe;
    int cantidad;
    char codigojuego[5];

public:

    bool CargarDetalle(int);
    bool GuardarDetalle();
    void MostrarDetalle();
    bool LeerDetalle(int);
    int getidmercaderia(){return idmercaderia;}
    void setidmercaderia(int id){idmercaderia=id;}
    void setcodigojuego(char *c){strcpy(codigojuego,c);}
    void setcantidad(int cant){cantidad=cant;}

};


//////////////////////////////////////////////////////

bool DetalleMercaderia::CargarDetalle(int id)
{

     char opcion;

     idmercaderia = id;


    while(true){

        ///////////////////////////////////////////

        system("cls");

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

        ////////////////////////////////////////////


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


        //////////////////////////////////////////

        importe = -1;

        while(importe<0){

        cout << "Importe: $";
        cin >> importe;

        if(importe<0){

            cout << "El importe ingresado es menor a 0." << endl << endl;
            system("pause");
            system("cls");

             }


        }

        //////////////////////////////////////////

        cout << "¿Desea ingresar mas productos? (S/N)" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        ModificarCantidad(cantidad,codigojuego);
        GuardarDetalle();


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

}
/////////////////////////////////////////////////////

bool DetalleMercaderia::GuardarDetalle()
{

    FILE*p = fopen("detallemercaderia.dat","ab");

    if(p==NULL)
    {
        return false;
    }


    fwrite(this,sizeof*this,1,p);

    fclose(p);

    return true;

}

///////////////////////////////////////

void DetalleMercaderia::MostrarDetalle()
{



    cout << "Codigo Juego: " << codigojuego << endl;
    cout << "Cantidad: " << cantidad << endl;

}


///////////////////////////////////////

bool DetalleMercaderia::LeerDetalle(int posicion)
{

    FILE* p = fopen ("detallemercaderia.dat","rb");

    if(p==NULL)
    {
        cout << "No se pudo abrir el archivo en rb";
        return false;
    }

    fseek(p,sizeof*this*posicion,0);

    bool leeme = fread(this,sizeof*this,1,p);

    fclose(p);

    return leeme;

}

/////////////////////////////////////////////////////

void ListarPorIdMerca(int id)
{

    DetalleMercaderia Ryze;

    int posicion = 0;

    while(Ryze.LeerDetalle(posicion++))
    {

        if(id==Ryze.getidmercaderia())
        {

            Ryze.MostrarDetalle();

        }


    }

}

//////////////////////////////////////////

class mercaderia
{

private:

    int idmercaderia;
    int numeroprove;
    fecha ingreso;
    int FormaDePago;

public:

    bool CargarIngreso();
    bool GuardarIngreso();
    void MostrarMerca();
    bool LeerMerca(int);
    int getidmercaderia(){return idmercaderia;}
    fecha getfecha(){return ingreso;}


};


//////////////////////////////////////////

int BuscarIDMercaderia()
{
    mercaderia obj;
    int mayorid = 0;

    FILE* p = fopen("mercaderia.dat","rb");
    if(p==NULL)
    {
        return mayorid+1;
    }

    while(fread(&obj,sizeof(mercaderia),1,p)==1)
    {

        if(obj.getidmercaderia()>mayorid)
        {

            mayorid = obj.getidmercaderia();
        }

    }


    return mayorid +1;
}

//////////////////////////////////////////

bool mercaderia::CargarIngreso()
{

    DetalleMercaderia Ryze;

    char opcion;

    idmercaderia = BuscarIDMercaderia();

    cout << "Numero de Proveedor: ";
    cin >> numeroprove;

    if(BuscarProveedor(numeroprove)==-1)
    {
        cout << endl;
        cout << "El numero de proveedor, no existe en el archivo proveedores.dat" << endl << endl;
        return false;

    }

    cout << endl;

    cout << "Fecha de ingreso" << endl;
    int x = ingreso.cargar();

    if(x==0)
    {

        system ("cls");

        cout << "Fecha invalida." << endl;

        return false;
    }



    cout << endl;
    cout << "Forma de pago (1 a 3) " << endl << endl;
    cout << "<1> Debito <2> Efectivo <3> Credito" << endl;

    cout << "Opcion: ";
    cin >> FormaDePago;


    if(FormaDePago<1 || FormaDePago >3)
    {

        system("cls");

        cout << "La forma de pago no es valida." << endl << endl;

        return false;
    }


    if(Ryze.CargarDetalle(idmercaderia)==false){


    }

  ////////////////////////////////////////////

return true;

}

/////////////////////////////////////////////


bool mercaderia::GuardarIngreso()
{

    FILE*p = fopen("mercaderia.dat","ab");

    if(p==NULL)
    {
        return false;
    }

    fwrite(this,sizeof*this,1,p);
    fclose(p);

    return true;

}

/////////////////////////////////////////////

void mercaderia::MostrarMerca()
{

    cout << "ID Mercaderia: " << getidmercaderia() << endl;
    cout << "ID Proveedor: " << numeroprove << endl;
    cout << "Forma de pago: " << FormaDePago << endl;
    cout << "Fecha Ingreso: " << ingreso.getdia() << "/" << ingreso.getmes() << "/" << ingreso.getanio() << endl;

    ListarDetalleMerca(idmercaderia);

    cout << "-------------------------------------------------------";

}


/////////////////////////////////////////////

bool mercaderia::LeerMerca(int posicion)
{

    FILE* p = fopen("mercaderia.dat","rb");

    if(p==NULL)
    {
        return false;
    }

    fseek(p,sizeof*this*posicion,0);

    bool leeme = fread(this,sizeof*this,1,p);

    fclose(p);

    return leeme;



}

////////////////////////////////////////////////


void ListarDetalleMerca(int id){

    DetalleMercaderia obj;

    int posicion = 0;


    while(obj.LeerDetalle(posicion++)){

        if(obj.getidmercaderia()==id){


            obj.MostrarDetalle();


        }
    }


}


////////////////////////////////////////////////

void MostrarMercaderiaPorAnio(){

    int anio;

    mercaderia obj;
    int posicion = 0;

    cout << "Ingrese anio: ";
    cin >> anio;

    cout << endl;

    cout << "-------------------------------------------------------" << endl;

    while(obj.LeerMerca(posicion++)){

        if(obj.getfecha().getanio()==anio){

            obj.MostrarMerca();
            cout << endl;
        }

    }


}


////////////////////////////////////////////////



#endif // MERCADERIA_H_INCLUDED
