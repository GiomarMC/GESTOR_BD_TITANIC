#include <iostream>
#include "filemanager.h"

int main()
{
    FileManager fileManager;
    fileManager.selectCsvFile();
    fileManager.displayColumnTypes();
    return 0;
}