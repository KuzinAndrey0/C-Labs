Для анализа времени поиска программа поиск случайного значения в деревьях разного размера и разным уровнем ветвленности по 1000 раз, с шагом размера 5000 и шаном ветвленности 0.25.

| SIZE   | BRANCHING | TIME    |
| :----- | :-------- | :------ |
| 100000 | 0.00      | 646 ms  |
| 100000 | 0.25      | 530 ms  |
| 100000 | 0.50      | 511 ms  |
| 100000 | 0.75      | 496 ms  |
| 100000 | 1.00      | 465 ms  |
| 150000 | 0.00      | 1231 ms |
| 150000 | 0.25      | 1162 ms |
| 150000 | 0.50      | 1105 ms |
| 150000 | 0.75      | 1005 ms |
| 150000 | 1.00      | 916 ms  |
| 200000 | 0.00      | 1965 ms |
| 200000 | 0.25      | 1846 ms |
| 200000 | 0.50      | 1707 ms |
| 200000 | 0.75      | 1412 ms |
| 200000 | 1.00      | 1307 ms |
| 250000 | 0.00      | 2987 ms |
| 250000 | 0.25      | 2535 ms |
| 250000 | 0.50      | 2497 ms |
| 250000 | 0.75      | 2512 ms |
| 250000 | 1.00      | 2243 ms |
| 300000 | 0.00      | 4045 ms |
| 300000 | 0.25      | 3646 ms |
| 300000 | 0.50      | 3462 ms |
| 300000 | 0.75      | 2852 ms |
| 300000 | 1.00      | 2731 ms |

По результатам измерений видно, что чем больше ветвленность дерева одинакого размера, тем быстрее в нём происходит поиск.