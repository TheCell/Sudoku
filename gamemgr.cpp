#include <QCoreApplication>
#include "gamemgr.h"

void Gamemgr::init()
{
    //Gamemgr::sudokugenerator = Sudokugenerator();
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

    Gamemgr::sudokugenerator.showArray();

}

void Gamemgr::clean()
{

}
