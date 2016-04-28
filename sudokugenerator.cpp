#include <QCoreApplication>
#include "sudokugenerator.h"
#include <iostream>
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end
#include <string>

Sudokugenerator::Sudokugenerator()
{
}

void Sudokugenerator::init(int seed)
{
    //Sudokugenerator::generateSudoku(seed);
    Sudokugenerator::prepareArray();
    //std::string sudokuString = "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
    std::string sudokuString = "000000600000305001001806400008102900700000008006708200002609500800203009005010300";
    if (Sudokugenerator::loadFromFile(sudokuString))
    {
        std::cout << "loading success!";
    }
    else
    {
        std::cout << "loading failed!";
    }
}

void Sudokugenerator::prepareArray()
{
    // fill floor 1-9 with numbers
    for (int i = 1; i < 10; i++)
    {
        for (int y = 0; y < 9; y++)
        {
            for (int x = 0; x < 9; x++)
            {
                Sudokugenerator::sudokuArray[x][y][i] = (i);
            }
        }
    }

    // floor 0 is the playfloor
    for (int y = 9; y >= 0; y--)
    {
        for (int x = 0; x < 9; x++)
        {
            Sudokugenerator::sudokuArray[x][y][0] = 0;
        }
    }

    Sudokugenerator::arrayChanged = true;
}

void Sudokugenerator::generateSudoku(int seed)
{
    Sudokugenerator::initGenerator(seed);

    /*while (Sudokugenerator[x][y][0] == 0)
    {
    }*/

    // one problem remains. I can run into a dead end.
    int randomNumber = 0;

    /*for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            while (Sudokugenerator::sudokuArray[x][y][0] == 0)
            {
                randomNumber = Sudokugenerator::numberGenerator.getNumber();

                if (Sudokugenerator::numberCanBePicked(x, y, randomNumber))
                {
                    Sudokugenerator::removeNumberFromArray(x, y, randomNumber);
                    printf("remove Number: %d\n", randomNumber);

                    Sudokugenerator::sudokuArray[x][y][0] = randomNumber;
                }

                Sudokugenerator::showArray();

            }

            Sudokugenerator::showArray();
        }
    }*/

    /*
     * working!
     */

    /*int x = 0;
    int y = 0;
    for (int i = 0; i < 7; i++)
    {
        bool numberRemoved = false;
        randomNumber = Sudokugenerator::numberGenerator.getNumber();

        while (!numberRemoved)
        {
            x = Sudokugenerator::numberGenerator.getNumber();
            y = Sudokugenerator::numberGenerator.getNumber();
            if (Sudokugenerator::numberCanBePicked(x, y, randomNumber))
            {
                Sudokugenerator::removeNumberFromArray(x, y, randomNumber);
                numberRemoved = true;
            }

        }

    }*/

    for (int i = 0; i < 9; i++)
    {
        bool numberRemoved = false;
        bool numberRemoved2 = false;

        while (!numberRemoved)
        {
            randomNumber = Sudokugenerator::numberGenerator.getNumber();
            if (Sudokugenerator::numberCanBePicked(i, 0, randomNumber))
            {
                Sudokugenerator::removeNumberFromArray(i, 0, randomNumber);
                numberRemoved = true;
            }
        }

        if (i > 0)
        {
            while (!numberRemoved2)
            {
                randomNumber = Sudokugenerator::numberGenerator.getNumber();
                if (Sudokugenerator::numberCanBePicked(0, i, randomNumber))
                {
                    Sudokugenerator::removeNumberFromArray(0, i, randomNumber);
                    numberRemoved2 = true;
                }
            }
        }
    }

    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(1);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(2);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(3);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(4);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(5);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(6);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(7);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(8);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(9);


    /*bool testnu = true;
    while(testnu)
    {
        randomNumber = Sudokugenerator::numberGenerator.getNumber();
        if (Sudokugenerator::numberCanBePicked(2,1,randomNumber))
        {
            Sudokugenerator::removeNumberFromArray(2,1,randomNumber);
            testnu = false;
        }
    }
    testnu = true;
    while(testnu)
    {
        randomNumber = Sudokugenerator::numberGenerator.getNumber();
        if (Sudokugenerator::numberCanBePicked(2,2,randomNumber))
        {
            Sudokugenerator::removeNumberFromArray(2,2,randomNumber);
            testnu = false;
        }
    }
    testnu = true;
    while(testnu)
    {
        randomNumber = Sudokugenerator::numberGenerator.getNumber();
        if (Sudokugenerator::numberCanBePicked(1,2,randomNumber))
        {
            Sudokugenerator::removeNumberFromArray(1,2,randomNumber);
            testnu = false;
        }
    }

    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(3);

    auto test = Sudokugenerator::blockHasOnlyOneValue(1, 1);
    printf("block has: %d,%d,%d\n", std::get<0>(test),std::get<1>(test),std::get<2>(test));
    int test2 = Sudokugenerator::cellHasOnlyOneValue(1, 1);
    printf("Cell has: %d\n", test2);*/

    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray();
}

