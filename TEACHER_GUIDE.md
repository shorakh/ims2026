# Инструкция для преподавателя
## Настройка репозитория на GitHub

---

## 1. Создать репозиторий на GitHub

1. Войдите в свой аккаунт GitHub
2. Нажмите **New repository**
3. Имя: `lab-ist` (или любое другое)
4. Видимость: **Public** (чтобы студенты могли делать Fork без организации)
5. Нажмите **Create repository**

---

## 2. Загрузить файлы из этого архива

```bash
git init
git add .
git commit -m "Initial: структура курса ИСиТ"
git branch -M main
git remote add origin https://github.com/<ваш-логин>/lab-ist.git
git push -u origin main
```

---

## 3. Защита ветки main

Чтобы студенты **не могли пушить напрямую**, а только через Pull Request:

1. Settings → Branches → **Add branch protection rule**
2. Branch name pattern: `main`
3. Включить: ✅ **Require a pull request before merging**
4. Включить: ✅ **Require status checks to pass before merging**
5. В поле статусов добавить: `Проверка структуры файлов`, `Запуск программы`, `Проверка синтаксиса Python`
6. Нажмите **Save changes**

---

## 4. Как принимать работы

### Автоматически (через GitHub Actions):
- Студент создаёт PR → Actions запускаются автоматически
- Зелёная галочка ✅ = все тесты прошли → работа может быть принята
- Красный крестик ❌ = есть ошибки → студент должен исправить

### Ручная проверка кода:
1. Откройте PR
2. Вкладка **Files changed** — посмотрите код
3. Оставьте комментарий или запросите правки через **Review**
4. После устного собеседования — нажмите **Merge pull request**

---

## 5. Таблица вариантов

Рекомендуется хранить соответствие студент ↔ вариант в отдельном файле (не в репо):

| ФИО студента | Группа | Вариант |
|-------------|--------|---------|
| Иванов И.И. | ИУС-21 | 1 |
| Петров П.П. | ИУС-21 | 2 |
| ...         | ...    | ... |

---

## 6. Структура репозитория

```
lab-ist/
├── README.md                    ← главная страница курса
├── report_template.md           ← шаблон отчёта для студентов
├── TEACHER_GUIDE.md             ← этот файл (для преподавателя)
├── .github/
│   └── workflows/
│       └── check.yml            ← автопроверка GitHub Actions
├── lab1/
│   ├── README.md                ← задание + 30 вариантов
│   └── variants/
│       └── variant01/           ← ПРИМЕР решения (образец)
│           ├── solution.py
│           └── report.md
├── lab2/
│   ├── README.md
│   └── variants/                ← сюда студенты добавляют свои папки
├── lab3/README.md
├── lab4/README.md
├── lab5/README.md
└── lab6/README.md
```

---

## 7. Возможные проблемы и решения

| Проблема | Решение |
|----------|---------|
| Actions не запускаются | Settings → Actions → Allow all actions |
| Студент не может сделать Fork | Убедитесь что репо **Public** |
| Actions не имеют доступа к коду | Settings → Actions → Workflow permissions → Read and write |
| Студент запушил не в ту ветку | Попросите пересоздать PR из правильной ветки |
