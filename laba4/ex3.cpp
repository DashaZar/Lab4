#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void generateSequence(long long x0, long long a, long long b, long long c) {
    vector<long long> sequence;
    unordered_map<long long, size_t> seen;

    sequence.push_back(x0);
    seen[x0] = 0;

    size_t i = 1;
    const size_t maxIterations = 1000;
    size_t cycleStart = 0;
    size_t cycleLength = 0;
    bool cycleFound = false;

    while (i < maxIterations) {
        long long next = (a * sequence[i - 1] + b) % c;
        sequence.push_back(next);

        if (seen.count(next)) {
            cycleStart = seen[next];
            cycleLength = i - cycleStart;
            cycleFound = true;
            break;
        }

        seen[next] = i;
        ++i;
    }

    if (cycleFound) {
        size_t targetSize = cycleStart + cycleLength * 2;
        while (sequence.size() < targetSize && sequence.size() < maxIterations) {
            long long next = (a * sequence.back() + b) % c;
            sequence.push_back(next);
        }

        cout << "Сгенерированная последовательность: ";
        size_t idx = 0;
        for (long long value : sequence) {
            if (idx >= targetSize) break;
            cout << value << " ";
            idx++;
        }
        cout << endl;
        cout << cycleStart + cycleLength + 1 << endl;
    } else {
        cout << "Цикл не найден в пределах " << maxIterations << " итераций." << endl;
        cout << "Сгенерированная последовательность: ";
        for (long long value : sequence) {
            cout << value << " ";
        }
        cout << endl;
    }
}

int main() {
    long long x0, a, b, c;

    cout << "Введите начальное значение X0 (0 <= X0 < C): ";
    cin >> x0;
    cout << "Введите множитель A (0 <= A <= C): ";
    cin >> a;
    cout << "Введите инкремент B (0 <= B <= C): ";
    cin >> b;
    cout << "Введите модуль C (C > 0): ";
    cin >> c;

    if (c <= 0 || x0 < 0 || x0 >= c || a < 0 || a > c || b < 0 || b > c) {
        cout << "Некорректные входные данные!" << endl;
        return 1;
    }

    generateSequence(x0, a, b, c);

    return 0;
}