void Sudokugenerator::showArray(int floor)
{
    if (Sudokugenerator::arrayChanged)
    {
        printf("3D Array, Floor number: %d\n", floor);

        printf(" |----------+-----------+----------| \n");
        for (int y = 0; y < 9; y++)
        {
            for (int x = 0; x < 9; x++)
            {
                if (x == 0)
                {
                    printf(" | %d ", Sudokugenerator::sudokuArray[x][y][floor]);
                }
                else if (x == 8)
                {
                    printf(" %d | ", Sudokugenerator::sudokuArray[x][y][floor]);
                }
                else if (x % 3 == 0)
                {
                    printf(" |  %d ", Sudokugenerator::sudokuArray[x][y][floor]);
                }
                else
                {
                    printf(" %d ", Sudokugenerator::sudokuArray[x][y][floor]);
                }
                if ((y + 1) % 3 == 0 && x == 8)
                {
                    printf("\n |----------+-----------+----------|");
                }
            }

            printf("\n");
        }

        Sudokugenerator::arrayChanged = false;
    }
}

bool Sudokugenerator::numberCanBePicked(int x, int y, int number)
{
    int x1 = 0;
    int y1 = 0;

    //Sudokugenerator::showArray(number);

    if (Sudokugenerator::sudokuArray[x][y][number] != number)
    {
        return false;
    }

    // check if the block does not already contain this number
    if ((x != 2 && y != 2) || (x != 5 && y != 5) || (x != 8 && y != 8))
    {
        if (x < 3)
        {
            x1 = 0;
        }
        else if (x < 6)
        {
            x1 = 3;
        }
        else
        {
            x1 = 6;
        }

        if (y < 3)
        {
            y1 = 0;
        }
        else if (y < 6)
        {
            y1 = 3;
        }
        else
        {
            y1 = 6;
        }

        // check blocks
        bool secondNumberExists = false;

        for (int i = 1; (i < 10 && !secondNumberExists); i++)
        {
            for (int y2 = 0; (y2 < 3 && !secondNumberExists); y2++)
            {
                for (int x2 = 0; (x2 < 3 && !secondNumberExists); x2++)
                {
                    //printf("_%d_", x2);
                    //printf(".%d.", x2 < 3);
                    if (Sudokugenerator::sudokuArray[x1 + x2][y1 + y2][i] == i )
                    {
                        secondNumberExists = true;
                    }
                }
            }
        }

        if (!secondNumberExists)
        {
            return false;
        }

        // check line number next to this one In case we snatch the last free place for this one

        for (int i = 1; i < 10; i++)
        {
            if ( i != number)
            {
                if (Sudokugenerator::sudokuArray[x+1][y][i] == i)
                {
                    secondNumberExists = true;
                }
            }
        }

        /*Sudokugenerator::showArray(1);
        Sudokugenerator::showArray(2);
        Sudokugenerator::showArray(3);
        Sudokugenerator::showArray(4);
        Sudokugenerator::showArray(5);
        Sudokugenerator::showArray(6);
        Sudokugenerator::showArray(7);
        Sudokugenerator::showArray(8);
        Sudokugenerator::showArray(9);*/

        if (!secondNumberExists)
        {
            return false;
        }

    }

    // add tests for empty blocks if the number gets removed. That would left me with a dead end
    // it's ok to take numbers out
    return true;
}

