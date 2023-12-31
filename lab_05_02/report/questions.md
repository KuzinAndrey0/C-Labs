1. Что такое FIFO и LIFO?

   FIFO - First In First Out - первый вошел, первый вышел
   LIFO - Last In First Out - последний вошел, первый вышел

2. Каким образом, и какой объем памяти выделяется под хранение очереди при различной ее реализации?

    Массив: сразу происходит выделение под максимальный размер очереди.
    Список: динамически происходит выделение и освобождение памяти по мере необходимости добавления и удаления элемента соответственно.

3. Каким образом освобождается память при удалении элемента из очереди при ее различной реализации?

   Массив: происходит сдвиг всех элементов очереди влево, указатель Pin сдвигается на одну позицию влево.
   Список: Освобождается память из под элемента списка, указатель Pout перемещается на следующий элемент очереди.

4. Что происходит с элементами очереди при ее просмотре?

    Удаление элементов из очереди, от первого вошедшего к последнему.

5. От чего зависит эффективность физической реализации очереди?

   Эффективнее использовать очередь в виде массива, в частности статического, так как доступ к элементам массива происходит быстрее. Это происходит за счёт того, что для статического массива память выделяется на стеке, а для списка на куче. Доступ к теку происходит быстрее, чем к куче.

6. Каковы достоинства и недостатки различных реализаций очереди в зависимости от выполняемых над ней операций?

   Массив: Ограничение по памяти, память выделена под максимальный размер очереди.
   Список: Размер ограничен выделенным программе объемом памяти, время создания и удаления элемента медленнее.

7. Что такое фрагментация памяти, и в какой части ОП она возникает?

   Фрагментация памяти - разбиение памяти на небольшие, несвязанные блоки. Возникают в куче.

8. Для чего нужен алгоритм «близнецов».

   Для выделения памяти по запросу для случая, когда различгын размеры блоков являются степенью 2.

9.  Какие дисциплины выделения памяти вы знаете?
    
    Best Fit - Самый подходящий.
    Выделяется тот свободный участок, размер которого равен запрошенному или превышает его минимальную величину.
    First Fit - Первый подходящий.
    Выделяется первый же найденный свободный участок, размер которого не меньше запрошенного.

10. На что необходимо обратить внимание при тестировании программы?
    
    Необходимо контроллировать удаление из пустой очереди и добавление в полную, а так же правильность освобождения памяти.

11. Каким образом физически выделяется и освобождается память при
динамических запросах?

    При выделении памяти резервируется (дабы исключить выделение памяти, затрагивающее этот блок) место в куче и возвращается указатель на зарезервированный участок.
    При освобождении памяти освобождаемый блок возвращается в список свободный областей памяти.