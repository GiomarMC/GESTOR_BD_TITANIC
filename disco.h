#ifndef DISCO_H
#define DISCO_H
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

const int bytes = 1024;

class Disco
{
    private:
        static const int discoMB = 2;
        static const int discoBytes = discoMB * bytes * bytes;
        float espacioOcupado = 0;
    public:
        Disco();
        int getEspacio();
        void agregarEspacio(int);
        bool espacioSuficiente() const;
        int obtenerEspacioRestante() const;
};

#endif