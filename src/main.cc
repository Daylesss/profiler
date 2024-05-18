#include <iostream>
#include <chrono>
#include <cstdlib>

const int ROWS = 100000;
const int COLS = 10000;

int** GetArray(int rows, int cols) {
    int** array = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) {
        array[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; ++j) {
            array[i][j] = i * cols + j;
        }
    }
    return array;
}

void readArrayRow(int** array, int rows, int cols) {
    volatile int sum = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum += array[i][j];
        }
    }
}

void readArrayCol(int** array, int rows, int cols) {
    volatile int sum = 0;
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            sum += array[i][j];
        }
    }
}

// Основная функция
int main() {
    // Выделение памяти и заполнение двумерного массива числами
    int** array = GetArray(ROWS, COLS);
    auto start = std::chrono::steady_clock::now();

    // readArrayRow(array, ROWS, COLS);
// Время чтения элементов: 66846247 микросекунд
// ==41464== 
// ==41464== I   refs:      38,036,230,473
// ==41464== I1  misses:             2,100
// ==41464== LLi misses:             2,059
// ==41464== I1  miss rate:           0.00%
// ==41464== LLi miss rate:           0.00%
// ==41464== 
// ==41464== D   refs:      21,013,024,856  (19,007,828,541 rd   + 2,005,196,315 wr)
// ==41464== D1  misses:       125,943,231  (    63,149,115 rd   +    62,794,116 wr)
// ==41464== LLd misses:       125,247,452  (    62,633,427 rd   +    62,614,025 wr)
// ==41464== D1  miss rate:            0.6% (           0.3%     +           3.1%  )
// ==41464== LLd miss rate:            0.6% (           0.3%     +           3.1%  )
// ==41464== 
// ==41464== LL refs:          125,945,331  (    63,151,215 rd   +    62,794,116 wr)
// ==41464== LL misses:        125,249,511  (    62,635,486 rd   +    62,614,025 wr)
// ==41464== LL miss rate:             0.2% (           0.1%     +           3.1%  )



    readArrayCol(array, ROWS, COLS);
// Время чтения элементов: 399049411 микросекунд
// ==43641== 
// ==43641== I   refs:      38,035,420,492
// ==43641== I1  misses:             2,100
// ==43641== LLi misses:             2,059
// ==43641== I1  miss rate:           0.00%
// ==43641== LLi miss rate:           0.00%
// ==43641== 
// ==43641== D   refs:      21,012,484,859  (19,007,378,543 rd   + 2,005,106,316 wr)
// ==43641== D1  misses:     1,188,407,760  ( 1,125,613,644 rd   +    62,794,116 wr)                                   
// ==43641== LLd misses:     1,187,723,893  ( 1,125,109,868 rd   +    62,614,025 wr)
// ==43641== D1  miss rate:            5.7% (           5.9%     +           3.1%  )
// ==43641== LLd miss rate:            5.7% (           5.9%     +           3.1%  )
// ==43641== 
// ==43641== LL refs:        1,188,409,860  ( 1,125,615,744 rd   +    62,794,116 wr)
// ==43641== LL misses:      1,187,725,952  ( 1,125,111,927 rd   +    62,614,025 wr)
// ==43641== LL miss rate:             2.0% (           2.0%     +           3.1%  )

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Вывод времени выполнения
    std::cout << "Время чтения элементов: " << duration << " микросекунд" << std::endl;

    return 0;
}

