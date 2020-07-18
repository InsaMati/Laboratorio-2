#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

int ContarClientes();

class cliente : public persona
{

private:

    int idcliente;
    char direccion[100];
    char gmail[100];
    bool estado;

public:

    bool CargarCliente();
    bool GuardarCliente();
    void MostrarCliente();
    bool LeerDisco(int);
    int modificarEnDisco(int);


    /// Getters

    int getidcliente(){return idcliente;}
    char *getdireccion(){return direccion;}
    char *getgmail(){return gmail;}
    char *getnombre(){return nombre;}
    char *getapellido(){return apellido;}
    bool getestado(){return estado;}

    /// Setters

    void setidcliente (int i){idcliente = i;}
    void setdireccion (char *d){strcpy(direccion,d);}
    void setgmail(char *g){strcpy(gmail,g);}
    void setnombre (char *n){strcpy(nombre,n);}
    void setapellido (char *a){strcpy(apellido,a);}
    void setestado (bool e){estado = e;}

};

bool cliente::CargarCliente()
{

    cout << "ID Cliente: ";
    cin >> idcliente;

    if(idcliente<0){

       system("cls");

       cout << "Id cliente, menor a 0." << endl << endl;

        return false;
    }
    if(BuscarCliente(idcliente)>=0){
        cout<< "cliente repetido."<< endl;
        return false;
    }

    if(CargarPersona()==false){

        return false;
    }

    cout << "Direccion: ";
    cin.getline(direccion,100);
    if(direccion<0){
        cout<< "direccion invalida."<< endl;;
        return false;
    }
    cout << "Gmail: ";
    cin >> gmail;
    if(gmail<0){
        cout<< "gmail invalido."<< endl;;
        return false;
    }

    estado = true;

    return true;

}

bool cliente::GuardarCliente()
{

    FILE*p = fopen("cliente.dat","ab");

    if(p==NULL)
    {
        cout << endl;
        cout << "Error al crear cliente. dat" << endl;
        return false;
    }

    fwrite(this,sizeof *this,1,p);
    fclose(p);

    return true;

}

void cliente::MostrarCliente()
{

    if(estado==true)
    {

        cout << "Id Cliente: " << idcliente << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Apellido: " << apellido << endl;
        cout << "Genero: "   << genero << endl;
        cout << "Zona: "     << zona << endl;
        cout << "Direccion: " << direccion << endl;
        cout << "Gmail: " << gmail << endl;


    }

}

bool cliente::LeerDisco(int posicion)
{

    FILE*b = fopen ("cliente.dat","rb");

    if(b==NULL)
    {

        return false;
    }



    fseek(b,sizeof*this*posicion,0);
    bool leyo = fread(this,sizeof*this,1,b);
    fclose(b);

    return leyo;



}

int cliente::modificarEnDisco(int posicion)
{
    FILE*p = fopen ("cliente.dat","rb+");

    if(p==NULL)
    {

        return false;
    }

    fseek(p,sizeof*this*posicion,0);
    fwrite(this,sizeof*this,1,p);
    fclose(p);

}
//////////////////////////////

void CargarVectorCliente(cliente *vec,int cantidad){

    FILE*p = fopen ("cliente.dat","rb");

    if(p==NULL){
        cout << "Error al abrir cliente.dat en funcion void CargarVectorCliente." << endl << endl;
    }

    fread(vec,sizeof(cliente),cantidad,p);
    fclose(p);

}

//////////////////////////////

void BordesArriba(){

    gotoxy(2,0);printf("%c",201);
    gotoxy(2,1);printf("%c",186);

    gotoxy(160,0);printf("%c",187);
    gotoxy(160,1);printf("%c",186);

     for(int x=3;x<160;x++){

        gotoxy(x,0);printf("%c",205);

    }

        gotoxy(10,1);printf("%c",186);
        gotoxy(22,1);printf("%c",186);
        gotoxy(43,1);printf("%c",186);
        gotoxy(64,1);printf("%c",186);
        gotoxy(78,1);printf("%c",186);
        gotoxy(96,1);printf("%c",186);
        gotoxy(125,1);printf("%c",186);

        gotoxy(10,0);printf("%c",203);
        gotoxy(22,0);printf("%c",203);
        gotoxy(43,0);printf("%c",203);
        gotoxy(64,0);printf("%c",203);
        gotoxy(78,0);printf("%c",203);
        gotoxy(96,0);printf("%c",203);
        gotoxy(125,0);printf("%c",203);


}


//////////////////////////////

void MostrarVectorCliente(cliente *vec,int cantidad){

    for(int x=0;x<cantidad;x++){

        if(vec[x].getestado()==true){

        gotoxy (5,1);
        cout << "ID";
        gotoxy (5,x+3);
        cout << vec[x].getidcliente();

        gotoxy(15,1);
        cout << "Dni";
        gotoxy(13,x+3);
        cout << vec[x].getdni();

        gotoxy(29,1);
        cout << "Nombre";
        gotoxy(25,x+3);
        cout<<vec[x].getnombre();

        gotoxy(50,1);
        cout<<"Apellido";
        gotoxy(45,x+3);
        cout<<vec[x].getapellido();

        gotoxy(68,1);
        cout<< "Genero";
        gotoxy(67,x+3);
        cout<< vec[x].getgenero();

        gotoxy(85,1);
        cout << "Zona";
        gotoxy(80,x+3);
        cout<< vec[x].getzona();

        gotoxy(106,1);
        cout << "Direccion";
        gotoxy(99,x+3);
        cout<< vec[x].getdireccion();


        gotoxy(140,1);
        cout << "Gmail";
        gotoxy(130,x+3);cout << vec[x].getgmail();

                         }

    }

    BordesArriba();


    //// No baja

    for(int x=2;x<160;x++){

        gotoxy(x,2);printf("%c",205);

    }

    gotoxy(2,2);printf("%c",204);

    gotoxy(160,2);printf("%c",185);

    gotoxy(96,2);printf("%c",206);

    //// Si baja

    int j ;

    //// Izq Full

    for(int k=3; k<2*cantidad+1; k++)
    {
        j = k;

        gotoxy(2,k);
        printf("%c",186);
    }

    gotoxy(160,j+1);printf("%c",188);
    gotoxy(2,j+1);printf("%c",200);

    for(int x=3;x<160;x++){

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
        gotoxy(160,k);
        printf("%c",186);
    }


  for(int k=3; k<2*cantidad+1; k++)
    {
        gotoxy(125,k);
        printf("%c",186);
    }

    gotoxy(125,2);printf("%c",206);




    //////////////



    gotoxy(3,20);




}

