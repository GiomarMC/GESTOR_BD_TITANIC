#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

class File
{
    private:
        std::string fileHead;
        std::string typeHead;
    public:
        File();
        void readfile(std::string filename);
};

#endif