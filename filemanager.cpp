#include "filemanager.h"

void listFiles(std::string path, std::string extension)
{
    std::cout << "Archivos encontrados: " << std::endl;
    std::filesystem::path files[MAXFILES];
    int filecount = 0;
    std::cout << "Seleccione un archivo " << extension << " para cargar o 0 para salir " << std::endl;
    std::cout << "0. Salir" << std::endl;
    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        if (entry.path().extension() == extension)
        {
            files[filecount] = entry.path();
            std::cout << filecount + 1 << ". " << files[filecount].filename() << std::endl;
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
            std::cerr << "Opcion invalida, ingrese la opcion nuevamente" << std::endl;
        }
        else if (option > 0)
        {
            std::string filename = files[option - 1].filename();
            if(filename.find(".csv") != std::string::npos)
            {
                std::string txtFilename = filename;
                txtFilename.replace(txtFilename.find(".csv"), 4, ".txt");
                std::cout << "Archivo seleccionado: " << filename << std::endl;
                break;
            }
            if(filename.find(".txt") != std::string::npos)
            {
                std::cout << "Archivo seleccionado: " << filename << std::endl;
                break;
            }
        }
    } while (option != 0);
}

void Menu()
{
    Disco disco;
    int primaryOption;
    std::cout << "Bienvenido a Megatron 3000" << std::endl;
    do
    {
        std::cout << "--------------------------------" << std::endl;
        std::cout << "1. Leer Archivo" << std::endl;
        std::cout << "2. Crear Relacion" << std::endl;
        std::cout << "3. Mostrar espacio en Disco" << std::endl;
        std::cout << "4. Agregar Registro" << std::endl;
        std::cout << "5. Realizar una consulta" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opcion >> ";
        std::cin >> primaryOption;
        std::cout << "--------------------------------" << std::endl;
        switch (primaryOption)
        {
            case 1:
                MenuLeerArchivo();
                break;
            
            case 0:
                std::cout << "Gracias por usar Megatron 3000" << std::endl;
                break;
            default:
                std::cout << "Opcion invalida, ingrese la opcion nuevamente" << std::endl;
                break;
        }

    } while (primaryOption != 0);
}

void MenuLeerArchivo()
{
    int option;
    do
    {
        std::cout << "--------------------------------" << std::endl;
        std::cout << "1. Mostrar Archivos" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opcion >> ";
        std::cin >> option;
        std::cout << "--------------------------------" << std::endl;
        switch (option)
        {
            case 1:
                listFiles(".", ".csv");
                break;
            case 0:
                break;
            default:
                std::cout << "Opcion invalida, ingrese la opcion nuevamente" << std::endl;
                break;
        }
    } while (option != 0);
    
}