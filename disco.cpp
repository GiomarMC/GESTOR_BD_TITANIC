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

void Disco::leerDatos()
{
    std::vector<std::string> csvFiles;
    for(const auto& entry: std::filesystem::directory_iterator("."))
    {
        if(entry.path().extension() == ".csv")
        {
            csvFiles.push_back(entry.path().string());
        }
    }

    if(csvFiles.empty())
    {
        std::cout << "No se encontraron archivos CSV en el directorio actual." << std::endl;
        return;
    }

    int opcion;

    do
    {
        std::cout << "Archivos CSV encontrados: " << std::endl;
        for (size_t i = 0; i < csvFiles.size(); i++)
        {
            std::cout << i + 1 << ". " << csvFiles[i] << std::endl;
        }

        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione un archivo CSV o 0 para salir >> ";
        std::cin >> opcion;

        if(opcion < 0 || opcion > csvFiles.size())
        {
            std::cerr << "Opción inválida, ingrese el valor nuevamente" << std::endl;
        }
        else if(opcion > 0)
        {
            std::string filename = csvFiles[opcion - 1];
            std::cout << "Trabajando con dataset >> " << filename << std::endl;
        }
    } while(opcion < 0 || opcion > csvFiles.size());
}