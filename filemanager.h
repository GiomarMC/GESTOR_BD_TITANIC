#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "disco.h"

const int MAXFILES = 100;

void listFiles(std::string, std::string);
void Menu();
void MenuLeerArchivo();
std::string createFolder(const std::string);
void readAndSaveCSV(const std::string&);
void addDataInDisk(std::string);
std::string readDataTypes(std::string);
size_t getByteSize(const std::string&, const std::string&);
void showColumns(const std::string&);

#endif