void Sudokugenerator::removeNumberFromArray(int x, int y, int number)
{
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::sudokuArray[x][y][number] = (number * -1);
    Sudokugenerator::sudokuArray[x][y][0] = number;

    for (int i = 0; i < 9; i++)
    {
        // remove column
        if (Sudokugenerator::sudokuArray[x][i][number] == number)
        {
            Sudokugenerator::sudokuArray[x][i][number] = 0;
        }

        // remove row
        if (Sudokugenerator::sudokuArray[i][y][number] == number)
        {
            Sudokugenerator::sudokuArray[i][y][number] = 0;
        }

        // remove on all other floors.
        if (Sudokugenerator::sudokuArray[x][y][i + 1] == i + 1)
        {
            Sudokugenerator::sudokuArray[x][y][i + 1] = 0;
        }
    }

    if (x < 3)
    {
        x = 0;
    }
    else if (x < 6)
    {
        x = 3;
    }
    else
    {
        x = 6;
    }

    if (y < 3)
    {
        y = 0;
    }
    else if (y < 6)
    {
        y = 3;
    }
    else
    {
        y = 6;
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Sudokugenerator::sudokuArray[x + j][y + i][number] == number)
            {
                Sudokugenerator::sudokuArray[x + j][y + i][number] = 0;
            }
        }
    }
}

void Sudokugenerator::initGenerator(int seed)
{
    printf("\nSeed: %d\n\n", seed);
    Sudokugenerator::numberGenerator = Randomengine(seed);
}

/**
 * @brief Sudokugenerator::cellHasOnlyOneValue checks a given cell. If there are multiple values still possible to fill in, it returns -1.
 * @param x
 * @param y
 * @param number we want to check
 * @return Returns the only possible Number, if there are multiple Numbers possible in the given cell returns -1.
 */
int Sudokugenerator::cellHasOnlyOneValue(int x, int y)
{
    int onlyNumber = -1;

    for (int i = 10; i > 0; i--)
    {
        if (Sudokugenerator::sudokuArray[x][y][i] == i)
        {
            // first match? asign the value. Multiple match will stop and return -1
            if (onlyNumber == -1)
            {
                onlyNumber = i;
            }
            else
            {
                // more then 1 number possible for this cell. Return -1
                return -1;
            }
        }
        /*
        // skip the one number we want to fill in
        if (i != number)
        {
            // if a floor has still the prefilled number in, we know that besides our wanted floor there is another floor that could possibly fill this cell.
            if (Sudokugenerator::sudokuArray[x][y][number] == number)
            {
                return false;
            }
        }*/
    }
    return onlyNumber;
}

/**
 * @brief Sudokugenerator::blockHasOnlyOneValue
 * @param x
 * @param y
 * @param number
 * @return tuple <number, x, y> number contains -1 if there are still multiple values available. Else returns the Number, X, Y coordinate.
 */
std::tuple<int, int, int> Sudokugenerator::blockHasOnlyOneValue(int x, int y)
{
    auto lastValue = std::make_tuple (-1, 0, 0);

    if (x < 3)
    {
        x = 0;
    }
    else if (x < 6)
    {
        x = 3;
    }
    else
    {
        x = 6;
    }

    if (y < 3)
    {
        y = 0;
    }
    else if (y < 6)
    {
        y = 3;
    }
    else
    {
        y = 6;
    }

    for (int x2 = 0; x2 < 3; x2++)
    {
        for (int y2 = 0; y2 < 3; y2++)
        {
            for (int i = 10; i > 0; i--)
            {
                if (Sudokugenerator::sudokuArray[x + x2][y + y2][i] == i)
                {
                    // was there already a value asigned other then the current i or is it the first value found and maybe unique in this block
                    if (std::get<0>(lastValue) == -1)
                    {
                        std::get<0>(lastValue) = i;
                        std::get<1>(lastValue) = x + x2;
                        std::get<2>(lastValue) = y + y2;

                        std::cout << "\nNumber:" << std::get<0>(lastValue) << "\n";
                    }
                    else
                    {
                        // more then 1 number possible, returning -1
                        std::get<0>(lastValue) = -1;
                        return lastValue;
                    }
                }
            }
        }
    }
    return lastValue;
}

