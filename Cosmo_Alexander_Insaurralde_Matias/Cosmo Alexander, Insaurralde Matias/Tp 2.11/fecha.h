#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

class fecha
{

protected:

    int dia;
    int mes;
    int anio;

public:

    int validacion(int,int,int);
    int getdia(){return dia;}
    int getmes(){return mes;}
    int getanio(){return anio;}
    void set_dia(int d){dia=d;}
    void set_mes(int m){mes=m;}
    void set_anio(int a){anio=a;}
    int cargar();
    void mostrar();



};
void fecha::mostrar()
{
    cout<< "FECHA DE PAGO: " << dia << "/" << mes << "/" << anio << endl;
}
int fecha::cargar()
{


    int f;

    cout << "Dia: ";
    cin >> dia;

    cout << "Mes: ";
    cin >> mes;

    cout << "Anio: ";
    cin >> anio;

    f = validacion(dia,mes,anio);

    return f;

}

int fecha::validacion(int dia,int mes,int anio)
{

    int bol = 0;

    if (mes>=1 && mes <= 12)
    {

        switch (mes)
        {

        /// Meses de 31 dias Enero, Marzo, Julio, Agosto, Octubre y Diciembre.

        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:

            if (dia>=1 && dia <=31)
            {
                bol = 1;


            }
            break;

        /// Meses de 30 dias Abril, Junio, Septiembre y Noviembre.

        case 4:
        case 6:
        case 9:
        case 11:

            if (dia >=1 && dia <= 30)
            {

                bol = 1;

            }
            break;

        case 2:

            /// Febrero

            /// Si el año es bisiesto + 1 dia.


            /// Formula para saber si un año es bisiesto.

            if( (anio%4 == 0)   &&   (anio%100 != 0)   ||   (anio%400 == 0) )
            {
                /// Si es bisiesto, sumamos un dia.

                if( dia >= 1 && dia <= 29 )
                {
                    bol = 1;
                };
            }
            else
            {
                /// En el caso contrario no sumamos nadaaaaaaaaaaaaaaaaaaaaa.

                if( dia >= 1 && dia <= 28 )
                {
                    bol = 1;
                };
            };
            break;

        }


    }

    return bol;

}


#endif // FECHA_H_INCLUDED
