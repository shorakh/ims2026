# Студентам: быстрый старт

## 5 шагов для сдачи лабораторной

### 1️⃣ Сделайте Fork
Нажмите **Fork** на странице репозитория → **Create fork**

### 2️⃣ Клонируйте
```bash
git clone https://github.com/ВАШ-ЛОГИН/lab-ist.git
cd lab-ist
```

### 3️⃣ Создайте вашу папку
```bash
# Пример: лабораторная №1, вариант 7
mkdir -p lab1/variants/variant07
```

### 4️⃣ Добавьте файлы
```
lab1/variants/variant07/
    solution.py     ← ваш код
    report.md       ← отчёт (используйте шаблон report_template.md)
```

### 5️⃣ Отправьте Pull Request
```bash
git add .
git commit -m "ЛР1 Вариант 07 — Петров П.П."
git push origin main
```
Затем на GitHub: **Compare & pull request** → **Create pull request**

---

## Пример структуры `solution.py`

```python
import sys

def main():
    if len(sys.argv) < 2:
        print("Использование: python solution.py input.txt")
        sys.exit(1)
    
    filepath = sys.argv[1]
    # ... ваш код ...

if __name__ == "__main__":
    main()
```

---

## Что проверяет автоматика

| Проверка | Что именно |
|----------|-----------|
| 📁 Структура | Наличие `solution.py` и `report.md` |
| 🔍 Синтаксис | Нет синтаксических ошибок Python |
| 🐍 Запуск | Программа запускается и не падает с ошибкой |

Посмотреть детали: вкладка **Checks** в вашем Pull Request.
