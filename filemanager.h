#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "diskManager.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstring>

const int MAXFILES = 100;

void listFiles(diskManager&,std::string, std::string);
void Menu();
void MenuLeerArchivo(diskManager&);
std::string createFolder(const std::string);
void readAndSaveCSV(const std::string&);
void addDataInDisk(diskManager&,std::string);
std::string readDataTypes(std::string);
size_t getByteSize(const std::string&, const std::string&);
void showColumns(const std::string&);
void createRelation(diskManager&);
void diskSpace(diskManager&);
void MenuConsulta();
void readSentence(std::string);
void executeSentence(std::string,std::string,std::string,std::string);
int getPosition(const std::string&, const std::string&);
bool getCondition(const std::string&, const std::string&, int, const std::string&);

#endif