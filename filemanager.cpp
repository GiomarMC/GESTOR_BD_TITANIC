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
                readCSV(filename);
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

std::string createFolder(const std::string foldername)
{
    std::filesystem::path folderPath = "user/data/" + foldername;

    if(!std::filesystem::exists(folderPath))
    {
        if(!std::filesystem::create_directory(folderPath))
        {
            std::cerr << "Error al crear la carpeta " << folderPath << std::endl;
        }
        else
        {
            std::cout << "Carpeta " << folderPath <<  " creada exitosamente" << std::endl;
            return folderPath;
        }
    }
    else
    {
        std::cout << "La carpeta ya existe" << std::endl;
        return folderPath;
    }
}

void readCSV(std::string filename)
{
    std::string path = createFolder("esquemas");
    path += "/" + filename;
    path.replace(path.find(".csv"), 4, ".txt");

    std::ifstream csvFile(filename);
    std::ofstream txtFile(path);

    if(!csvFile.is_open())
    {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }

    std::string line;
    if(std::getline(csvFile, line))
    {
        line.pop_back();
        line.push_back(',');
        std::istringstream iss(line);
        std::string column;
        txtFile << filename << std::endl;
        std::cout << "Columnas encontradas" << std::endl;
        std::cout << "Asignar tipo de dato int, float, o char" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
        std::string type;
        while(std::getline(iss,column,','))
        {
            do
            {
                std::cout << column << " >>";
                std::cin >> type;
                if(type != "int" && type != "float" && type != "char")
                    std::cerr << "Tipo de dato invalido, intente nuevamente" << std::endl;
                else
                    txtFile << "#" << column << "#" << type;
            } while (type != "int" && type != "float" && type != "char");
        }
        std::cout << "---------------------------------------------" << std::endl;
        csvFile.close();
        txtFile.close();
    }
}

void dataInDisk(std::string filename)
{
    std::ifstream csvFile(filename);
    std::string newfile = filename.replace(filename.find(".csv"), 4, ".txt");
    std::ofstream txtFile(newfile);

    if(!csvFile.is_open())
    {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }

    std::string types = createSchema(filename);
    std::istringstream iss(types);
    size_t indexType = 0;
    const int MAX_COLUMNS = 100;
    std::string columnsTypes[MAX_COLUMNS];
    while(std::getline(iss, types, ','))
    {
        if(types == "int")
        {
            columnsTypes[indexType] = "int";
            indexType++;
        }
        if(types == "float")
        {
            columnsTypes[indexType] = "float";
            indexType++;
        }
        if(types == "char")
        {
            columnsTypes[indexType] = "char";
            indexType++;
        }
    }

    std::string line;
    size_t count = 0;
    while(std::getline(csvFile, line))
    {
        line.pop_back();
        line.push_back(',');
        txtFile << count;
        std::istringstream iss(line);
        std::string column;
        std::string temp;
        size_t index = 0;
        size_t dataSize = 0;
        while(std::getline(iss, column, ','))
        {
            if(column[0] == '"')
            {
                column.erase(0, 1);
                temp += column;
            }
            else if(column[column.size() - 1] == '"')
            {
                column.erase(column.size() - 1, 1);
                temp += column;
                dataSize = getByteSize(columnsTypes[index], temp);
                txtFile << '#' << temp;
                temp.clear();
            }
            else
            {
                dataSize = getByteSize(columnsTypes[index], column);
                txtFile << '#' << column;
            
            }
            index++;
        }
        txtFile << '\n';
        count++;
    }
    csvFile.close();
    txtFile.close();
}

std::string createSchema(std::string filename)
{
    std::string path = createFolder("esquemas") + "/" + filename;
    path.replace(path.find(".csv"), 4, ".txt");

    std::ifstream txtFile(path);
    
    if(!txtFile.is_open())
    {
        std::cerr << "Error al abrir el archivo " << path << std::endl;
        return;
    }

    std::string schemaLine;
    std::getline(txtFile, schemaLine);
    txtFile.close();

    size_t firstPos = schemaLine.find("#");
    std::string schema;
    if(firstPos != std::string::npos)
    {
        schema = schemaLine.substr(firstPos + 1);
    }

    std::istringstream iss(schema);
    std::string columnType;

    std::string types;

    size_t indexType = 0;

    while(std::getline(iss, columnType, '#'))
    {
        if(columnType == "int")
        {
            types += "int" + ',';
        }
        if(columnType == "float")
        {
            types += "float" + ',';
        }
        if(columnType == "char")
        {
            types += "char" + ',';
        }
    }

    return types;
}

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