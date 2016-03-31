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

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            while (Sudokugenerator::sudokuArray[x][y][0] == 0)
            {
                randomNumber = Sudokugenerator::numberGenerator.getNumber();

                if (Sudokugenerator::numberCanBePicked(x, y, randomNumber))
                {
                    Sudokugenerator::removeNumberFromArray(x, y, randomNumber);
                    Sudokugenerator::sudokuArray[x][y][0] = randomNumber;
                }
            }
        }
    }

    Sudokugenerator::showArray(9);
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
        Sudokugenerator::sudokuArray[x][i][number] = 0;
        // remove vertical
        Sudokugenerator::sudokuArray[i][y][number] = 0;
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
            Sudokugenerator::sudokuArray[x + j][y + i][number] = 0;
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

bool Sudokugenerator::sudokuGeneratedFromBlocks()
{

    return true;
}

bool Sudokugenerator::horizontalBlocksOk()
{
    // check the 9 rows
    for (int i = 0; i < 9; i++)
    {
        // the cringe starts here, sorry too lazy at the moment
        int zero = 0;
        int one = 0;
        int two = 0;
        int three = 0;
        int four = 0;
        int five = 0;
        int six = 0;
        int seven = 0;
        int eight = 0;
        int nine = 0;

        int k;
        if (i < 3)
        {
            k = 0;
        }
        else if (i < 6)
        {
            k = 3;
        }
        else
        {
            k = 6;
        }

        // check 3 blocks at a time
        //printf("\nZahlen:");
        for (int counter = 0; counter < 3; counter++)
        {
            for (int j = 0; j < 3; j++)
            {
                /*printf("%d", Sudokugenerator::sudokuBlocks[j][i % 3][k]);
                Sudokugenerator::showBlock(k);*/
                switch (Sudokugenerator::sudokuBlocks[j][i % 3][k])
                {
                    case 0:
                        zero++;
                    break;
                    case 1:
                        one++;
                    break;
                    case 2:
                        two++;
                    break;
                    case 3:
                        three++;
                    break;
                    case 4:
                        four++;
                    break;
                    case 5:
                        five++;
                    break;
                    case 6:
                        six++;
                    break;
                    case 7:
                        seven++;
                    break;
                    case 8:
                        eight++;
                    break;
                    case 9:
                        nine++;
                    break;
                    default:
                        zero++;
                    break;
                }
            }
            k++;
        }
        //printf("\n");

        //printf("zahlenreihe: %d%d%d%d%d%d%d%d%d%d", zero, one,two,three,four,five,six,seven,eight,nine);
        if (zero > 1 || one > 1 || two > 1 || three > 1 || four > 1 || five > 1 || six > 1 || seven > 1 || eight > 1 || nine > 1)
        {
            return false;
        }
    }
    return true;
}

bool Sudokugenerator::verticalBlocksOk()
{
    return true;
}
