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