#include <iostream>
#include <vector>
#include <string>
#include "matrix.cpp"

using namespace std;

int main()
{
    cout << "Last column in vector is vector ans" << endl;
    int row, column;
    cout << "Input row matrix: ";
    cin >> row;
    cout << "Input column matrix: ";
    cin >> column;
    cout << endl;
    Matrix<float> m(row, column);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cout << "Input [" << i << "]" << "[" << j << "]" << " value: ";
            cin >> m[i][j];
        }
    }
    m.print();
    m.gaus();
    return 0;
}