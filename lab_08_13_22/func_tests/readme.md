# Тесты для лабораторной работы №08
## Входные данные
Файл с размерами, кол-вом и координатами ненулевых элментов матрицы
## Выходные данные
Сумма матриц, произведение матрицы или определитель матрицы
## Позитивные тесты:
- 01 - Сумма: отсутствуют нулевые элементы
- 02 - Сумма: матрица 1x1
- 03 - Сумма: присутствуют нулевые элементы
- 04 - Сумма: Не квадратные матрицы
- 05 - Умножение: отсутствуют нулевые элементы
- 06 - Умножение: матрица 1x1
- 07 - Умножение: присутствуют нулевые элементы
- 08 - Умножение: Не квадратные матрицы
- 09 - Определитель: матрица 1x1
- 10 - Определитель: матрица 2x2
- 11 - Определитель: матрица 3x3
- 12 - Определитель: матрица 4x4
- 13 - Определитель: Нулевая матрица

## Негативные тесты:
- 01 - Пустой файл
- 02 - Файл отсутствует
- 02 - Вместо размерности буква
- 03 - Ненулевых элементов больше, чем размер матрицы
- 04 - Вместо координаты буква
- 05 - вместо значения буква
- 06 - Сумма: матрицы не равных размерностей
- 07 - Произведение: матрицы не согласованы
- 08 - Определитель: матрица не квадратная
- 09 - Неверный ключ
- 10 - Ключей больше чем необходимо
- 11 - Нет файла для результата
