#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "disco.h"

const int MAXFILES = 100;

void listFiles(Disco&,std::string, std::string);
void Menu();
void MenuLeerArchivo(Disco&);
std::string createFolder(const std::string);
void readAndSaveCSV(const std::string&);
void addDataInDisk(Disco&,std::string);
std::string readDataTypes(std::string);
size_t getByteSize(const std::string&, const std::string&);
void showColumns(const std::string&);
void createRelation(Disco&);
void diskSpace(Disco&);

#endif