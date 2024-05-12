#include "filemanager.h"

void listFiles(Disco& disco,std::string path, std::string extension)
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
                readAndSaveCSV(filename);
                addDataInDisk(disco,filename);
                break;
            }
            if(filename.find(".txt") != std::string::npos)
            {
                std::cout << "Archivo seleccionado: " << filename << std::endl;
                showColumns(filename);
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
                MenuLeerArchivo(disco);
                break;
            case 2:
                createRelation(disco);
                break;
            case 3:
                diskSpace(disco);
                break;
            case 4:
                break;
            case 5:
                MenuConsulta();
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

void MenuLeerArchivo(Disco& disco)
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
                listFiles(disco,".", ".csv");
                break;
            case 0:
                break;
            default:
                std::cout << "Opcion invalida, ingrese la opcion nuevamente" << std::endl;
                break;
        }
    } while (option != 0);
}

void MenuConsulta()
{
    std::string sentence;
    std::cout << "Ingrese la consulta >> ";
    std::cin.ignore();
    std::getline(std::cin, sentence);
    readSentence(sentence);
}

std::string createFolder(const std::string foldername)
{
    std::filesystem::path folderPath = "user/data/" + foldername;

    if(!std::filesystem::exists(folderPath))
    {
        if(!std::filesystem::create_directories(folderPath))
        {
            std::cerr << "Error al crear la carpeta " << folderPath << std::endl;
            return 0;
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

void readAndSaveCSV(const std::string& filename)
{
    std::filesystem::path path = createFolder("esquemas");
    std::string newfile = filename;
    newfile.replace(newfile.find(".csv"), 4, ".txt");
    path += "/" + newfile;
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
        txtFile << filename;
        std::cout << "Columnas encontradas" << std::endl;
        std::cout << "Asignar tipo de dato int, float, o char" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
        std::string type;
        while(std::getline(iss,column,','))
        {
            do
            {
                std::cout << column << " >> ";
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
    std::cout << "Archivo guardado exitosamente" << std::endl;
}

void addDataInDisk(Disco& disco,std::string filename)
{
    std::ifstream csvFile(filename);
    std::string newfile = filename;
    newfile.replace(newfile.find(".csv"), 4, ".txt");
    std::ofstream txtFile(newfile);

    if(!csvFile.is_open())
    {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return;
    }

    std::filesystem::path path = createFolder("esquemas") + "/" + filename;
    std::cout << "Path: " << path << std::endl;
    std::string types = readDataTypes(path);
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
                dataSize += getByteSize(columnsTypes[index], temp);
                txtFile << '#' << temp;
                temp.clear();
            }
            else
            {
                dataSize += getByteSize(columnsTypes[index], column);
                txtFile << '#' << column;
            
            }
            index++;
        }
        std::cout << "Espacio ocupado: " << dataSize << " bytes" << std::endl;
        disco.agregarEspacio(dataSize);
        txtFile << '\n';
        count++;
    }
    csvFile.close();
    txtFile.close();
}

std::string readDataTypes(std::string filename)
{
    filename.replace(filename.find(".csv"), 4, ".txt");
    std::cout << "Path: " << filename << std::endl;

    std::ifstream txtFile(filename);
    
    if(!txtFile.is_open())
    {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return 0;
    }
    else
    {
        std::string fileLine;
        std::getline(txtFile, fileLine);
        txtFile.close();

        size_t firstPos = fileLine.find("#");
        std::string file;
        if(firstPos != std::string::npos)
        {
            file = fileLine.substr(firstPos + 1);
        }
        
        std::istringstream iss(file);
        std::string columnType;

        std::string types;

        size_t indexType = 0;

        while(std::getline(iss, columnType, '#'))
        {
            if(columnType == "int" || columnType == "float" || columnType == "char")
            {
                types += columnType + ',';
                std::cout << columnType << std::endl;
            }
        }
        types.pop_back();
        return types;
    }
}

size_t getByteSize(const std::string& datatype, const std::string& value)
{
    if(datatype == "int")
        return sizeof(int);
    else if(datatype == "float")
        return sizeof(float);
    else if(datatype == "char")
        return value.size() * sizeof(char);
    return 0;
}

void showColumns(const std::string& filename)
{
    std::string relationPath = createFolder("esquemas");
    std::string schemaPath = createFolder("esquemas") + "/" + filename;

    std::ifstream schemaFile(schemaPath);
    std::string schemaLine;
    std::getline(schemaFile, schemaLine);
    schemaFile.close();

    size_t firstPos = schemaLine.find("#");
    std::string trimmedSchema;
    if(firstPos != std::string::npos)
    {
        trimmedSchema = schemaLine.substr(firstPos + 1);
    }

    std::istringstream iss(trimmedSchema);
    std::string column;

    const int MAX_COLUMNS = 100;
    std::string columns[MAX_COLUMNS];
    size_t index = 0;

    while(std::getline(iss, column, '#'))
    {
        if(column != "int" && column != "float" && column != "char")
        {
            columns[index] = column;
            index++;
        }
    }

    std::cout << "--------------------------------" << std::endl;
    std::cout << "Seleccione las columnas para generar la relacion" << std::endl;
    
    for(int i = 0; i < index; i++)
    {
        std::cout << i + 1 << ". " << columns[i] << std::endl;
    }

    std::cout << "--------------------------------" << std::endl;

    std::string relationName;
    std::cout << "Ingrese el nombre de la relacion >> ";
    std::cin >> relationName;
    relationName += ".txt";

    std::string columnsSelected;
    std::cout << "Ingrese las columnas seleccionadas separadas por # >> ";
    std::cin >> columnsSelected;

    std::istringstream issColumns(columnsSelected);
    std::string columnSchema;
    relationPath += "/" + relationName;
    std::ofstream relationSchemaFile(relationPath);
    relationSchemaFile << filename;

    std::cout << "Asignar tipo de dato int, float, o char" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    
    std::string type;
    std::string schema[MAX_COLUMNS];

    size_t indexSchema = 0;

    while (std::getline(issColumns, columnSchema, '#'))
    {
        do
        {
            std::cout << columnSchema << " >> ";
            std::cin >> type;
            if(type != "int" && type != "float" && type != "char")
                std::cerr << "Tipo de dato invalido, intente nuevamente" << std::endl;
            else
            {
                relationSchemaFile << '#' << columnSchema << '#' << type;
                schema[indexSchema] = columnSchema;
                indexSchema++;
            }
        } while (type != "int" && type != "float" && type != "char");
    }

    std::cout << "--------------------------------" << std::endl;
    relationSchemaFile.close();

    int indexRelation[MAX_COLUMNS];
    size_t indexRelationSize = 0;
    for(int i = 0; i < index; i++)
    {
        for(int j = 0; j < indexSchema; j++)
        {
            if(columns[i] == schema[j])
            {
                indexRelation[indexRelationSize] = j;
                indexRelationSize++;
            }
        }
    }

    std::filesystem::path pathRelation = createFolder("relaciones") + "/" + relationName;
    std::ofstream relationFile(pathRelation);
    std::ifstream filetxt(filename);
    std::string lineTxt;
    std::getline(filetxt, lineTxt);
    relationFile << columnsSelected << "\n";
    while(std::getline(filetxt, lineTxt))
    {
        std::istringstream iss(lineTxt);
        std::string columnTxt;
        std::string word;
        int count = -1;
        while(std::getline(iss, columnTxt, '#'))
        {
            for(int i = 0; i < indexRelationSize; i++)
            {
                if(count == indexRelation[i])
                {
                    word += columnTxt + '#';
                }
            }
            count++;
            if(count == index - 1)
            {
                word.pop_back();
                relationFile << word << "\n";
            }
        }
    }
    relationFile.close();
    std::cout << "Relacion creada exitosamente" << std::endl;
}

void createRelation(Disco& disco)
{
    listFiles(disco, "user/data/esquemas", ".txt");
}

void diskSpace(Disco& disco)
{
    std::cout << "Espacio ocupado: " << disco.getEspacio() << " bytes" << std::endl;
    std::cout << "Espacio disponible: " << disco.obtenerEspacioRestante() << " bytes" << std::endl;
}

void readSentence(std::string sentence)
{
    if(sentence.find('&') != std::string::npos && sentence.find('#') != std::string::npos)
    {
        std::string word;
        bool select = false;
        bool from = false;
        bool where = false;
        bool filename = false;
        std::string columns;
        std::string tables;
        std::string conditions;
        std::string file;
        sentence.pop_back();
        sentence.erase(sentence.find('&'), 1);
        std::istringstream iss(sentence);
        while(std::getline(iss, word, ' '))
        {
            if(word == "select")
            {
                select = true;
            }

            else if(word == "from")
            {
                select = false;
                from = true;
            }

            else if(word == "where")
            {
                from = false;
                where = true;
            }
            
            else if(word == "|")
            {
                where = false;
                filename = true;
            }

            else if(select)
            {
                columns += word;
            }

            else if(from)
            {
                tables = word;
            }
            
            else if(where)
            {
                conditions += word + ' ';
            }

            else if(filename)
            {
                file = word;
                file.pop_back();
                file += ".txt";
            }
            else
            {
                std::cerr << "Error en la consulta" << std::endl;
            }
        }
        tables += ".txt";
        executeSentence(columns,tables,conditions,file);
    }
}

void executeSentence(std::string columns, std::string tables, std::string conditions, std::string filename)
{
    std::ifstream file(tables);
    std::string columnsLine;
    int positionColumns;
    std::getline(file, columnsLine);
    positionColumns = getPosition(columnsLine, columns);
    std::cout << "Columna encontrada en la posicion " << positionColumns << std::endl;

    std::istringstream iss(conditions);
    std::string word;
    std::getline(iss, word, ' ');
    std::cout << "Palabra: " << word << std::endl;
    int positionCondition;
    positionCondition = getPosition(columnsLine, word);
    std::cout << "Condicion encontrada en la posicion " << positionCondition << std::endl;
    
    while(std::getline(file, columnsLine))
    {
        std::istringstream iss(columnsLine);
        std::string column;
        int count = 0;
        while(std::getline(iss, column, '#'))
        {
            if(count == positionColumns)
            {
                std::cout << column << std::endl;
            }
            count++;
        }
    }
}

int getPosition(const std::string& columns, const std::string& column)
{
    std::istringstream iss(columns);
    std::string word;
    int count = 0;
    while(std::getline(iss, word, '#'))
    {
        if(word == column)
        {
            return count;
        }
        count++;
    }
    return count;
}