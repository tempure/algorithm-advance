#include <iostream>
#include <cassert>

using namespace std;

//https://blog.csdn.net/weixin_43379056/article/details/83022441
//没找到非暴力解法的题解。。。。

const int max_size  = 20;
const int max_steps = 4;

int Matrix[max_size][max_size] = {
    { 8, 02, 22, 97, 38, 15, 00, 40, 00, 75, 04, 05, 07, 78, 52, 12, 50, 77, 91, 8},
    {49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 04, 56, 62, 00},
    {81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 03, 49, 13, 36, 65},
    {52, 70, 95, 23, 04, 60, 11, 42, 69, 24, 68, 56, 01, 32, 56, 71, 37, 02, 36, 91},
    {22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80},
    {24, 47, 32, 60, 99, 03, 45, 02, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50},
    {32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70},
    {67, 26, 20, 68, 02, 62, 12, 20, 95, 63, 94, 39, 63, 8, 40, 91, 66, 49, 94, 21},
    {24, 55, 58, 05, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72},
    {21, 36, 23, 9, 75, 00, 76, 44, 20, 45, 35, 14, 00, 61, 33, 97, 34, 31, 33, 95},
    {78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 03, 80, 04, 62, 16, 14, 9, 53, 56, 92},
    {16, 39, 05, 42, 96, 35, 31, 47, 55, 58, 88, 24, 00, 17, 54, 24, 36, 29, 85, 57},
    {86, 56, 00, 48, 35, 71, 89, 07, 05, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58},
    {19, 80, 81, 68, 05, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 04, 89, 55, 40},
    {04, 52, 8, 83, 97, 35, 99, 16, 07, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66},
    {88, 36, 68, 87, 57, 62, 20, 72, 03, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69},
    {04, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18, 8, 46, 29, 32, 40, 62, 76, 36},
    {20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 04, 36, 16},
    {20, 73, 35, 29, 78, 31, 90, 01, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 05, 54},
    {01, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 01, 89, 19, 67, 48}
};

// #define UNIT_TEST

class PE0011
{
private:
    int m_maxProduct;

#ifdef UNIT_TEST
    int m_adjacentNumbersArray[max_steps];
#endif

    void getMaxProductFromUpToDown();
    void getMaxProductFromLeftToRight();
    void getMaxProductFromLeftDownToRightUp();
    void getMaxProductFromLeftUpToRightDown();

public:
    PE0011() { m_maxProduct = 1;};

    long getMaxProduct();

#ifdef UNIT_TEST
    void printAdjacentNumbers();
#endif
};

void PE0011::getMaxProductFromUpToDown()
{
    long product;

    // from up to down (0 --> 19) && from left -> right (0 --> 19)
    // Matrix[row][col], Matrix[row][col+1],
    //                   Matrix[row][col+2], Matrix[row][col+3]
    for (int row = 0; row < max_size; row++)
    {
        for (int col = 0; col + 3 < max_size; col++)
        {
            product = Matrix[row][col] * Matrix[row][col + 1]*\
                      Matrix[row][col + 2] * Matrix[row][col + 3];
            if (product > m_maxProduct)
            {
                m_maxProduct = product;
#ifdef UNIT_TEST
                m_adjacentNumbersArray[0] = Matrix[row][col];
                m_adjacentNumbersArray[1] = Matrix[row][col + 1];
                m_adjacentNumbersArray[2] = Matrix[row][col + 2];
                m_adjacentNumbersArray[3] = Matrix[row][col + 3];
#endif
            }
        }
    }
}

void PE0011::getMaxProductFromLeftToRight()
{
    long product;

    // from left -> right (0 --> 19) && from up to down (0 --> 19)
    // Matrix[col][row], Matrix[col][row+1],
    //                   Matrix[col][row+2], Matrix[col][row+3]
    for (int col = 0; col < max_size; col++)
    {
        for (int row = 0; row + 3 < max_size; row++)
        {
            product = Matrix[col][row] * Matrix[col][row + 1]*\
                      Matrix[col][row + 2] * Matrix[col][row + 3];
            if (product > m_maxProduct)
            {
                m_maxProduct = product;
#ifdef UNIT_TEST
                m_adjacentNumbersArray[0] = Matrix[col][row];
                m_adjacentNumbersArray[1] = Matrix[col][row + 1];
                m_adjacentNumbersArray[2] = Matrix[col][row + 2];
                m_adjacentNumbersArray[3] = Matrix[col][row + 3];
#endif
            }
        }
    }
}

void PE0011::getMaxProductFromLeftDownToRightUp()
{
    long product;

    // diagonally1:left-down to right-up
    // Matrix[row][col], Matrix[row-1][col+1],
    //                   Matrix[row-2][col+2], Matrix[row-3][col+3]
    for (int row = 3; row < max_size; row++)
    {
        for (int col = 0; col + 3 < max_size; col++)
        {
            product = Matrix[row][col] * Matrix[row - 1][col + 1]*\
                      Matrix[row - 2][col + 2] * Matrix[row - 3][col + 3];
            if (product > m_maxProduct)
            {
                m_maxProduct = product;
#ifdef UNIT_TEST
                m_adjacentNumbersArray[0] = Matrix[row][col];
                m_adjacentNumbersArray[1] = Matrix[row - 1][col + 1];
                m_adjacentNumbersArray[2] = Matrix[row - 2][col + 2];
                m_adjacentNumbersArray[3] = Matrix[row - 3][col + 3];
#endif
            }
        }
    }
}

void PE0011::getMaxProductFromLeftUpToRightDown()
{
    long product;

    // diagonally2:left-up to right-down
    // Matrix[row][col], Matrix[row+1][col+1],
    //                   Matrix[row+2][col+2], Matrix[row+3][col+3]
    for (int row = 0; row + 3 < max_size; row++)
    {
        for (int col = 0; col + 3 < max_size; col++)
        {
            product = Matrix[row][col] * Matrix[row + 1][col + 1]*\
                      Matrix[row + 2][col + 2] * Matrix[row + 3][col + 3];
            if (product > m_maxProduct)
            {
                m_maxProduct = product;
#ifdef UNIT_TEST
                m_adjacentNumbersArray[0] = Matrix[row][col];
                m_adjacentNumbersArray[1] = Matrix[row + 1][col + 1];
                m_adjacentNumbersArray[2] = Matrix[row + 2][col + 2];
                m_adjacentNumbersArray[3] = Matrix[row + 3][col + 3];
#endif
            }
        }
    }
}

#ifdef UNIT_TEST
void PE0011::printAdjacentNumbers()
{
    cout << "The four adjacent numbers are " << m_adjacentNumbersArray[0] << ", ";
    cout << m_adjacentNumbersArray[1] << ", " << m_adjacentNumbersArray[2] << ", ";
    cout << m_adjacentNumbersArray[3] << "." << endl;
}
#endif

long PE0011::getMaxProduct()
{
    getMaxProductFromLeftToRight();
    getMaxProductFromUpToDown();
    getMaxProductFromLeftDownToRightUp();
    getMaxProductFromLeftUpToRightDown();

    return m_maxProduct;
}

int main()
{
    PE0011 pe0011;

    cout << "The greatest product of four adjacent numbers in" << endl;
    cout << "any direction in the 20x20 grid is " << pe0011.getMaxProduct() << endl;

#ifdef UNIT_TEST
    pe0011.printAdjacentNumbers();
#endif

    return 0;
}