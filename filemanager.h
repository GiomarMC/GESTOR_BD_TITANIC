#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <fstream>

class FileManager
{
    private:
        std::vector<std::string> csvFiles;
        std::vector<std::string> findCsvFiles();
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> columnType;
    public:
        FileManager();
        void displayCsvFiles() const;
        void selectCsvFile();
        void readColumnTypes(const std::string&);
        void assingColumnTypes(const std::vector<std::string>&);
        void displayColumnTypes() const;
};

#endif