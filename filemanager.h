#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iomanip>

class FileManager
{
    private:
        std::vector<std::string> csvFiles;
        std::vector<std::string> findCsvFiles();
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> columnType;
        std::unordered_map<std::string, int> dataTypes;
    public:
        FileManager();
        void displayCsvFiles() const;
        void selectCsvFile();
        void readColumnTypes(const std::string&);
        void loadDataTypes();
        bool isValidDataType(const std::string&) const;
        void assingColumnTypes(const std::vector<std::string>&);
        void displayColumnTypes() const;
};

#endif