bool Sudokugenerator::loadFromFile(std::string sudokuString)
{
    int x = -1;
    int y = -1;

    for (int i = 0; i < sudokuString.length(); i++)
    {
        x = i % 9;
        if (i % 9 == 0)
        {
            y++;
        }
        /*std::cout << i << ": " << sudokuString[i] << "\n";
        printf("\n%d\n", (sudokuString[i] - '0'));*/
        /*if ((sudokuString[i] - '0') > 0)
        {
            printf("x:%d y:%d\n", x, y);
        }*/
        if (sudokuString[i] - '0' > 0)
        {

            if (Sudokugenerator::numberCanBePicked(x, y, (sudokuString[i] - '0')))
            {
                Sudokugenerator::removeNumberFromArray(x, y, (sudokuString[i] - '0'));
                /*if (x == 0 && y == 4)
                {
                    printf("number xy 7 oder 9 _%d_", sudokuString[i] - '0');
                    Sudokugenerator::arrayChanged = true;
                    Sudokugenerator::showArray(7);
                }*/
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief Sudokugenerator::fillSingleCells checks the Sudoku for Cells with a single applicable Number
 * @return true if a cell has been filled, false if no cell has a single value left
 */
bool Sudokugenerator::fillSingleCells()
{
    bool arrayModified = false;

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            int number = Sudokugenerator::cellHasOnlyOneValue(x, y);

            //printf("_%d/x%d/y%d_", number,x,y);
            if (number > 0)
            {
                Sudokugenerator::removeNumberFromArray(x, y, number);
                arrayModified = true;
                Sudokugenerator::arrayChanged = true;
            }
        }
    }

    if (arrayModified)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Sudokugenerator::solveSudoku()
{
    bool cellRemoved = true;
    while (cellRemoved)
    {
        cellRemoved = false;
        Sudokugenerator::arrayChanged = true;
        Sudokugenerator::showArray();
        cellRemoved = Sudokugenerator::fillSingleCells();
    }

    // no cell can be easily filled in now but there can be free cells.
    std::string placeholder = Sudokugenerator::sudokuToString();

    //std::cout << "tempSudoku: " << placeholder << std::endl;

    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(9);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(8);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(7);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(6);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(5);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(4);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(3);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(2);
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(1);


    bool valueGuessed = Sudokugenerator::guessNextValue();
    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray(0);
    if (valueGuessed)
    {
        std::cout << "value guessed";
        bool cellRemoved = true;
        while (cellRemoved)
        {
            cellRemoved = false;
            Sudokugenerator::arrayChanged = true;
            Sudokugenerator::showArray();
            cellRemoved = Sudokugenerator::fillSingleCells();
        }
    }
    else
    {
        std::cout << "value NOT guessed";
    }

    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray();

    // TODO check dead ends and load other branches in
    printf("SOLVED!\n");
}

int Sudokugenerator::blockWithMinimumRemainingValues()
{
    // the 9 blocks of a Sudoku
    int blocks[9];
    // temporary array for holding the numbers
    int tempValues[9];
    int blockWithMinimum = -1;

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            int x2 = 0;
            int y2 = 0;

            if (x < 3)
            {
                x2 = 0;
            }
            else if (x < 6)
            {
                x2 = 3;
            }
            else
            {
                x2 = 6;
            }

            if (y < 3)
            {
                y2 = 0;
            }
            else if (y < 6)
            {
                y2 = 3;
            }
            else
            {
                y2 = 6;
            }

            // THIS IS A MESS, DON'T KILL ME, I'm sorry for copy pasta this, struct with inner method was a struggle
            if (x2 == 0 && y2 == 0)
            {
                int blockNumber = 0;
                blocks[blockNumber] = 0;
                for (int i = 0; i < 9; i++)
                {
                    tempValues[i] = 0;
                }

                // loop through the block and check every cell
                for (int y3 = 0; y3 < 3; y3++)
                {
                    for (int x3 = 0; x3 < 3; x3++)
                    {
                        // check if there is not already a number assigned to this cell
                        if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][0] == 0)
                        {
                            // iterate all numbers to check which number is possible
                            for (int i = 9; i > 0; i--)
                            {
                                //int numberInArr = Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][i];
                                //printf("%d and i = %d | x%d y%d\n", numberInArr, i, x3 + x2, y3 + y2);
                                // check if the cell is still untouched
                                if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][i] == i)
                                {
                                    //printf("number %d is possible in block %d at Pos x%d, y%d\n", i, blockNumber, x3 + x2, y3 + y2);

                                    // check if number is already found at another cell of this block;
                                    if (tempValues[i] != i)
                                    {
                                        tempValues[i] = i;
                                        blocks[blockNumber] ++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (x2 == 3 && y2 == 0)
            {
                int blockNumber = 1;
                blocks[blockNumber] = 0;
                for (int i = 0; i < 9; i++)
                {
                    tempValues[i] = 0;
                }
                // loop through the block and check every cell
                for (int y3 = 0; y3 < 3; y3++)
                {
                    for (int x3 = 0; x3 < 3; x3++)
                    {
                        // check if there is not already a number assigned to this cell
                        if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][0] == 0)
                        {
                            // iterate all numbers to check which number is possible
                            for (int i = 9; i > 0; i--)
                            {
                                //int numberInArr = Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][i];
                                //printf("%d and i = %d | x%d y%d\n", numberInArr, i, x3 + x2, y3 + y2);
                                // check if the cell is still untouched
                                if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][i] == i)
                                {
                                    //printf("number %d is possible in block %d at Pos x%d, y%d\n", i, blockNumber, x3 + x2, y3 + y2);

                                    // check if number is already found at another cell of this block;
                                    if (tempValues[i] != i)
                                    {
                                        tempValues[i] = i;
                                        blocks[blockNumber] ++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (x2 == 6 && y2 == 0)
            {
                int blockNumber = 2;
                blocks[blockNumber] = 0;
                for (int i = 0; i < 9; i++)
                {
                    tempValues[i] = 0;
                }

                // loop through the block and check every cell
                for (int y3 = 0; y3 < 3; y3++)
                {
                    for (int x3 = 0; x3 < 3; x3++)
                    {
                        // check if there is not already a number assigned to this cell
                        if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][0] == 0)
                        {
                            // iterate all numbers to check which number is possible
                            for (int i = 9; i > 0; i--)
                            {
                                // check if the cell is still untouched
                                if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][i] == i)
                                {
                                    //printf("number %d is possible in block %d at Pos x%d, y%d\n", i, blockNumber, x3 + x2, y3 + y2);

                                    // check if number is already found at another cell of this block;
                                    if (tempValues[i] != i)
                                    {
                                        tempValues[i] = i;
                                        blocks[blockNumber] ++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (x2 == 0 && y2 == 3)
            {
                int blockNumber = 3;
                blocks[blockNumber] = 0;
                for (int i = 0; i < 9; i++)
                {
                    tempValues[i] = 0;
                }

                // loop through the block and check every cell
                for (int y3 = 0; y3 < 3; y3++)
                {
                    for (int x3 = 0; x3 < 3; x3++)
                    {
                        // check if there is not already a number assigned to this cell
                        if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][0] == 0)
                        {
                            // iterate all numbers to check which number is possible
                            for (int i = 9; i > 0; i--)
                            {
                                // check if the cell is still untouched
                                if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][i] == i)
                                {
                                    //printf("number %d is possible in block %d at Pos x%d, y%d\n", i, blockNumber, x3 + x2, y3 + y2);

                                    // check if number is already found at another cell of this block;
                                    if (tempValues[i] != i)
                                    {
                                        tempValues[i] = i;
                                        blocks[blockNumber] ++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (x2 == 3 && y2 == 3)
            {
                int blockNumber = 4;
                blocks[blockNumber] = 0;
                for (int i = 0; i < 9; i++)
                {
                    tempValues[i] = 0;
                }

                // loop through the block and check every cell
                for (int y3 = 0; y3 < 3; y3++)
                {
                    for (int x3 = 0; x3 < 3; x3++)
                    {
                        // check if there is not already a number assigned to this cell
                        if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][0] == 0)
                        {
                            // iterate all numbers to check which number is possible
                            for (int i = 9; i > 0; i--)
                            {
                                // check if the cell is still untouched
                                if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][i] == i)
                                {
                                    //printf("number %d is possible in block %d at Pos x%d, y%d\n", i, blockNumber, x3 + x2, y3 + y2);

                                    // check if number is already found at another cell of this block;
                                    if (tempValues[i] != i)
                                    {
                                        tempValues[i] = i;
                                        blocks[blockNumber] ++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (x2 == 6 && y2 == 3)
            {
                int blockNumber = 5;
                blocks[blockNumber] = 0;
                for (int i = 0; i < 9; i++)
                {
                    tempValues[i] = 0;
                }

                // loop through the block and check every cell
                for (int y3 = 0; y3 < 3; y3++)
                {
                    for (int x3 = 0; x3 < 3; x3++)
                    {
                        // check if there is not already a number assigned to this cell
                        if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][0] == 0)
                        {
                            // iterate all numbers to check which number is possible
                            for (int i = 9; i > 0; i--)
                            {
                                // check if the cell is still untouched
                                if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][i] == i)
                                {
                                    //printf("number %d is possible in block %d at Pos x%d, y%d\n", i, blockNumber, x3 + x2, y3 + y2);

                                    // check if number is already found at another cell of this block;
                                    if (tempValues[i] != i)
                                    {
                                        tempValues[i] = i;
                                        blocks[blockNumber] ++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (x2 == 0 && y2 == 6)
            {
                int blockNumber = 6;
                blocks[blockNumber] = 0;
                for (int i = 0; i < 9; i++)
                {
                    tempValues[i] = 0;
                }

                // loop through the block and check every cell
                for (int y3 = 0; y3 < 3; y3++)
                {
                    for (int x3 = 0; x3 < 3; x3++)
                    {
                        // check if there is not already a number assigned to this cell
                        if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][0] == 0)
                        {
                            // iterate all numbers to check which number is possible
                            for (int i = 9; i > 0; i--)
                            {
                                // check if the cell is still untouched
                                if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][i] == i)
                                {
                                    //printf("number %d is possible in block %d at Pos x%d, y%d\n", i, blockNumber, x3 + x2, y3 + y2);

                                    // check if number is already found at another cell of this block;
                                    if (tempValues[i] != i)
                                    {
                                        tempValues[i] = i;
                                        blocks[blockNumber] ++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (x2 == 3 && y2 == 6)
            {
                int blockNumber = 7;
                blocks[blockNumber] = 0;
                for (int i = 0; i < 9; i++)
                {
                    tempValues[i] = 0;
                }

                // loop through the block and check every cell
                for (int y3 = 0; y3 < 3; y3++)
                {
                    for (int x3 = 0; x3 < 3; x3++)
                    {
                        // check if there is not already a number assigned to this cell
                        if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][0] == 0)
                        {
                            // iterate all numbers to check which number is possible
                            for (int i = 9; i > 0; i--)
                            {
                                // check if the cell is still untouched
                                if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][i] == i)
                                {
                                    //printf("number %d is possible in block %d at Pos x%d, y%d\n", i, blockNumber, x3 + x2, y3 + y2);

                                    // check if number is already found at another cell of this block;
                                    if (tempValues[i] != i)
                                    {
                                        tempValues[i] = i;
                                        blocks[blockNumber] ++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (x2 == 6 && y2 == 6)
            {
                int blockNumber = 8;
                blocks[blockNumber] = 0;
                for (int i = 0; i < 9; i++)
                {
                    tempValues[i] = 0;
                }

                // loop through the block and check every cell
                for (int y3 = 0; y3 < 3; y3++)
                {
                    for (int x3 = 0; x3 < 3; x3++)
                    {
                        // check if there is not already a number assigned to this cell
                        if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][0] == 0)
                        {
                            // iterate all numbers to check which number is possible
                            for (int i = 9; i > 0; i--)
                            {
                                // check if the cell is still untouched
                                if (Sudokugenerator::sudokuArray[x3 + x2][y3 + y2][i] == i)
                                {
                                    //printf("number %d is possible in block %d at Pos x%d, y%d\n", i, blockNumber, x3 + x2, y3 + y2);

                                    // check if number is already found at another cell of this block;
                                    if (tempValues[i] != i)
                                    {
                                        tempValues[i] = i;
                                        blocks[blockNumber] ++;
                                    }
                                }
                            }
                        }
                    }
                }
            }

        }
    }

    int tempAmount = 10;
    for (int i = 0; i < 9; i++)
    {
        if (blocks[i] < tempAmount)
        {
            tempAmount = blocks[i];
            blockWithMinimum = i;
        }
    }

    return blockWithMinimum;

}

std::tuple<int, int, int> Sudokugenerator::cellInBlockWithLowestPossibilities(int blockNumber)
{
    int x = 0;
    int y = 0;
    int tempLowest = -1;
    auto coordinates = std::make_tuple (-1, -1, -1);

    if (blockNumber == 2 || blockNumber == 5 || blockNumber == 8)
    {
        x = 3;
    }
    else if (blockNumber == 3 || blockNumber == 6 || blockNumber == 9)
    {
        x = 6;
    }

    if (blockNumber > 3 && blockNumber < 7)
    {
        y = 3;
    }
    else if (blockNumber > 6)
    {
        y = 6;
    }

    for (int y2 = 0; y2 < 3; y2++)
    {
        for (int x2 = 0; x2 < 3; x2++)
        {
            if (Sudokugenerator::sudokuArray[x + x2][y + y2][0] == 0)
            {
                int numbers = Sudokugenerator::amountOfPossibleValuesForCell(x + x2, y + y2);

                if (tempLowest < numbers)
                {
                    tempLowest = numbers;
                    std::get<0>(coordinates) = x + x2;
                    std::get<1>(coordinates) = y + y2;
                    std::get<2>(coordinates) = Sudokugenerator::getFirstFreeNumber(x + x2, y + y2);
                }
            }
        }
    }

    return coordinates;
}

std::string Sudokugenerator::sudokuToString()
{
    std::string sudokuAsString = "";

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            sudokuAsString += std::to_string(Sudokugenerator::sudokuArray[x][y][0]);
        }
    }

    return sudokuAsString;
}

bool Sudokugenerator::guessNextValue()
{
    int nextBlockCheck = Sudokugenerator::blockWithMinimumRemainingValues();
    printf("Block Number %d has the lowest possibilities\n", nextBlockCheck);

    auto nextCell = Sudokugenerator::cellInBlockWithLowestPossibilities(nextBlockCheck);
    printf("Cell x%d y%d has the lowest possibilities\n", std::get<0>(nextCell), std::get<1>(nextCell));

    if (std::get<0>(nextCell) > -1 && std::get<1>(nextCell) > -1)
    {
        if (Sudokugenerator::numberCanBePicked(std::get<0>(nextCell), std::get<1>(nextCell), std::get<2>(nextCell)))
        {
            std::cout << "Number " << std::get<2>(nextCell) << " at Pos x" << std::get<0>(nextCell) << ", y" << std::get<1>(nextCell) << " guessed" << std::endl;
            Sudokugenerator::removeNumberFromArray(std::get<0>(nextCell), std::get<1>(nextCell), std::get<2>(nextCell));
            return true;
        }
        else
        {
            std::cout << "Number can not be picked" << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "woops" << std::endl;
        return false;
    }
}

int Sudokugenerator::amountOfPossibleValuesForCell(int x, int y)
{
    int possibilities = 0;

    for (int i = 10; i > 0; i--)
    {
        if (Sudokugenerator::sudokuArray[x][y][i] == i)
        {
            possibilities++;
        }
    }

    return possibilities;
}

int Sudokugenerator::getFirstFreeNumber(int x, int y)
{
    for (int i = 10; i > 0; i--)
    {
        if (Sudokugenerator::sudokuArray[x][y][i] == i)
        {
            return i;
        }
    }

    std::cout << "Cell has no free Numbers";
    return -1;
}

//todo
bool Sudokugenerator::pathIsDeadEnd()
{
    bool isDeadEnd = true;

    if (!Sudokugenerator::sudokuHasEmptySpots())
    {

    }
    return isDeadEnd;
}

//todo
bool Sudokugenerator::sudokuHasEmptySpots()
{
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            if (Sudokugenerator::sudokuArray[x][y][0] == 0)
            {
                return true;
            }
        }
    }
    return false;
}
