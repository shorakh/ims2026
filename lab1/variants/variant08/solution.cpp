#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    // чек аргументов командной строки 
    if (argc < 2) {
        cout << "Использование: program input.txt\n";
        return 1;
    }

    string name = argv[1];

    // открытие файла в бинарном режиме и переход в конец чтобы сразу узнать размер файла
    ifstream f(name, ios::binary | ios::ate);
    if (!f) {
        cout << "Файл не найден\n";
        return 1;
    }

    // размер файла в байтах
    long long size = f.tellg();
    f.seekg(0); // возврат в начало файла для чтения

    // чтение всего файла в память
    vector<unsigned char> data(size);
    if (size) {
        f.read((char*)data.data(), size);
    }
    f.close();

    // чвстоты
    long long cnt[256] = { 0 };

    for (auto b : data) {
        // игнорируем служебные спец символы
        if (b == '\n' || b == '\r' || b == '\t')
            continue;

        cnt[b]++;
    }

    // вектор для тех символов которые встретились
    vector<pair<int, long long>> v;

    for (int i = 0; i < 256; i++) {
        if (cnt[i]) {
            v.emplace_back(i, cnt[i]);
        }
    }

    // сортировка по убыванию
    sort(v.begin(), v.end(),
        [](auto a, auto b) {
            return a.second > b.second;
        });

    long long total = 0;

    // общее количество символов
    for (auto& p : v) total += p.second;

    double h = 0.0;
    vector<double> probabilities;

    // вычисление вероятностей и энтропии
    for (auto& p : v) {
        double pi = (double)p.second / total;
        probabilities.push_back(pi);
        h -= pi * log2(pi);
    }

    int N = v.size();

    // макс энтропия
    double h_max = (N > 0) ? log2(N) : 0;

    // избыточность
    double R = (h_max > 0) ? (1 - h / h_max) : 0;

    cout << "Файл: " << name << endl;
    cout << "Всего символов: " << total << endl;
    cout << "Уникальных символов: " << N << endl;

    cout << fixed << setprecision(4);
    cout << "Энтропия H = " << h << " бит" << endl;
    cout << "Макс. энтропия Hmax = " << h_max << " бит" << endl;
    cout << "Избыточность R = " << R << " (" << R * 100 << "%)" << endl;

    ofstream csv("output.csv");

    // заголовок csv файла
    csv << "символ;частота;вероятность\n";

    for (size_t i = 0; i < v.size(); i++) {
        int byte = v[i].first;
        long long count = v[i].second;
        double pi = probabilities[i];

        // байт в символ
        string symbol(1, (char)byte);

        // кавычки для csv
        if (symbol == "\"") {
            symbol = "\"\"";
        }

        // запись строки csv
        csv << "\"" << symbol << "\""
            << ";" << count
            << ";" << fixed << setprecision(6) << pi
            << "\n";
    }

    csv.close();

    cout << "Файл output.csv создан\n";

    return 0;
}