//////////////////////////////

bool CrearVectorCliente(){

    cliente *vec;

    int cantidad = ContarClientes();

    vec = new cliente[cantidad];

    if(vec==NULL){

        return false;
    }

    CargarVectorCliente(vec,cantidad);
    MostrarVectorCliente(vec,cantidad);

    delete vec;


}




//////////////////////////////

int BajaCliente();
void ListarCliente();
int ModificarCliente();
int BuscarCliente (int);
void BuscarClientePorID();


//////////////////////////////

int BuscarCliente(int id)
{

    cliente obj;

    int posicion = 0;

    while(obj.LeerDisco(posicion))
    {


        if(obj.getidcliente()==id && obj.getestado() == true)
        {

            return posicion;
        }

        posicion++;

    }

    return -1;

}

int ModificarCliente()
{

    cliente obj;

    char gmail[100];
    char direccion [100];
    int id;
    int posicion = 0;
    char opc;

    cout << "Ingrese, id de cliente a modificar: ";
    cin >> id;

    obj.LeerDisco(0);
    system ("cls");

    while(obj.LeerDisco(posicion)==1)
    {
        if(obj.getidcliente()==id)
        {

            cout << "Cliente encontrado en el archivo." << endl << endl;

            obj.MostrarCliente();
            cout << endl;

            cout << "Esta seguro que desea modificar este Cliente? S/N" << endl << endl;
            cout << "OPCION: [ ]\b\b";
            cin >> opc;

            switch (opc)
            {

            case 's':
            case 'S':

                system ("cls");

                cout << "Ingrese nuevo gmail: ";
                cin >> gmail;

                obj.setgmail(gmail);
                obj.modificarEnDisco(posicion);

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

int BajaCliente()
{

    cliente obj;

    int numero;
    int posicion = 0;
    char opc;

    cout << "Ingresar, ID Cliente que desee dar de baja: ";
    cin >> numero;

    obj.LeerDisco(0);
    system ("cls");

    while(obj.LeerDisco(posicion)==1)
    {
        if(obj.getidcliente()==numero)
        {

            cout << "Proveedor encontrado en el archivo." << endl << endl;

            obj.MostrarCliente();
            cout << endl;

            cout << "Esta seguro que desea dar de baja a este Cliente? S/N" << endl << endl;
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

void ListarCliente()
{

    cliente obj;

    int posicion = 0;

    obj.LeerDisco(0);

    while(obj.LeerDisco(posicion++))
    {

        obj.MostrarCliente();
        cout << endl;
    }

}



void BuscarClientePorID()
{
    cliente obj;

    int id;
    int posicion = 0;


    cout << "Ingrese, ID de cliente: ";
    cin >> id;

    system ("cls");

    while(obj.LeerDisco(posicion++))
    {

        if(obj.getestado()==true)
        {

            if(obj.getidcliente()==id)
            {

                obj.MostrarCliente();
                cout << endl;
            }
        }


    }


}


int ContarClientes()
{

    int cantidad;

    FILE*p = fopen("cliente.dat","rb");

    if(p==NULL)
    {

        cout << "Error" << endl;
    }

    fseek (p,0,2);

    cantidad = ftell(p);

    return cantidad/sizeof(cliente);

}


////////////////////////////////////////////////////////////////////////////////


int MenuCliente()
{
    cliente obj;


    int OpcionSelec;

    while (true)
    {

        Datos();
        Bordes ();

        gotoxy(75,10);
        cout << "MENU CLIENTE";
        gotoxy(53,10);
        cout << "*******************";
        gotoxy(92,10);
        cout << "*******************";
        gotoxy(53,12);
        cout << "<1> Cargar Cliente";
        gotoxy(53,13);
        cout << "<2> Mostrar Cliente";
        gotoxy(53,14);
        cout << "<3> Modificar ";
        gotoxy(53,15);
        cout << "<4> Buscar por ID";
        gotoxy(53,16);
        cout << "<5> Baja Cliente";
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
            if(obj.CargarCliente()==true)
            {

                if(obj.GuardarCliente()==true)
                {

                    system ("cls");
                    cout << "Se ha guardado correctamente, el cliente en el archivo." << endl << endl;
                }




            }

            system ("pause");
            system ("cls");
            break;

        case 2:
            CrearVectorCliente();
            system ("pause");
            system ("cls");
            break;

        case 3:
            ModificarCliente();
            system ("pause");
            system ("cls");
            break;

        case 4:
            BuscarClientePorID();
            system ("pause");
            system ("cls");
            break;

        case 5:
            BajaCliente();
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



#endif // CLIENTES_H_INCLUDED
