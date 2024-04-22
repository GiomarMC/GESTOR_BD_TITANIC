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
            break;
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
        line.pop_back();
        line.push_back(',');
        std::istringstream iss(line);
        std::string column;
        while(std::getline(iss, column, ','))
        {
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
        std::cout << i + 1 << ". " << columns[i] << std::endl;
    }

    std::cout << "---------------------------------------------" << std::endl;

    assingColumnTypes(columns);
}

void FileManager::loadDataTypes()
{
    std::ifstream file("tipo_datos.txt");
    if(!file.is_open())
    {
        std::cerr << "Error al abrir el archivo datatypes.csv" << std::endl;
    }

    std::string line;
    std::getline(file, line);

    std::cout << "Tipos de datos disponibles: " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    while(std::getline(file, line))
    {
        line.push_back(',');
        std::istringstream iss(line);
        std::string type, sizestr;
        if(std::getline(iss, type, ',') && std::getline(iss, sizestr, ','))
        {
            int size = std::stoi(sizestr);
            dataTypes[type] = size;
            std::cout << type << std::endl;
        }
    }
    std::cout << "---------------------------------------------" << std::endl;

    file.close();
}

bool FileManager::isValidDataType(const std::string& type) const
{
    return dataTypes.find(type) != dataTypes.end();
}

void FileManager::assingColumnTypes(const std::vector<std::string>& columns)
{
    loadDataTypes();
    std::string type;

    std::cout << "\nAsignar tipos de datos a las columnas" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    
    for(int column = 0; column < columns.size(); column++)
    {
        do
        {
            std::cout << columns[column] << " >> ";
            std::cin >> type;

            if(!isValidDataType(type))
            {
                std::cerr << "Tipo de dato inválido, intente nuevamente" << std::endl;
            }
        } while(!isValidDataType(type));
        
        columnType[csvFiles.back()][columns[column]] = type;
    }

    std::cout << "---------------------------------------------" << std::endl;
}

void FileManager::displayColumnTypes() const
{
    std::cout << "Archivo: " << csvFiles.back() << std::endl;
    std::cout << "Tipos de datos asignados a las columnas: " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << std::setw(15) << std::left << "Columna" << "Tipo de dato" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    for(const auto& [filename, columns]: columnType)
    {
        for(const auto& [column, type]: columns)
        {
            std::cout << std::setw(20) << std::left << column << type << std::endl;
        }
    }
    std::cout << "---------------------------------------------" << std::endl;
}