#ifndef DISKMANAGER_H
#define DISKMANAGER_H
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class diskManager
{
    private:
        int platos;
        int sectores;
        int pistas;
        int sectorBytes;
        unsigned long tamanioTotal;
        unsigned long espacioOcupado;
    public:
        diskManager();
        void print();
        unsigned long getEspacio();
        void agregarEspacio(size_t);
        bool espacioSuficiente() const;
        unsigned long obtenerEspacioRestante() const;
};


#endif