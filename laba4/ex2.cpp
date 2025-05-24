#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm> // Для std::reverse_copy

using namespace std;

int main() {
    // Инициализация генератора случайных чисел
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-250, 250);

    // Задание 1
    cout << "=== Задание 1 ===\n";
    int n;
    do {
        cout << "Введите размер массива (n >= 20): ";
        cin >> n;
    } while(n < 20);

    vector<int> arr(n);
    for(auto& x : arr) x = dist(gen);

    cout << "Сгенерированный массив:\n";
    for(const auto& x : arr) cout << x << " ";
    cout << "\n\n";

    // Задание 2
    cout << "=== Задание 2 ===\n";
    int negative_count = 0;
    int min_abs_value = abs(arr[0]);
    int min_abs_index = 0;
    long long sum_after_min = 0; // Используем long long для суммы, чтобы избежать переполнения

    for(int i = 0; i < n; ++i) {
        if(arr[i] < 0) negative_count++;
        
        if(abs(arr[i]) < min_abs_value) {
            min_abs_value = abs(arr[i]);
            min_abs_index = i;
        }
    }

    for(int i = min_abs_index + 1; i < n; ++i) {
        sum_after_min += abs(arr[i]);
    }

    cout << "Количество отрицательных элементов: " << negative_count << "\n";
    cout << "Сумма модулей после минимального по модулю элемента: " 
         << sum_after_min << "\n\n";

    // Задание 3
    cout << "=== Задание 3 ===\n";
    int max_len = 0, current_len = 0; // Инициализируем нулем для случая, если нет убыв. последовательности
    int start_idx = 0, end_idx = -1; // end_idx = -1 означает, что последовательность не найдена
    int current_start = 0;

    if (n > 0) { // Только если массив не пуст
        max_len = 1;
        current_len = 1;
        end_idx = 0; // По умолчанию первая последовательность - один элемент
         for(int i = 1; i < n; ++i) {
            if(arr[i] < arr[i-1]) {
                current_len++;
            } else {
                if(current_len > max_len) {
                    max_len = current_len;
                    start_idx = current_start;
                    end_idx = i - 1;
                }
                current_len = 1;
                current_start = i;
            }
        }
        // Проверка после цикла для последней последовательности
        if(current_len > max_len) {
            max_len = current_len;
            start_idx = current_start;
            end_idx = n - 1;
        }
    }


    if (end_idx != -1) {
        cout << "Самая длинная убывающая последовательность:\n";
        cout << "Индексы: [" << start_idx << " - " << end_idx << "]\n";
        cout << "Длина: " << max_len << "\n";
        cout << "Элементы: ";
        for(int i = start_idx; i <= end_idx; ++i) cout << arr[i] << " ";
        cout << "\n\n";
    } else {
        cout << "Убывающая последовательность не найдена.\n\n";
    }


    // Задание 4
    cout << "=== Задание 4 ===\n";
    if (end_idx != -1 && max_len > 0) { // Только если последовательность была найдена
        vector<int> reversed_seq(max_len);
        reverse_copy(arr.begin() + start_idx, arr.begin() + end_idx + 1, reversed_seq.begin());
        
        cout << "Перевернутая последовательность:\n";
        for(const auto& x : reversed_seq) cout << x << " ";
        cout << "\n\n";
    } else {
        cout << "Нет последовательности для переворачивания.\n\n";
    }


    // Задание 5
    cout << "=== Задание 5 ===\n";
    int m, k;
    
    // Первый массив
    do {
        cout << "Введите размер первого массива (m > 0): ";
        cin >> m;
    } while(m <= 0);
    
    vector<int> arr1(m);
    cout << "Введите элементы первого массива (или оставьте для авто-генерации):\n";
    // Пример ручного ввода для теста:
    // if (m == 5) arr1 = {1, 2, 3, 4, 5}; else for(auto& x : arr1) x = dist(gen);
for(auto& x : arr1) x = dist(gen); // Оставляем авто-генерацию
    
    // Второй массив
    do {
        cout << "Введите размер второго массива (k > 0): ";
        cin >> k;
    } while(k <= 0);
    
    vector<int> arr2(k);
    cout << "Введите элементы второго массива (или оставьте для авто-генерации):\n";
    // Пример ручного ввода для теста:
    // if (k == 3) arr2 = {1, 2, 3}; else for(auto& x : arr2) x = dist(gen);
    for(auto& x : arr2) x = dist(gen); // Оставляем авто-генерацию

    // Вывод исходных массивов
    cout << "\nПервый массив до сдвига:\n";
    for(const auto& x : arr1) cout << x << " ";
    cout << "\nВторой массив до сдвига:\n";
    for(const auto& x : arr2) cout << x << " ";
    cout << "\n\n";

    // Выполнение сдвига согласно примеру
    // ([1, 2, 3, 4, 5] и [1, 2, 3] → [3, 1, 2, 3, 4] и [5, 1, 2])
    if (m > 0 && k > 0) { // Убедимся, что массивы не пусты
        int last_arr1 = arr1.back();
        int last_arr2 = arr2.back();

        // Сдвиг первого массива
        for(int i = m - 1; i > 0; --i) {
            arr1[i] = arr1[i-1];
        }
        arr1[0] = last_arr2;

        // Сдвиг второго массива
        for(int i = k - 1; i > 0; --i) {
            arr2[i] = arr2[i-1];
        }
        arr2[0] = last_arr1;
    } else if (m > 0) { // Если только первый массив не пуст, сдвигаем его циклически
        if (m > 1) {
            int last = arr1.back();
            for(int i = m-1; i > 0; --i)
                arr1[i] = arr1[i-1];
            arr1[0] = last;
        }
    } else if (k > 0) { // Если только второй массив не пуст, сдвигаем его циклически
         if (k > 1) {
            int last = arr2.back();
            for(int i = k-1; i > 0; --i)
                arr2[i] = arr2[i-1];
            arr2[0] = last;
        }
    }


    // Вывод результатов
    cout << "Первый массив после сдвига: ";
    for(const auto& x : arr1) cout << x << " ";
    cout << "\nВторой массив после сдвига: ";
    for(const auto& x : arr2) cout << x << " ";
    cout << endl;

    return 0;
}
