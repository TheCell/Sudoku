#include <QCoreApplication>
#include "gamemgr.h"
//#include "sudokugenerator.h"

int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);

   Gamemgr game;


   game.init();

   while (game.isRunning())
   {
       game.handleEvents();
       game.update();
       game.render();
   }

   game.clean();

    /*Sudokugenerator sudokugame;
    sudokugame.showArray(10);*/

    //sudokugame.init();
/*
    sudokugame = new Game();

    sudokugame->init();

    while (sudokugame->isRunning())
    {
        sudokugame->handleEvents();
        sudokugame->update();
        sudokugame->render();
    }

    sudokugame->clean();
*/
    return a.exec();
}
