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
            readColumnTypes(csvFiles[opcion - 1]);
        }
    } while(opcion != 0);
}

void FileManager::readColumnTypes(const std::string& filename)
{
    std::ifstream file(filename);
    if(!file.is_open())
    {
        std::cerr << "Error al abrir el archivo " << std::endl;
    }

    std::string line;
    std::vector<std::string> columns;
    if(std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string column;
        while(std::getline(iss, column, ','))
        {
            if(!column.empty() && column.back() == '\n')
            {
                column.pop_back();
            }
            columns.push_back(column);
        }
    }
    else
    {
        std::cerr << "El dataset esta vacio" << std::endl;
    }

    file.close();

    std::cout << "Columnas encontradas: " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    for(int i = 0; i < columns.size(); i++)
    {
        std::cout << i << ". " << columns[i] << std::endl;
    }

    std::cout << "---------------------------------------------" << std::endl;

    for(const auto& str: columns)
    {
        if(!str.empty() && str.back() == '\n')
            continue;
        std::cout << str << "  " << str.size() << std::endl;
    }

    assingColumnTypes(columns);
}

void FileManager::assingColumnTypes(const std::vector<std::string>& columns)
{
    std::string type;

    std::cout << "\nAsignar tipos de datos a las columnas" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    
    for(int column = 0; column < columns.size(); column++)
    {
        std::cout << "Ingrese el tipo de dato para la columna " << columns[column] << " >> ";
        std::cin >> type;
        columnType[csvFiles.back()][columns[column]] = type;
    }

    std::cout << "---------------------------------------------" << std::endl;
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