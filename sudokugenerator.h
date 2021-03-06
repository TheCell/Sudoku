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
    bool loadFromFile(std::string sudokuString);
    void solveSudoku();

protected:
    int sudokuArray[9][9][10];
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
    int cellHasOnlyOneValue(int x, int y);
    std::tuple<int, int, int> blockHasOnlyOneValue(int x, int y);
    bool fillSingleCells();
    int blockWithMinimumRemainingValues();
    std::string Sudokugenerator::sudokuToString();
    bool Sudokugenerator::guessNextValue();
    std::tuple<int, int, int> Sudokugenerator::cellInBlockWithLowestPossibilities(int blockNumber);
    int Sudokugenerator::amountOfPossibleValuesForCell(int x, int y);
    int Sudokugenerator::getFirstFreeNumber(int x, int y);
    bool Sudokugenerator::sudokuHasEmptySpots();
    bool Sudokugenerator::pathIsDeadEnd();
};

#endif // __Sudokugenerator__

