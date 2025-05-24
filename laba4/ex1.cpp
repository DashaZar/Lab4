#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

const double E = 0.0001; // Точность

// Функция f(x) = sin(x) - 2x - 1
double f(double x) {
    return sin(x) - 2*x - 1;
}

// Производная f'(x) = cos(x) - 2
double f1(double x) {
    return cos(x) - 2;
}

// Функция phi(x) = (sin(x) - 1)/2
double phi(double x) {
    return (sin(x) - 1)/2;
}

// Метод половинного деления
int halfDivision(double a, double b, vector<double>& roots) {
    if (f(a) * f(b) >= 0.0) {
        cout << "Неверный интервал для метода половинного деления" << endl;
        return 0;
    }
    int k = 0;
    double c;
    cout << "МЕТОД ПОЛОВИННОГО ДЕЛЕНИЯ" << endl;
    cout << setw(2) << "N" << " | " << setw(7) << "an" << " | " 
         << setw(9) << "bn" << " | " << "bn - an" << endl;
    while (abs(b - a) >= E) {
        c = (a + b)/2;
        cout << setw(2) << k << " | " << fixed << setprecision(4) << setw(7) << a
             << " | " << setw(9) << b << " | " << abs(b - a) << endl;
        if (f(c) == 0.0) break;
        if (f(c)*f(a) < 0) b = c;
        else a = c;
        k++;
    }
    roots.push_back(c);
    cout << "КОРЕНЬ " << fixed << setprecision(4) << c << " ЗА " << k << " ИТЕРАЦИЙ" << endl;
    return k;
}

// Метод Ньютона
int newtonMethod(double x0, vector<double>& roots) {
    int k = 0;
    double x1 = x0 - f(x0)/f1(x0);
    cout << "\nМЕТОД НЬЮТОНА" << endl;
    cout << setw(2) << "N" << " | " << setw(7) << "xn" << " | " 
         << setw(9) << "xn+1" << " | " << "xn+1 - xn" << endl;
    while (abs(x1 - x0) > E) {
        cout << setw(2) << k << " | " << fixed << setprecision(4) << setw(7) << x0
             << " | " << setw(9) << x1 << " | " << abs(x1 - x0) << endl;
        x0 = x1;
        x1 = x0 - f(x0)/f1(x0);
        k++;
    }
    roots.push_back(x1);
    cout << "КОРЕНЬ " << fixed << setprecision(4) << x1 << " ЗА " << k << " ИТЕРАЦИЙ" << endl;
    return k;
}

// Метод простых итераций
int simpleIterations(double x0, vector<double>& roots) {
    int k = 0;
    double x1 = phi(x0);
    cout << "\nМЕТОД ПРОСТЫХ ИТЕРАЦИЙ" << endl;
    cout << setw(2) << "N" << " | " << setw(7) << "xn" << " | " 
         << setw(9) << "xn+1" << " | " << "xn+1 - xn" << endl;
    while (abs(x1 - x0) > E) {
        cout << setw(2) << k << " | " << fixed << setprecision(4) << setw(7) << x0
             << " | " << setw(9) << x1 << " | " << abs(x1 - x0) << endl;
        x0 = x1;
        x1 = phi(x0);
        k++;
    }
    roots.push_back(x1);
    cout << "КОРЕНЬ " << fixed << setprecision(4) << x1 << " ЗА " << k << " ИТЕРАЦИЙ" << endl;
    return k;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    vector<double> roots;
    int s1, s2, s3;

    // Метод половинного деления на [-1, 0]
    s1 = halfDivision(-1, 0, roots);

    // Метод Ньютона с начальным приближением x0 = -1
    s2 = newtonMethod(-1, roots);

    // Метод простых итераций с начальным приближением x0 = -1
    s3 = simpleIterations(-1, roots);

    // Вывод корней
    cout << "\nНАЙДЕННЫЕ КОРНИ:" << endl;
    for (double root : roots) {
        cout << fixed << setprecision(4) << root << " ";
    }
    cout << endl;

    // Сравнение методов
    cout << "\nСРАВНЕНИЕ СКОРОСТИ СХОДИМОСТИ:" << endl;
    cout << "Метод половинного деления: " << s1 << " итераций" << endl;
    cout << "Метод Ньютона: " << s2 << " итераций" << endl;
    cout << "Метод простых итераций: " << s3 << " итераций" << endl;

    return 0;
}
