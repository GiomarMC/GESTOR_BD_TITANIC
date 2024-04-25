#include "filemanager.h"

FileManager::FileManager()
{
    csvFilesCount = 0;
    csvFilesCount = findCsvFiles();
}

int FileManager::findCsvFiles()
{
    int count = 0;
    for(const auto& entry: std::filesystem::directory_iterator("."))
    {
        if(entry.path().extension() == ".csv")
        {
            strcpy(csvFiles[count], entry.path().filename().c_str());
            count++;
        }
    }

    return count;
}

void FileManager::displayCsvFiles() const
{
    std::cout << "Archivos CSV encontrados: " << std::endl;
    for(size_t i = 0; i < csvFilesCount; i++)
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

        if(opcion < 0 || opcion > csvFilesCount)
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
    char columns[MAX_COLUMNS][MAX_COLUMN_NAME_LENGTH];
    int count = 0;
    if(std::getline(file, line))
    {
        line.pop_back();
        line.push_back(',');
        std::istringstream iss(line);
        std::string column;
        while(std::getline(iss, column, ','))
        {
            strcpy(columns[count], column.c_str());
            count++;
        }
    }
    else
    {
        std::cerr << "El dataset esta vacio" << std::endl;
    }

    file.close();

    std::cout << "Columnas encontradas: " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    for(int i = 0; i < count; i++)
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
    int count = 0;

    std::cout << "Tipos de datos disponibles: " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    while(std::getline(file, line))
    {
        line.push_back(',');
        std::istringstream iss(line);
        std::string type, sizestr;
        if(std::getline(iss, type, ',') && std::getline(iss, sizestr, ','))
        {
            strcpy(dataType[count], type.c_str());
            count++;
            std::cout << type << std::endl;
        }
    }
    std::cout << "---------------------------------------------" << std::endl;

    file.close();
}

bool FileManager::isValidDataType(const char type[MAX_TYPE_LENGTH]) const
{
    for(int i = 0; i < MAX_TYPE_LENGTH; i++)
    {
        if(strcmp(dataType[i], type) == 0)
        {
            return true;
        }
    }
    return false;
}

void FileManager::assingColumnTypes(const char columns[MAX_COLUMNS][MAX_COLUMN_NAME_LENGTH])
{
    loadDataTypes();
    char type[MAX_TYPE_LENGTH];

    std::cout << "\nAsignar tipos de datos a las columnas" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    
    for(int column = 0; column < MAX_COLUMNS && columns[column][0] != '\0'; column++)
    {
        do
        {
            std::cout << columns[column] << " >> ";
            std::cin >> type;

            if(!isValidDataType(type))
            {
                std::cerr << "Tipo de dato inválido, intente nuevamente" << std::endl;
            }
        } while(!isValidDataType(type) && strcmp(type, "0") != 0);

        if(strcmp(type, "0") == 0)
        {
            break;
        }
        
        strcpy(columnTypes[csvFilesCount - 1][column], type);
    }

    std::cout << "---------------------------------------------" << std::endl;
}

void FileManager::displayColumnTypes() const
{
    if(csvFilesCount == 0)
    {
        std::cerr << "No se encontraron archivos CSV" << std::endl;
        return;
    }
    
    std::cout << "Archivo: " << csvFiles[csvFilesCount - 1] << std::endl;
    std::cout << "Tipos de datos asignados a las columnas: " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << std::setw(15) << std::left << "Columna" << "Tipo de dato" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    for(int i = 0; i < MAX_COLUMNS && columnTypes[csvFilesCount - 1][i][0] != '\0'; i++)
    {
        std::cout << std::setw(15) << std::left << i + 1 << columnTypes[csvFilesCount - 1][i] << std::endl;
    }
    std::cout << "---------------------------------------------" << std::endl;
}