#ifndef INFORME_H_INCLUDED
#define INFORME_H_INCLUDED

void PonerEnCero(float *v,int cantidad)
{

    for(int x=0; x<cantidad; x++)
    {

        v[x]=0;
    }

}

float SumarImportes (int idventa)
{

    float importe;

    detalle_venta obj;

    FILE*p = fopen("detalleventa.dat","rb");

    if(p==NULL)
    {
        return -2;
    }

    while(fread(&obj,sizeof(detalle_venta),1,p)==1)
    {


        if(obj.getidventa()==idventa)
        {

            importe+=obj.getimporte();

        }


    }


    fclose(p);

    return importe;

}

///////////////////////////////////////////////////////

bool CargarVecMeses(float *v, int anio)
{

    venta reg;

    float importe;

    FILE*p = fopen("venta.dat","rb");
    if(p==NULL)
    {
        return false;
    }

    while(fread(&reg,sizeof(venta),1,p)==1)
    {

        if(reg.getfechaventa().getanio()==anio)
        {

            importe = SumarImportes(reg.getidventa());


            v[reg.getfechaventa().getmes()-1]+=importe;


        }

    }


}

///////////////////////////////////////////////////////

///////////////////////////////////////////////////////

void BordeMeses(){

   for(int x=5;x<17;x++){

    gotoxy(12,x);printf("%c",186);
   }

   for(int j=1;j<25;j++){

    gotoxy(j,4);printf("%c",205);
    gotoxy(12,4);printf("%c",203);
   }


}

///////////////////////////////////////////////////////

void MostrarVecMeses(float *vectorsito,int anio){


     float total = 0;

     string nombre[12] = {"Enero", "Febrero", "Marzo" ,"Abril", "Mayo","Junio", "Julio", "Agosto" ,"Septiembre", "Octubre","Noviembre", "Diciembre"};

     gotoxy (1,1);cout <<"Ingreso del anio: " << anio << endl;

     gotoxy(2,3);cout << "MES";
     gotoxy(14,3);cout<< "RECAUDACION";

     cout << endl;

     BordeMeses();

     for(int x = 0;x<12;x++){


        gotoxy(1,x+5);cout << nombre [x];
        gotoxy(15,x+5);cout << vectorsito[x];
        total+=vectorsito[x];

     }

     gotoxy(1,19);cout << "RECAUDACION TOTAL: " << total;


}

///////////////////////////////////////////////////////

//////////////////////////////////

int NumeroConsola(char *consola)
{
    if(strcmp(consola,"xbox")==0){return 1;}
    if(strcmp(consola,"xbox one")==0){return 2;}
    if(strcmp(consola,"pc")==0){return 3;}
    if(strcmp(consola,"ps4")==0){return 4;}
    if(strcmp(consola,"ps4 pro")==0){return 5;}
    if(strcmp(consola,"nintendo")==0){return 6;}
    if(strcmp(consola,"nintendo switch")==0){return 7;}
}


int Consola(char *codigo){

    juego obj;

    int posicion = 0;

    while(obj.LeerJuego(posicion++))
    {

        if(strcmp(obj.getcodigo(),codigo)==0)
        {

            return NumeroConsola(obj.getconsola());

        }


    }



}

void LeerDetalleVenta(float *v,int anio)
{

    detalle_venta obj;
    venta ven;
    FILE *p=fopen("venta.dat","rb");
    if(p==NULL){return;}
    int posicion = 0;
    int GuardarPos;

    while(obj.LeerDetalleVenta(posicion++)){

        GuardarPos = Consola(obj.getcodigojuego());
        while(fread(&ven,sizeof(venta),1,p)){
        if(ven.getfechaventa().getanio()==anio){
        v[GuardarPos-1]+=obj.getimporte();
        }
        }
    }

fclose(p);


}

void  MostrarRecaudacionPorConsola(float *v)
{

    string ConsolaNombres[7]= {"xbox","xbox one","pc","ps4","ps4 pro","nintendo","nintendo switch"};

    gotoxy(10,2);cout << "Consola";
    gotoxy(30,2);cout<< "Recaudado";

    for(int x=0; x<7; x++)
    {

        gotoxy(10,x+5);
        cout << ConsolaNombres[x];
        gotoxy(30,x+5);
        cout << v[x];

    }



}



/////////////////////////////////////////////////
int NumeroConsola(char);

/////////////////////////////////////////////////////////
bool RecaudacionPorMes()
{

    float vecmeses[12];

    int anio;

    PonerEnCero(vecmeses,12);
    system("cls");

    cout << "Ingrese anio: ";
    cin >> anio;

    CargarVecMeses(vecmeses,anio);
    system ("cls");
    MostrarVecMeses(vecmeses,anio);

    gotoxy(1,22);



}

///////////////////////////////////

