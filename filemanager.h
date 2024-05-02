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
void createFolder(const std::string);

#endif