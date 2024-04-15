#ifndef PASAJEROS_H
#define PASAJEROS_H
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class Pasajeros
{
    private:
        int passengerID;
        int survived;
        int pClass;
        std::string name;
        std::string sex;
        int age;
        int sibSp;
        int parch;
        std::string ticket;
        float fare;
        std::string cabin;
        char embarked;
    public:
        Pasajeros();
        Pasajeros(int, int, int, std::string, std::string, int, int, int, std::string, float, std::string, char);
        void mostrarDatos() const;
};

#endif