string RetornarNombreConsola(int num){


     if(num==1)return "xbox";
     if(num==2)return "xbox one";
     if(num==3)return "pc";
     if(num==4)return "ps4 pro";
     if(num==5)return "ps4";
     if(num==6)return "nintendo";
     if(num==8)return "todas";


}

///////////////////////////////////
/*char *buscar_genero(char *cod){
juego ju;
FILE *p=fopen("juegos.dat","rb");
if(p==NULL){
    cout<< "error en recaudacion por generojuego."<< endl;
    return 0;
}
while(fread(&ju,sizeof(juego),1,p)){
    if(strcmp(cod,ju.getcodigo())==0){
        return ju.getclasificacion();
    }
fclose(p);
}
}

float buscarrecaudacion(char *genero){
float rec=0;
char genero1[20];
detalle_venta d;
FILE *p=fopen("detalleventa.dat","rb");
if(p==NULL){
    cout<< "error en funcion buscarrecaudacion."<< endl;
    return 0;
}
while(fread(&d,sizeof (detalle_venta),1,p)){
   strcpy(genero1,buscar_genero(d.getcodigojuego()));
   if(strcmp(genero,genero1)==0){
    rec+=d.getimporte();
   }
}
fclose(p);
return rec;
}
///////////////////////////////////
void RecaudacionPorGeneroJuego() {
juego ju;
FILE *p=fopen("juegos.dat","rb");
if(p==NULL){
    cout<< "error en recaudacion por generojuego."<< endl;
    return;
}
float rec=0;
while(fread(&ju,sizeof(juego),1,p)){
    cout<< "genero "<< ju.getclasificacion() << endl;
    rec=buscarrecaudacion(ju.getclasificacion());
    cout<< "recaudacion: "<< rec << endl;
}
fclose(p);
}*/

/////////////////////////////////////////////////

int MostrarVentasPorEmpleado(int id,int anio){

    venta obj;

    int contador = 0;
    int posicion = 0;

    while(obj.LeerVenta(posicion++)){


        if(id==obj.getidempleado()&& obj.getfechaventa().getanio()==anio){

            contador+=1;
        }
    }


    return contador;

}


/////////////////////////////////////////////////

bool VentasPorEmpleado() {

    empleado obj;

    int anio;
    int c = 0;
    int posicion = 0;

    cout << "Ingrese, anio: ";
    cin >> anio;

    system("cls");

    while(obj.LeerDisco(posicion++)){

        if(obj.getestado()==true){

        c=MostrarVentasPorEmpleado(obj.getidempleado(),anio);

        cout << endl;

        if(c>0){

            cout << "Empleado: " << obj.getidempleado() << endl;
            cout << "Apellido: " << obj.getapellido() << endl;
            cout << "Nombre: " << obj.getnombre() << endl;
            cout << "Cantidad: " << c << endl;
            cout << endl;

        }

        }

    }


}

/////////////////////////////////////////////////


//////////////////////////////////



void LeerDetalleVenta(float *v)
{

    detalle_venta obj;

    int posicion = 0;
    int GuardarPos;

    while(obj.LeerDetalleVenta(posicion++))
    {

        GuardarPos = Consola(obj.getcodigojuego());

        v[GuardarPos-1]+=obj.getimporte();

    }




}

/*void  MostrarRecaudacionPorConsola(float *v)
{

    string ConsolaNombres[7]= {"xbox","xbox one","pc","ps4","ps4 pro","nintendo","nintendo switch"};

    gotoxy(10,2);cout << "Consola";
    gotoxy(30,2);cout<< "Recaudado";

    for(int x=0; x<7; x++)
    {

        gotoxy(10,x+5);
        cout << ConsolaNombres[x];
        gotoxy(30,x+5);
        cout << v[x];

    }



}
*/

bool RecaudacionPorConsola()
{

    float ImporteConsola[7];

    PonerEnCero(ImporteConsola,7);

    int anio;

    cout << "Ingrese, anio: ";
    cin >> anio;

    LeerDetalleVenta(ImporteConsola);
    MostrarRecaudacionPorConsola(ImporteConsola);
    gotoxy(1,15);

}

/////////////////////////////////////////////////
int MenuInformes(){
    int OpcionSelec;

    int s;

    while (true)
    {
         Datos();

        Bordes ();

        gotoxy(75,9);
        cout << "MENU INFORME";
        gotoxy(92,9);
        cout << "*******************";
        gotoxy(53,9);
        cout << "*******************";
        gotoxy(53,11);
        cout << "<1> Recaudacion por mes";
        gotoxy(53,13);
        cout << "<2> Recaudacion por genero juego (No Funciona)";
        gotoxy(53,15);
        cout << "<3> Ventas Por Empleado";
        gotoxy(53,17);
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

            RecaudacionPorMes();
            system ("pause");
            system ("cls");
            break;

        case 2:
            RecaudacionPorConsola();
            system ("pause");
            system ("cls");
            break;

        case 3:
            VentasPorEmpleado();
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




#endif // INFORME_H_INCLUDED
