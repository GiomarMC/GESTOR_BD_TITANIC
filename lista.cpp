#include "lista.h"

ListaEnlazada::ListaEnlazada()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

ListaEnlazada::~ListaEnlazada()
{
    while(head)
    {
        Nodo* temp = head;
        head = head->next;
        delete temp->pasajero;
        delete temp;
    }
}

void ListaEnlazada::agregarDatos(const std::vector<std::string>& campos)
{
    int ID = !campos[0].empty() ? std::stoi(campos[0]) : -1;
    int survived = !campos[1].empty() ? std::stoi(campos[1]) : -1;
    int pclass = !campos[2].empty() ? std::stoi(campos[2]) : -1;
    std::string name = campos[3];
    std::string sex = campos[4];
    int age = !campos[5].empty() ? std::stoi(campos[5]) : -1;
    int sibsp = !campos[6].empty() ? std::stoi(campos[6]) : -1;
    int parch = !campos[7].empty() ? std::stoi(campos[7]) : -1;
    std::string ticket = campos[8];
    float fare = !campos[9].empty() ? std::stof(campos[9]) : -1.0f;
    std::string cabin = campos[10];
    char embarked = !campos[11].empty() ? campos[11][0] : ' ';

    Pasajeros* nuevoPasajero = new Pasajeros
    (
        ID,
        survived,
        pclass,
        name,
        sex,
        age,
        sibsp,
        parch,
        ticket,
        fare,
        cabin,
        embarked
    );

    insertar(nuevoPasajero);

}

void ListaEnlazada::leerArchivo(const std::string& file)
{
    std::ifstream archivo(file);

    if(!archivo.is_open())
    {
        throw std::runtime_error("Error al abrir el archivo csv.");
    }

    std::string linea;

    std::getline(archivo,linea);

    while(std::getline(archivo,linea))
    {
        std::stringstream palabra(linea);
        std::string valor;
        std::vector<std::string> campos;
        std::string nombreCompleto;

        while(std::getline(palabra,valor, ','))
        {
            if(valor[0] == '"')
            {
                valor.erase(0,1);
                nombreCompleto = valor;
            }
            else if(valor[valor.size() - 1] == '"')
            {
                valor.erase(valor.size() - 1);
                nombreCompleto += valor;
                campos.push_back(nombreCompleto);
                nombreCompleto.clear();
            }
            else
                campos.push_back(valor);
        }

        if(campos.size() < 12)
        {
            throw std::runtime_error("Numero insuficiente de campos en la linea.");
        }

        agregarDatos(campos);
    }
}

void ListaEnlazada::insertar(Pasajeros* pasajero)
{
    Nodo* newNode = new Nodo(pasajero);

    if(!head)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }

    size++;
}

void ListaEnlazada::mostrar() const
{
    Nodo* temp = head;
    while(temp)
    {
        temp->pasajero->mostrarDatos();
        temp = temp->next;
    }
}