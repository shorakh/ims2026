#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

// структура одного символа и его кода
struct Node {
    unsigned char symbol; // сам символ
    long long freq;       // частота появления
    string code;          // код шенона-фано
};

// для хранения шагов разбиения
vector<string> steps;

// алгоритм шенона-фано 
void shannonFano(vector<Node>& v, int l, int r) {
    if (l >= r) return;

    long long total = 0;

    // считаем суммарную частоту текущего диапазона
    for (int i = l; i <= r; i++) total += v[i].freq;

    long long leftSum = 0;
    int bestSplit = l;
    long long bestDiff = LLONG_MAX;

    // ищем оптимальную точку разбиения
    for (int i = l; i < r; i++) {
        leftSum += v[i].freq;
        long long diff = abs(leftSum - (total - leftSum));

        if (diff < bestDiff) {
            bestDiff = diff;
            bestSplit = i;
        }
    }

    // сохраняем шаг разбиения
    steps.push_back("Группа [" + to_string(l) + "-" + to_string(bestSplit) +
        "] | [" + to_string(bestSplit + 1) + "-" + to_string(r) + "]");

    // добавляем биты кодов лево - 0 право - 1
    for (int i = l; i <= bestSplit; i++) v[i].code += "0";
    for (int i = bestSplit + 1; i <= r; i++) v[i].code += "1";

    // рекурсивно делим дальше
    shannonFano(v, l, bestSplit);
    shannonFano(v, bestSplit + 1, r);
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    // проверка аргументов
    if (argc < 2) {
        cout << "Использование: solution.exe input.txt\n";
        return 1;
    }

    string filename = argv[1];

    // открываем файл в бинарном режиме и сразу в конец
    ifstream f(filename, ios::binary | ios::ate);
    if (!f) {
        cout << "Файл не найден: " << filename << endl;
        return 1;
    }

    long long fileSize = f.tellg();
    f.seekg(0);

    // читаем весь файл в память
    vector<unsigned char> data(fileSize);
    if (fileSize) f.read(reinterpret_cast<char*>(data.data()), fileSize);
    f.close();

    // массив частот символов
    long long cnt[256] = { 0 };

    // считаем частоты
    for (auto b : data) {
        if (b == '\n' || b == '\r' || b == '\t') continue;
        cnt[b]++;
    }

    // список символов которые встречаются в файле
    vector<Node> v;
    for (int i = 0; i < 256; i++) {
        if (cnt[i] > 0) {
            v.push_back({ (unsigned char)i, cnt[i], "" });
        }
    }

    if (v.empty()) {
        cout << "Нет данных\n";
        return 0;
    }

    // сортировка по убыванию частоты
    sort(v.begin(), v.end(), [](const Node& a, const Node& b) {
        return a.freq > b.freq;
        });

    // построение кодов
    shannonFano(v, 0, (int)v.size() - 1);

    cout << "Файл: " << filename << endl;
    cout << "Метод: Шеннон-Фано" << endl;

    cout << "\nКодовая таблица:" << endl;
    cout << "Символ | Частота | Код          | Длина" << endl;

    long long totalSymbols = 0;
    for (const auto& x : v) totalSymbols += x.freq;

    double L = 0.0; // средняя длина кода
    double H = 0.0; // энтропия

    for (const auto& x : v) {
        double p = static_cast<double>(x.freq) / totalSymbols;
        int len = (int)x.code.length();

        // средняя длина
        L += p * len;

        // энтропия
        if (p > 0) H -= p * log2(p);

        // вывод символов
        cout << "'";
        if (x.symbol == '\'') cout << "\\'";
        else if (x.symbol == '\\') cout << "\\\\";
        else cout << x.symbol;
        cout << "' |";

        cout << setw(8) << x.freq << " | "
            << left << setw(12) << x.code
            << " | " << len << endl;
    }

    // коэффициент сжатия
    double K = (L > 0) ? (8.0 / L) : 0.0;

    cout << fixed << setprecision(4);
    cout << "\nСредняя длина кодового слова L = " << L << " бит" << endl;
    cout << "Энтропия H = " << H << " бит" << endl;
    cout << "Коэффициент сжатия K = " << K << endl;

    cout << "\nШаги разбиения на группы:" << endl;
    for (const auto& s : steps) {
        cout << s << endl;
    }

    return 0;
}