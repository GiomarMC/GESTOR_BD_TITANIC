#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <cstring>
#include "filemanager.h"
#include <fstream>
#include <sstream>
#include <filesystem>

class FileManager
{
    private:
        static const int MAX_CSV_FILES = 1000;
        static const int MAX_COLUMNS = 1000;
        static const int MAX_COLUMN_NAME_LENGTH = 100;
        static const int MAX_TYPE_LENGTH = 100;

        char csvFiles[MAX_CSV_FILES][MAX_COLUMN_NAME_LENGTH];
        char columnTypes[MAX_CSV_FILES][MAX_COLUMNS][MAX_COLUMN_NAME_LENGTH];
        char dataType[MAX_TYPE_LENGTH][MAX_TYPE_LENGTH];

        int csvFilesCount;
        int columnCount[MAX_CSV_FILES];

        int findCsvFiles();
        void displayCsvFiles() const;
        void readColumnTypes(const std::string&);
        void assingColumnTypes(const char columns[MAX_COLUMNS][MAX_COLUMN_NAME_LENGTH]);
        void loadDataTypes();
        bool isValidDataType(const char type[MAX_TYPE_LENGTH]) const;
    public:
        FileManager();
        void selectCsvFile();
        void displayColumnTypes() const;
};

#endif