#include <QCoreApplication>
#include "sudokugenerator.h"
#include <iostream>
#include "randomengine.h"

Sudokugenerator::Sudokugenerator()
{
}

void Sudokugenerator::init(int seed)
{
    Sudokugenerator::generateSudoku(seed);
}

void Sudokugenerator::prepareArray()
{
    for (int i = 9; i >= 0; i--)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 9; k++)
            {
                Sudokugenerator::sudokuArray[k][j][i] = i;
            }
        }
    }

    for (int i = 9; i >= 0; i--)
    {
        for (int j = 0; j < 9; j++)
        {
            Sudokugenerator::sudokuArray[j][i][10] = 11;
        }
    }

    Sudokugenerator::arrayChanged = true;
}

void Sudokugenerator::generateSudoku(int seed)
{
    Sudokugenerator::prepareArray();
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

*/
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

    Sudokugenerator::arrayChanged = true;
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

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                printf("%d ", Sudokugenerator::sudokuArray[j][i][floor]);
            }

            printf("\n");
        }

        Sudokugenerator::arrayChanged = false;
    }
}

bool Sudokugenerator::numberCanBePicked(int x, int y, int number)
{
    if (Sudokugenerator::sudokuArray[x][y][number] != number)
    {
        return false;
    }
    // it's ok to take numbers out
    return true;
}

void Sudokugenerator::removeNumberFromArray(int x, int y, int number)
{
    for (int i = 0; i < 9; i++)
    {
        // remove horizontal
        Sudokugenerator::sudokuArray[x][i][number] = -1;
        // remove vertical
        Sudokugenerator::sudokuArray[i][y][number] = -1;
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
            Sudokugenerator::sudokuArray[x + j][y + i][number] = -1 ;
        }
    }
}
