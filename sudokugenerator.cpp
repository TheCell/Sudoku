#include <QCoreApplication>
#include "sudokugenerator.h"
#include <iostream>
#include "randomengine.h"

Sudokugenerator::Sudokugenerator()
{
    Sudokugenerator::generateSudoku();
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

    Sudokugenerator::arrayChanged = true;
}

void Sudokugenerator::generateSudoku(int seed)
{
    Sudokugenerator::prepareArray();

    Randomengine myEngine = Randomengine(seed);

    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;
    std::cout << myEngine.getNumber() << std::endl;


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
                printf("%d ", Sudokugenerator::sudokuArray[i][j][floor]);
            }

            printf("\n");
        }

        Sudokugenerator::arrayChanged = false;
    }
}
