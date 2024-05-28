#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>

const int MAXFILES = 100;

class File
{
    private:
        std::string filename;
        std::string fileHead;
        std::string typeHead;
        std::string path;
    public:
        File();
        void selecFile(std::string extension);
        void readHead();
        void dataTypes();
        void readfile();
};

#endif