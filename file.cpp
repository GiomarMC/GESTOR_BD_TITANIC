#include "file.h"

File::File()
{
    filename = "";
    fileHead = "";
    typeHead = "";
    path = "";
}

void File::selecFile(std::string extension)
{
    std::cout << "Archivos encontrados: " << std::endl;
    std::filesystem::path file[MAXFILES];
    int filecount = 0;
    std::cout << "Selecciona un archivo " << extension << " para cargar o 0 para salir " << std::endl;
    std::cout << "0. Salir" << std::endl;
    for(auto &it: std::filesystem::directory_iterator(std::filesystem::current_path()))
    {
        if (it.path().extension() == extension)
        {
            file[filecount] = it.path();
            std::cout << filecount + 1 << ". " << file[filecount].filename() << std::endl;
            filecount++;
        }
    }

    int option;
    do
    {
        std::cout << "Ingrese una opcion >> ";
        std::cin >> option;
        if(option < 0 || option > filecount)
        {
            std::cout << "Opcion no valida" << std::endl;
        }
        else if (option > 0)
        {
            filename = file[option - 1].filename();
            path = file[option - 1].string();
            std::cout << "Archivo seleccionado: " << filename << std::endl;
        }
    } while (option != 0);
}

void File::readHead()
{
    std::ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        std::cout << "Error al abrir el archivo" << std::endl;
    }
    else
    {
        std::string line;
        std::getline(file, line);
        line.pop_back();
        line.push_back(',');
        std::istringstream iss(line);
        std::string column;
        std::string temp;
        while(std::getline(iss, column, ','))
        {
            fileHead += column + ",";
        }
        fileHead.pop_back();
    }
    file.close();
}

void File::dataTypes()
{
    std::string type;
    std::string column;
    std::istringstream iss(fileHead);
    while(std::getline(iss, column, ','))
    {
        std::cout << column << " >> ";
        std::cin >> type;
        typeHead += type + ",";
    }
    typeHead.pop_back();
    std::cout << "Tipos de datos: " << typeHead << std::endl;
}

void File::readfile()
{
    std::ifstream file;
    file.open("file.txt");
    if (!file.is_open())
    {
        std::cout << "Error al abrir el archivo" << std::endl;
    }
    else
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::cout << line << std::endl;
        }
    }
    file.close();
}