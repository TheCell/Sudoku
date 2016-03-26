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
    Sudokugenerator::initGenerator(seed);
    for (int i = 0; i < 9; i++)
    {
        Sudokugenerator::generateBlock(i);
        Sudokugenerator::showBlock(i);
    }
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

void Sudokugenerator::generateBlock(int blockNr)
{
    int randomNumber = 0;
    int addedNumbers = 0;
    bool sequenceGenerated = false;
    int numberSequence[9];
    int counter = 0;
    int* end = numberSequence + 9;

    while (!sequenceGenerated)
    {
        randomNumber = Sudokugenerator::numberGenerator.getNumber();

        int* result = std::find(numberSequence, end, randomNumber);
        if (result == end)
        {
            numberSequence[addedNumbers] = randomNumber;
            addedNumbers++;
        }
        if (addedNumbers == 9)
        {
            sequenceGenerated = true;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Sudokugenerator::sudokuBlocks[j][i][blockNr] = numberSequence[counter];
            counter ++;
        }
    }
}

void Sudokugenerator::initGenerator(int seed)
{
    Sudokugenerator::numberGenerator = Randomengine(seed);
}

void Sudokugenerator::showBlock(int blockNr)
{
    printf("3D Array, Floor number: %d\n", blockNr);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", Sudokugenerator::sudokuBlocks[j][i][blockNr]);
        }

        printf("\n");
    }
}
