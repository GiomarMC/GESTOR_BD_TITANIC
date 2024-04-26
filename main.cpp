#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "disco.h"

size_t getByteSize(const std::string& datatype, const std::string& value)
{
    if(datatype == "int")
        return sizeof(int);
    else if(datatype == "float")
        return sizeof(float);
    else if(datatype == "string")
        return value.size() * sizeof(char);
    return 0;
}

void spaceInDisk(const std::string& filename, Disco& disco)
{
    std::ifstream file(filename);
    std::string fileContent = filename;
    fileContent.replace(fileContent.find(".csv"), 4, ".txt");
    std::filesystem::path filePath = "usr/data/esquemas/" + fileContent;
    std::ifstream schemaFile(filePath);
    std::ofstream file2(fileContent);

    if(!file.is_open() || !schemaFile.is_open())
    {
        std::cerr << "Error al abrir el archivo " << std::endl;
        return;
    }
    std::string schemaLine;
    std::getline(schemaFile,schemaLine);
    schemaFile.close();

    size_t firtsPos = schemaLine.find("#");
    std::string trimmedSchema;
    if(firtsPos != std::string::npos)
    {
        trimmedSchema = schemaLine.substr(firtsPos + 1);
    }
    std::istringstream iss(trimmedSchema);
    std::string columnType;

    const int MAX_COLUMNS = 1000;
    std::string columnTypes[MAX_COLUMNS];

    size_t indexType = 0;

    while(std::getline(iss, columnType, '#'))
    {
        if(columnType == "int")
        {
            columnTypes[indexType] = "int";
            indexType++;
        }
        else if(columnType == "float")
        {
            columnTypes[indexType] = "float";
            indexType++;
        }
        else if(columnType == "string")
        {
            columnTypes[indexType] = "string";
            indexType++;
        }
    }

    std::string line;
    size_t count = 0;
    while(std::getline(file,line))
    {
        line.pop_back();
        line.push_back(',');
        std::istringstream iss(line);
        std::string column;
        file2 << count;
        std::string temp;
        size_t index = 0;
        size_t dataSize = 0;
        while(std::getline(iss, column, ','))
        {
            if(column[0] == '"')
            {
                column.erase(0,1);
                temp = column;
            }
            else if(column[column.size() - 1] == '"')
            {
                column.erase(column.size() - 1, 1);
                temp += column;
                dataSize += getByteSize(columnTypes[index], temp);
                file2 << "#" << temp;
                temp.clear();
            }
            else
            {
                dataSize += getByteSize(columnTypes[index], column);
                file2 << "#" << column;
            }
            index++;
        }
        disco.agregarEspacio(dataSize);
        file2 << "\n";
        count++;
    }
    file.close();
    file2.close();
}

void readCSV(const std::string& filename, const std::string& filename2)
{
    std::filesystem::path folderPath = "usr/data/esquemas";

    if(!std::filesystem::exists(folderPath))
    {
        if(!std::filesystem::create_directories(folderPath))
        {
            std::cerr << "Error al crear el directorio" << std::endl;
            return;
        }
    }

    std::filesystem::path filePath = folderPath / filename2;

    std::ifstream file(filename);
    std::ofstream file2(filePath);
    if(!file.is_open())
    {
        std::cerr << "Error al abrir el archivo " << std::endl;
        return;
    }
    std::string line;
    if(std::getline(file, line))
    {
        line.pop_back();
        line.push_back(',');
        std::istringstream iss(line);
        std::string column;
        file2 << filename;
        std::cout << "Columnas encontradas: " << std::endl;
        std::cout << "Asignar tipo de dato int, float o string"  << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
        std::string type;
        while(std::getline(iss, column, ','))
        {
            do
            {
                std::cout << column << " >> ";
                std::cin >> type;
                if(type != "int" && type != "float" && type != "string")
                    std::cerr << "Tipo de dato inválido, intente nuevamente" << std::endl;
                else
                    file2 << "#" << column << "#" << type;
            } while(type != "int" && type != "float" && type != "string");
        }
        std::cout << "---------------------------------------------" << std::endl;
        file.close();
        file2.close();
    }
    else
    {
        std::cerr << "El dataset esta vacio" << std::endl;
    }
    
}

void listCSVFiles(Disco& disco)
{
    std::cout << "Archivos CSV encontrados: " << std::endl;
    const int MAX_FILES = 1000;
    std::filesystem::path Files[MAX_FILES];
    int csvCount = 0;   
    std::cout << "Seleccione un archivo CSV o 0 para salir >>" << std::endl;
    for(const auto& entry: std::filesystem::directory_iterator("."))
    {
        if(entry.path().extension() == ".csv")
        {
            Files[csvCount] = entry.path();
            csvCount++;
        }
    }

    int option;
    do
    {
        int index = 1;
        for(int i = 0; i < csvCount; i++)
        {
            std::cout << index << ". " << Files[i].filename() << std::endl;
            index++;
        }
        std::cout << "Seleccione un archivo o 0 para salir >> ";
        std::cin >> option;
        if(option < 0 || option > csvCount)
        {
            std::cerr << "Opción inválida, ingrese el valor nuevamente" << std::endl;
        }
        else if(option > 0)
        {
            std::string filename = Files[option - 1].filename();
            if(filename.find(".csv") != std::string::npos)
            {
                std::string txtFilname = filename;
                txtFilname.replace(txtFilname.find(".csv"), 4, ".txt");
                std::cout << "Archivo seleccionado: " << filename << std::endl;
                readCSV(filename, txtFilname);
                spaceInDisk(filename,disco);
                break;
            }
            
        }
    } while (option != 0); 
}

void userCSV()
{
    std::string filename;
    std::string filename2;
    std::cout << "Ingrese el nombre del archivo CSV de lectura: ";
    std::cin >> filename;
    std::cout << "Ingrese el nombre del archivo de escritura: ";
    std::cin >> filename2;
    readCSV(filename, filename2);
}

void diskSpace(Disco& disco)
{
    std::cout << "Espacio ocupado: " << disco.getEspacio() << " bytes" << std::endl;
    std::cout << "Espacio disponible: " << disco.obtenerEspacioRestante() << " bytes" << std::endl;
}

void Menu()
{
    Disco disco;
    int primaryOption;
    std::cout << "Bienvenido a MegatronDB" << std::endl;
    do
    {
        std::cout << "1. Leer archivo CSV" << std::endl;
        std::cout << "2. Mostrar esquema" << std::endl;
        std::cout << "3. Mostrar espacio en Disco" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opción >> ";
        std::cin >> primaryOption;
        switch(primaryOption)
        {
            case 1:
                int option;
                do
                {
                    std::cout << "1. Mostar archivos CSV" << std::endl;
                    std::cout << "0. Regresar" << std::endl;
                    std::cout << "Seleccione una opción >> ";
                    std::cin >> option;
                    if(option == 1)
                        listCSVFiles(disco);
                    else if(option == 0)
                        break;
                    else
                        std::cerr << "Opción inválida, ingrese el valor nuevamente" << std::endl;
                } while (option != 0);
                
                break;
            case 2:
                break;
            case 3:
                diskSpace(disco);
                break;
            case 0:
                break;
            default:
                std::cerr << "Opción inválida, ingrese el valor nuevamente" << std::endl;
        }
    } while(primaryOption != 0);
    std::cout << "Gracias por usar MegatronDB" << std::endl;
}

int main()
{
    Menu();
    return 0;
}