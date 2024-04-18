#include "filemanager.h"

FileManager::FileManager()
{
    csvFiles = findCsvFiles();
}

std::vector<std::string> FileManager::findCsvFiles()
{
    std::vector<std::string> csvFiles;
    for(const auto& entry: std::filesystem::directory_iterator("."))
    {
        if(entry.path().extension() == ".csv")
        {
            csvFiles.push_back(entry.path().string());
        }
    }

    return csvFiles;
}

void FileManager::displayCsvFiles() const
{
    std::cout << "Archivos CSV encontrados: " << std::endl;
    for(size_t i = 0; i < csvFiles.size(); i++)
    {
        std::cout << i + 1 << ". " << csvFiles[i] << std::endl;
    }
}

void FileManager::selectCsvFile()
{
    int opcion;
    do
    {
        displayCsvFiles();
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione un archivo CSV o 0 para salir >> ";
        std::cin >> opcion;

        if(opcion < 0 || opcion > csvFiles.size())
        {
            std::cerr << "Opción inválida, ingrese el valor nuevamente" << std::endl;
        }
        else if(opcion > 0)
        {
            mapColumnTypes(csvFiles[opcion - 1]);
        }
    } while(opcion != 0);
}

void FileManager::mapColumnTypes(const std::string& filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Error al abrir el archivo " << std::endl;
    }

    std::string line;
    if(std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string column;
        while(std::getline(iss, column, ','))
        {
            std::string type;
            std::cout << "Ingrese el tipo de dato para la columna " << column << " >> ";
            std::getline(std::cin,type);
            columnType[filename][column] = type;
            std::cin.clear();
        }
    }
    else
    {
        std::cerr << "El dataset esta vacio" << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    file.close();
}

void FileManager::displayColumnTypes() const
{
    std::cout << "Tipos de datos asignados a las columnas: " << std::endl;
    for(const auto& [filename, columns]: columnType)
    {
        std::cout << "Archivo: " << filename << std::endl;
        for(const auto& [column, type]: columns)
        {
            std::cout << "\t" << column << "\t\t" << type << std::endl;
        }
    }
}