#ifndef __Sudokugenerator__
#define __Sudokugenerator__

#include "randomengine.h"

class Sudokugenerator
{
public:

    Sudokugenerator();
    ~Sudokugenerator(){}

    void showArray(int floor = 0);
    void showBlock(int blockNr = 0);
    void init(int seed = 0);

protected:
    int sudokuArray[9][9][10];
    int sudokuBlocks[3][3][9];
    int size = 9;

private:
    /*int size = 0;
    int** sudokuArray;
    int** generateSudoku(int size);*/
    Randomengine numberGenerator;
    void initGenerator(int seed = 0);
    void prepareArray();
    void generateSudoku(int seed = 0);
    bool arrayChanged = false;
    bool numberCanBePicked(int x, int y, int number);
    void removeNumberFromArray(int x, int y, int number);
    void generateBlock(int blockNr);
    void fillBlockArray();
    bool sudokuGeneratedFromBlocks();
    bool horizontalBlocksOk();
    bool verticalBlocksOk();
};

#endif // __Sudokugenerator__

