#include <QCoreApplication>
#include "gamemgr.h"

void Gamemgr::init()
{
    Gamemgr::sudokugenerator.init(123);
    Gamemgr::m_isRunning = true;
}

void Gamemgr::handleEvents()
{

}

void Gamemgr::update()
{

}

void Gamemgr::render()
{

    Gamemgr::sudokugenerator.showArray(0);
}

void Gamemgr::clean()
{

}
