#ifndef PAQUETE_HPP_INCLUDED
#define PAQUETE_HPP_INCLUDED

#include <iostream>

#define TAM_ORIGEN 50
#define TAM_DESTINO 50
#define ORIGEN_POR_DEF "N/A"
#define DESTINO_POR_DEF "N/A"
#define PESO_POR_DEF 0

using namespace std;

class Paquete
{
private:
    long id;
    char origen[TAM_ORIGEN+1];
    char destino[TAM_DESTINO+1];
    double peso;

public:
    Paquete(long id, char origen[], char destino[], double peso)
    {
        fijaId(id);
        fijaOrigen(origen);
        fijaDestino(destino);
        fijaPeso(peso);
    }
    void fijaId(long id)
    {
        if(id>0)
        {
            this->id = id;
        }
        else
        {
            id = 1;
        }
    }
    void fijaOrigen(char origen[])
    {
        if(strlen(origen)>1)
        {
            strcpy(this->origen, origen);
        }
        else
        {
            strcpy(this->origen, ORIGEN_POR_DEF);
        }
    }
    void fijaDestino(char destino[])
    {
        if(strlen(destino)>1)
        {
            strcpy(this->destino, destino);
        }
        else
        {
            strcpy(this->destino, DESTINO_POR_DEF);
        }
    }
    void fijaPeso(double peso)
    {
        if(peso>0)
        {
            this->peso = peso;
        }
        else
        {
            this->peso = PESO_POR_DEF;
        }
    }
    long dameId()
    {
        return id;
    }
    char* dameOrigen()
    {
        return origen;
    }
    char* dameDestino()
    {
        return destino;
    }
    double damePeso()
    {
        return peso;
    }
};

#endif // PAQUETE_HPP_INCLUDED
