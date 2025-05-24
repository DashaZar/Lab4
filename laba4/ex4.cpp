#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <set>

using namespace std;

vector<int> borda_winners(const vector<vector<int>>& prefs, int n) {
    vector<int> scores(n, 0);
    for (const auto& ranking : prefs) {
        for (int pos = 0; pos < n; ++pos) {
            scores[ranking[pos]] += (n - 1 - pos);
        }
    }
    
    int max_score = *max_element(scores.begin(), scores.end());
    vector<int> winners;
    for (int i = 0; i < n; ++i) {
        if (scores[i] == max_score) winners.push_back(i);
    }
    return winners;
}

bool is_condorcet_winner(int c, const vector<vector<int>>& prefs, int n, int k) {
    for (int other = 0; other < n; ++other) {
        if (other == c) continue;
        int wins = 0;
        for (const auto& ranking : prefs) {
            auto c_pos = find(ranking.begin(), ranking.end(), c);
            auto other_pos = find(ranking.begin(), ranking.end(), other);
            if (c_pos < other_pos) wins++;
        }
        if (wins <= k / 2) return false;
    }
    return true;
}

int condorcet_winner(const vector<vector<int>>& prefs, int n, int k) {
    for (int c = 0; c < n; ++c) {
        if (is_condorcet_winner(c, prefs, n, k)) return c;
    }
    return -1;
}

int main() {
    int n, k;
    cout << "Введите количество кандидатов (n): ";
    cin >> n;
    cout << "Введите количество избирателей (k): ";
    cin >> k;
    cin.ignore();

    // Ввод имён кандидатов
    vector<string> candidates(n);
    unordered_map<string, int> candidate_to_idx;
    cout << "Введите имена кандидатов (как есть, без нормализации):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Кандидат " << i+1 << ": ";
        getline(cin, candidates[i]);
        if (candidate_to_idx.count(candidates[i])) {
            cerr << "Ошибка: Кандидат '" << candidates[i] << "' уже существует!";
            return 1;
        }
        candidate_to_idx[candidates[i]] = i;
    }

    // Ввод предпочтений
    vector<vector<int>> prefs(k, vector<int>(n));
    cout << "\nВведите предпочтения (" << n << " имен через пробел):\n";
    for (int i = 0; i < k; ++i) {
        while (true) {
            cout << "Избиратель " << i+1 << ": ";
            string line;
            getline(cin, line);
            stringstream ss(line);
            vector<int> votes;
            string name;
            bool error = false;

            while (ss >> name) {
                if (!candidate_to_idx.count(name)) {
                    cout << "Ошибка: Неизвестный кандидат '" << name << "'\n";
                    error = true;
                    break;
                }
                votes.push_back(candidate_to_idx[name]);
            }

            if (error) continue;
            if (votes.size() != n) {
                cout << "Ошибка: Нужно " << n << " кандидатов!\n";
                continue;
            }

            set<int> unique(votes.begin(), votes.end());
            if (unique.size() != n) {
                cout << "Ошибка: Повторы в списке!\n";
                continue;
            }

            prefs[i] = votes;
            break;
        }
    }

    // Результаты
    vector<int> borda = borda_winners(prefs, n);
    int condorcet = condorcet_winner(prefs, n, k);

    cout << "\nРезультаты:\nМетод Борда: ";
    if (borda.size() == 1) cout << candidates[borda[0]];
    else {
        cout << "Ничья между: ";
        for (size_t i = 0; i < borda.size(); ++i) {
            cout << "'" << candidates[borda[i]] << "'";
            if (i != borda.size()-1) cout << ", ";
        }
    }

    cout << "\nМетод Кондорсе: ";
    if (condorcet != -1) cout << candidates[condorcet];
    else cout << "Нет победителя";

    if (condorcet != -1 && find(borda.begin(), borda.end(), condorcet) == borda.end()) {
        cout << "\n\n⚠️ Методы дали разных победителей!";
    }

    return 0;
}
