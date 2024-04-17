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

void Disco::leerDatos(const std::string& file)
{
    std::ifstream archivo(file);
    if (!archivo.is_open())
    {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return;
    }
    
    std::string linea;
    std::string cabecera;
    std::getline(archivo, linea);
    std::stringstream ss(linea);
    std::string database;
    std::vector<std::string> campos;

    std::cout << "Nombre de la base de datos >> ";
    std::cin >> database;

    std::ofstream db(database + ".txt");

    if(!db.is_open())
    {
        std::cerr << "Error al abrir el archivo" << database <<std::endl;
        return;
    }

    while(std::getline(ss, cabecera, ','))
    {
        campos.push_back(cabecera);
    }

    db << "Data columns (total " << campos.size() << " columns):\n";

    std::map<std::string, std::string> columnTypes;
    for(const auto& campo : campos)
    {
        std::string tipo;
        std::cout << "Tipo de dato para " << campo << " >> ";
        std::cin >> tipo;
        columnTypes[campo] = tipo;
    }

    for(const auto& pair : columnTypes)
    {
        db << pair.first << "\t" << pair.second << "\n";
    }

    campos.clear();

    while(std::getline(archivo, linea))
    {
        std::stringstream palabra(linea);
        std::string valor;
        std::string nombreCompleto;

        while(std::getline(palabra, valor, ','))
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
            std::cerr << "Numero insuficiente de campos en la linea." << std::endl;
            return;
        }

        for(int i = 0; i < campos.size(); i++)
        {
            std::cout << campos[i] << "\t";
        }
        std::cout << std::endl;
    }

    archivo.close();
}