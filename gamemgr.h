#ifndef __Gamemgr__
#define __Gamemgr__
#include "sudokugenerator.h"

class Gamemgr
{
public:

    Gamemgr(){}
    ~Gamemgr(){}

    void init();
    void handleEvents();
    void update();
    void render();
    void clean();

    bool isRunning() { return m_isRunning; }

private:
    Sudokugenerator sudokugenerator;
    bool m_isRunning = false;
};

#endif // __Gamemgr__
