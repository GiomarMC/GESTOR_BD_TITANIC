#ifndef LISTA_H
#define LISTA_H
#include "pasajeros.h"

class Nodo
{
    public:
        Pasajeros* pasajero;
        Nodo* next;

        Nodo(Pasajeros* _pasajero) : pasajero(_pasajero), next(nullptr) {}
};

class ListaEnlazada
{
    private:
        Nodo* head;
        Nodo* tail;
        int size;
    
    public:
        ListaEnlazada();
        ~ListaEnlazada();
        void agregarDatos(const std::vector<std::string>&);
        void leerArchivo(const std::string&);
        void insertar(Pasajeros*);
        void mostrar() const;
};

#endif