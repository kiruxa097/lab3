#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

template <typename T>
class Matrix : public vector<vector<T>> {
    private:
        int line; // кол-во строк
        int col; // кол-во столбцов
        vector<T> max_values; // вектор, который используем в find_max_v(), храним в нем максимальные элементы в строках
        vector<int> arr_num;  // вектор, который используем в find_max_v(), храним в нем индексы столбцов, в которых элементы из max_values
    public:
        Matrix(int row, int column, T val = 0) : vector<vector<T>> (row, vector<T>(column, val)) {
            line = row;
            col = column;
            max_values.resize(line);
            arr_num.resize(line);
        }


        void find_max_v(){

            // Поиск максимального по модулю значения в строке - выбор ведущего элемента
            for (int i = 0; i < line; i++){

                T max_abs_val = 0;
                int t_p = 0;
                for (int j = 0; j < col; j++){
                    if (abs((*this)[i][j]) > max_abs_val) {
                        bool flag = true;
                        for (int q = 0; q < i; q++) {
                            if (arr_num[q] == j) { flag = false; break; }
                        }
                        if (flag) {
                            max_abs_val = abs((*this)[i][j]);
                            t_p = j;
                        }
                    }
                }
                max_values[i] = max_abs_val;
                arr_num[i] = t_p;
            }
        }

        void straight_to_del(){

            // Зануляем не ведущие элементы в столбцах
            for (int i = 0; i < line; i++) {
                T t1 = max_values[i]; // умножаем это число на строку, в которой будем занулять элемент 
                for (int j = i + 1; j < line; j++){
                    T t2 = (*this)[j][arr_num[i]]; // умножаем это число на строку, которую будем вычитать 
                    for (int u = 0; u < col; u++) {
                        (*this)[j][u] = (*this)[j][u]*t1 - (*this)[i][u]*t2;
                    }
                    max_values[j] = (*this)[j][arr_num[j]];
                }
                for (int j = i - 1; j >= 0; j--){
                    T t2 = (*this)[j][arr_num[i]]; // умножаем это число на строку, которую будем вычитать 
                    for (int u = 0; u < col; u++) {
                        (*this)[j][u] = (*this)[j][u]*t1 - (*this)[i][u]*t2;
                    }
                    max_values[j] = (*this)[j][arr_num[j]];
                }
            }
        }
};