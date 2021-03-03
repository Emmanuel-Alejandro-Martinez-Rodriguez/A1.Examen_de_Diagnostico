#include <iostream>
#include <cstring>
#include <clocale>
#include "Paquete.hpp"
#include "Paqueteria.hpp"

#ifdef _WIN32
#define LIMPIA_PANTALLA "cls"
#else
#define LIMPIA_PANTALLA "clear"
#endif // _WIN32

using namespace std;

typedef enum{INSERTA_INICIO=1, ELIMINA_INICIO, ORDENA_POR_ORIGEN, ORDENAR_POR_PESO, MOSTRAR,
GUARDADO_ARCHIVO, RECUPERADO_ARCHIVO, SALIDA} opcionesMenuPrincipal;

Paqueteria<Paquete> paqueteria;

int eligeOpcionMenu();
void esperaContinuar();
void despidePrograma();
void insertarInicio();
void eliminarInicio();
void ordenarPorOrigen();
void ordenarPorPeso();
void mostrarLista();

int main()
{
    bool permisoSalida;
    setlocale(LC_CTYPE, "Spanish");

    permisoSalida = false;
    do
    {
        switch(eligeOpcionMenu())
        {
        case INSERTA_INICIO:
            insertarInicio();
            break;
        case ELIMINA_INICIO:
            eliminarInicio();
            break;
        case ORDENA_POR_ORIGEN:
            ordenarPorOrigen();
            break;
        case ORDENAR_POR_PESO:
            ordenarPorPeso();
            break;
        case MOSTRAR:
            mostrarLista();
            break;
        case GUARDADO_ARCHIVO:
            paqueteria.guardarArchivo();
            break;
        case RECUPERADO_ARCHIVO:
            paqueteria.recuperarArchivo();
            break;
        case SALIDA:
            permisoSalida = true;
            break;
        default:
            cout<< "Opción no válida."<< endl;
        }
        if(permisoSalida)
        {
            despidePrograma();
        }
        else
        {
            esperaContinuar();
        }
    }
    while(!permisoSalida);

    return 0;
}

void esperaContinuar()
{
    cout<< endl<< "Presiona entrar para continuar. . .";
    cin.ignore();
    system(LIMPIA_PANTALLA);
}

void despidePrograma()
{
    cout<< endl<< "Hasta luego."<< endl<< endl;
    cout<< "Presiona entrar para terminar. . .";
    cin.ignore();
    system(LIMPIA_PANTALLA);
}

int eligeOpcionMenu()
{
    int opcion;

    cout<< "\t\tBienvenido usuario."<< endl<< endl;
    cout<< "Registro de Paqueteria."<< endl<<
    "1. Insertar al inicio."<< endl<<
    "2. Elminar al inicio."<< endl<<
    "3. Ordenar por origen."<< endl<<
    "4. Ordenar por peso."<< endl<<
    "5. Mostrar lista."<< endl<<
    "6. Guardar archivo."<< endl<<
    "7. Recuperar archivo."<< endl<<
    "8. Salir del progrma."<< endl<<
    "Elige una opción: ";
    cin>> opcion;
    cin.ignore();
    system(LIMPIA_PANTALLA);

    return opcion;
}

void insertarInicio()
{
    char origen[TAM_ORIGEN+1], destino[TAM_DESTINO+1];
    long id;
    double peso;

    cout<< "\t\tINSERTA UN PAQUETE"<< endl<< endl;
    cout<< "Ingresa los datos del paquete para el registro #"<< paqueteria.dameContNodo()<< endl;
    cout<< "ID: ";
    cin>> id;
    cin.ignore();
    cout<< "Origen: ";
    cin.getline(origen, TAM_ORIGEN+1);
    cout<< "Destino: ";
    cin.getline(destino, TAM_DESTINO+1);
    cout<< "Peso en Kg.: ";
    cin>> peso;
    cin.ignore();

    if(paqueteria.insertarInicio(new Paquete(id, origen, destino, peso)))
    {
        cout<< endl<< "Se agrego el paquete correctamente."<< endl;
    }
    else
    {
        cout<< endl<< "No fue posible agregar el paquete."<< endl;
    }
}

void eliminarInicio()
{
    cout<< "\t\tELIMINAR UN PAQUETE."<< endl<< endl;

    if(paqueteria.eliminarInicio())
    {
        cout<< "Se ha eliminado el registro correctamente."<< endl;
    }
    else
    {
        cout<< "No fue posible eliminar el registro."<< endl;
    }
}

void ordenarPorOrigen()
{
    cout<< "\t\tORDENANDO PAQUETES POR SU ORIGEN."<< endl<< endl;

    if(paqueteria.dameLongitud()>0)
    {
        cout<< paqueteria.ordenarPorOrigen()<< endl;
    }
    else
    {
        cout<< "No hay paquetes que organizar."<< endl;
    }
}

void ordenarPorPeso()
{
    cout<< "\t\tORDENANDO PAQUETES POR SU PESO (kg.)"<< endl<< endl;

    if(paqueteria.dameLongitud()>0)
    {
        cout<< paqueteria.ordenarPorPeso()<< endl;
    }
    else
    {
        cout<< "No hay paquetes que organizar."<< endl;
    }
}

void mostrarLista()
{
    cout<< "\t\tLISTADO DE PAQUETES."<< endl<< endl;

    if(paqueteria.dameLongitud()>0)
    {
        cout<< paqueteria.mostrarLista()<< endl;
    }
    else
    {
        cout<< "No hay paquetes que mostrar."<< endl;
    }
}

template<class TipoElemento>
void Paqueteria<TipoElemento>::guardarArchivo()
{
    posicion p, f;
    Paquete *paquete;
    ofstream archivo;

    cout<< "\t\tGUARDANDO EN ARCHIVO."<< endl<< endl;
    if(paqueteria.dameLongitud()>0)
    {
        archivo.open(NOM_ARCHIVO_PAQUETERIA, ios::trunc | ios::binary);
        if(archivo.is_open())
        {
            for(p=primero(), f=fin(); p!=f; p=siguiente(p))
            {
                paquete = (Paquete*)(p->sig->elemento);
                archivo.write((char*)paquete, sizeof(Paquete));
            }

            archivo.close();
            cout<< "Se guardo el archivo correctamente."<< endl;
        }
        else
        {
            cout<< "No fue posible guardar el archivo."<< endl;
        }
    }
    else
    {
        cout<< "No hay paquetes que guardar."<< endl;
    }

}

template<class TipoElemento>
void Paqueteria<TipoElemento>::recuperarArchivo()
{
    Paquete *paquete;
    ifstream archivo;
    long i, cantPaquetes;

    cout<< "\t\tRECUPERADOR DE ARCHIVO."<< endl<< endl;

    archivo.open(NOM_ARCHIVO_PAQUETERIA, ios::in);
    if(archivo.is_open())
    {
        archivo.seekg(0, ios_base::end);
        cantPaquetes = archivo.tellg()/sizeof(Paquete);
        archivo.seekg(0, ios_base::beg);
        for(i=0; i<cantPaquetes; i++)
        {
            paquete = new Paquete(0, (char*)"", (char*)"", 0);
            archivo.read((char*)paquete, sizeof(Paquete));
            insertar(paquete, fin());
        }

        archivo.close();
        cout<< "Se recupero el archivo correctamente."<< endl;
    }
    else
    {
        cout<< "No hay datos guardados."<< endl;
    }

}
