#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

class ArchivarDni{

private:

    int dni;

public:

  bool GuardarDni();
  bool LeerDni(int);
  void setdni(int d){dni=d;}
  int getdni(){return dni;}

};

////////////////////////////////////////////////////////////

bool ArchivarDni::GuardarDni(){

     FILE*p = fopen ("GuardarDni.dat","ab");

     if(p==NULL){return false;}


     fwrite(this,sizeof*this,1,p);

     fclose(p);

     return true;

}

////////////////////////////////////////////////////////////

bool ArchivarDni::LeerDni(int posicion){

    FILE* p = fopen("GuardarDni.dat","rb");

    if(p==NULL){return false;}

    fseek(p,sizeof*this*posicion,0);

    bool leeme = fread(this,sizeof*this,1,p);

    fclose(p);

    return leeme;

}

////////////////////////////////////////////////////////////

int BuscarDni(int dni){

   ArchivarDni obj;

   int posicion = 0;

   while(obj.LeerDni(posicion++)){

        if(obj.getdni()==dni){

            return -1;

        }


}


return 0;

}

/////////////////////////////////////////////////////////////

class persona
{

protected:
    char nombre[20];
    char apellido[20];
    char genero[20];
    fecha nacimiento;
    int dni;
    char zona[30];

public:
    bool CargarPersona();
    char *getnombre(){return nombre;}
    char *getapellido(){return apellido;}
    int getdni(){return dni;}
    char *getgenero(){return genero;}
    char *getzona(){return zona;}

};
///////////////////////////////
/*int validar_cadena(char *cadena){
int i=0,tam=0,c=0;
tam=strlen(cadena);
while(i<tam && c==0){
   if(isalpha(cadena[i])!=0){
    i++;
   }
    else{
        c=1;
    }
return c;
}

}*/
///////////////////////////////
bool persona::CargarPersona()
{


    ArchivarDni ap;

    cout << "DNI: ";
    cin >> dni;

    if(dni<0){

        cout << endl;

        cout << "Dni negativo." << endl << endl;

        return false;
    }

    if(BuscarDni(dni)==-1){


        cout << endl;

        cout << "El dni ya esta registrado." << endl << endl;

        return false;
    }

    ap.setdni(dni);


    cout << "Nombre: ";
    cin.ignore();
    cin.getline(nombre,20);
   /*if(validar_cadena(nombre)==1){
        cout<< "nombre invalido."<< endl;
        return false;
    }*/
    cout << "Apellido: ";
    cin.getline(apellido,20);
     /*if(validar_cadena(apellido)==1){
        cout<< "apellido invalido."<< endl;
        return false;
    }*/
    cout << "Genero: ";
    cin>> genero;
    /*if(validar_cadena(genero)==1){
        cout<< "genero invalido."<< endl;
        return false;
    }*/
    cout<< "Zona: ";
    cin.ignore();
    cin.getline(zona,20);
    /*if(validar_cadena(zona)==1){
        cout<< "zona invalido."<< endl;
        return false;
    }*/
    ap.GuardarDni();
    return true;

}

//////////////////////////////////////////////////////////


#endif // PERSONA_H_INCLUDED
