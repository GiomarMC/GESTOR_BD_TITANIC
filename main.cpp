#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
//#include "filemanager.h"
#include "file.h"

int main()
{
    File fileManager;
    fileManager.selecFile(".csv");
    fileManager.readHead();
    fileManager.dataTypes();
    //diskCreation();
    return 0;
}