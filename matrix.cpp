#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

template <typename T>
class Matrix : public vector<vector<T>>
{
private:
    int line;             // кол-во строк
    int col;              // кол-во столбцов
    vector<T> max_values; // вектор, который используем в find_max_v(), храним в нем максимальные элементы в строках
    vector<int> arr_num;  // вектор, который используем в find_max_v(), храним в нем индексы столбцов, в которых элементы из max_values
public:
    Matrix(int row, int column, T val = 0) : vector<vector<T>>(row, vector<T>(column, val))
    {
        line = row;
        col = column;
        max_values.resize(line);
        arr_num.resize(line);
    }

    void find_max_v()
    {

        // Поиск максимального по модулю значения в строке - выбор ведущего элемента
        for (int i = 0; i < line; i++)
        {

            T max_abs_val = 0;
            int t_p = 0;
            for (int j = 0; j < col - 1; j++)
            {
                if (abs((*this)[i][j]) > max_abs_val)
                {
                    bool flag = true;
                    for (int q = 0; q < i; q++)
                    {
                        if (arr_num[q] == j)
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (flag)
                    {
                        max_abs_val = (*this)[i][j];
                        t_p = j;
                    }
                }
            }
            max_values[i] = max_abs_val;
            arr_num[i] = t_p;
        }
    }

    void straight_to_del()
    {

        // Зануляем не ведущие элементы в столбцах
        for (int i = 0; i < line; i++)
        {
            T t1 = max_values[i]; // умножаем это число на строку, в которой будем занулять элемент
            for (int j = i + 1; j < line; j++)
            {
                T t2 = (*this)[j][arr_num[i]]; // умножаем это число на строку, которую будем вычитать
                T d = t2 / t1;
                for (int u = 0; u < col; u++)
                {
                    (*this)[j][u] = (*this)[j][u] - (*this)[i][u] * d;
                }
                max_values[j] = (*this)[j][arr_num[j]];
            }
            for (int j = i - 1; j >= 0; j--)
            {
                T t2 = (*this)[j][arr_num[i]]; // умножаем это число на строку, которую будем вычитать
                T d = t2 / t1;
                for (int u = 0; u < col; u++)
                {
                    (*this)[j][u] = (*this)[j][u] - (*this)[i][u] * d;
                }
                max_values[j] = (*this)[j][arr_num[j]];
            }
        }
    }

    void print()
    {
        cout << "matrix: \n";
        for (int i = 0; i < line; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cout << " " << (*this)[i][j] << " ";
            }
            cout << endl;
        }
    }

    void solve_problem()
    {
        find_max_v();
        straight_to_del();
    }

    vector<T> get_row(int i)
    {
        try
        {
            return (*this).at(i);
        }
        catch (const out_of_range &e)
        {
            cout << "Index out of range: " << e.what() << endl;
            return vector<T>();
        }
    }

    void gaus()
    {
        solve_problem();
        for (int i = 0; i < line; i++)
        {
            T d = (*this)[i][arr_num[i]];
            cout << "x" << arr_num[i] + 1 << " = " << (*this)[i][col - 1] / d;
            for (int j = 0; j < col - 1; j++)
            {
                if ((*this)[i][j] != 0 && j != arr_num[i])
                {
                    cout << "-(" << (*this)[i][j] / d << ")" << "*x" << j + 1 << "";
                }
            }
            cout << endl;
        }
    }
};