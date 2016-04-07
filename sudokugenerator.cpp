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
    std::string sudokuString = "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
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

        for (int y = 0; y < 9; y++)
        {
            for (int x = 0; x < 9; x++)
            {
                printf("%d ", Sudokugenerator::sudokuArray[x][y][floor]);
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
        if (Sudokugenerator::sudokuArray[x][y][i] == i)
        {
            Sudokugenerator::sudokuArray[x][y][i] = 0;
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
        if (Sudokugenerator::numberCanBePicked(x, y, (sudokuString[i] - '0')))
        {
            Sudokugenerator::removeNumberFromArray(x, y, (sudokuString[i] - '0'));
        }
        else
        {
            return false;
        }
    }
    return true;
}
