## Исходные данные
Исходными данными является последовательность целых чисел, хранящаяся в дереве.

- Значения элементов – целые числа.
- Максимальное значение элемента: 2 147 483 647
- Минимальное значение элемента: -2 147 483 647

## Выходные данные
Результат программы зависит от выбора пользователя:

Действием 1 происходит вывод текущего дерева в формате .gv в файл export.gv;  

Действием 2 происходит прямой вывод дерева;

Действием 3 происходит фланговый вывод дерева;

Действием 4 происходит обратный вывод дерева;

Действием 5 происходит добавление элемента в дерево;  

Действием 6 происходит удаление элемента из дерева если такой имеется.  

Действием 7 программа обходит каталог файлов, представленный в виде дерева, и удаляет файлы, с датой обращения меньше заданной.

## Описание задачи, реализуемой программой  
Программа получает на вход целочисленные деревья и выполняет простейшие операции над ними.  
## Способ обращения к программе  
Обращение с программой происходит с помощью консольного ввода.  
## Описание возможных аварийных ситуаций и ошибок пользователя.  
- Неверные данные данные стека – неверно задан элемент дерева.  
- Дерево уже пусто – попытка удалить элемент из пустого дерева.  
- Элемент не найден - попытка удалить элемент, которого нет в дереве.
- Элемент уже существует - попытка добавлить элемент, уже существующий в дереве.
