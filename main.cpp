#include <iostream>
#include <vector>
#include "matrix.cpp"

using namespace std;

int main()
{
    Matrix<float> m(3,4);
    m[0][1] = 1;
    cout << m[0][1];
    return 0;
}