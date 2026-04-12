"""
Лабораторная работа №1 — Частотная таблица файла. Энтропия
Вариант 1: Вывести таблицу символов, отсортированную по убыванию частоты; показать топ-5

Пример решения (можно использовать как образец структуры)
"""
import sys
import math
from collections import Counter


def build_frequency_table(text):
    """Подсчёт частоты символов."""
    return Counter(text)


def compute_entropy(freq_table, total):
    """Вычисление энтропии по Шеннону."""
    entropy = 0.0
    for count in freq_table.values():
        p = count / total
        if p > 0:
            entropy -= p * math.log2(p)
    return entropy


def main():
    if len(sys.argv) < 2:
        print("Использование: python solution.py input.txt")
        sys.exit(1)

    filepath = sys.argv[1]
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            text = f.read()
    except FileNotFoundError:
        print(f"Ошибка: файл '{filepath}' не найден")
        sys.exit(1)

    total = len(text)
    if total == 0:
        print("Файл пустой")
        sys.exit(1)

    freq = build_frequency_table(text)
    n = len(freq)  # мощность алфавита

    # Энтропия
    H = compute_entropy(freq, total)
    H_max = math.log2(n) if n > 1 else 0
    R = 1 - (H / H_max) if H_max > 0 else 0

    # Основной вывод
    print(f"Файл: {filepath}")
    print(f"Всего символов: {total}")
    print(f"Уникальных символов: {n}")
    print(f"Энтропия H = {H:.4f} бит")
    print(f"Макс. энтропия Hmax = {H_max:.4f} бит")
    print(f"Избыточность R = {R:.4f} ({R*100:.2f}%)")
    print()

    # Вариант 1: топ-5 по убыванию частоты
    print("Топ-5 символов по частоте:")
    print(f"{'Символ':<10} {'Частота':>8} {'Вероятность':>12}")
    print("-" * 32)
    for char, count in freq.most_common(5):
        display = repr(char) if char in ('\n', '\t', ' ') else char
        prob = count / total
        print(f"{display:<10} {count:>8} {prob:>12.4f}")


if __name__ == "__main__":
    main()
