#include <QCoreApplication>
#include "sudokugenerator.h"
#include <iostream>
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end

Sudokugenerator::Sudokugenerator()
{
}

void Sudokugenerator::init(int seed)
{
    Sudokugenerator::generateSudoku(seed);
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
    Sudokugenerator::prepareArray();
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

    int x = 0;
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

    }

    Sudokugenerator::arrayChanged = true;
    Sudokugenerator::showArray();


    //Sudokugenerator::showArray(9);
    /*Sudokugenerator::fillBlockArray();

    printf("horizontal: %d\n", Sudokugenerator::horizontalBlocksOk());
    while (!Sudokugenerator::horizontalBlocksOk())
    {
        Sudokugenerator::fillBlockArray();
    }
    printf("horizontal: %d\n", Sudokugenerator::horizontalBlocksOk());

    for (int i = 0; i < 9; i++)
    {
        //Sudokugenerator::generateBlock(i);
        Sudokugenerator::showBlock(i);
    }*/
    /*
    Sudokugenerator::removeNumberFromArray(8, 8, 3);
    if (Sudokugenerator::numberCanBePicked(5, 5, 3))
    {
        std::cout << "yes";
    }
    else
    {
        std::cout << "nope";
    }


    Randomengine myEngine = Randomengine(seed);
    bool finished = false;
    bool gotNumber = false;
    int randomNumber = 0;
    int x = 0;
    int y = 0;

    while (!finished)
    {
        gotNumber = false;

        while (!gotNumber)
        {
            randomNumber = myEngine.getNumber();
            //std::cout << randomNumber;
            if (Sudokugenerator::numberCanBePicked(x, y, randomNumber))
            {
                Sudokugenerator::sudokuArray[x][y][10] = randomNumber;
                Sudokugenerator::removeNumberFromArray(x, y, randomNumber);
                gotNumber = true;
                Sudokugenerator::arrayChanged = true;
                Sudokugenerator::showArray(10);
            }
        }
        x++;
        if (x > 8)
        {
            x = 0;
            y++;
        }
        if (y > 8)
        {
            finished = true;
        }

        std::cout << "x: " << x << " y: " << y << std::endl;
    }

    Sudokugenerator::arrayChanged = true;*/
    /*
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
*/


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
        // remove horizontal
        if (Sudokugenerator::sudokuArray[x][i][number] == number)
        {
            Sudokugenerator::sudokuArray[x][i][number] = 0;
        }

        // remove vertical
        if (Sudokugenerator::sudokuArray[i][y][number] == number)
        {
            Sudokugenerator::sudokuArray[i][y][number] = 0;
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

void Sudokugenerator::fillBlockArray()
{
    bool blocksFilled = false;
    int counter = 0;

    while (!blocksFilled)
    {
        Sudokugenerator::generateBlock(counter);

        counter ++;
        if (counter == 9)
        {
            blocksFilled = true;
        }
    }
}

void Sudokugenerator::initGenerator(int seed)
{
    printf("\nSeed: %d\n\n", seed);
    Sudokugenerator::numberGenerator = Randomengine(seed);
}
