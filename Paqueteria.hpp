#ifndef PAQUETERIA_HPP_INCLUDED
#define PAQUETERIA_HPP_INCLUDED

#include <iostream>
#include <sstream>
#include <fstream>

#define NOM_ARCHIVO_PAQUETERIA "Paqueteria.dat"

using namespace std;

class Nodo
{
public:
    void* elemento;
    Nodo* sig;
};

typedef Nodo* posicion;

const posicion ERROR_POSICION = nullptr;

template<class TipoElemento>
class Paqueteria
{
private:
    posicion encabezado;
    long contNodo;

    posicion reservarNodo();
    void liberarNodo(posicion p);

public:
    Paqueteria();
    ~Paqueteria();
    posicion primero();
    posicion fin();
    posicion ultimo();
    posicion siguiente(posicion p);
    posicion anterior(posicion p);
    bool estaVacia();
    bool estaLlena();
    bool insertar(TipoElemento* dato, posicion p);
    bool insertarInicio(TipoElemento* dato);
    bool eliminar(posicion p);
    bool eliminarInicio();
    string ordenarPorOrigen();
    string ordenarPorPeso();
    string mostrarLista();
    void guardarArchivo(); //Desarrollar el metodo en el archivo main, para que sea reutilizable
    void recuperarArchivo(); //Desarrollar el metodo en el archivo main, para que sea reutilizable
    long dameContNodo();
    long dameLongitud();
};


template<class TipoElemento>
Paqueteria<TipoElemento>::Paqueteria()
{
    contNodo = 0;
    encabezado = reservarNodo();
    encabezado->sig = nullptr;
}

template<class TipoElemento>
Paqueteria<TipoElemento>::~Paqueteria()
{
    while(!estaVacia())
    {
        eliminar(primero());
    }
}

template<class TipoElemento>
posicion Paqueteria<TipoElemento>::primero()
{
    return encabezado;
}

template<class TipoElemento>
posicion Paqueteria<TipoElemento>::fin()
{
    posicion p = encabezado;

    while(p->sig!=ERROR_POSICION)
    {
        p = p->sig;
    }

    return p;
}

template<class TipoElemento>
posicion Paqueteria<TipoElemento>::ultimo()
{
    if(estaVacia())
    {
        return ERROR_POSICION;
    }
    else
    {
        return anterior(fin());
    }
}

template<class TipoElemento>
posicion Paqueteria<TipoElemento>::siguiente(posicion p)
{
    posicion nodo = p->sig;
    if(nodo!=ERROR_POSICION)
    {
        return nodo;
    }
    else
    {
        return ERROR_POSICION;
    }
}

template<class TipoElemento>
posicion Paqueteria<TipoElemento>::anterior(posicion p)
{
    posicion ant = encabezado;

    if(ant!=ERROR_POSICION)
    {
        while(ant->sig!=p)
        {
            ant = ant->sig;
        }
        return ant;
    }
    else
    {
        return ERROR_POSICION;
    }
}

template<class TipoElemento>
bool Paqueteria<TipoElemento>::estaVacia()
{
    return encabezado->sig==ERROR_POSICION;
}

template<class TipoElemento>
bool Paqueteria<TipoElemento>::estaLlena()
{
    return false;
}

template<class TipoElemento>
posicion Paqueteria<TipoElemento>::reservarNodo()
{
    contNodo++;
    return new Nodo;
}

template<class TipoElemento>
void Paqueteria<TipoElemento>::liberarNodo(posicion p)
{
    contNodo--;

    delete p;
}

template<class TipoElemento>
bool Paqueteria<TipoElemento>::insertar(TipoElemento* dato, posicion p)
{
    posicion temp = p->sig;
    p->sig = reservarNodo();
    p->sig->elemento = dato;
    p->sig->sig = temp;

    return true;
}

template<class TipoElemento>
bool Paqueteria<TipoElemento>::insertarInicio(TipoElemento* dato)
{
    return insertar(dato, primero());
}

template<class TipoElemento>
bool Paqueteria<TipoElemento>::eliminar(posicion p)
{
    posicion nodo;
    bool eliminable;

    nodo = p->sig;
    eliminable = false;
    if(nodo!=ERROR_POSICION)
    {
        p->sig = nodo->sig;
        liberarNodo(nodo);
        eliminable = true;
    }

    return eliminable;
}

template<class TipoElemento>
bool Paqueteria<TipoElemento>::eliminarInicio()
{
    return eliminar(primero());
}

template<class TipoElemento>
string Paqueteria<TipoElemento>::ordenarPorOrigen()
{
    posicion p, i, f;
    TipoElemento *dato, *datoAux;

    for(p=primero(), f=fin(); p!=f; p=siguiente(p))
    {
        for(i=siguiente(p->sig); i!=f->sig; i=siguiente(i))
        {
            dato = (TipoElemento*)(i->elemento);
            datoAux = (TipoElemento*)(p->sig->elemento);
            if(strcmp(datoAux->dameOrigen(), dato->dameOrigen())>0)
            {
                p->sig->elemento = dato;
                i->elemento = datoAux;
            }
        }
    }

    return mostrarLista();
}

template<class TipoElemento>
string Paqueteria<TipoElemento>::ordenarPorPeso()
{
    posicion p, f, i;
    TipoElemento *dato, *datoAux;

    for(p=primero(), f=fin(); p!=f; p=siguiente(p))
    {
        for(i=siguiente(p->sig); i!=f->sig; i=siguiente(i))
        {
            dato = (TipoElemento*)(i->elemento);
            datoAux = (TipoElemento*)(p->sig->elemento);

            if(datoAux->damePeso()<dato->damePeso())
            {
                p->sig->elemento = dato;
                i->elemento = datoAux;
            }
        }
    }

    return mostrarLista();
}

template<class TipoElemento>
string Paqueteria<TipoElemento>::mostrarLista()
{
    posicion p, f;
    TipoElemento* dato;
    stringstream info;

    info<< "Id\t|Origen\t|Destino\t|Peso (Kg.)"<< endl;
    for(p=primero(), f=fin(); p!=f; p=siguiente(p))
    {
        dato = (TipoElemento*)(p->sig->elemento);
        info<< dato->dameId()<< "\t|"<< dato->dameOrigen()<< "\t|"<< dato->dameDestino()<<
            "\t|"<< dato->damePeso()<< endl;
    }

    return info.str();
}

template<class TipoElemento>
long Paqueteria<TipoElemento>::dameContNodo()
{
    return contNodo;
}

template<class TipoElemento>
long Paqueteria<TipoElemento>::dameLongitud()
{
    return contNodo-1;
}

#endif // PAQUETERIA_HPP_INCLUDED
