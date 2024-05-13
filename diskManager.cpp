#include "diskManager.h"

diskManager::diskManager()
{
    platos = 8LL;
    sectores = 16384;
    pistas = 128;
    sectorBytes = 4096;
    espacioOcupado = 0;

    this->tamanioTotal = 8LL * 16384 * 128 * 4096;
}

diskManager::diskManager(int platos, int sectores, int pistas, int sectorBytes)
{
    this->platos = platos;
    this->sectores = sectores;
    this->pistas = pistas;
    this->sectorBytes = sectorBytes;
    espacioOcupado = 0;

    this->tamanioTotal = platos * sectores * pistas * sectorBytes;
}

void diskManager::createDirectory()
{
    std::filesystem::create_directory("Disco");
    std::filesystem::create_directory("Disco/Platos");
    std::ofstream file("Disco/Platos/Platos.txt");
    for(int i = 0; i < platos; i++)
    {
        file << "Plato " << i + 1 << " :\n";
        for(int j = 0; j < 2; j++)
        {
            file << "   Superficie " << j + 1 << " :\n";
            for(int k = 0; k < pistas; k++)
            {
                file << "      Pista " << k + 1 << " :\n";
                for(int l = 0; l < sectores; l++)
                {
                    file << "         Sector " << l + 1 << ' ';
                }
                file << '\n';
            }
        }
    }
    file.close();
}

unsigned long diskManager::getEspacio()
{
    return espacioOcupado;
}

void diskManager::agregarEspacio(size_t byte)
{
    this->espacioOcupado += byte;
}

bool diskManager::espacioSuficiente() const
{
    return espacioOcupado <= tamanioTotal;
}

unsigned long diskManager::obtenerEspacioRestante() const
{
    return tamanioTotal - espacioOcupado;
}