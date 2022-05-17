# Task 6 - qr-codes: detecting finder pattern
Идея моего алгоритма
Мы знаем, что finder pattern - фигура(квадрат), отношение заолненных сторон которой - 1:1:3:1:1 
Я предлагаю искать такие последовательности белых и черных точек на картике.

Сам алгоритм:
- картинку делаем серой
- нормируем по минимуму и максмуму
- медиан фильтр
- билетерал фильтр
- Поиск в каждой строке/столбце изображаения однотонных последовательностей и проверка, что она подходит к паттерну 1:1:3:1:1 
- Немного похачить, чтобы избавиться от большинства неподходящих вариантов
- Non-maximum suppression
- Рисовка боксов


Precision/Recall
- TestSet1:
- TestSet2:
- TestSet3:
Метрика считалась вручную [таблица](https://docs.google.com/spreadsheets/d/1SR2zrWLiCzkhu38AXZg_lx9AveeMQtKu2nGNusNeePQ/edit?usp=sharing)




Ссылка на обработанные данные на [GoogleDisk](https://vk.com/away.php?utf=1&to=https%3A%2F%2Fdrive.google.com%2Fdrive%2Ffolders%2F155InSjaBxX-4U1ae8jdy5_Jj5dGQOAZV%3Fusp%3Dsharing)

