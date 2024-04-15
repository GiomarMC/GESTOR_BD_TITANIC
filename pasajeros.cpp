#include "pasajeros.h"

Pasajeros::Pasajeros()
{
    passengerID = 0;
    survived = 0;
    pClass = 0;
    name = "user";
    sex = "none";
    age = 0;
    sibSp = 0;
    parch = 0;
    ticket = "none";
    fare = 0.0f;
    cabin = "none";
    embarked = ' ';
}

Pasajeros::Pasajeros(int _passengerID, int _survived, int _pClass, std::string _name, std::string _sex, int _age, int _sibSp, int _parch,
 std::string _ticket, float _fare, std::string _cabin, char _embarked)
{
    passengerID = _passengerID;
    survived = _survived;
    pClass = _pClass;
    name = _name;
    sex = _sex;
    age = _age;
    sibSp = _sibSp;
    parch = _parch;
    ticket = _ticket;
    cabin = _cabin;
    embarked = _embarked;
}

void Pasajeros::mostrarDatos() const
{
    std::cout << "ID: " << passengerID << std::endl;
    std::cout << "Survived: " << survived << std::endl;
    std::cout << "Class: " << pClass << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Sex: " << sex << std::endl;
    std::cout << "Age: " << age << std::endl;
    std::cout << "SibSp: " << sibSp << std::endl;
    std::cout << "Parch: " << parch << std::endl;
    std::cout << "Ticket: " << ticket << std::endl;
    std::cout << "Fare: " << fare << std::endl;
    std::cout << "Cabin: " << cabin << std::endl;
    std::cout << "Embarked: " << embarked << std::endl;
    std::cout << "------------------------------------" << std::endl;
}