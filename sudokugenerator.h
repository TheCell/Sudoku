#ifndef __Sudokugenerator__
#define __Sudokugenerator__

class Sudokugenerator
{
public:

    Sudokugenerator();
    ~Sudokugenerator(){}

    void showArray(int floor = 10);
    void init(int seed = 0);

protected:
    int sudokuArray[9][9][10];
    int size = 9;

private:
    /*int size = 0;
    int** sudokuArray;
    int** generateSudoku(int size);*/
    void prepareArray();
    void generateSudoku(int seed = 0);
    bool arrayChanged = false;
    bool numberCanBePicked(int x, int y, int number);
    void removeNumberFromArray(int x, int y, int number);
};

#endif // __Sudokugenerator__

