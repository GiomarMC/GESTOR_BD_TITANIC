#include "disco.h"

Disco::Disco() {}

int Disco::getEspacio()
{
    return espacioOcupado;
}

void Disco::agregarEspacio(int byte)
{
    espacioOcupado += byte;
}

bool Disco::espacioSuficiente() const
{
    return espacioOcupado <= discoBytes;
}

int Disco::obtenerEspacioRestante() const
{
    return discoBytes - espacioOcupado;
}

void Disco::calcularEspacioLista()
{
    ListaEnlazada mylist;
    mylist.leerArchivo("Titanic control 2024 - Hoja 1.csv");
    mylist.mostrar();
}